======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("bowed")
	AddHorizontalSlider("bend", fHslider3, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("freq", fHslider2, 400.0f, 50.0f, 2000.0f, 0.00999999978f)
	AddHorizontalSlider("keyboard", fHslider1, 0.0f, 0.0f, 5.0f, 1.0f)
	AddHorizontalSlider("x", fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddHorizontalSlider("y", fHslider4, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, float, fRec26[2])
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
	StoreVarInst(struct, fConst1, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(10.0f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst2, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(400.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l1)], Float(0.0f))
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
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 11
Store = 0
Binop = 7
Numbers = 6
Declare = 10
Cast = 6
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "int", iSlow1, CastInst("int", CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "int", iSlow2, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(3)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider2)), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider4))))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(2)))
	DeclareVarInst(stack, "int", iSlow6, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(0)))
	DeclareVarInst(stack, "int", iSlow7, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(1)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 211
Store = 67
Binop = 129
Numbers = 99
Declare = 33
Cast = 10
Select = 0
Loop = 1
Funcall = 22

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec2[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, FunCallInst("fabsf", FunCallInst("fabsf", BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec2[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp1, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(stack, fTemp0)) LoadVarInst(struct, fConst2) LoadVarInst(struct, fConst1)))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(stack, fTemp0), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp1)))))
		StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(0)], Select2Inst(LoadVarInst(stack, iSlow2) LoadVarInst(stack, fSlow3) LoadVarInst(struct, fRec6[Int32(1)])))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fRec6[Int32(0)]))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec9[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("+", BinopInst("*", Float(0.300000012f), LoadVarInst(struct, fRec9[Int32(0)])), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("*", LoadVarInst(struct, fRec5[Int32(0)]), LoadVarInst(stack, fTemp2))))
		DeclareVarInst(stack, "float", fTemp4, FunCallInst("sinf", LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fTemp5, FunCallInst("cosf", LoadVarInst(stack, fTemp3)))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(stack, fTemp4)), BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(stack, fTemp5))))
		DeclareVarInst(stack, "int", iTemp6, BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(stack, fTemp5)), BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp4)))), CastInst("float", LoadVarInst(stack, iTemp6))))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec12[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp7, FunCallInst("fabsf", FunCallInst("fabsf", BinopInst("-", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fRec12[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp8, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(stack, fTemp7)) LoadVarInst(struct, fConst2) LoadVarInst(struct, fConst1)))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(stack, fTemp8)), BinopInst("*", LoadVarInst(stack, fTemp7), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp8)))))
		StoreVarInst(struct, fRec10[Int32(0)], LoadVarInst(struct, fRec11[Int32(0)]))
		DeclareVarInst(stack, "float", fTemp9, FunCallInst("min_f", Float(1.0f), BinopInst("*", Float(8000.0f), LoadVarInst(struct, fRec10[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", LoadVarInst(struct, fRec5[Int32(0)]), BinopInst("*", Float(1000.0f), BinopInst("*", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(stack, fTemp9))))))
		DeclareVarInst(stack, "float", fTemp11, FunCallInst("sinf", LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp12, FunCallInst("cosf", LoadVarInst(stack, fTemp10)))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp11)), BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(stack, fTemp12))))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp12)), BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))), CastInst("float", LoadVarInst(stack, iTemp6))))
		StoreVarInst(struct, fRec16[Int32(0)], Select2Inst(LoadVarInst(stack, iSlow5) LoadVarInst(stack, fSlow3) LoadVarInst(struct, fRec16[Int32(1)])))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fRec16[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("*", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fTemp2))))
		DeclareVarInst(stack, "float", fTemp14, FunCallInst("sinf", LoadVarInst(stack, fTemp13)))
		DeclareVarInst(stack, "float", fTemp15, FunCallInst("cosf", LoadVarInst(stack, fTemp13)))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec18[Int32(1)]), LoadVarInst(stack, fTemp14)), BinopInst("*", LoadVarInst(struct, fRec17[Int32(1)]), LoadVarInst(stack, fTemp15))))
		StoreVarInst(struct, fRec18[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec18[Int32(1)]), LoadVarInst(stack, fTemp15)), BinopInst("*", LoadVarInst(struct, fRec17[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp14)))), CastInst("float", LoadVarInst(stack, iTemp6))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", LoadVarInst(struct, fRec15[Int32(0)]), BinopInst("*", Float(1000.0f), BinopInst("*", LoadVarInst(struct, fRec17[Int32(0)]), LoadVarInst(stack, fTemp9))))))
		DeclareVarInst(stack, "float", fTemp17, FunCallInst("sinf", LoadVarInst(stack, fTemp16)))
		DeclareVarInst(stack, "float", fTemp18, FunCallInst("cosf", LoadVarInst(stack, fTemp16)))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(stack, fTemp17)), BinopInst("*", LoadVarInst(struct, fRec13[Int32(1)]), LoadVarInst(stack, fTemp18))))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(stack, fTemp18)), BinopInst("*", LoadVarInst(struct, fRec13[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp17)))), CastInst("float", LoadVarInst(stack, iTemp6))))
		StoreVarInst(struct, fRec22[Int32(0)], Select2Inst(LoadVarInst(stack, iSlow6) LoadVarInst(stack, fSlow3) LoadVarInst(struct, fRec22[Int32(1)])))
		StoreVarInst(struct, fRec21[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fRec22[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("*", LoadVarInst(struct, fRec21[Int32(0)]), LoadVarInst(stack, fTemp2))))
		DeclareVarInst(stack, "float", fTemp20, FunCallInst("sinf", LoadVarInst(stack, fTemp19)))
		DeclareVarInst(stack, "float", fTemp21, FunCallInst("cosf", LoadVarInst(stack, fTemp19)))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec24[Int32(1)]), LoadVarInst(stack, fTemp20)), BinopInst("*", LoadVarInst(struct, fRec23[Int32(1)]), LoadVarInst(stack, fTemp21))))
		StoreVarInst(struct, fRec24[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec24[Int32(1)]), LoadVarInst(stack, fTemp21)), BinopInst("*", LoadVarInst(struct, fRec23[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp20)))), CastInst("float", LoadVarInst(stack, iTemp6))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", LoadVarInst(struct, fRec21[Int32(0)]), BinopInst("*", Float(1000.0f), BinopInst("*", LoadVarInst(struct, fRec23[Int32(0)]), LoadVarInst(stack, fTemp9))))))
		DeclareVarInst(stack, "float", fTemp23, FunCallInst("sinf", LoadVarInst(stack, fTemp22)))
		DeclareVarInst(stack, "float", fTemp24, FunCallInst("cosf", LoadVarInst(stack, fTemp22)))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec20[Int32(1)]), LoadVarInst(stack, fTemp23)), BinopInst("*", LoadVarInst(struct, fRec19[Int32(1)]), LoadVarInst(stack, fTemp24))))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec20[Int32(1)]), LoadVarInst(stack, fTemp24)), BinopInst("*", LoadVarInst(struct, fRec19[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp23)))), CastInst("float", LoadVarInst(stack, iTemp6))))
		StoreVarInst(struct, fRec28[Int32(0)], Select2Inst(LoadVarInst(stack, iSlow7) LoadVarInst(stack, fSlow3) LoadVarInst(struct, fRec28[Int32(1)])))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fRec28[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("*", LoadVarInst(struct, fRec27[Int32(0)]), LoadVarInst(stack, fTemp2))))
		DeclareVarInst(stack, "float", fTemp26, FunCallInst("sinf", LoadVarInst(stack, fTemp25)))
		DeclareVarInst(stack, "float", fTemp27, FunCallInst("cosf", LoadVarInst(stack, fTemp25)))
		StoreVarInst(struct, fRec29[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec30[Int32(1)]), LoadVarInst(stack, fTemp26)), BinopInst("*", LoadVarInst(struct, fRec29[Int32(1)]), LoadVarInst(stack, fTemp27))))
		StoreVarInst(struct, fRec30[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec30[Int32(1)]), LoadVarInst(stack, fTemp27)), BinopInst("*", LoadVarInst(struct, fRec29[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp26)))), CastInst("float", LoadVarInst(stack, iTemp6))))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", LoadVarInst(struct, fRec27[Int32(0)]), BinopInst("*", Float(1000.0f), BinopInst("*", LoadVarInst(struct, fRec29[Int32(0)]), LoadVarInst(stack, fTemp9))))))
		DeclareVarInst(stack, "float", fTemp29, FunCallInst("sinf", LoadVarInst(stack, fTemp28)))
		DeclareVarInst(stack, "float", fTemp30, FunCallInst("cosf", LoadVarInst(stack, fTemp28)))
		StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec26[Int32(1)]), LoadVarInst(stack, fTemp29)), BinopInst("*", LoadVarInst(struct, fRec25[Int32(1)]), LoadVarInst(stack, fTemp30))))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec26[Int32(1)]), LoadVarInst(stack, fTemp30)), BinopInst("*", LoadVarInst(struct, fRec25[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp29)))), CastInst("float", LoadVarInst(stack, iTemp6))))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("*", FunCallInst("min_f", Float(1.0f), BinopInst("*", Float(8000.0f), LoadVarInst(struct, fRec0[Int32(0)]))), BinopInst("+", LoadVarInst(struct, fRec3[Int32(0)]), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), BinopInst("+", LoadVarInst(struct, fRec19[Int32(0)]), LoadVarInst(struct, fRec25[Int32(0)]))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp31)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp31)))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
		StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, float, fRec26[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(10.0f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst2, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(400.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l1)], Float(0.0f))
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
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "int", iSlow1, CastInst("int", CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "int", iSlow2, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(3)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider2)), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider4))))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(2)))
	DeclareVarInst(stack, "int", iSlow6, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(0)))
	DeclareVarInst(stack, "int", iSlow7, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(1)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec2[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, FunCallInst("fabsf", FunCallInst("fabsf", BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec2[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp1, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(stack, fTemp0)) LoadVarInst(struct, fConst2) LoadVarInst(struct, fConst1)))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(stack, fTemp0), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp1)))))
			StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(0)], Select2Inst(LoadVarInst(stack, iSlow2) LoadVarInst(stack, fSlow3) LoadVarInst(struct, fRec6[Int32(1)])))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fRec6[Int32(0)]))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec9[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("+", BinopInst("*", Float(0.300000012f), LoadVarInst(struct, fRec9[Int32(0)])), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("*", LoadVarInst(struct, fRec5[Int32(0)]), LoadVarInst(stack, fTemp2))))
			DeclareVarInst(stack, "float", fTemp4, FunCallInst("sinf", LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fTemp5, FunCallInst("cosf", LoadVarInst(stack, fTemp3)))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(stack, fTemp4)), BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(stack, fTemp5))))
			DeclareVarInst(stack, "int", iTemp6, BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(stack, fTemp5)), BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp4)))), CastInst("float", LoadVarInst(stack, iTemp6))))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec12[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp7, FunCallInst("fabsf", FunCallInst("fabsf", BinopInst("-", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fRec12[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp8, Select2Inst(BinopInst(">", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(stack, fTemp7)) LoadVarInst(struct, fConst2) LoadVarInst(struct, fConst1)))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(stack, fTemp8)), BinopInst("*", LoadVarInst(stack, fTemp7), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp8)))))
			StoreVarInst(struct, fRec10[Int32(0)], LoadVarInst(struct, fRec11[Int32(0)]))
			DeclareVarInst(stack, "float", fTemp9, FunCallInst("min_f", Float(1.0f), BinopInst("*", Float(8000.0f), LoadVarInst(struct, fRec10[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", LoadVarInst(struct, fRec5[Int32(0)]), BinopInst("*", Float(1000.0f), BinopInst("*", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(stack, fTemp9))))))
			DeclareVarInst(stack, "float", fTemp11, FunCallInst("sinf", LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp12, FunCallInst("cosf", LoadVarInst(stack, fTemp10)))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp11)), BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(stack, fTemp12))))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp12)), BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))), CastInst("float", LoadVarInst(stack, iTemp6))))
			StoreVarInst(struct, fRec16[Int32(0)], Select2Inst(LoadVarInst(stack, iSlow5) LoadVarInst(stack, fSlow3) LoadVarInst(struct, fRec16[Int32(1)])))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fRec16[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("*", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fTemp2))))
			DeclareVarInst(stack, "float", fTemp14, FunCallInst("sinf", LoadVarInst(stack, fTemp13)))
			DeclareVarInst(stack, "float", fTemp15, FunCallInst("cosf", LoadVarInst(stack, fTemp13)))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec18[Int32(1)]), LoadVarInst(stack, fTemp14)), BinopInst("*", LoadVarInst(struct, fRec17[Int32(1)]), LoadVarInst(stack, fTemp15))))
			StoreVarInst(struct, fRec18[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec18[Int32(1)]), LoadVarInst(stack, fTemp15)), BinopInst("*", LoadVarInst(struct, fRec17[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp14)))), CastInst("float", LoadVarInst(stack, iTemp6))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", LoadVarInst(struct, fRec15[Int32(0)]), BinopInst("*", Float(1000.0f), BinopInst("*", LoadVarInst(struct, fRec17[Int32(0)]), LoadVarInst(stack, fTemp9))))))
			DeclareVarInst(stack, "float", fTemp17, FunCallInst("sinf", LoadVarInst(stack, fTemp16)))
			DeclareVarInst(stack, "float", fTemp18, FunCallInst("cosf", LoadVarInst(stack, fTemp16)))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(stack, fTemp17)), BinopInst("*", LoadVarInst(struct, fRec13[Int32(1)]), LoadVarInst(stack, fTemp18))))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(stack, fTemp18)), BinopInst("*", LoadVarInst(struct, fRec13[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp17)))), CastInst("float", LoadVarInst(stack, iTemp6))))
			StoreVarInst(struct, fRec22[Int32(0)], Select2Inst(LoadVarInst(stack, iSlow6) LoadVarInst(stack, fSlow3) LoadVarInst(struct, fRec22[Int32(1)])))
			StoreVarInst(struct, fRec21[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fRec22[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("*", LoadVarInst(struct, fRec21[Int32(0)]), LoadVarInst(stack, fTemp2))))
			DeclareVarInst(stack, "float", fTemp20, FunCallInst("sinf", LoadVarInst(stack, fTemp19)))
			DeclareVarInst(stack, "float", fTemp21, FunCallInst("cosf", LoadVarInst(stack, fTemp19)))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec24[Int32(1)]), LoadVarInst(stack, fTemp20)), BinopInst("*", LoadVarInst(struct, fRec23[Int32(1)]), LoadVarInst(stack, fTemp21))))
			StoreVarInst(struct, fRec24[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec24[Int32(1)]), LoadVarInst(stack, fTemp21)), BinopInst("*", LoadVarInst(struct, fRec23[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp20)))), CastInst("float", LoadVarInst(stack, iTemp6))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", LoadVarInst(struct, fRec21[Int32(0)]), BinopInst("*", Float(1000.0f), BinopInst("*", LoadVarInst(struct, fRec23[Int32(0)]), LoadVarInst(stack, fTemp9))))))
			DeclareVarInst(stack, "float", fTemp23, FunCallInst("sinf", LoadVarInst(stack, fTemp22)))
			DeclareVarInst(stack, "float", fTemp24, FunCallInst("cosf", LoadVarInst(stack, fTemp22)))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec20[Int32(1)]), LoadVarInst(stack, fTemp23)), BinopInst("*", LoadVarInst(struct, fRec19[Int32(1)]), LoadVarInst(stack, fTemp24))))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec20[Int32(1)]), LoadVarInst(stack, fTemp24)), BinopInst("*", LoadVarInst(struct, fRec19[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp23)))), CastInst("float", LoadVarInst(stack, iTemp6))))
			StoreVarInst(struct, fRec28[Int32(0)], Select2Inst(LoadVarInst(stack, iSlow7) LoadVarInst(stack, fSlow3) LoadVarInst(struct, fRec28[Int32(1)])))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fRec28[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("*", LoadVarInst(struct, fRec27[Int32(0)]), LoadVarInst(stack, fTemp2))))
			DeclareVarInst(stack, "float", fTemp26, FunCallInst("sinf", LoadVarInst(stack, fTemp25)))
			DeclareVarInst(stack, "float", fTemp27, FunCallInst("cosf", LoadVarInst(stack, fTemp25)))
			StoreVarInst(struct, fRec29[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec30[Int32(1)]), LoadVarInst(stack, fTemp26)), BinopInst("*", LoadVarInst(struct, fRec29[Int32(1)]), LoadVarInst(stack, fTemp27))))
			StoreVarInst(struct, fRec30[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec30[Int32(1)]), LoadVarInst(stack, fTemp27)), BinopInst("*", LoadVarInst(struct, fRec29[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp26)))), CastInst("float", LoadVarInst(stack, iTemp6))))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", LoadVarInst(struct, fRec27[Int32(0)]), BinopInst("*", Float(1000.0f), BinopInst("*", LoadVarInst(struct, fRec29[Int32(0)]), LoadVarInst(stack, fTemp9))))))
			DeclareVarInst(stack, "float", fTemp29, FunCallInst("sinf", LoadVarInst(stack, fTemp28)))
			DeclareVarInst(stack, "float", fTemp30, FunCallInst("cosf", LoadVarInst(stack, fTemp28)))
			StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec26[Int32(1)]), LoadVarInst(stack, fTemp29)), BinopInst("*", LoadVarInst(struct, fRec25[Int32(1)]), LoadVarInst(stack, fTemp30))))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec26[Int32(1)]), LoadVarInst(stack, fTemp30)), BinopInst("*", LoadVarInst(struct, fRec25[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp29)))), CastInst("float", LoadVarInst(stack, iTemp6))))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("*", FunCallInst("min_f", Float(1.0f), BinopInst("*", Float(8000.0f), LoadVarInst(struct, fRec0[Int32(0)]))), BinopInst("+", LoadVarInst(struct, fRec3[Int32(0)]), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), BinopInst("+", LoadVarInst(struct, fRec19[Int32(0)]), LoadVarInst(struct, fRec25[Int32(0)]))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp31)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp31)))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
			StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 284 bytes
Heap size = 296 bytes
Stack size in compute = 48 bytes

