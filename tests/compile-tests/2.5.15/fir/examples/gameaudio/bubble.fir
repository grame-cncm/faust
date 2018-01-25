======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("bubble")
	OpenHorizontalBox("Freeverb")
	AddMetaDeclareInst(0, "0", "")
	OpenVerticalBox("0x00")
	AddMetaDeclareInst(fVslider1, "0", "")
	AddMetaDeclareInst(fVslider1, "style", "knob")
	AddMetaDeclareInst(fVslider1, "tooltip", "Somehow control the   density of the reverb.")
	AddVerticalSlider("Damp", fVslider1, 0.5f, 0.0f, 1.0f, 0.0250000004f)
	AddMetaDeclareInst(fVslider0, "1", "")
	AddMetaDeclareInst(fVslider0, "style", "knob")
	AddMetaDeclareInst(fVslider0, "tooltip", "The room size   between 0 and 1 with 1 for the largest room.")
	AddVerticalSlider("RoomSize", fVslider0, 0.5f, 0.0f, 1.0f, 0.0250000004f)
	AddMetaDeclareInst(fVslider3, "2", "")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddMetaDeclareInst(fVslider3, "tooltip", "Spatial   spread between 0 and 1 with 1 for maximum spread.")
	AddVerticalSlider("Stereo Spread", fVslider3, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(fVslider2, "1", "")
	AddMetaDeclareInst(fVslider2, "tooltip", "The amount of reverb applied to the signal   between 0 and 1 with 1 for the maximum amount of reverb.")
	AddVerticalSlider("Wet", fVslider2, 0.333299994f, 0.0f, 1.0f, 0.0250000004f)
	CloseboxInst
	OpenVerticalBox("bubble")
	AddHorizontalSlider("freq", fHslider0, 600.0f, 150.0f, 2000.0f, 1.0f)
	CloseboxInst
	AddButtonInst("drop"fButton0)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, int, iRec12[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec2[8192])
	DeclareVarInst(struct, "int", iConst6)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fVec3[8192])
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fVec4[8192])
	DeclareVarInst(struct, "int", iConst8)
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fVec5[8192])
	DeclareVarInst(struct, "int", iConst9)
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, float, fVec6[8192])
	DeclareVarInst(struct, "int", iConst10)
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fVec7[8192])
	DeclareVarInst(struct, "int", iConst11)
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, float, fVec8[8192])
	DeclareVarInst(struct, "int", iConst12)
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fVec9[8192])
	DeclareVarInst(struct, "int", iConst13)
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fVec10[2048])
	DeclareVarInst(struct, "int", iConst14)
	DeclareVarInst(struct, "int", iConst15)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fVec11[2048])
	DeclareVarInst(struct, "int", iConst16)
	DeclareVarInst(struct, "int", iConst17)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fVec12[2048])
	DeclareVarInst(struct, "int", iConst18)
	DeclareVarInst(struct, "int", iConst19)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fVec13[1024])
	DeclareVarInst(struct, "int", iConst20)
	DeclareVarInst(struct, "int", iConst21)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec37[2])
	DeclareVarInst(struct, float, fVec14[8192])
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fRec36[2])
	DeclareVarInst(struct, float, fRec39[2])
	DeclareVarInst(struct, float, fVec15[8192])
	DeclareVarInst(struct, float, fRec38[2])
	DeclareVarInst(struct, float, fRec41[2])
	DeclareVarInst(struct, float, fVec16[8192])
	DeclareVarInst(struct, float, fRec40[2])
	DeclareVarInst(struct, float, fRec43[2])
	DeclareVarInst(struct, float, fVec17[8192])
	DeclareVarInst(struct, float, fRec42[2])
	DeclareVarInst(struct, float, fRec45[2])
	DeclareVarInst(struct, float, fVec18[8192])
	DeclareVarInst(struct, float, fRec44[2])
	DeclareVarInst(struct, float, fRec47[2])
	DeclareVarInst(struct, float, fVec19[8192])
	DeclareVarInst(struct, float, fRec46[2])
	DeclareVarInst(struct, float, fRec49[2])
	DeclareVarInst(struct, float, fVec20[8192])
	DeclareVarInst(struct, float, fRec48[2])
	DeclareVarInst(struct, float, fRec51[2])
	DeclareVarInst(struct, float, fVec21[8192])
	DeclareVarInst(struct, float, fRec50[2])
	DeclareVarInst(struct, float, fVec22[2048])
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, float, fVec23[2048])
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fVec24[2048])
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, float, fVec25[2048])
	DeclareVarInst(struct, float, fRec28[2])
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(12348.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(17640.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(0.075000003f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, iConst6, CastInst("int", BinopInst("*", Float(0.0253061224f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst7, CastInst("int", BinopInst("*", Float(0.0269387756f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst8, CastInst("int", BinopInst("*", Float(0.0289569162f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst9, CastInst("int", BinopInst("*", Float(0.0307482984f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst10, CastInst("int", BinopInst("*", Float(0.0322448984f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst11, CastInst("int", BinopInst("*", Float(0.033809524f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst12, CastInst("int", BinopInst("*", Float(0.0353061222f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst13, CastInst("int", BinopInst("*", Float(0.0366666652f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst14, CastInst("int", BinopInst("*", Float(0.0126077095f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst15, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst14), Int32(-1)))))
	StoreVarInst(struct, iConst16, CastInst("int", BinopInst("*", Float(0.00999999978f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst17, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst16), Int32(-1)))))
	StoreVarInst(struct, iConst18, CastInst("int", BinopInst("*", Float(0.00773242628f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst19, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst18), Int32(-1)))))
	StoreVarInst(struct, iConst20, CastInst("int", BinopInst("*", Float(0.00510204071f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst21, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst20), Int32(-1)))))
	StoreVarInst(struct, fConst22, BinopInst("*", Float(0.00104308384f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(0.33329999999999999f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(600.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(0.5f)))
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
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l1)], Float(0.0f))
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
			StoreVarInst(struct, iRec12[LoadVarInst(loop, l3)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(8192))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l7)], Float(0.0f))
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
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(8192))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(8192))
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
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(8192))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l16)], Float(0.0f))
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
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(8192))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(8192))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(8192))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l26)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l28), Int32(8192))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2048))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2048))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2048))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(1024))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(8192))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec14[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(2))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(8192))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec15[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(2))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(2))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(8192))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec16[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(2))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(8192))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec17[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(8192))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec18[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(2))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(8192))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec19[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(2))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(2))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l56)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(8192))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec20[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(2))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l59, Int32(0))
		BinopInst("<", LoadVarInst(loop, l59), Int32(2))
		StoreVarInst(loop, l59, BinopInst("+", LoadVarInst(loop, l59), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l59)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l60, Int32(0))
		BinopInst("<", LoadVarInst(loop, l60), Int32(8192))
		StoreVarInst(loop, l60, BinopInst("+", LoadVarInst(loop, l60), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec21[LoadVarInst(loop, l60)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l61, Int32(0))
		BinopInst("<", LoadVarInst(loop, l61), Int32(2))
		StoreVarInst(loop, l61, BinopInst("+", LoadVarInst(loop, l61), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l61)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l62, Int32(0))
		BinopInst("<", LoadVarInst(loop, l62), Int32(2048))
		StoreVarInst(loop, l62, BinopInst("+", LoadVarInst(loop, l62), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec22[LoadVarInst(loop, l62)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l63, Int32(0))
		BinopInst("<", LoadVarInst(loop, l63), Int32(2))
		StoreVarInst(loop, l63, BinopInst("+", LoadVarInst(loop, l63), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l63)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l64, Int32(0))
		BinopInst("<", LoadVarInst(loop, l64), Int32(2048))
		StoreVarInst(loop, l64, BinopInst("+", LoadVarInst(loop, l64), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec23[LoadVarInst(loop, l64)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l65, Int32(0))
		BinopInst("<", LoadVarInst(loop, l65), Int32(2))
		StoreVarInst(loop, l65, BinopInst("+", LoadVarInst(loop, l65), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l65)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l66, Int32(0))
		BinopInst("<", LoadVarInst(loop, l66), Int32(2048))
		StoreVarInst(loop, l66, BinopInst("+", LoadVarInst(loop, l66), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec24[LoadVarInst(loop, l66)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l67, Int32(0))
		BinopInst("<", LoadVarInst(loop, l67), Int32(2))
		StoreVarInst(loop, l67, BinopInst("+", LoadVarInst(loop, l67), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l67)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l68, Int32(0))
		BinopInst("<", LoadVarInst(loop, l68), Int32(2048))
		StoreVarInst(loop, l68, BinopInst("+", LoadVarInst(loop, l68), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec25[LoadVarInst(loop, l68)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l69, Int32(0))
		BinopInst("<", LoadVarInst(loop, l69), Int32(2))
		StoreVarInst(loop, l69, BinopInst("+", LoadVarInst(loop, l69), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l69)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 47
Store = 0
Binop = 27
Numbers = 17
Declare = 28
Cast = 7
Select = 0
Loop = 0
Funcall = 9

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fVslider0))), Float(0.699999988f)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fVslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fVslider2)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.200000003f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("+", BinopInst("*", Float(0.0430000015f), LoadVarInst(stack, fSlow5)), BinopInst("*", Float(0.00139999995f), FunCallInst("powf", LoadVarInst(stack, fSlow5), Float(1.5f)))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow9, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow7))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "int", iSlow12, CastInst("int", BinopInst("*", LoadVarInst(struct, fConst22), CastInst("float", LoadVarInst(struct, fVslider3)))))
	DeclareVarInst(stack, "int", iSlow13, BinopInst("+", LoadVarInst(struct, iConst6), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow14, BinopInst("+", LoadVarInst(struct, iConst7), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow15, BinopInst("+", LoadVarInst(struct, iConst8), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow16, BinopInst("+", LoadVarInst(struct, iConst9), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow17, BinopInst("+", LoadVarInst(struct, iConst10), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow18, BinopInst("+", LoadVarInst(struct, iConst11), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow19, BinopInst("+", LoadVarInst(struct, iConst12), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow20, BinopInst("+", LoadVarInst(struct, iConst13), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow21, BinopInst("+", LoadVarInst(stack, iSlow12), Int32(-1)))
	DeclareVarInst(stack, "int", iSlow22, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst14), LoadVarInst(stack, iSlow21)))))
	DeclareVarInst(stack, "int", iSlow23, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst16), LoadVarInst(stack, iSlow21)))))
	DeclareVarInst(stack, "int", iSlow24, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst18), LoadVarInst(stack, iSlow21)))))
	DeclareVarInst(stack, "int", iSlow25, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst20), LoadVarInst(stack, iSlow21)))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 297
Store = 120
Binop = 184
Numbers = 151
Declare = 23
Cast = 5
Select = 0
Loop = 1
Funcall = 3

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec8[Int32(1)]))))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow9))
		StoreVarInst(struct, iRec12[Int32(0)], BinopInst("+", Select2Inst(BinopInst(">", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fVec1[Int32(1)])) Int32(0) LoadVarInst(struct, iRec12[Int32(1)])), Int32(1)))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(stack, fSlow6), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), CastInst("float", LoadVarInst(struct, iRec12[Int32(0)]))), Float(1.0f))))
		DeclareVarInst(stack, "float", fTemp1, FunCallInst("sinf", LoadVarInst(stack, fTemp0)))
		DeclareVarInst(stack, "float", fTemp2, FunCallInst("cosf", LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(stack, fTemp2))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(stack, fTemp2)), BinopInst("*", LoadVarInst(struct, fRec10[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp1)))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", Float(0.99000001f), LoadVarInst(struct, fRec13[Int32(1)])), BinopInst("*", Float(0.00999999978f), FunCallInst("expf", BinopInst("*", LoadVarInst(stack, fSlow10), CastInst("float", LoadVarInst(struct, iRec12[Int32(0)])))))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fRec10[Int32(0)]), LoadVarInst(struct, fRec13[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(stack, fTemp3)))
		StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec9[Int32(0)])), LoadVarInst(stack, fTemp4)))
		StoreVarInst(struct, fRec8[Int32(0)], LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst6)), Int32(8191))]))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec14[Int32(1)]))))
		StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec15[Int32(0)]))))
		StoreVarInst(struct, fRec14[Int32(0)], LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst7)), Int32(8191))]))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec16[Int32(1)]))))
		StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec17[Int32(0)]))))
		StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst8)), Int32(8191))]))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec18[Int32(1)]))))
		StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec19[Int32(0)]))))
		StoreVarInst(struct, fRec18[Int32(0)], LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst9)), Int32(8191))]))
		StoreVarInst(struct, fRec21[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec20[Int32(1)]))))
		StoreVarInst(struct, fVec6[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec21[Int32(0)]))))
		StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(struct, fVec6[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst10)), Int32(8191))]))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec22[Int32(1)]))))
		StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec23[Int32(0)]))))
		StoreVarInst(struct, fRec22[Int32(0)], LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst11)), Int32(8191))]))
		StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec25[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec24[Int32(1)]))))
		StoreVarInst(struct, fVec8[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec25[Int32(0)]))))
		StoreVarInst(struct, fRec24[Int32(0)], LoadVarInst(struct, fVec8[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst12)), Int32(8191))]))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec26[Int32(1)]))))
		StoreVarInst(struct, fVec9[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec27[Int32(0)]))))
		StoreVarInst(struct, fRec26[Int32(0)], LoadVarInst(struct, fVec9[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst13)), Int32(8191))]))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec8[Int32(0)]), LoadVarInst(struct, fRec14[Int32(0)])), LoadVarInst(struct, fRec16[Int32(0)])), LoadVarInst(struct, fRec18[Int32(0)])), LoadVarInst(struct, fRec20[Int32(0)])), LoadVarInst(struct, fRec22[Int32(0)])), LoadVarInst(struct, fRec24[Int32(0)])), LoadVarInst(struct, fRec26[Int32(0)])), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec6[Int32(1)]))))
		StoreVarInst(struct, fVec10[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp5))
		StoreVarInst(struct, fRec6[Int32(0)], LoadVarInst(struct, fVec10[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst15)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec7, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp5))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec7), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec4[Int32(1)])))))
		StoreVarInst(struct, fVec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp6))
		StoreVarInst(struct, fRec4[Int32(0)], LoadVarInst(struct, fVec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst17)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec5, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp6))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec5), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec2[Int32(1)])))))
		StoreVarInst(struct, fVec12[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp7))
		StoreVarInst(struct, fRec2[Int32(0)], LoadVarInst(struct, fVec12[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst19)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec3, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp7))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec3), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec0[Int32(1)])))))
		StoreVarInst(struct, fVec13[BinopInst("&", LoadVarInst(struct, IOTA), Int32(1023))], LoadVarInst(stack, fTemp8))
		StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(struct, fVec13[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst21)), Int32(1023))]))
		DeclareVarInst(stack, "float", fRec1, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp8))))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(stack, fTemp3)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec1), LoadVarInst(struct, fRec0[Int32(1)])), LoadVarInst(stack, fTemp9))))
		StoreVarInst(struct, fRec37[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec36[Int32(1)]))))
		StoreVarInst(struct, fVec14[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec37[Int32(0)]))))
		StoreVarInst(struct, fRec36[Int32(0)], LoadVarInst(struct, fVec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow13)), Int32(8191))]))
		StoreVarInst(struct, fRec39[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec39[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec38[Int32(1)]))))
		StoreVarInst(struct, fVec15[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec39[Int32(0)]))))
		StoreVarInst(struct, fRec38[Int32(0)], LoadVarInst(struct, fVec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow14)), Int32(8191))]))
		StoreVarInst(struct, fRec41[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec41[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec40[Int32(1)]))))
		StoreVarInst(struct, fVec16[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec41[Int32(0)]))))
		StoreVarInst(struct, fRec40[Int32(0)], LoadVarInst(struct, fVec16[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow15)), Int32(8191))]))
		StoreVarInst(struct, fRec43[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec43[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec42[Int32(1)]))))
		StoreVarInst(struct, fVec17[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec43[Int32(0)]))))
		StoreVarInst(struct, fRec42[Int32(0)], LoadVarInst(struct, fVec17[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow16)), Int32(8191))]))
		StoreVarInst(struct, fRec45[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec45[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec44[Int32(1)]))))
		StoreVarInst(struct, fVec18[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec45[Int32(0)]))))
		StoreVarInst(struct, fRec44[Int32(0)], LoadVarInst(struct, fVec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow17)), Int32(8191))]))
		StoreVarInst(struct, fRec47[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec47[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec46[Int32(1)]))))
		StoreVarInst(struct, fVec19[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec47[Int32(0)]))))
		StoreVarInst(struct, fRec46[Int32(0)], LoadVarInst(struct, fVec19[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow18)), Int32(8191))]))
		StoreVarInst(struct, fRec49[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec49[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec48[Int32(1)]))))
		StoreVarInst(struct, fVec20[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec49[Int32(0)]))))
		StoreVarInst(struct, fRec48[Int32(0)], LoadVarInst(struct, fVec20[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow19)), Int32(8191))]))
		StoreVarInst(struct, fRec51[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec51[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec50[Int32(1)]))))
		StoreVarInst(struct, fVec21[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec51[Int32(0)]))))
		StoreVarInst(struct, fRec50[Int32(0)], LoadVarInst(struct, fVec21[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow20)), Int32(8191))]))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec36[Int32(0)]), LoadVarInst(struct, fRec38[Int32(0)])), LoadVarInst(struct, fRec40[Int32(0)])), LoadVarInst(struct, fRec42[Int32(0)])), LoadVarInst(struct, fRec44[Int32(0)])), LoadVarInst(struct, fRec46[Int32(0)])), LoadVarInst(struct, fRec48[Int32(0)])), LoadVarInst(struct, fRec50[Int32(0)])), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec34[Int32(1)]))))
		StoreVarInst(struct, fVec22[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp10))
		StoreVarInst(struct, fRec34[Int32(0)], LoadVarInst(struct, fVec22[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow22)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec35, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp10))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(struct, fRec34[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec35), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec32[Int32(1)])))))
		StoreVarInst(struct, fVec23[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp11))
		StoreVarInst(struct, fRec32[Int32(0)], LoadVarInst(struct, fVec23[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow23)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec33, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp11))))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec33), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec30[Int32(1)])))))
		StoreVarInst(struct, fVec24[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp12))
		StoreVarInst(struct, fRec30[Int32(0)], LoadVarInst(struct, fVec24[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow24)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec31, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("+", LoadVarInst(struct, fRec30[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec31), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec28[Int32(1)])))))
		StoreVarInst(struct, fVec25[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp13))
		StoreVarInst(struct, fRec28[Int32(0)], LoadVarInst(struct, fVec25[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow25)), Int32(2047))]))
		DeclareVarInst(stack, "float", fRec29, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec29), LoadVarInst(stack, fTemp9)))))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, iRec12[Int32(1)], LoadVarInst(struct, iRec12[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
		StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
		StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
		StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
		StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
		StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
		StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
		StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
		StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
		StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
		StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
		StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
		StoreVarInst(struct, fRec49[Int32(1)], LoadVarInst(struct, fRec49[Int32(0)]))
		StoreVarInst(struct, fRec48[Int32(1)], LoadVarInst(struct, fRec48[Int32(0)]))
		StoreVarInst(struct, fRec51[Int32(1)], LoadVarInst(struct, fRec51[Int32(0)]))
		StoreVarInst(struct, fRec50[Int32(1)], LoadVarInst(struct, fRec50[Int32(0)]))
		StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, int, iRec12[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec2[8192])
	DeclareVarInst(struct, "int", iConst6)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fVec3[8192])
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fVec4[8192])
	DeclareVarInst(struct, "int", iConst8)
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fVec5[8192])
	DeclareVarInst(struct, "int", iConst9)
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, float, fVec6[8192])
	DeclareVarInst(struct, "int", iConst10)
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fVec7[8192])
	DeclareVarInst(struct, "int", iConst11)
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, float, fVec8[8192])
	DeclareVarInst(struct, "int", iConst12)
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fVec9[8192])
	DeclareVarInst(struct, "int", iConst13)
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fVec10[2048])
	DeclareVarInst(struct, "int", iConst14)
	DeclareVarInst(struct, "int", iConst15)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fVec11[2048])
	DeclareVarInst(struct, "int", iConst16)
	DeclareVarInst(struct, "int", iConst17)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fVec12[2048])
	DeclareVarInst(struct, "int", iConst18)
	DeclareVarInst(struct, "int", iConst19)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fVec13[1024])
	DeclareVarInst(struct, "int", iConst20)
	DeclareVarInst(struct, "int", iConst21)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, float, fRec37[2])
	DeclareVarInst(struct, float, fVec14[8192])
	DeclareVarInst(struct, "float", fConst22)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fRec36[2])
	DeclareVarInst(struct, float, fRec39[2])
	DeclareVarInst(struct, float, fVec15[8192])
	DeclareVarInst(struct, float, fRec38[2])
	DeclareVarInst(struct, float, fRec41[2])
	DeclareVarInst(struct, float, fVec16[8192])
	DeclareVarInst(struct, float, fRec40[2])
	DeclareVarInst(struct, float, fRec43[2])
	DeclareVarInst(struct, float, fVec17[8192])
	DeclareVarInst(struct, float, fRec42[2])
	DeclareVarInst(struct, float, fRec45[2])
	DeclareVarInst(struct, float, fVec18[8192])
	DeclareVarInst(struct, float, fRec44[2])
	DeclareVarInst(struct, float, fRec47[2])
	DeclareVarInst(struct, float, fVec19[8192])
	DeclareVarInst(struct, float, fRec46[2])
	DeclareVarInst(struct, float, fRec49[2])
	DeclareVarInst(struct, float, fVec20[8192])
	DeclareVarInst(struct, float, fRec48[2])
	DeclareVarInst(struct, float, fRec51[2])
	DeclareVarInst(struct, float, fVec21[8192])
	DeclareVarInst(struct, float, fRec50[2])
	DeclareVarInst(struct, float, fVec22[2048])
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, float, fVec23[2048])
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fVec24[2048])
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, float, fVec25[2048])
	DeclareVarInst(struct, float, fRec28[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(12348.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(17640.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(0.075000003f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, iConst6, CastInst("int", BinopInst("*", Float(0.0253061224f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst7, CastInst("int", BinopInst("*", Float(0.0269387756f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst8, CastInst("int", BinopInst("*", Float(0.0289569162f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst9, CastInst("int", BinopInst("*", Float(0.0307482984f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst10, CastInst("int", BinopInst("*", Float(0.0322448984f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst11, CastInst("int", BinopInst("*", Float(0.033809524f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst12, CastInst("int", BinopInst("*", Float(0.0353061222f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst13, CastInst("int", BinopInst("*", Float(0.0366666652f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst14, CastInst("int", BinopInst("*", Float(0.0126077095f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst15, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst14), Int32(-1)))))
	StoreVarInst(struct, iConst16, CastInst("int", BinopInst("*", Float(0.00999999978f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst17, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst16), Int32(-1)))))
	StoreVarInst(struct, iConst18, CastInst("int", BinopInst("*", Float(0.00773242628f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst19, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst18), Int32(-1)))))
	StoreVarInst(struct, iConst20, CastInst("int", BinopInst("*", Float(0.00510204071f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst21, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst20), Int32(-1)))))
	StoreVarInst(struct, fConst22, BinopInst("*", Float(0.00104308384f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(0.33329999999999999f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(600.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(0.5f)))
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
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l1)], Float(0.0f))
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
			StoreVarInst(struct, iRec12[LoadVarInst(loop, l3)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(8192))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l7)], Float(0.0f))
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
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(8192))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(8192))
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
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(8192))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l16)], Float(0.0f))
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
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(8192))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(8192))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(8192))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l26)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l28), Int32(8192))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2048))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2048))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2048))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(1024))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(8192))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec14[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(2))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(8192))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec15[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(2))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(2))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(8192))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec16[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(2))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(8192))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec17[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(8192))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec18[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(2))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(8192))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec19[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(2))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(2))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l56)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(8192))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec20[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(2))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l59, Int32(0))
		BinopInst("<", LoadVarInst(loop, l59), Int32(2))
		StoreVarInst(loop, l59, BinopInst("+", LoadVarInst(loop, l59), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l59)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l60, Int32(0))
		BinopInst("<", LoadVarInst(loop, l60), Int32(8192))
		StoreVarInst(loop, l60, BinopInst("+", LoadVarInst(loop, l60), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec21[LoadVarInst(loop, l60)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l61, Int32(0))
		BinopInst("<", LoadVarInst(loop, l61), Int32(2))
		StoreVarInst(loop, l61, BinopInst("+", LoadVarInst(loop, l61), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l61)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l62, Int32(0))
		BinopInst("<", LoadVarInst(loop, l62), Int32(2048))
		StoreVarInst(loop, l62, BinopInst("+", LoadVarInst(loop, l62), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec22[LoadVarInst(loop, l62)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l63, Int32(0))
		BinopInst("<", LoadVarInst(loop, l63), Int32(2))
		StoreVarInst(loop, l63, BinopInst("+", LoadVarInst(loop, l63), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l63)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l64, Int32(0))
		BinopInst("<", LoadVarInst(loop, l64), Int32(2048))
		StoreVarInst(loop, l64, BinopInst("+", LoadVarInst(loop, l64), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec23[LoadVarInst(loop, l64)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l65, Int32(0))
		BinopInst("<", LoadVarInst(loop, l65), Int32(2))
		StoreVarInst(loop, l65, BinopInst("+", LoadVarInst(loop, l65), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l65)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l66, Int32(0))
		BinopInst("<", LoadVarInst(loop, l66), Int32(2048))
		StoreVarInst(loop, l66, BinopInst("+", LoadVarInst(loop, l66), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec24[LoadVarInst(loop, l66)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l67, Int32(0))
		BinopInst("<", LoadVarInst(loop, l67), Int32(2))
		StoreVarInst(loop, l67, BinopInst("+", LoadVarInst(loop, l67), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l67)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l68, Int32(0))
		BinopInst("<", LoadVarInst(loop, l68), Int32(2048))
		StoreVarInst(loop, l68, BinopInst("+", LoadVarInst(loop, l68), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec25[LoadVarInst(loop, l68)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l69, Int32(0))
		BinopInst("<", LoadVarInst(loop, l69), Int32(2))
		StoreVarInst(loop, l69, BinopInst("+", LoadVarInst(loop, l69), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l69)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fVslider0))), Float(0.699999988f)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fVslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fVslider2)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.200000003f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("+", BinopInst("*", Float(0.0430000015f), LoadVarInst(stack, fSlow5)), BinopInst("*", Float(0.00139999995f), FunCallInst("powf", LoadVarInst(stack, fSlow5), Float(1.5f)))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow9, CastInst("float", LoadVarInst(struct, fButton0)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow7))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "int", iSlow12, CastInst("int", BinopInst("*", LoadVarInst(struct, fConst22), CastInst("float", LoadVarInst(struct, fVslider3)))))
	DeclareVarInst(stack, "int", iSlow13, BinopInst("+", LoadVarInst(struct, iConst6), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow14, BinopInst("+", LoadVarInst(struct, iConst7), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow15, BinopInst("+", LoadVarInst(struct, iConst8), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow16, BinopInst("+", LoadVarInst(struct, iConst9), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow17, BinopInst("+", LoadVarInst(struct, iConst10), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow18, BinopInst("+", LoadVarInst(struct, iConst11), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow19, BinopInst("+", LoadVarInst(struct, iConst12), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow20, BinopInst("+", LoadVarInst(struct, iConst13), LoadVarInst(stack, iSlow12)))
	DeclareVarInst(stack, "int", iSlow21, BinopInst("+", LoadVarInst(stack, iSlow12), Int32(-1)))
	DeclareVarInst(stack, "int", iSlow22, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst14), LoadVarInst(stack, iSlow21)))))
	DeclareVarInst(stack, "int", iSlow23, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst16), LoadVarInst(stack, iSlow21)))))
	DeclareVarInst(stack, "int", iSlow24, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst18), LoadVarInst(stack, iSlow21)))))
	DeclareVarInst(stack, "int", iSlow25, FunCallInst("min_i", Int32(1024), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(struct, iConst20), LoadVarInst(stack, iSlow21)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec8[Int32(1)]))))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow9))
			StoreVarInst(struct, iRec12[Int32(0)], BinopInst("+", Select2Inst(BinopInst(">", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fVec1[Int32(1)])) Int32(0) LoadVarInst(struct, iRec12[Int32(1)])), Int32(1)))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(stack, fSlow6), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), CastInst("float", LoadVarInst(struct, iRec12[Int32(0)]))), Float(1.0f))))
			DeclareVarInst(stack, "float", fTemp1, FunCallInst("sinf", LoadVarInst(stack, fTemp0)))
			DeclareVarInst(stack, "float", fTemp2, FunCallInst("cosf", LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(stack, fTemp2))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(stack, fTemp2)), BinopInst("*", LoadVarInst(struct, fRec10[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp1)))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", Float(0.99000001f), LoadVarInst(struct, fRec13[Int32(1)])), BinopInst("*", Float(0.00999999978f), FunCallInst("expf", BinopInst("*", LoadVarInst(stack, fSlow10), CastInst("float", LoadVarInst(struct, iRec12[Int32(0)])))))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fRec10[Int32(0)]), LoadVarInst(struct, fRec13[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(stack, fTemp3)))
			StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec9[Int32(0)])), LoadVarInst(stack, fTemp4)))
			StoreVarInst(struct, fRec8[Int32(0)], LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst6)), Int32(8191))]))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec14[Int32(1)]))))
			StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec15[Int32(0)]))))
			StoreVarInst(struct, fRec14[Int32(0)], LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst7)), Int32(8191))]))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec16[Int32(1)]))))
			StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec17[Int32(0)]))))
			StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst8)), Int32(8191))]))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec18[Int32(1)]))))
			StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec19[Int32(0)]))))
			StoreVarInst(struct, fRec18[Int32(0)], LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst9)), Int32(8191))]))
			StoreVarInst(struct, fRec21[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec21[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec20[Int32(1)]))))
			StoreVarInst(struct, fVec6[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec21[Int32(0)]))))
			StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(struct, fVec6[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst10)), Int32(8191))]))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec22[Int32(1)]))))
			StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec23[Int32(0)]))))
			StoreVarInst(struct, fRec22[Int32(0)], LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst11)), Int32(8191))]))
			StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec25[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec24[Int32(1)]))))
			StoreVarInst(struct, fVec8[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec25[Int32(0)]))))
			StoreVarInst(struct, fRec24[Int32(0)], LoadVarInst(struct, fVec8[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst12)), Int32(8191))]))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec26[Int32(1)]))))
			StoreVarInst(struct, fVec9[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec27[Int32(0)]))))
			StoreVarInst(struct, fRec26[Int32(0)], LoadVarInst(struct, fVec9[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst13)), Int32(8191))]))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec8[Int32(0)]), LoadVarInst(struct, fRec14[Int32(0)])), LoadVarInst(struct, fRec16[Int32(0)])), LoadVarInst(struct, fRec18[Int32(0)])), LoadVarInst(struct, fRec20[Int32(0)])), LoadVarInst(struct, fRec22[Int32(0)])), LoadVarInst(struct, fRec24[Int32(0)])), LoadVarInst(struct, fRec26[Int32(0)])), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec6[Int32(1)]))))
			StoreVarInst(struct, fVec10[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp5))
			StoreVarInst(struct, fRec6[Int32(0)], LoadVarInst(struct, fVec10[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst15)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec7, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp5))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec7), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec4[Int32(1)])))))
			StoreVarInst(struct, fVec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp6))
			StoreVarInst(struct, fRec4[Int32(0)], LoadVarInst(struct, fVec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst17)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec5, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp6))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec5), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec2[Int32(1)])))))
			StoreVarInst(struct, fVec12[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp7))
			StoreVarInst(struct, fRec2[Int32(0)], LoadVarInst(struct, fVec12[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst19)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec3, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp7))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec3), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec0[Int32(1)])))))
			StoreVarInst(struct, fVec13[BinopInst("&", LoadVarInst(struct, IOTA), Int32(1023))], LoadVarInst(stack, fTemp8))
			StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(struct, fVec13[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst21)), Int32(1023))]))
			DeclareVarInst(stack, "float", fRec1, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp8))))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(stack, fTemp3)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec1), LoadVarInst(struct, fRec0[Int32(1)])), LoadVarInst(stack, fTemp9))))
			StoreVarInst(struct, fRec37[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec37[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec36[Int32(1)]))))
			StoreVarInst(struct, fVec14[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec37[Int32(0)]))))
			StoreVarInst(struct, fRec36[Int32(0)], LoadVarInst(struct, fVec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow13)), Int32(8191))]))
			StoreVarInst(struct, fRec39[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec39[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec38[Int32(1)]))))
			StoreVarInst(struct, fVec15[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec39[Int32(0)]))))
			StoreVarInst(struct, fRec38[Int32(0)], LoadVarInst(struct, fVec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow14)), Int32(8191))]))
			StoreVarInst(struct, fRec41[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec41[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec40[Int32(1)]))))
			StoreVarInst(struct, fVec16[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec41[Int32(0)]))))
			StoreVarInst(struct, fRec40[Int32(0)], LoadVarInst(struct, fVec16[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow15)), Int32(8191))]))
			StoreVarInst(struct, fRec43[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec43[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec42[Int32(1)]))))
			StoreVarInst(struct, fVec17[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec43[Int32(0)]))))
			StoreVarInst(struct, fRec42[Int32(0)], LoadVarInst(struct, fVec17[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow16)), Int32(8191))]))
			StoreVarInst(struct, fRec45[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec45[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec44[Int32(1)]))))
			StoreVarInst(struct, fVec18[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec45[Int32(0)]))))
			StoreVarInst(struct, fRec44[Int32(0)], LoadVarInst(struct, fVec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow17)), Int32(8191))]))
			StoreVarInst(struct, fRec47[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec47[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec46[Int32(1)]))))
			StoreVarInst(struct, fVec19[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec47[Int32(0)]))))
			StoreVarInst(struct, fRec46[Int32(0)], LoadVarInst(struct, fVec19[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow18)), Int32(8191))]))
			StoreVarInst(struct, fRec49[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec49[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec48[Int32(1)]))))
			StoreVarInst(struct, fVec20[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec49[Int32(0)]))))
			StoreVarInst(struct, fRec48[Int32(0)], LoadVarInst(struct, fVec20[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow19)), Int32(8191))]))
			StoreVarInst(struct, fRec51[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec51[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec50[Int32(1)]))))
			StoreVarInst(struct, fVec21[BinopInst("&", LoadVarInst(struct, IOTA), Int32(8191))], BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec51[Int32(0)]))))
			StoreVarInst(struct, fRec50[Int32(0)], LoadVarInst(struct, fVec21[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow20)), Int32(8191))]))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec36[Int32(0)]), LoadVarInst(struct, fRec38[Int32(0)])), LoadVarInst(struct, fRec40[Int32(0)])), LoadVarInst(struct, fRec42[Int32(0)])), LoadVarInst(struct, fRec44[Int32(0)])), LoadVarInst(struct, fRec46[Int32(0)])), LoadVarInst(struct, fRec48[Int32(0)])), LoadVarInst(struct, fRec50[Int32(0)])), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec34[Int32(1)]))))
			StoreVarInst(struct, fVec22[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp10))
			StoreVarInst(struct, fRec34[Int32(0)], LoadVarInst(struct, fVec22[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow22)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec35, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp10))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(struct, fRec34[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec35), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec32[Int32(1)])))))
			StoreVarInst(struct, fVec23[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp11))
			StoreVarInst(struct, fRec32[Int32(0)], LoadVarInst(struct, fVec23[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow23)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec33, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp11))))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(struct, fRec32[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec33), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec30[Int32(1)])))))
			StoreVarInst(struct, fVec24[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp12))
			StoreVarInst(struct, fRec30[Int32(0)], LoadVarInst(struct, fVec24[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow24)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec31, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("+", LoadVarInst(struct, fRec30[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec31), BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec28[Int32(1)])))))
			StoreVarInst(struct, fVec25[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp13))
			StoreVarInst(struct, fRec28[Int32(0)], LoadVarInst(struct, fVec25[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iSlow25)), Int32(2047))]))
			DeclareVarInst(stack, "float", fRec29, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), BinopInst("+", LoadVarInst(stack, fRec29), LoadVarInst(stack, fTemp9)))))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, iRec12[Int32(1)], LoadVarInst(struct, iRec12[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
			StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
			StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
			StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
			StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
			StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
			StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
			StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
			StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
			StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
			StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
			StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
			StoreVarInst(struct, fRec49[Int32(1)], LoadVarInst(struct, fRec49[Int32(0)]))
			StoreVarInst(struct, fRec48[Int32(1)], LoadVarInst(struct, fRec48[Int32(0)]))
			StoreVarInst(struct, fRec51[Int32(1)], LoadVarInst(struct, fRec51[Int32(0)]))
			StoreVarInst(struct, fRec50[Int32(1)], LoadVarInst(struct, fRec50[Int32(0)]))
			StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 72 bytes
Heap size int* = 16 bytes
Heap size real = 586132 bytes
Heap size = 586220 bytes
Stack size in compute = 120 bytes

