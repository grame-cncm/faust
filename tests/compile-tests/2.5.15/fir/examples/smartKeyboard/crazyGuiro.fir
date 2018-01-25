======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("crazyGuiro")
	AddButtonInst("gate"fButton0)
	AddHorizontalSlider("key", fHslider2, 0.0f, 0.0f, 2.0f, 1.0f)
	AddHorizontalSlider("keyboard", fHslider3, 0.0f, 0.0f, 2.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "acc", "1 0 -10 0 10")
	AddHorizontalSlider("res", fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider1, "acc", "0 0 -10 0 10")
	AddHorizontalSlider("wet", fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, int, iRec11[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, float, fRec10[3])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec2[8192])
	DeclareVarInst(struct, "int", iConst5)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fVec3[8192])
	DeclareVarInst(struct, "int", iConst6)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fVec4[8192])
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fVec5[8192])
	DeclareVarInst(struct, "int", iConst8)
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fVec6[8192])
	DeclareVarInst(struct, "int", iConst9)
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fVec7[8192])
	DeclareVarInst(struct, "int", iConst10)
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fVec8[8192])
	DeclareVarInst(struct, "int", iConst11)
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fVec9[8192])
	DeclareVarInst(struct, "int", iConst12)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, float, fVec10[2048])
	DeclareVarInst(struct, "int", iConst13)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fVec11[2048])
	DeclareVarInst(struct, "int", iConst14)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fVec12[2048])
	DeclareVarInst(struct, "int", iConst15)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fVec13[1024])
	DeclareVarInst(struct, "int", iConst16)
	DeclareVarInst(struct, float, fRec0[2])
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1382.30078f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00200000009f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, iConst5, CastInst("int", BinopInst("*", Float(0.0253061224f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst6, CastInst("int", BinopInst("*", Float(0.0269387756f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst7, CastInst("int", BinopInst("*", Float(0.0289569162f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst8, CastInst("int", BinopInst("*", Float(0.0307482984f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst9, CastInst("int", BinopInst("*", Float(0.0322448984f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst10, CastInst("int", BinopInst("*", Float(0.033809524f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst11, CastInst("int", BinopInst("*", Float(0.0353061222f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst12, CastInst("int", BinopInst("*", Float(0.0366666652f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst13, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", CastInst("int", BinopInst("*", Float(0.0126077095f), LoadVarInst(struct, fConst0))), Int32(-1)))))
	StoreVarInst(struct, iConst14, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", CastInst("int", BinopInst("*", Float(0.00999999978f), LoadVarInst(struct, fConst0))), Int32(-1)))))
	StoreVarInst(struct, iConst15, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", CastInst("int", BinopInst("*", Float(0.00773242628f), LoadVarInst(struct, fConst0))), Int32(-1)))))
	StoreVarInst(struct, iConst16, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", CastInst("int", BinopInst("*", Float(0.00510204071f), LoadVarInst(struct, fConst0))), Int32(-1)))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l0)], Float(0.0f))
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
			StoreVarInst(struct, iRec11[LoadVarInst(loop, l2)], Int32(0))
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
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(3))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(8192))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(8192))
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
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(8192))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(8192))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l15)], Float(0.0f))
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
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(8192))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l19)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l21), Int32(8192))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l22)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l24), Int32(8192))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(8192))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2048))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2048))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2048))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(1024))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 20
Store = 0
Binop = 20
Numbers = 15
Declare = 14
Cast = 5
Select = 0
Loop = 0
Funcall = 3

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(struct, fHslider2)), BinopInst("*", Float(8.0f), CastInst("float", LoadVarInst(struct, fHslider3)))), Float(-19.0f)))))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow3), Float(0.125f)), LoadVarInst(stack, fSlow2)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow3), Float(-0.125f)), LoadVarInst(stack, fSlow2)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow2))))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)), LoadVarInst(stack, fSlow4)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 161
Store = 67
Binop = 104
Numbers = 100
Declare = 13
Cast = 3
Select = 0
Loop = 1
Funcall = 1

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(struct, fRec8[Int32(1)]))))
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(struct, fConst0))
		StoreVarInst(struct, iRec11[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec11[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow6))
		StoreVarInst(struct, fRec12[Int32(0)], Select2Inst(BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fVec1[Int32(1)])), Float(0.0f)), Int32(0)) Float(0.0f) FunCallInst("min_f", LoadVarInst(struct, fConst2), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("*", Float(0.00200000009f), BinopInst("-", LoadVarInst(struct, fConst0), LoadVarInst(struct, fVec0[Int32(1)])))), Float(1.0f)))))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fConst3)))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), BinopInst("*", CastInst("float", LoadVarInst(struct, iRec11[Int32(0)])), Select2Inst(LoadVarInst(stack, iTemp0) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp0) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec12[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fConst2)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fConst3)))), Float(1.0f)) Float(0.0f))))), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec10[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec10[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec10[Int32(0)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec10[Int32(2)]))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fTemp1)))
		StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec9[Int32(0)])), LoadVarInst(stack, fTemp2)))
		StoreVarInst(struct, fRec8[Int32(0)], LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst5)), Int32(8191))]))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(struct, fRec13[Int32(1)]))))
		StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec14[Int32(0)]))))
		StoreVarInst(struct, fRec13[Int32(0)], LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst6)), Int32(8191))]))
		StoreVarInst(struct, fRec16[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fRec15[Int32(1)]))))
		StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec16[Int32(0)]))))
		StoreVarInst(struct, fRec15[Int32(0)], LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst7)), Int32(8191))]))
		StoreVarInst(struct, fRec18[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec18[Int32(1)]), LoadVarInst(struct, fRec17[Int32(1)]))))
		StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec18[Int32(0)]))))
		StoreVarInst(struct, fRec17[Int32(0)], LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst8)), Int32(8191))]))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), LoadVarInst(struct, fRec19[Int32(1)]))))
		StoreVarInst(struct, fVec6[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec20[Int32(0)]))))
		StoreVarInst(struct, fRec19[Int32(0)], LoadVarInst(struct, fVec6[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst9)), Int32(8191))]))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fRec21[Int32(1)]))))
		StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec22[Int32(0)]))))
		StoreVarInst(struct, fRec21[Int32(0)], LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst10)), Int32(8191))]))
		StoreVarInst(struct, fRec24[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), LoadVarInst(struct, fRec23[Int32(1)]))))
		StoreVarInst(struct, fVec8[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec24[Int32(0)]))))
		StoreVarInst(struct, fRec23[Int32(0)], LoadVarInst(struct, fVec8[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst11)), Int32(8191))]))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec26[Int32(1)]), LoadVarInst(struct, fRec25[Int32(1)]))))
		StoreVarInst(struct, fVec9[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec26[Int32(0)]))))
		StoreVarInst(struct, fRec25[Int32(0)], LoadVarInst(struct, fVec9[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst12)), Int32(8191))]))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec8[Int32(0)]), LoadVarInst(struct, fRec13[Int32(0)])), LoadVarInst(struct, fRec15[Int32(0)])), LoadVarInst(struct, fRec17[Int32(0)])), LoadVarInst(struct, fRec19[Int32(0)])), LoadVarInst(struct, fRec21[Int32(0)])), LoadVarInst(struct, fRec23[Int32(0)])), LoadVarInst(struct, fRec25[Int32(0)])), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec6[Int32(1)]))))
		StoreVarInst(struct, fVec10[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp3))
		StoreVarInst(struct, fRec6[Int32(0)], LoadVarInst(struct, fVec10[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst13)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec7, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp3))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec7), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec4[Int32(1)])))))
		StoreVarInst(struct, fVec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp4))
		StoreVarInst(struct, fRec4[Int32(0)], LoadVarInst(struct, fVec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst14)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec5, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp4))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec5), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec2[Int32(1)])))))
		StoreVarInst(struct, fVec12[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp5))
		StoreVarInst(struct, fRec2[Int32(0)], LoadVarInst(struct, fVec12[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst15)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec3, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp5))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec3), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec0[Int32(1)])))))
		StoreVarInst(struct, fVec13[BinopInst("&", LoadVarInst(struct, IOTA), Int32(1023))], LoadVarInst(stack, fTemp6))
		StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(struct, fVec13[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst16)), Int32(1023))]))
		DeclareVarInst(stack, "float", fRec1, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp6))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec1), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(stack, fTemp1)))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp7)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp7)))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, iRec11[Int32(1)], LoadVarInst(struct, iRec11[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(2)], LoadVarInst(struct, fRec10[Int32(1)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, int, iRec11[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, float, fRec10[3])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec2[8192])
	DeclareVarInst(struct, "int", iConst5)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fVec3[8192])
	DeclareVarInst(struct, "int", iConst6)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fVec4[8192])
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fVec5[8192])
	DeclareVarInst(struct, "int", iConst8)
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fVec6[8192])
	DeclareVarInst(struct, "int", iConst9)
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fVec7[8192])
	DeclareVarInst(struct, "int", iConst10)
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fVec8[8192])
	DeclareVarInst(struct, "int", iConst11)
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fVec9[8192])
	DeclareVarInst(struct, "int", iConst12)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, float, fVec10[2048])
	DeclareVarInst(struct, "int", iConst13)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fVec11[2048])
	DeclareVarInst(struct, "int", iConst14)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fVec12[2048])
	DeclareVarInst(struct, "int", iConst15)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fVec13[1024])
	DeclareVarInst(struct, "int", iConst16)
	DeclareVarInst(struct, float, fRec0[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1382.30078f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00200000009f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00100000005f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, iConst5, CastInst("int", BinopInst("*", Float(0.0253061224f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst6, CastInst("int", BinopInst("*", Float(0.0269387756f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst7, CastInst("int", BinopInst("*", Float(0.0289569162f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst8, CastInst("int", BinopInst("*", Float(0.0307482984f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst9, CastInst("int", BinopInst("*", Float(0.0322448984f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst10, CastInst("int", BinopInst("*", Float(0.033809524f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst11, CastInst("int", BinopInst("*", Float(0.0353061222f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst12, CastInst("int", BinopInst("*", Float(0.0366666652f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst13, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", CastInst("int", BinopInst("*", Float(0.0126077095f), LoadVarInst(struct, fConst0))), Int32(-1)))))
	StoreVarInst(struct, iConst14, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", CastInst("int", BinopInst("*", Float(0.00999999978f), LoadVarInst(struct, fConst0))), Int32(-1)))))
	StoreVarInst(struct, iConst15, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", CastInst("int", BinopInst("*", Float(0.00773242628f), LoadVarInst(struct, fConst0))), Int32(-1)))))
	StoreVarInst(struct, iConst16, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", CastInst("int", BinopInst("*", Float(0.00510204071f), LoadVarInst(struct, fConst0))), Int32(-1)))))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l0)], Float(0.0f))
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
			StoreVarInst(struct, iRec11[LoadVarInst(loop, l2)], Int32(0))
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
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(3))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(8192))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(8192))
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
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(8192))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(8192))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l15)], Float(0.0f))
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
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(8192))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l19)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l21), Int32(8192))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l22)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l24), Int32(8192))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(8192))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2048))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2048))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2048))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(1024))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(struct, fHslider2)), BinopInst("*", Float(8.0f), CastInst("float", LoadVarInst(struct, fHslider3)))), Float(-19.0f)))))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow3), Float(0.125f)), LoadVarInst(stack, fSlow2)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow3), Float(-0.125f)), LoadVarInst(stack, fSlow2)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow2))))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)), LoadVarInst(stack, fSlow4)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(struct, fRec8[Int32(1)]))))
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(struct, fConst0))
			StoreVarInst(struct, iRec11[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec11[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow6))
			StoreVarInst(struct, fRec12[Int32(0)], Select2Inst(BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fVec1[Int32(1)])), Float(0.0f)), Int32(0)) Float(0.0f) FunCallInst("min_f", LoadVarInst(struct, fConst2), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("*", Float(0.00200000009f), BinopInst("-", LoadVarInst(struct, fConst0), LoadVarInst(struct, fVec0[Int32(1)])))), Float(1.0f)))))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fConst3)))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), BinopInst("*", CastInst("float", LoadVarInst(struct, iRec11[Int32(0)])), Select2Inst(LoadVarInst(stack, iTemp0) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp0) BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(struct, fRec12[Int32(0)])) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fConst2)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fConst3)))), Float(1.0f)) Float(0.0f))))), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec10[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec10[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec10[Int32(0)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec10[Int32(2)]))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fTemp1)))
			StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec9[Int32(0)])), LoadVarInst(stack, fTemp2)))
			StoreVarInst(struct, fRec8[Int32(0)], LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst5)), Int32(8191))]))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(struct, fRec13[Int32(1)]))))
			StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec14[Int32(0)]))))
			StoreVarInst(struct, fRec13[Int32(0)], LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst6)), Int32(8191))]))
			StoreVarInst(struct, fRec16[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fRec15[Int32(1)]))))
			StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec16[Int32(0)]))))
			StoreVarInst(struct, fRec15[Int32(0)], LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst7)), Int32(8191))]))
			StoreVarInst(struct, fRec18[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec18[Int32(1)]), LoadVarInst(struct, fRec17[Int32(1)]))))
			StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec18[Int32(0)]))))
			StoreVarInst(struct, fRec17[Int32(0)], LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst8)), Int32(8191))]))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec20[Int32(1)]), LoadVarInst(struct, fRec19[Int32(1)]))))
			StoreVarInst(struct, fVec6[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec20[Int32(0)]))))
			StoreVarInst(struct, fRec19[Int32(0)], LoadVarInst(struct, fVec6[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst9)), Int32(8191))]))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fRec21[Int32(1)]))))
			StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec22[Int32(0)]))))
			StoreVarInst(struct, fRec21[Int32(0)], LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst10)), Int32(8191))]))
			StoreVarInst(struct, fRec24[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec24[Int32(1)]), LoadVarInst(struct, fRec23[Int32(1)]))))
			StoreVarInst(struct, fVec8[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec24[Int32(0)]))))
			StoreVarInst(struct, fRec23[Int32(0)], LoadVarInst(struct, fVec8[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst11)), Int32(8191))]))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec26[Int32(1)]), LoadVarInst(struct, fRec25[Int32(1)]))))
			StoreVarInst(struct, fVec9[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec26[Int32(0)]))))
			StoreVarInst(struct, fRec25[Int32(0)], LoadVarInst(struct, fVec9[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst12)), Int32(8191))]))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec8[Int32(0)]), LoadVarInst(struct, fRec13[Int32(0)])), LoadVarInst(struct, fRec15[Int32(0)])), LoadVarInst(struct, fRec17[Int32(0)])), LoadVarInst(struct, fRec19[Int32(0)])), LoadVarInst(struct, fRec21[Int32(0)])), LoadVarInst(struct, fRec23[Int32(0)])), LoadVarInst(struct, fRec25[Int32(0)])), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec6[Int32(1)]))))
			StoreVarInst(struct, fVec10[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp3))
			StoreVarInst(struct, fRec6[Int32(0)], LoadVarInst(struct, fVec10[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst13)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec7, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp3))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec7), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec4[Int32(1)])))))
			StoreVarInst(struct, fVec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp4))
			StoreVarInst(struct, fRec4[Int32(0)], LoadVarInst(struct, fVec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst14)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec5, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp4))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec5), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec2[Int32(1)])))))
			StoreVarInst(struct, fVec12[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp5))
			StoreVarInst(struct, fRec2[Int32(0)], LoadVarInst(struct, fVec12[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst15)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec3, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp5))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec3), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec0[Int32(1)])))))
			StoreVarInst(struct, fVec13[BinopInst("&", LoadVarInst(struct, IOTA), Int32(1023))], LoadVarInst(stack, fTemp6))
			StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(struct, fVec13[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst16)), Int32(1023))]))
			DeclareVarInst(stack, "float", fRec1, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp6))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec1), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(stack, fTemp1)))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp7)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp7)))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, iRec11[Int32(1)], LoadVarInst(struct, iRec11[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(2)], LoadVarInst(struct, fRec10[Int32(1)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 56 bytes
Heap size int* = 8 bytes
Heap size real = 291052 bytes
Heap size = 291116 bytes
Stack size in compute = 64 bytes

