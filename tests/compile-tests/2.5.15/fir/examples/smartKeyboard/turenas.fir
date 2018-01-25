======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("turenas")
	AddHorizontalSlider("freq", fHslider0, 400.0f, 50.0f, 2000.0f, 0.00999999978f)
	AddButtonInst("gate"fButton0)
	AddMetaDeclareInst(fHslider2, "acc", "0 0 -10 0 10")
	AddHorizontalSlider("res", fHslider2, 2.5f, 0.00999999978f, 5.0f, 0.00999999978f)
	AddHorizontalSlider("y", fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f)
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
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fVec5[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fVec7[2])
	DeclareVarInst(struct, float, fRec18[2])
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(400.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(2.5f)))
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
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
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
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 41
Store = 0
Binop = 31
Numbers = 19
Declare = 29
Cast = 4
Select = 0
Loop = 0
Funcall = 12

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(0.833333313f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("sinf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("cosf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(1.66666663f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow9, FunCallInst("sinf", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("cosf", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(2.5f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow13, FunCallInst("sinf", LoadVarInst(stack, fSlow12)))
	DeclareVarInst(stack, "float", fSlow14, FunCallInst("cosf", LoadVarInst(stack, fSlow12)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(3.33333325f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow17, FunCallInst("sinf", LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow18, FunCallInst("cosf", LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(4.16666651f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow21, FunCallInst("sinf", LoadVarInst(stack, fSlow20)))
	DeclareVarInst(stack, "float", fSlow22, FunCallInst("cosf", LoadVarInst(stack, fSlow20)))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(5.0f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow25, FunCallInst("sinf", LoadVarInst(stack, fSlow24)))
	DeclareVarInst(stack, "float", fSlow26, FunCallInst("cosf", LoadVarInst(stack, fSlow24)))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow25)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 235
Store = 56
Binop = 174
Numbers = 138
Declare = 21
Cast = 7
Select = 0
Loop = 1
Funcall = 6

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec0[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec0[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow6))
		DeclareVarInst(stack, "int", iTemp1, BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fVec1[Int32(1)])), Float(0.0f)), Int32(0)))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec3[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(struct, fRec3[Int32(0)]), Float(0.00100000005f)))
		StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp2))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp2)))
		StoreVarInst(struct, fRec2[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp3), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec2[Int32(1)]), LoadVarInst(stack, fTemp2))))))))
		DeclareVarInst(stack, "int", iTemp4, BinopInst("<", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fConst2)))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec4[Int32(1)]))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec4[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", BinopInst("*", Float(0.866666675f), LoadVarInst(struct, fRec3[Int32(0)])), Float(0.00100000005f)))
		StoreVarInst(struct, fVec3[Int32(0)], LoadVarInst(stack, fTemp5))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp5)))
		StoreVarInst(struct, fRec6[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp6), BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec3[Int32(1)]), LoadVarInst(stack, fTemp5))))))))
		DeclareVarInst(stack, "int", iTemp7, BinopInst("<", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(struct, fConst2)))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec7[Int32(1)]))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec7[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("+", BinopInst("*", Float(0.733333349f), LoadVarInst(struct, fRec3[Int32(0)])), Float(0.00100000005f)))
		StoreVarInst(struct, fVec4[Int32(0)], LoadVarInst(stack, fTemp8))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp8)))
		StoreVarInst(struct, fRec9[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp9), BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec4[Int32(1)]), LoadVarInst(stack, fTemp8))))))))
		DeclareVarInst(stack, "int", iTemp10, BinopInst("<", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(struct, fConst2)))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow17), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec10[Int32(1)]))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), LoadVarInst(struct, fRec10[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec3[Int32(0)])), Float(0.00100000005f)))
		StoreVarInst(struct, fVec5[Int32(0)], LoadVarInst(stack, fTemp11))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp11)))
		StoreVarInst(struct, fRec12[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp12), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec5[Int32(1)]), LoadVarInst(stack, fTemp11))))))))
		DeclareVarInst(stack, "int", iTemp13, BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fConst2)))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow21), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(struct, fRec13[Int32(1)]))))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow23), LoadVarInst(struct, fRec13[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("+", BinopInst("*", Float(0.466666669f), LoadVarInst(struct, fRec3[Int32(0)])), Float(0.00100000005f)))
		StoreVarInst(struct, fVec6[Int32(0)], LoadVarInst(stack, fTemp14))
		DeclareVarInst(stack, "float", fTemp15, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp14)))
		StoreVarInst(struct, fRec15[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp15), BinopInst("+", LoadVarInst(struct, fRec15[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec6[Int32(1)]), LoadVarInst(stack, fTemp14))))))))
		DeclareVarInst(stack, "int", iTemp16, BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(struct, fConst2)))
		StoreVarInst(struct, fRec16[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(struct, fRec16[Int32(1)]))))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow27), LoadVarInst(struct, fRec16[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("+", BinopInst("*", Float(0.333333343f), LoadVarInst(struct, fRec3[Int32(0)])), Float(0.00100000005f)))
		StoreVarInst(struct, fVec7[Int32(0)], LoadVarInst(stack, fTemp17))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp17)))
		StoreVarInst(struct, fRec18[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp18), BinopInst("+", LoadVarInst(struct, fRec18[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec7[Int32(1)]), LoadVarInst(stack, fTemp17))))))))
		DeclareVarInst(stack, "int", iTemp19, BinopInst("<", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(struct, fConst2)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.0500000007f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.444444448f), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), Select2Inst(LoadVarInst(stack, iTemp4) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec2[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp4) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec2[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(stack, fTemp3)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp2), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))), BinopInst("*", LoadVarInst(struct, fRec4[Int32(0)]), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.111111112f), Select2Inst(LoadVarInst(stack, iTemp7) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec6[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp7) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec6[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(stack, fTemp6)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp5), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))))), BinopInst("*", LoadVarInst(struct, fRec7[Int32(0)]), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.666666687f), Select2Inst(LoadVarInst(stack, iTemp10) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec9[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp10) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec9[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(stack, fTemp9)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp8), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))))), BinopInst("*", LoadVarInst(struct, fRec10[Int32(0)]), BinopInst("-", Float(0.0f), BinopInst("*", Float(1.22222221f), Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec12[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(stack, fTemp12)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp11), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))))), BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), BinopInst("-", Float(0.0f), BinopInst("*", Float(1.77777779f), Select2Inst(LoadVarInst(stack, iTemp16) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp16) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec15[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fTemp15)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp14), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))))), BinopInst("*", LoadVarInst(struct, fRec16[Int32(0)]), BinopInst("-", Float(0.0f), BinopInst("*", Float(2.33333325f), Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec18[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec18[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(stack, fTemp18)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp17), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))))))))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fVec5[Int32(1)], LoadVarInst(struct, fVec5[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fVec7[Int32(1)], LoadVarInst(struct, fVec7[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fVec5[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fVec7[2])
	DeclareVarInst(struct, float, fRec18[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(400.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(2.5f)))
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
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
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
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(0.833333313f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("sinf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("cosf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(1.66666663f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow9, FunCallInst("sinf", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("cosf", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(2.5f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow13, FunCallInst("sinf", LoadVarInst(stack, fSlow12)))
	DeclareVarInst(stack, "float", fSlow14, FunCallInst("cosf", LoadVarInst(stack, fSlow12)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(3.33333325f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow17, FunCallInst("sinf", LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow18, FunCallInst("cosf", LoadVarInst(stack, fSlow16)))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(4.16666651f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow21, FunCallInst("sinf", LoadVarInst(stack, fSlow20)))
	DeclareVarInst(stack, "float", fSlow22, FunCallInst("cosf", LoadVarInst(stack, fSlow20)))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("*", Float(5.0f), LoadVarInst(stack, fSlow1)), Float(1.0f)))))
	DeclareVarInst(stack, "float", fSlow25, FunCallInst("sinf", LoadVarInst(stack, fSlow24)))
	DeclareVarInst(stack, "float", fSlow26, FunCallInst("cosf", LoadVarInst(stack, fSlow24)))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow25)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec0[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec0[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow6))
			DeclareVarInst(stack, "int", iTemp1, BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fVec1[Int32(1)])), Float(0.0f)), Int32(0)))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec3[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(struct, fRec3[Int32(0)]), Float(0.00100000005f)))
			StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp2))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp2)))
			StoreVarInst(struct, fRec2[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp3), BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec2[Int32(1)]), LoadVarInst(stack, fTemp2))))))))
			DeclareVarInst(stack, "int", iTemp4, BinopInst("<", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fConst2)))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec4[Int32(1)]))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec4[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", BinopInst("*", Float(0.866666675f), LoadVarInst(struct, fRec3[Int32(0)])), Float(0.00100000005f)))
			StoreVarInst(struct, fVec3[Int32(0)], LoadVarInst(stack, fTemp5))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp5)))
			StoreVarInst(struct, fRec6[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp6), BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec3[Int32(1)]), LoadVarInst(stack, fTemp5))))))))
			DeclareVarInst(stack, "int", iTemp7, BinopInst("<", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(struct, fConst2)))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec7[Int32(1)]))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec7[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("+", BinopInst("*", Float(0.733333349f), LoadVarInst(struct, fRec3[Int32(0)])), Float(0.00100000005f)))
			StoreVarInst(struct, fVec4[Int32(0)], LoadVarInst(stack, fTemp8))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp8)))
			StoreVarInst(struct, fRec9[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp9), BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec4[Int32(1)]), LoadVarInst(stack, fTemp8))))))))
			DeclareVarInst(stack, "int", iTemp10, BinopInst("<", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(struct, fConst2)))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow17), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec10[Int32(1)]))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow19), LoadVarInst(struct, fRec10[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec3[Int32(0)])), Float(0.00100000005f)))
			StoreVarInst(struct, fVec5[Int32(0)], LoadVarInst(stack, fTemp11))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp11)))
			StoreVarInst(struct, fRec12[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp12), BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec5[Int32(1)]), LoadVarInst(stack, fTemp11))))))))
			DeclareVarInst(stack, "int", iTemp13, BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fConst2)))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow21), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(struct, fRec13[Int32(1)]))))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow23), LoadVarInst(struct, fRec13[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("+", BinopInst("*", Float(0.466666669f), LoadVarInst(struct, fRec3[Int32(0)])), Float(0.00100000005f)))
			StoreVarInst(struct, fVec6[Int32(0)], LoadVarInst(stack, fTemp14))
			DeclareVarInst(stack, "float", fTemp15, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp14)))
			StoreVarInst(struct, fRec15[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp15), BinopInst("+", LoadVarInst(struct, fRec15[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec6[Int32(1)]), LoadVarInst(stack, fTemp14))))))))
			DeclareVarInst(stack, "int", iTemp16, BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(struct, fConst2)))
			StoreVarInst(struct, fRec16[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(struct, fRec16[Int32(1)]))))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow27), LoadVarInst(struct, fRec16[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp0))))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("+", BinopInst("*", Float(0.333333343f), LoadVarInst(struct, fRec3[Int32(0)])), Float(0.00100000005f)))
			StoreVarInst(struct, fVec7[Int32(0)], LoadVarInst(stack, fTemp17))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp17)))
			StoreVarInst(struct, fRec18[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp1) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp18), BinopInst("+", LoadVarInst(struct, fRec18[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("-", LoadVarInst(struct, fVec7[Int32(1)]), LoadVarInst(stack, fTemp17))))))))
			DeclareVarInst(stack, "int", iTemp19, BinopInst("<", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(struct, fConst2)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.0500000007f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.444444448f), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), Select2Inst(LoadVarInst(stack, iTemp4) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec2[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp4) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec2[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(stack, fTemp3)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp2), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))), BinopInst("*", LoadVarInst(struct, fRec4[Int32(0)]), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.111111112f), Select2Inst(LoadVarInst(stack, iTemp7) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec6[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp7) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec6[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(stack, fTemp6)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp5), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))))), BinopInst("*", LoadVarInst(struct, fRec7[Int32(0)]), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.666666687f), Select2Inst(LoadVarInst(stack, iTemp10) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec9[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp10) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec9[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(stack, fTemp9)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp8), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))))), BinopInst("*", LoadVarInst(struct, fRec10[Int32(0)]), BinopInst("-", Float(0.0f), BinopInst("*", Float(1.22222221f), Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec12[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(stack, fTemp12)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp11), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))))), BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), BinopInst("-", Float(0.0f), BinopInst("*", Float(1.77777779f), Select2Inst(LoadVarInst(stack, iTemp16) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp16) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec15[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fTemp15)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp14), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))))), BinopInst("*", LoadVarInst(struct, fRec16[Int32(0)]), BinopInst("-", Float(0.0f), BinopInst("*", Float(2.33333325f), Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec18[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec18[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(stack, fTemp18)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(struct, fConst2))), BinopInst("+", LoadVarInst(stack, fTemp17), Float(-0.00100000005f)))), Float(1.0f)) Float(0.0f))))))))))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fVec5[Int32(1)], LoadVarInst(struct, fVec5[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fVec7[Int32(1)], LoadVarInst(struct, fVec7[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 244 bytes
Heap size = 256 bytes
Stack size in compute = 120 bytes

