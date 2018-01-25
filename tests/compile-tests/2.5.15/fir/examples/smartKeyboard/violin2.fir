======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("violin2")
	AddHorizontalSlider("kb0bend", fHslider1, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("kb0fingers", fHslider2, 0.0f, 0.0f, 10.0f, 1.0f)
	AddHorizontalSlider("kb0freq", fHslider0, 220.0f, 20.0f, 10000.0f, 0.00999999978f)
	AddHorizontalSlider("kb1bend", fHslider5, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("kb1fingers", fHslider6, 0.0f, 0.0f, 10.0f, 1.0f)
	AddHorizontalSlider("kb1freq", fHslider4, 330.0f, 20.0f, 10000.0f, 0.00999999978f)
	AddHorizontalSlider("kb2bend", fHslider8, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("kb2fingers", fHslider9, 0.0f, 0.0f, 10.0f, 1.0f)
	AddHorizontalSlider("kb2freq", fHslider7, 440.0f, 20.0f, 10000.0f, 0.00999999978f)
	AddHorizontalSlider("kb3bend", fHslider11, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("kb3fingers", fHslider12, 0.0f, 0.0f, 10.0f, 1.0f)
	AddHorizontalSlider("kb3freq", fHslider10, 550.0f, 20.0f, 10000.0f, 0.00999999978f)
	AddHorizontalSlider("y", fHslider3, 0.0f, 0.0f, 1.0f, 1.0f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower4_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, int, iRec10[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fRec29[4])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec30[2048])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fVec1[2048])
	DeclareVarInst(struct, float, fRec18[2048])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec16[4])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, int, iRec6[2])
	DeclareVarInst(struct, float, fRec2[2048])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, int, iRec42[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec58[2])
	DeclareVarInst(struct, float, fRec54[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec59[4])
	DeclareVarInst(struct, float, fRec60[2048])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fVec3[2048])
	DeclareVarInst(struct, float, fRec50[2048])
	DeclareVarInst(struct, float, fRec52[2])
	DeclareVarInst(struct, float, fRec48[4])
	DeclareVarInst(struct, float, fRec46[3])
	DeclareVarInst(struct, int, iRec38[2])
	DeclareVarInst(struct, float, fRec34[2048])
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, int, iRec72[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, float, fRec88[2])
	DeclareVarInst(struct, float, fRec84[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, float, fRec89[4])
	DeclareVarInst(struct, float, fRec90[2048])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, float, fVec5[2048])
	DeclareVarInst(struct, float, fRec80[2048])
	DeclareVarInst(struct, float, fRec82[2])
	DeclareVarInst(struct, float, fRec78[4])
	DeclareVarInst(struct, float, fRec76[3])
	DeclareVarInst(struct, int, iRec68[2])
	DeclareVarInst(struct, float, fRec64[2048])
	DeclareVarInst(struct, float, fRec62[2])
	DeclareVarInst(struct, int, iRec102[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider10)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider11)
	DeclareVarInst(struct, float, fRec118[2])
	DeclareVarInst(struct, float, fRec114[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider12)
	DeclareVarInst(struct, float, fRec119[4])
	DeclareVarInst(struct, float, fRec120[2048])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, float, fVec7[2048])
	DeclareVarInst(struct, float, fRec110[2048])
	DeclareVarInst(struct, float, fRec112[2])
	DeclareVarInst(struct, float, fRec108[4])
	DeclareVarInst(struct, float, fRec106[3])
	DeclareVarInst(struct, int, iRec98[2])
	DeclareVarInst(struct, float, fRec94[2048])
	DeclareVarInst(struct, float, fRec92[2])
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
	StoreVarInst(struct, fConst1, FunCallInst("tanf", BinopInst("/", Float(1570.79639f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst1)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(0.5f)), LoadVarInst(struct, fConst1)), Float(1.0f))))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("*", Float(0.000441176468f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, BinopInst("*", Float(0.0010294118f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst7, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(-0.5f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst8, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst1))))))
	StoreVarInst(struct, fConst9, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst2)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(220.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(330.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider10, CastInst("FAUSTFLOAT", Double(550.0f)))
	StoreVarInst(struct, fHslider11, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider12, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec10[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(4))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2048))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2048))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2048))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(4))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(3))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[LoadVarInst(loop, l13)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2048))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec42[LoadVarInst(loop, l16)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec58[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec54[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(4))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2048))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2048))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2048))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec52[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(4))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(3))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec38[LoadVarInst(loop, l27)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2048))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec72[LoadVarInst(loop, l30)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec88[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec84[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(4))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec89[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2048))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec90[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2048))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2048))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec80[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec82[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(4))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec78[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(3))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec76[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec68[LoadVarInst(loop, l41)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2048))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec64[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(2))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec62[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(2))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec102[LoadVarInst(loop, l44)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(2))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec118[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec114[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(4))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec119[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(2048))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec120[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2048))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(2048))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec110[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec112[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(4))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec108[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(3))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec106[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(2))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec98[LoadVarInst(loop, l55)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(2048))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec94[LoadVarInst(loop, l56)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(2))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec92[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 15
Store = 0
Binop = 13
Numbers = 9
Declare = 11
Cast = 17
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "int", iSlow1, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider2))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider4)), CastInst("float", LoadVarInst(struct, fHslider5)))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider6))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider7)), CastInst("float", LoadVarInst(struct, fHslider8)))))
	DeclareVarInst(stack, "int", iSlow6, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider9))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider10)), CastInst("float", LoadVarInst(struct, fHslider11)))))
	DeclareVarInst(stack, "int", iSlow8, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider12))), Int32(0)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 931
Store = 116
Binop = 781
Numbers = 476
Declare = 310
Cast = 102
Select = 0
Loop = 9
Funcall = 102

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec10[Int32(0)], Int32(0))
		DeclareVarInst(stack, "int", iRec11, LoadVarInst(struct, iRec10[Int32(1)]))
		DeclareVarInst(stack, "float", fRec15, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec6[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec16[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fRec16[Int32(3)])))))))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec26[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("+", LoadVarInst(struct, fRec26[Int32(0)]), Float(-0.0799999982f)))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp0)))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(stack, fTemp1), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp3, CastInst("int", LoadVarInst(stack, fTemp2)))
		DeclareVarInst(stack, "int", iTemp4, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp3))))))
		DeclareVarInst(stack, "float", fTemp5, FunCallInst("floorf", LoadVarInst(stack, fTemp2)))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp5))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp6)))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp5))))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp8))))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp5))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp10))))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp5))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("-", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp5)))
		DeclareVarInst(stack, "int", iTemp15, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp3), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "int", iTemp18, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp3), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp8)))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp10))))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("*", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fTemp8)))
		DeclareVarInst(stack, "int", iTemp23, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp3), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "int", iTemp26, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp3), Int32(4)))))))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp9)), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), BinopInst("*", LoadVarInst(stack, fTemp14), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp6), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp15), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp16)), LoadVarInst(stack, fTemp17))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp18), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp23), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp24)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp26), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec28[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec28[Int32(1)]))))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", Float(0.00100000005f), FunCallInst("min_f", Float(1.0f), BinopInst("*", Float(3000.0f), FunCallInst("fabsf", BinopInst("-", LoadVarInst(struct, fRec28[Int32(0)]), LoadVarInst(struct, fRec28[Int32(1)]))))))))
		StoreVarInst(struct, fRec29[Int32(0)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec30[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec29[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec29[Int32(1)]), LoadVarInst(struct, fRec29[Int32(3)])))))))
		DeclareVarInst(stack, "int", iRec31, Int32(0))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp0)))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("+", LoadVarInst(stack, fTemp27), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp29, CastInst("int", LoadVarInst(stack, fTemp28)))
		DeclareVarInst(stack, "int", iTemp30, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp29))))))
		DeclareVarInst(stack, "float", fTemp31, FunCallInst("floorf", LoadVarInst(stack, fTemp28)))
		DeclareVarInst(stack, "float", fTemp32, BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp31))))
		DeclareVarInst(stack, "float", fTemp33, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp32)))
		DeclareVarInst(stack, "float", fTemp34, BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp31))))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp31))))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp36))))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp31))))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp38))))
		DeclareVarInst(stack, "float", fTemp40, BinopInst("-", LoadVarInst(stack, fTemp27), LoadVarInst(stack, fTemp31)))
		DeclareVarInst(stack, "int", iTemp41, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp29), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp36)))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp38))))
		DeclareVarInst(stack, "int", iTemp44, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp29), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp45, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp34)))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp36))))
		DeclareVarInst(stack, "float", fTemp47, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp38))))
		DeclareVarInst(stack, "float", fTemp48, BinopInst("*", LoadVarInst(stack, fTemp32), LoadVarInst(stack, fTemp34)))
		DeclareVarInst(stack, "int", iTemp49, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp29), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp50, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp38)))
		DeclareVarInst(stack, "float", fTemp51, BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(stack, fTemp36)))
		DeclareVarInst(stack, "int", iTemp52, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp29), Int32(4)))))))
		StoreVarInst(struct, fVec0[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp30), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp33)), LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp37)), LoadVarInst(stack, fTemp39)), BinopInst("*", LoadVarInst(stack, fTemp40), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp32), LoadVarInst(struct, fRec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp41), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp42)), LoadVarInst(stack, fTemp43))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp44), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(struct, fRec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp49), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp50)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(struct, fRec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp52), Int32(2))), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp53, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow1)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fVec0[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("*", LoadVarInst(stack, fTemp53), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp53))), Float(0.75f)))))))
		DeclareVarInst(stack, "float", fRec23, BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(stack, fTemp54)))
		DeclareVarInst(stack, "float", fTemp55, BinopInst("+", LoadVarInst(struct, fVec0[Int32(1)]), LoadVarInst(stack, fTemp54)))
		StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp55))
		DeclareVarInst(stack, "float", fRec24, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp9)), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp4)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp14), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp26)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp18)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fTemp16)), LoadVarInst(stack, fTemp17)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp15)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(stack, fTemp24)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp23)), Int32(2047))]))))))))
		DeclareVarInst(stack, "int", iRec25, LoadVarInst(stack, iRec31))
		StoreVarInst(struct, fRec18[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec23))
		DeclareVarInst(stack, "float", fRec19, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp37)), LoadVarInst(stack, fTemp39)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp30), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp40), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(stack, fTemp50)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp49), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp45), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp44), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp32), LoadVarInst(stack, fTemp42)), LoadVarInst(stack, fTemp43)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp41), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp52), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(stack, fRec24))
		DeclareVarInst(stack, "int", iRec21, LoadVarInst(stack, iRec25))
		StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(struct, fRec20[Int32(1)]))
		DeclareVarInst(stack, "int", iRec17, LoadVarInst(stack, iRec21))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec14[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec14[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp56, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec14[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec14[Int32(2)])))))
		DeclareVarInst(stack, "float", fRec12, LoadVarInst(stack, fTemp56))
		DeclareVarInst(stack, "float", fRec13, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec17)), LoadVarInst(stack, fTemp56)))
		StoreVarInst(struct, iRec6[Int32(0)], LoadVarInst(stack, iRec11))
		DeclareVarInst(stack, "float", fRec7, LoadVarInst(stack, fRec15))
		DeclareVarInst(stack, "float", fRec8, LoadVarInst(stack, fRec12))
		DeclareVarInst(stack, "float", fRec9, LoadVarInst(stack, fRec13))
		StoreVarInst(struct, fRec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec7))
		DeclareVarInst(stack, "float", fRec3, LoadVarInst(stack, fRec19))
		DeclareVarInst(stack, "float", fRec4, LoadVarInst(stack, fRec8))
		DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
		StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec3))
		DeclareVarInst(stack, "float", fRec1, LoadVarInst(stack, fRec5))
		StoreVarInst(struct, iRec42[Int32(0)], Int32(0))
		DeclareVarInst(stack, "int", iRec43, LoadVarInst(struct, iRec42[Int32(1)]))
		DeclareVarInst(stack, "float", fRec47, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec38[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec48[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec48[Int32(1)]), LoadVarInst(struct, fRec48[Int32(3)])))))))
		StoreVarInst(struct, fRec58[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec58[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp57, BinopInst("+", LoadVarInst(struct, fRec58[Int32(0)]), Float(-0.0799999982f)))
		DeclareVarInst(stack, "float", fTemp58, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp57)))
		DeclareVarInst(stack, "float", fTemp59, BinopInst("+", LoadVarInst(stack, fTemp58), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp60, CastInst("int", LoadVarInst(stack, fTemp59)))
		DeclareVarInst(stack, "int", iTemp61, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp60))))))
		DeclareVarInst(stack, "float", fTemp62, FunCallInst("floorf", LoadVarInst(stack, fTemp59)))
		DeclareVarInst(stack, "float", fTemp63, BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp62))))
		DeclareVarInst(stack, "float", fTemp64, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp63)))
		DeclareVarInst(stack, "float", fTemp65, BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp62))))
		DeclareVarInst(stack, "float", fTemp66, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp65))))
		DeclareVarInst(stack, "float", fTemp67, BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp62))))
		DeclareVarInst(stack, "float", fTemp68, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp67))))
		DeclareVarInst(stack, "float", fTemp69, BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp62))))
		DeclareVarInst(stack, "float", fTemp70, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp69))))
		DeclareVarInst(stack, "float", fTemp71, BinopInst("-", LoadVarInst(stack, fTemp58), LoadVarInst(stack, fTemp62)))
		DeclareVarInst(stack, "int", iTemp72, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp60), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp73, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp67)))
		DeclareVarInst(stack, "float", fTemp74, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp69))))
		DeclareVarInst(stack, "int", iTemp75, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp60), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp76, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp65)))
		DeclareVarInst(stack, "float", fTemp77, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp67))))
		DeclareVarInst(stack, "float", fTemp78, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp69))))
		DeclareVarInst(stack, "float", fTemp79, BinopInst("*", LoadVarInst(stack, fTemp63), LoadVarInst(stack, fTemp65)))
		DeclareVarInst(stack, "int", iTemp80, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp60), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp81, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp69)))
		DeclareVarInst(stack, "float", fTemp82, BinopInst("*", LoadVarInst(stack, fTemp79), LoadVarInst(stack, fTemp67)))
		DeclareVarInst(stack, "int", iTemp83, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp60), Int32(4)))))))
		StoreVarInst(struct, fRec54[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp61), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp64)), LoadVarInst(stack, fTemp66)), LoadVarInst(stack, fTemp68)), LoadVarInst(stack, fTemp70)), BinopInst("*", LoadVarInst(stack, fTemp71), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp63), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp72), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp73)), LoadVarInst(stack, fTemp74))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp75), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp76)), LoadVarInst(stack, fTemp77)), LoadVarInst(stack, fTemp78))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp79), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp80), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp81)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp82), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp83), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec59[Int32(0)], LoadVarInst(struct, fRec32[Int32(1)]))
		StoreVarInst(struct, fRec60[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec59[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec59[Int32(1)]), LoadVarInst(struct, fRec59[Int32(3)])))))))
		DeclareVarInst(stack, "int", iRec61, Int32(0))
		DeclareVarInst(stack, "float", fTemp84, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp57)))
		DeclareVarInst(stack, "float", fTemp85, BinopInst("+", LoadVarInst(stack, fTemp84), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp86, CastInst("int", LoadVarInst(stack, fTemp85)))
		DeclareVarInst(stack, "int", iTemp87, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp86))))))
		DeclareVarInst(stack, "float", fTemp88, FunCallInst("floorf", LoadVarInst(stack, fTemp85)))
		DeclareVarInst(stack, "float", fTemp89, BinopInst("+", LoadVarInst(stack, fTemp84), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp88))))
		DeclareVarInst(stack, "float", fTemp90, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp89)))
		DeclareVarInst(stack, "float", fTemp91, BinopInst("+", LoadVarInst(stack, fTemp84), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp88))))
		DeclareVarInst(stack, "float", fTemp92, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp91))))
		DeclareVarInst(stack, "float", fTemp93, BinopInst("+", LoadVarInst(stack, fTemp84), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp88))))
		DeclareVarInst(stack, "float", fTemp94, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp93))))
		DeclareVarInst(stack, "float", fTemp95, BinopInst("+", LoadVarInst(stack, fTemp84), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp88))))
		DeclareVarInst(stack, "float", fTemp96, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp95))))
		DeclareVarInst(stack, "float", fTemp97, BinopInst("-", LoadVarInst(stack, fTemp84), LoadVarInst(stack, fTemp88)))
		DeclareVarInst(stack, "int", iTemp98, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp86), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp99, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp93)))
		DeclareVarInst(stack, "float", fTemp100, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp95))))
		DeclareVarInst(stack, "int", iTemp101, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp86), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp102, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp91)))
		DeclareVarInst(stack, "float", fTemp103, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp93))))
		DeclareVarInst(stack, "float", fTemp104, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp95))))
		DeclareVarInst(stack, "float", fTemp105, BinopInst("*", LoadVarInst(stack, fTemp89), LoadVarInst(stack, fTemp91)))
		DeclareVarInst(stack, "int", iTemp106, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp86), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp107, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp95)))
		DeclareVarInst(stack, "float", fTemp108, BinopInst("*", LoadVarInst(stack, fTemp105), LoadVarInst(stack, fTemp93)))
		DeclareVarInst(stack, "int", iTemp109, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp86), Int32(4)))))))
		StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec60[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp90)), LoadVarInst(stack, fTemp92)), LoadVarInst(stack, fTemp94)), LoadVarInst(stack, fTemp96)), BinopInst("*", LoadVarInst(stack, fTemp97), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp89), LoadVarInst(struct, fRec60[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp98), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp99)), LoadVarInst(stack, fTemp100))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec60[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp101), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp102)), LoadVarInst(stack, fTemp103)), LoadVarInst(stack, fTemp104))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp105), LoadVarInst(struct, fRec60[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp106), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp107)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp108), LoadVarInst(struct, fRec60[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp109), Int32(2))), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp110, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow4)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec54[Int32(1)]), LoadVarInst(struct, fVec2[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp111, BinopInst("*", LoadVarInst(stack, fTemp110), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp110))), Float(0.75f)))))))
		DeclareVarInst(stack, "float", fRec55, BinopInst("+", LoadVarInst(struct, fRec54[Int32(1)]), LoadVarInst(stack, fTemp111)))
		DeclareVarInst(stack, "float", fTemp112, BinopInst("+", LoadVarInst(struct, fVec2[Int32(1)]), LoadVarInst(stack, fTemp111)))
		StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp112))
		DeclareVarInst(stack, "float", fRec56, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp64), LoadVarInst(stack, fTemp66)), LoadVarInst(stack, fTemp68)), LoadVarInst(stack, fTemp70)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp61)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp71), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp82), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp83)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp76), LoadVarInst(stack, fTemp77)), LoadVarInst(stack, fTemp78)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp75)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp63), LoadVarInst(stack, fTemp73)), LoadVarInst(stack, fTemp74)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp72)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp79), LoadVarInst(stack, fTemp81)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp80)), Int32(2047))]))))))))
		DeclareVarInst(stack, "int", iRec57, LoadVarInst(stack, iRec61))
		StoreVarInst(struct, fRec50[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec55))
		DeclareVarInst(stack, "float", fRec51, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp90), LoadVarInst(stack, fTemp92)), LoadVarInst(stack, fTemp94)), LoadVarInst(stack, fTemp96)), LoadVarInst(struct, fRec50[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp97), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp105), LoadVarInst(stack, fTemp107)), LoadVarInst(struct, fRec50[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp106), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp102), LoadVarInst(stack, fTemp103)), LoadVarInst(stack, fTemp104)), LoadVarInst(struct, fRec50[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp101), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp89), LoadVarInst(stack, fTemp99)), LoadVarInst(stack, fTemp100)), LoadVarInst(struct, fRec50[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp98), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp108), LoadVarInst(struct, fRec50[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp109), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec52[Int32(0)], LoadVarInst(stack, fRec56))
		DeclareVarInst(stack, "int", iRec53, LoadVarInst(stack, iRec57))
		StoreVarInst(struct, fRec48[Int32(0)], LoadVarInst(struct, fRec52[Int32(1)]))
		DeclareVarInst(stack, "int", iRec49, LoadVarInst(stack, iRec53))
		StoreVarInst(struct, fRec46[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec48[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec46[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec46[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp113, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec46[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec46[Int32(2)])))))
		DeclareVarInst(stack, "float", fRec44, LoadVarInst(stack, fTemp113))
		DeclareVarInst(stack, "float", fRec45, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec49)), LoadVarInst(stack, fTemp113)))
		StoreVarInst(struct, iRec38[Int32(0)], LoadVarInst(stack, iRec43))
		DeclareVarInst(stack, "float", fRec39, LoadVarInst(stack, fRec47))
		DeclareVarInst(stack, "float", fRec40, LoadVarInst(stack, fRec44))
		DeclareVarInst(stack, "float", fRec41, LoadVarInst(stack, fRec45))
		StoreVarInst(struct, fRec34[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec39))
		DeclareVarInst(stack, "float", fRec35, LoadVarInst(stack, fRec51))
		DeclareVarInst(stack, "float", fRec36, LoadVarInst(stack, fRec40))
		DeclareVarInst(stack, "float", fRec37, LoadVarInst(stack, fRec41))
		StoreVarInst(struct, fRec32[Int32(0)], LoadVarInst(stack, fRec35))
		DeclareVarInst(stack, "float", fRec33, LoadVarInst(stack, fRec37))
		StoreVarInst(struct, iRec72[Int32(0)], Int32(0))
		DeclareVarInst(stack, "int", iRec73, LoadVarInst(struct, iRec72[Int32(1)]))
		DeclareVarInst(stack, "float", fRec77, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec68[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec78[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec78[Int32(1)]), LoadVarInst(struct, fRec78[Int32(3)])))))))
		StoreVarInst(struct, fRec88[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec88[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp114, BinopInst("+", LoadVarInst(struct, fRec88[Int32(0)]), Float(-0.0799999982f)))
		DeclareVarInst(stack, "float", fTemp115, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp114)))
		DeclareVarInst(stack, "float", fTemp116, BinopInst("+", LoadVarInst(stack, fTemp115), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp117, CastInst("int", LoadVarInst(stack, fTemp116)))
		DeclareVarInst(stack, "int", iTemp118, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp117))))))
		DeclareVarInst(stack, "float", fTemp119, FunCallInst("floorf", LoadVarInst(stack, fTemp116)))
		DeclareVarInst(stack, "float", fTemp120, BinopInst("+", LoadVarInst(stack, fTemp115), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp119))))
		DeclareVarInst(stack, "float", fTemp121, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp120)))
		DeclareVarInst(stack, "float", fTemp122, BinopInst("+", LoadVarInst(stack, fTemp115), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp119))))
		DeclareVarInst(stack, "float", fTemp123, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp122))))
		DeclareVarInst(stack, "float", fTemp124, BinopInst("+", LoadVarInst(stack, fTemp115), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp119))))
		DeclareVarInst(stack, "float", fTemp125, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp124))))
		DeclareVarInst(stack, "float", fTemp126, BinopInst("+", LoadVarInst(stack, fTemp115), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp119))))
		DeclareVarInst(stack, "float", fTemp127, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp126))))
		DeclareVarInst(stack, "float", fTemp128, BinopInst("-", LoadVarInst(stack, fTemp115), LoadVarInst(stack, fTemp119)))
		DeclareVarInst(stack, "int", iTemp129, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp117), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp130, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp124)))
		DeclareVarInst(stack, "float", fTemp131, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp126))))
		DeclareVarInst(stack, "int", iTemp132, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp117), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp133, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp122)))
		DeclareVarInst(stack, "float", fTemp134, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp124))))
		DeclareVarInst(stack, "float", fTemp135, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp126))))
		DeclareVarInst(stack, "float", fTemp136, BinopInst("*", LoadVarInst(stack, fTemp120), LoadVarInst(stack, fTemp122)))
		DeclareVarInst(stack, "int", iTemp137, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp117), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp138, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp126)))
		DeclareVarInst(stack, "float", fTemp139, BinopInst("*", LoadVarInst(stack, fTemp136), LoadVarInst(stack, fTemp124)))
		DeclareVarInst(stack, "int", iTemp140, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp117), Int32(4)))))))
		StoreVarInst(struct, fRec84[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec64[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp118), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp121)), LoadVarInst(stack, fTemp123)), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp127)), BinopInst("*", LoadVarInst(stack, fTemp128), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp120), LoadVarInst(struct, fRec64[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp129), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp130)), LoadVarInst(stack, fTemp131))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec64[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp132), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp133)), LoadVarInst(stack, fTemp134)), LoadVarInst(stack, fTemp135))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp136), LoadVarInst(struct, fRec64[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp137), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp138)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp139), LoadVarInst(struct, fRec64[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp140), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec89[Int32(0)], LoadVarInst(struct, fRec62[Int32(1)]))
		StoreVarInst(struct, fRec90[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec89[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec89[Int32(1)]), LoadVarInst(struct, fRec89[Int32(3)])))))))
		DeclareVarInst(stack, "int", iRec91, Int32(0))
		DeclareVarInst(stack, "float", fTemp141, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp114)))
		DeclareVarInst(stack, "float", fTemp142, BinopInst("+", LoadVarInst(stack, fTemp141), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp143, CastInst("int", LoadVarInst(stack, fTemp142)))
		DeclareVarInst(stack, "int", iTemp144, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp143))))))
		DeclareVarInst(stack, "float", fTemp145, FunCallInst("floorf", LoadVarInst(stack, fTemp142)))
		DeclareVarInst(stack, "float", fTemp146, BinopInst("+", LoadVarInst(stack, fTemp141), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp145))))
		DeclareVarInst(stack, "float", fTemp147, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp146)))
		DeclareVarInst(stack, "float", fTemp148, BinopInst("+", LoadVarInst(stack, fTemp141), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp145))))
		DeclareVarInst(stack, "float", fTemp149, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp148))))
		DeclareVarInst(stack, "float", fTemp150, BinopInst("+", LoadVarInst(stack, fTemp141), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp145))))
		DeclareVarInst(stack, "float", fTemp151, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp150))))
		DeclareVarInst(stack, "float", fTemp152, BinopInst("+", LoadVarInst(stack, fTemp141), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp145))))
		DeclareVarInst(stack, "float", fTemp153, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp152))))
		DeclareVarInst(stack, "float", fTemp154, BinopInst("-", LoadVarInst(stack, fTemp141), LoadVarInst(stack, fTemp145)))
		DeclareVarInst(stack, "int", iTemp155, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp143), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp156, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp150)))
		DeclareVarInst(stack, "float", fTemp157, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp152))))
		DeclareVarInst(stack, "int", iTemp158, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp143), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp159, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp148)))
		DeclareVarInst(stack, "float", fTemp160, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp150))))
		DeclareVarInst(stack, "float", fTemp161, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp152))))
		DeclareVarInst(stack, "float", fTemp162, BinopInst("*", LoadVarInst(stack, fTemp146), LoadVarInst(stack, fTemp148)))
		DeclareVarInst(stack, "int", iTemp163, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp143), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp164, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp152)))
		DeclareVarInst(stack, "float", fTemp165, BinopInst("*", LoadVarInst(stack, fTemp162), LoadVarInst(stack, fTemp150)))
		DeclareVarInst(stack, "int", iTemp166, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp143), Int32(4)))))))
		StoreVarInst(struct, fVec4[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec90[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp144), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp147)), LoadVarInst(stack, fTemp149)), LoadVarInst(stack, fTemp151)), LoadVarInst(stack, fTemp153)), BinopInst("*", LoadVarInst(stack, fTemp154), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp146), LoadVarInst(struct, fRec90[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp155), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp156)), LoadVarInst(stack, fTemp157))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec90[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp158), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp159)), LoadVarInst(stack, fTemp160)), LoadVarInst(stack, fTemp161))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp162), LoadVarInst(struct, fRec90[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp163), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp164)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp165), LoadVarInst(struct, fRec90[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp166), Int32(2))), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp167, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow6)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec84[Int32(1)]), LoadVarInst(struct, fVec4[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp168, BinopInst("*", LoadVarInst(stack, fTemp167), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp167))), Float(0.75f)))))))
		DeclareVarInst(stack, "float", fRec85, BinopInst("+", LoadVarInst(struct, fRec84[Int32(1)]), LoadVarInst(stack, fTemp168)))
		DeclareVarInst(stack, "float", fTemp169, BinopInst("+", LoadVarInst(struct, fVec4[Int32(1)]), LoadVarInst(stack, fTemp168)))
		StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp169))
		DeclareVarInst(stack, "float", fRec86, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp121), LoadVarInst(stack, fTemp123)), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp127)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp118)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp128), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp139), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp140)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp133), LoadVarInst(stack, fTemp134)), LoadVarInst(stack, fTemp135)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp132)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp120), LoadVarInst(stack, fTemp130)), LoadVarInst(stack, fTemp131)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp129)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp136), LoadVarInst(stack, fTemp138)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp137)), Int32(2047))]))))))))
		DeclareVarInst(stack, "int", iRec87, LoadVarInst(stack, iRec91))
		StoreVarInst(struct, fRec80[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec85))
		DeclareVarInst(stack, "float", fRec81, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp147), LoadVarInst(stack, fTemp149)), LoadVarInst(stack, fTemp151)), LoadVarInst(stack, fTemp153)), LoadVarInst(struct, fRec80[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp144), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp154), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp162), LoadVarInst(stack, fTemp164)), LoadVarInst(struct, fRec80[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp163), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp159), LoadVarInst(stack, fTemp160)), LoadVarInst(stack, fTemp161)), LoadVarInst(struct, fRec80[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp158), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp146), LoadVarInst(stack, fTemp156)), LoadVarInst(stack, fTemp157)), LoadVarInst(struct, fRec80[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp155), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp165), LoadVarInst(struct, fRec80[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp166), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec82[Int32(0)], LoadVarInst(stack, fRec86))
		DeclareVarInst(stack, "int", iRec83, LoadVarInst(stack, iRec87))
		StoreVarInst(struct, fRec78[Int32(0)], LoadVarInst(struct, fRec82[Int32(1)]))
		DeclareVarInst(stack, "int", iRec79, LoadVarInst(stack, iRec83))
		StoreVarInst(struct, fRec76[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec78[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec76[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec76[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp170, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec76[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec76[Int32(2)])))))
		DeclareVarInst(stack, "float", fRec74, LoadVarInst(stack, fTemp170))
		DeclareVarInst(stack, "float", fRec75, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec79)), LoadVarInst(stack, fTemp170)))
		StoreVarInst(struct, iRec68[Int32(0)], LoadVarInst(stack, iRec73))
		DeclareVarInst(stack, "float", fRec69, LoadVarInst(stack, fRec77))
		DeclareVarInst(stack, "float", fRec70, LoadVarInst(stack, fRec74))
		DeclareVarInst(stack, "float", fRec71, LoadVarInst(stack, fRec75))
		StoreVarInst(struct, fRec64[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec69))
		DeclareVarInst(stack, "float", fRec65, LoadVarInst(stack, fRec81))
		DeclareVarInst(stack, "float", fRec66, LoadVarInst(stack, fRec70))
		DeclareVarInst(stack, "float", fRec67, LoadVarInst(stack, fRec71))
		StoreVarInst(struct, fRec62[Int32(0)], LoadVarInst(stack, fRec65))
		DeclareVarInst(stack, "float", fRec63, LoadVarInst(stack, fRec67))
		StoreVarInst(struct, iRec102[Int32(0)], Int32(0))
		DeclareVarInst(stack, "int", iRec103, LoadVarInst(struct, iRec102[Int32(1)]))
		DeclareVarInst(stack, "float", fRec107, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec98[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec108[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec108[Int32(1)]), LoadVarInst(struct, fRec108[Int32(3)])))))))
		StoreVarInst(struct, fRec118[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec118[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp171, BinopInst("+", LoadVarInst(struct, fRec118[Int32(0)]), Float(-0.0799999982f)))
		DeclareVarInst(stack, "float", fTemp172, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp171)))
		DeclareVarInst(stack, "float", fTemp173, BinopInst("+", LoadVarInst(stack, fTemp172), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp174, CastInst("int", LoadVarInst(stack, fTemp173)))
		DeclareVarInst(stack, "int", iTemp175, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp174))))))
		DeclareVarInst(stack, "float", fTemp176, FunCallInst("floorf", LoadVarInst(stack, fTemp173)))
		DeclareVarInst(stack, "float", fTemp177, BinopInst("+", LoadVarInst(stack, fTemp172), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp176))))
		DeclareVarInst(stack, "float", fTemp178, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp177)))
		DeclareVarInst(stack, "float", fTemp179, BinopInst("+", LoadVarInst(stack, fTemp172), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp176))))
		DeclareVarInst(stack, "float", fTemp180, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp179))))
		DeclareVarInst(stack, "float", fTemp181, BinopInst("+", LoadVarInst(stack, fTemp172), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp176))))
		DeclareVarInst(stack, "float", fTemp182, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp181))))
		DeclareVarInst(stack, "float", fTemp183, BinopInst("+", LoadVarInst(stack, fTemp172), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp176))))
		DeclareVarInst(stack, "float", fTemp184, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp183))))
		DeclareVarInst(stack, "float", fTemp185, BinopInst("-", LoadVarInst(stack, fTemp172), LoadVarInst(stack, fTemp176)))
		DeclareVarInst(stack, "int", iTemp186, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp174), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp187, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp181)))
		DeclareVarInst(stack, "float", fTemp188, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp183))))
		DeclareVarInst(stack, "int", iTemp189, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp174), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp190, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp179)))
		DeclareVarInst(stack, "float", fTemp191, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp181))))
		DeclareVarInst(stack, "float", fTemp192, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp183))))
		DeclareVarInst(stack, "float", fTemp193, BinopInst("*", LoadVarInst(stack, fTemp177), LoadVarInst(stack, fTemp179)))
		DeclareVarInst(stack, "int", iTemp194, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp174), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp195, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp183)))
		DeclareVarInst(stack, "float", fTemp196, BinopInst("*", LoadVarInst(stack, fTemp193), LoadVarInst(stack, fTemp181)))
		DeclareVarInst(stack, "int", iTemp197, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp174), Int32(4)))))))
		StoreVarInst(struct, fRec114[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec94[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp175), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp178)), LoadVarInst(stack, fTemp180)), LoadVarInst(stack, fTemp182)), LoadVarInst(stack, fTemp184)), BinopInst("*", LoadVarInst(stack, fTemp185), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp177), LoadVarInst(struct, fRec94[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp186), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp187)), LoadVarInst(stack, fTemp188))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec94[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp189), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp190)), LoadVarInst(stack, fTemp191)), LoadVarInst(stack, fTemp192))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp193), LoadVarInst(struct, fRec94[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp194), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp195)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp196), LoadVarInst(struct, fRec94[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp197), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec119[Int32(0)], LoadVarInst(struct, fRec92[Int32(1)]))
		StoreVarInst(struct, fRec120[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec119[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec119[Int32(1)]), LoadVarInst(struct, fRec119[Int32(3)])))))))
		DeclareVarInst(stack, "int", iRec121, Int32(0))
		DeclareVarInst(stack, "float", fTemp198, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp171)))
		DeclareVarInst(stack, "float", fTemp199, BinopInst("+", LoadVarInst(stack, fTemp198), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp200, CastInst("int", LoadVarInst(stack, fTemp199)))
		DeclareVarInst(stack, "int", iTemp201, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp200))))))
		DeclareVarInst(stack, "float", fTemp202, FunCallInst("floorf", LoadVarInst(stack, fTemp199)))
		DeclareVarInst(stack, "float", fTemp203, BinopInst("+", LoadVarInst(stack, fTemp198), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp202))))
		DeclareVarInst(stack, "float", fTemp204, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp203)))
		DeclareVarInst(stack, "float", fTemp205, BinopInst("+", LoadVarInst(stack, fTemp198), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp202))))
		DeclareVarInst(stack, "float", fTemp206, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp205))))
		DeclareVarInst(stack, "float", fTemp207, BinopInst("+", LoadVarInst(stack, fTemp198), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp202))))
		DeclareVarInst(stack, "float", fTemp208, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp207))))
		DeclareVarInst(stack, "float", fTemp209, BinopInst("+", LoadVarInst(stack, fTemp198), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp202))))
		DeclareVarInst(stack, "float", fTemp210, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp209))))
		DeclareVarInst(stack, "float", fTemp211, BinopInst("-", LoadVarInst(stack, fTemp198), LoadVarInst(stack, fTemp202)))
		DeclareVarInst(stack, "int", iTemp212, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp200), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp213, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp207)))
		DeclareVarInst(stack, "float", fTemp214, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp209))))
		DeclareVarInst(stack, "int", iTemp215, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp200), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp216, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp205)))
		DeclareVarInst(stack, "float", fTemp217, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp207))))
		DeclareVarInst(stack, "float", fTemp218, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp209))))
		DeclareVarInst(stack, "float", fTemp219, BinopInst("*", LoadVarInst(stack, fTemp203), LoadVarInst(stack, fTemp205)))
		DeclareVarInst(stack, "int", iTemp220, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp200), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp221, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp209)))
		DeclareVarInst(stack, "float", fTemp222, BinopInst("*", LoadVarInst(stack, fTemp219), LoadVarInst(stack, fTemp207)))
		DeclareVarInst(stack, "int", iTemp223, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp200), Int32(4)))))))
		StoreVarInst(struct, fVec6[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec120[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp201), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp204)), LoadVarInst(stack, fTemp206)), LoadVarInst(stack, fTemp208)), LoadVarInst(stack, fTemp210)), BinopInst("*", LoadVarInst(stack, fTemp211), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp203), LoadVarInst(struct, fRec120[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp212), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp213)), LoadVarInst(stack, fTemp214))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec120[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp215), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp216)), LoadVarInst(stack, fTemp217)), LoadVarInst(stack, fTemp218))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp219), LoadVarInst(struct, fRec120[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp220), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp221)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp222), LoadVarInst(struct, fRec120[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp223), Int32(2))), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp224, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow8)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec114[Int32(1)]), LoadVarInst(struct, fVec6[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp225, BinopInst("*", LoadVarInst(stack, fTemp224), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp224))), Float(0.75f)))))))
		DeclareVarInst(stack, "float", fRec115, BinopInst("+", LoadVarInst(struct, fRec114[Int32(1)]), LoadVarInst(stack, fTemp225)))
		DeclareVarInst(stack, "float", fTemp226, BinopInst("+", LoadVarInst(struct, fVec6[Int32(1)]), LoadVarInst(stack, fTemp225)))
		StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp226))
		DeclareVarInst(stack, "float", fRec116, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp178), LoadVarInst(stack, fTemp180)), LoadVarInst(stack, fTemp182)), LoadVarInst(stack, fTemp184)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp175)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp185), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp196), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp197)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp190), LoadVarInst(stack, fTemp191)), LoadVarInst(stack, fTemp192)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp189)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp177), LoadVarInst(stack, fTemp187)), LoadVarInst(stack, fTemp188)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp186)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp193), LoadVarInst(stack, fTemp195)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp194)), Int32(2047))]))))))))
		DeclareVarInst(stack, "int", iRec117, LoadVarInst(stack, iRec121))
		StoreVarInst(struct, fRec110[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec115))
		DeclareVarInst(stack, "float", fRec111, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp204), LoadVarInst(stack, fTemp206)), LoadVarInst(stack, fTemp208)), LoadVarInst(stack, fTemp210)), LoadVarInst(struct, fRec110[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp201), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp211), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp219), LoadVarInst(stack, fTemp221)), LoadVarInst(struct, fRec110[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp220), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp216), LoadVarInst(stack, fTemp217)), LoadVarInst(stack, fTemp218)), LoadVarInst(struct, fRec110[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp215), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp203), LoadVarInst(stack, fTemp213)), LoadVarInst(stack, fTemp214)), LoadVarInst(struct, fRec110[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp212), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp222), LoadVarInst(struct, fRec110[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp223), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec112[Int32(0)], LoadVarInst(stack, fRec116))
		DeclareVarInst(stack, "int", iRec113, LoadVarInst(stack, iRec117))
		StoreVarInst(struct, fRec108[Int32(0)], LoadVarInst(struct, fRec112[Int32(1)]))
		DeclareVarInst(stack, "int", iRec109, LoadVarInst(stack, iRec113))
		StoreVarInst(struct, fRec106[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec108[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec106[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec106[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp227, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec106[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec106[Int32(2)])))))
		DeclareVarInst(stack, "float", fRec104, LoadVarInst(stack, fTemp227))
		DeclareVarInst(stack, "float", fRec105, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec109)), LoadVarInst(stack, fTemp227)))
		StoreVarInst(struct, iRec98[Int32(0)], LoadVarInst(stack, iRec103))
		DeclareVarInst(stack, "float", fRec99, LoadVarInst(stack, fRec107))
		DeclareVarInst(stack, "float", fRec100, LoadVarInst(stack, fRec104))
		DeclareVarInst(stack, "float", fRec101, LoadVarInst(stack, fRec105))
		StoreVarInst(struct, fRec94[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec99))
		DeclareVarInst(stack, "float", fRec95, LoadVarInst(stack, fRec111))
		DeclareVarInst(stack, "float", fRec96, LoadVarInst(stack, fRec100))
		DeclareVarInst(stack, "float", fRec97, LoadVarInst(stack, fRec101))
		StoreVarInst(struct, fRec92[Int32(0)], LoadVarInst(stack, fRec95))
		DeclareVarInst(stack, "float", fRec93, LoadVarInst(stack, fRec97))
		DeclareVarInst(stack, "float", fTemp228, BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec1), LoadVarInst(stack, fRec33)), LoadVarInst(stack, fRec63)), LoadVarInst(stack, fRec93)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp228)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp228)))
		StoreVarInst(struct, iRec10[Int32(1)], LoadVarInst(struct, iRec10[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j0, Int32(3))
			BinopInst(">", LoadVarInst(loop, j0), Int32(0))
			StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec29[LoadVarInst(loop, j0)], LoadVarInst(struct, fRec29[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j1, Int32(3))
			BinopInst(">", LoadVarInst(loop, j1), Int32(0))
			StoreVarInst(loop, j1, BinopInst("-", LoadVarInst(loop, j1), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec16[LoadVarInst(loop, j1)], LoadVarInst(struct, fRec16[BinopInst("-", LoadVarInst(loop, j1), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fRec14[Int32(2)], LoadVarInst(struct, fRec14[Int32(1)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, iRec6[Int32(1)], LoadVarInst(struct, iRec6[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, iRec42[Int32(1)], LoadVarInst(struct, iRec42[Int32(0)]))
		StoreVarInst(struct, fRec58[Int32(1)], LoadVarInst(struct, fRec58[Int32(0)]))
		StoreVarInst(struct, fRec54[Int32(1)], LoadVarInst(struct, fRec54[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j2, Int32(3))
			BinopInst(">", LoadVarInst(loop, j2), Int32(0))
			StoreVarInst(loop, j2, BinopInst("-", LoadVarInst(loop, j2), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec59[LoadVarInst(loop, j2)], LoadVarInst(struct, fRec59[BinopInst("-", LoadVarInst(loop, j2), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec52[Int32(1)], LoadVarInst(struct, fRec52[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j3, Int32(3))
			BinopInst(">", LoadVarInst(loop, j3), Int32(0))
			StoreVarInst(loop, j3, BinopInst("-", LoadVarInst(loop, j3), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec48[LoadVarInst(loop, j3)], LoadVarInst(struct, fRec48[BinopInst("-", LoadVarInst(loop, j3), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fRec46[Int32(2)], LoadVarInst(struct, fRec46[Int32(1)]))
		StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
		StoreVarInst(struct, iRec38[Int32(1)], LoadVarInst(struct, iRec38[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, iRec72[Int32(1)], LoadVarInst(struct, iRec72[Int32(0)]))
		StoreVarInst(struct, fRec88[Int32(1)], LoadVarInst(struct, fRec88[Int32(0)]))
		StoreVarInst(struct, fRec84[Int32(1)], LoadVarInst(struct, fRec84[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j4, Int32(3))
			BinopInst(">", LoadVarInst(loop, j4), Int32(0))
			StoreVarInst(loop, j4, BinopInst("-", LoadVarInst(loop, j4), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec89[LoadVarInst(loop, j4)], LoadVarInst(struct, fRec89[BinopInst("-", LoadVarInst(loop, j4), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
		StoreVarInst(struct, fRec82[Int32(1)], LoadVarInst(struct, fRec82[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j5, Int32(3))
			BinopInst(">", LoadVarInst(loop, j5), Int32(0))
			StoreVarInst(loop, j5, BinopInst("-", LoadVarInst(loop, j5), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec78[LoadVarInst(loop, j5)], LoadVarInst(struct, fRec78[BinopInst("-", LoadVarInst(loop, j5), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fRec76[Int32(2)], LoadVarInst(struct, fRec76[Int32(1)]))
		StoreVarInst(struct, fRec76[Int32(1)], LoadVarInst(struct, fRec76[Int32(0)]))
		StoreVarInst(struct, iRec68[Int32(1)], LoadVarInst(struct, iRec68[Int32(0)]))
		StoreVarInst(struct, fRec62[Int32(1)], LoadVarInst(struct, fRec62[Int32(0)]))
		StoreVarInst(struct, iRec102[Int32(1)], LoadVarInst(struct, iRec102[Int32(0)]))
		StoreVarInst(struct, fRec118[Int32(1)], LoadVarInst(struct, fRec118[Int32(0)]))
		StoreVarInst(struct, fRec114[Int32(1)], LoadVarInst(struct, fRec114[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j6, Int32(3))
			BinopInst(">", LoadVarInst(loop, j6), Int32(0))
			StoreVarInst(loop, j6, BinopInst("-", LoadVarInst(loop, j6), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec119[LoadVarInst(loop, j6)], LoadVarInst(struct, fRec119[BinopInst("-", LoadVarInst(loop, j6), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
		StoreVarInst(struct, fRec112[Int32(1)], LoadVarInst(struct, fRec112[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j7, Int32(3))
			BinopInst(">", LoadVarInst(loop, j7), Int32(0))
			StoreVarInst(loop, j7, BinopInst("-", LoadVarInst(loop, j7), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec108[LoadVarInst(loop, j7)], LoadVarInst(struct, fRec108[BinopInst("-", LoadVarInst(loop, j7), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fRec106[Int32(2)], LoadVarInst(struct, fRec106[Int32(1)]))
		StoreVarInst(struct, fRec106[Int32(1)], LoadVarInst(struct, fRec106[Int32(0)]))
		StoreVarInst(struct, iRec98[Int32(1)], LoadVarInst(struct, iRec98[Int32(0)]))
		StoreVarInst(struct, fRec92[Int32(1)], LoadVarInst(struct, fRec92[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower4_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, int, iRec10[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fRec29[4])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec30[2048])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fVec1[2048])
	DeclareVarInst(struct, float, fRec18[2048])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec16[4])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, int, iRec6[2])
	DeclareVarInst(struct, float, fRec2[2048])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, int, iRec42[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec58[2])
	DeclareVarInst(struct, float, fRec54[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec59[4])
	DeclareVarInst(struct, float, fRec60[2048])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fVec3[2048])
	DeclareVarInst(struct, float, fRec50[2048])
	DeclareVarInst(struct, float, fRec52[2])
	DeclareVarInst(struct, float, fRec48[4])
	DeclareVarInst(struct, float, fRec46[3])
	DeclareVarInst(struct, int, iRec38[2])
	DeclareVarInst(struct, float, fRec34[2048])
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, int, iRec72[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, float, fRec88[2])
	DeclareVarInst(struct, float, fRec84[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, float, fRec89[4])
	DeclareVarInst(struct, float, fRec90[2048])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, float, fVec5[2048])
	DeclareVarInst(struct, float, fRec80[2048])
	DeclareVarInst(struct, float, fRec82[2])
	DeclareVarInst(struct, float, fRec78[4])
	DeclareVarInst(struct, float, fRec76[3])
	DeclareVarInst(struct, int, iRec68[2])
	DeclareVarInst(struct, float, fRec64[2048])
	DeclareVarInst(struct, float, fRec62[2])
	DeclareVarInst(struct, int, iRec102[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider10)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider11)
	DeclareVarInst(struct, float, fRec118[2])
	DeclareVarInst(struct, float, fRec114[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider12)
	DeclareVarInst(struct, float, fRec119[4])
	DeclareVarInst(struct, float, fRec120[2048])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, float, fVec7[2048])
	DeclareVarInst(struct, float, fRec110[2048])
	DeclareVarInst(struct, float, fRec112[2])
	DeclareVarInst(struct, float, fRec108[4])
	DeclareVarInst(struct, float, fRec106[3])
	DeclareVarInst(struct, int, iRec98[2])
	DeclareVarInst(struct, float, fRec94[2048])
	DeclareVarInst(struct, float, fRec92[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, FunCallInst("tanf", BinopInst("/", Float(1570.79639f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst1)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(0.5f)), LoadVarInst(struct, fConst1)), Float(1.0f))))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("*", Float(0.000441176468f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, BinopInst("*", Float(0.0010294118f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst7, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(-0.5f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst8, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst1))))))
	StoreVarInst(struct, fConst9, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst2)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(220.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(330.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider10, CastInst("FAUSTFLOAT", Double(550.0f)))
	StoreVarInst(struct, fHslider11, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider12, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec10[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(4))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2048))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2048))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2048))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(4))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(3))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[LoadVarInst(loop, l13)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2048))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec42[LoadVarInst(loop, l16)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec58[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec54[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(4))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2048))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2048))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2048))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec52[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(4))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(3))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec38[LoadVarInst(loop, l27)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2048))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec72[LoadVarInst(loop, l30)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec88[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec84[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(4))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec89[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2048))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec90[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2048))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2048))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec80[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec82[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(4))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec78[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(3))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec76[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec68[LoadVarInst(loop, l41)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2048))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec64[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(2))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec62[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(2))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec102[LoadVarInst(loop, l44)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(2))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec118[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec114[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(4))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec119[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(2048))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec120[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2048))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(2048))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec110[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec112[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(4))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec108[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(3))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec106[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(2))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec98[LoadVarInst(loop, l55)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(2048))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec94[LoadVarInst(loop, l56)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(2))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec92[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "int", iSlow1, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider2))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider4)), CastInst("float", LoadVarInst(struct, fHslider5)))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider6))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider7)), CastInst("float", LoadVarInst(struct, fHslider8)))))
	DeclareVarInst(stack, "int", iSlow6, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider9))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider10)), CastInst("float", LoadVarInst(struct, fHslider11)))))
	DeclareVarInst(stack, "int", iSlow8, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider12))), Int32(0)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec10[Int32(0)], Int32(0))
			DeclareVarInst(stack, "int", iRec11, LoadVarInst(struct, iRec10[Int32(1)]))
			DeclareVarInst(stack, "float", fRec15, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec6[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec16[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fRec16[Int32(3)])))))))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec26[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("+", LoadVarInst(struct, fRec26[Int32(0)]), Float(-0.0799999982f)))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp0)))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(stack, fTemp1), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp3, CastInst("int", LoadVarInst(stack, fTemp2)))
			DeclareVarInst(stack, "int", iTemp4, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp3))))))
			DeclareVarInst(stack, "float", fTemp5, FunCallInst("floorf", LoadVarInst(stack, fTemp2)))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp5))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp6)))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp5))))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp8))))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp5))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp10))))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp5))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("-", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp5)))
			DeclareVarInst(stack, "int", iTemp15, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp3), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "int", iTemp18, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp3), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp8)))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp10))))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("*", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fTemp8)))
			DeclareVarInst(stack, "int", iTemp23, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp3), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "int", iTemp26, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp3), Int32(4)))))))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp9)), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), BinopInst("*", LoadVarInst(stack, fTemp14), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp6), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp15), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp16)), LoadVarInst(stack, fTemp17))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp18), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp23), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp24)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp26), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec28[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec28[Int32(1)]))))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", Float(0.00100000005f), FunCallInst("min_f", Float(1.0f), BinopInst("*", Float(3000.0f), FunCallInst("fabsf", BinopInst("-", LoadVarInst(struct, fRec28[Int32(0)]), LoadVarInst(struct, fRec28[Int32(1)]))))))))
			StoreVarInst(struct, fRec29[Int32(0)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec30[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec29[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec29[Int32(1)]), LoadVarInst(struct, fRec29[Int32(3)])))))))
			DeclareVarInst(stack, "int", iRec31, Int32(0))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp0)))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("+", LoadVarInst(stack, fTemp27), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp29, CastInst("int", LoadVarInst(stack, fTemp28)))
			DeclareVarInst(stack, "int", iTemp30, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp29))))))
			DeclareVarInst(stack, "float", fTemp31, FunCallInst("floorf", LoadVarInst(stack, fTemp28)))
			DeclareVarInst(stack, "float", fTemp32, BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp31))))
			DeclareVarInst(stack, "float", fTemp33, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp32)))
			DeclareVarInst(stack, "float", fTemp34, BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp31))))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp31))))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp36))))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp31))))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp38))))
			DeclareVarInst(stack, "float", fTemp40, BinopInst("-", LoadVarInst(stack, fTemp27), LoadVarInst(stack, fTemp31)))
			DeclareVarInst(stack, "int", iTemp41, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp29), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp36)))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp38))))
			DeclareVarInst(stack, "int", iTemp44, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp29), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp45, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp34)))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp36))))
			DeclareVarInst(stack, "float", fTemp47, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp38))))
			DeclareVarInst(stack, "float", fTemp48, BinopInst("*", LoadVarInst(stack, fTemp32), LoadVarInst(stack, fTemp34)))
			DeclareVarInst(stack, "int", iTemp49, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp29), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp50, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp38)))
			DeclareVarInst(stack, "float", fTemp51, BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(stack, fTemp36)))
			DeclareVarInst(stack, "int", iTemp52, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp29), Int32(4)))))))
			StoreVarInst(struct, fVec0[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp30), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp33)), LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp37)), LoadVarInst(stack, fTemp39)), BinopInst("*", LoadVarInst(stack, fTemp40), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp32), LoadVarInst(struct, fRec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp41), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp42)), LoadVarInst(stack, fTemp43))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp44), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(struct, fRec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp49), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp50)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(struct, fRec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp52), Int32(2))), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp53, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow1)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fVec0[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("*", LoadVarInst(stack, fTemp53), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp53))), Float(0.75f)))))))
			DeclareVarInst(stack, "float", fRec23, BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(stack, fTemp54)))
			DeclareVarInst(stack, "float", fTemp55, BinopInst("+", LoadVarInst(struct, fVec0[Int32(1)]), LoadVarInst(stack, fTemp54)))
			StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp55))
			DeclareVarInst(stack, "float", fRec24, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp9)), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp4)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp14), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp26)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp18)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fTemp16)), LoadVarInst(stack, fTemp17)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp15)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(stack, fTemp24)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp23)), Int32(2047))]))))))))
			DeclareVarInst(stack, "int", iRec25, LoadVarInst(stack, iRec31))
			StoreVarInst(struct, fRec18[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec23))
			DeclareVarInst(stack, "float", fRec19, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp37)), LoadVarInst(stack, fTemp39)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp30), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp40), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(stack, fTemp50)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp49), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp45), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp44), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp32), LoadVarInst(stack, fTemp42)), LoadVarInst(stack, fTemp43)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp41), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp52), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(stack, fRec24))
			DeclareVarInst(stack, "int", iRec21, LoadVarInst(stack, iRec25))
			StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(struct, fRec20[Int32(1)]))
			DeclareVarInst(stack, "int", iRec17, LoadVarInst(stack, iRec21))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec14[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec14[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp56, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec14[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec14[Int32(2)])))))
			DeclareVarInst(stack, "float", fRec12, LoadVarInst(stack, fTemp56))
			DeclareVarInst(stack, "float", fRec13, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec17)), LoadVarInst(stack, fTemp56)))
			StoreVarInst(struct, iRec6[Int32(0)], LoadVarInst(stack, iRec11))
			DeclareVarInst(stack, "float", fRec7, LoadVarInst(stack, fRec15))
			DeclareVarInst(stack, "float", fRec8, LoadVarInst(stack, fRec12))
			DeclareVarInst(stack, "float", fRec9, LoadVarInst(stack, fRec13))
			StoreVarInst(struct, fRec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec7))
			DeclareVarInst(stack, "float", fRec3, LoadVarInst(stack, fRec19))
			DeclareVarInst(stack, "float", fRec4, LoadVarInst(stack, fRec8))
			DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
			StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec3))
			DeclareVarInst(stack, "float", fRec1, LoadVarInst(stack, fRec5))
			StoreVarInst(struct, iRec42[Int32(0)], Int32(0))
			DeclareVarInst(stack, "int", iRec43, LoadVarInst(struct, iRec42[Int32(1)]))
			DeclareVarInst(stack, "float", fRec47, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec38[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec48[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec48[Int32(1)]), LoadVarInst(struct, fRec48[Int32(3)])))))))
			StoreVarInst(struct, fRec58[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec58[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp57, BinopInst("+", LoadVarInst(struct, fRec58[Int32(0)]), Float(-0.0799999982f)))
			DeclareVarInst(stack, "float", fTemp58, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp57)))
			DeclareVarInst(stack, "float", fTemp59, BinopInst("+", LoadVarInst(stack, fTemp58), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp60, CastInst("int", LoadVarInst(stack, fTemp59)))
			DeclareVarInst(stack, "int", iTemp61, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp60))))))
			DeclareVarInst(stack, "float", fTemp62, FunCallInst("floorf", LoadVarInst(stack, fTemp59)))
			DeclareVarInst(stack, "float", fTemp63, BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp62))))
			DeclareVarInst(stack, "float", fTemp64, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp63)))
			DeclareVarInst(stack, "float", fTemp65, BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp62))))
			DeclareVarInst(stack, "float", fTemp66, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp65))))
			DeclareVarInst(stack, "float", fTemp67, BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp62))))
			DeclareVarInst(stack, "float", fTemp68, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp67))))
			DeclareVarInst(stack, "float", fTemp69, BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp62))))
			DeclareVarInst(stack, "float", fTemp70, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp69))))
			DeclareVarInst(stack, "float", fTemp71, BinopInst("-", LoadVarInst(stack, fTemp58), LoadVarInst(stack, fTemp62)))
			DeclareVarInst(stack, "int", iTemp72, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp60), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp73, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp67)))
			DeclareVarInst(stack, "float", fTemp74, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp69))))
			DeclareVarInst(stack, "int", iTemp75, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp60), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp76, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp65)))
			DeclareVarInst(stack, "float", fTemp77, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp67))))
			DeclareVarInst(stack, "float", fTemp78, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp69))))
			DeclareVarInst(stack, "float", fTemp79, BinopInst("*", LoadVarInst(stack, fTemp63), LoadVarInst(stack, fTemp65)))
			DeclareVarInst(stack, "int", iTemp80, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp60), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp81, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp69)))
			DeclareVarInst(stack, "float", fTemp82, BinopInst("*", LoadVarInst(stack, fTemp79), LoadVarInst(stack, fTemp67)))
			DeclareVarInst(stack, "int", iTemp83, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp60), Int32(4)))))))
			StoreVarInst(struct, fRec54[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp61), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp64)), LoadVarInst(stack, fTemp66)), LoadVarInst(stack, fTemp68)), LoadVarInst(stack, fTemp70)), BinopInst("*", LoadVarInst(stack, fTemp71), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp63), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp72), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp73)), LoadVarInst(stack, fTemp74))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp75), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp76)), LoadVarInst(stack, fTemp77)), LoadVarInst(stack, fTemp78))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp79), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp80), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp81)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp82), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp83), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec59[Int32(0)], LoadVarInst(struct, fRec32[Int32(1)]))
			StoreVarInst(struct, fRec60[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec59[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec59[Int32(1)]), LoadVarInst(struct, fRec59[Int32(3)])))))))
			DeclareVarInst(stack, "int", iRec61, Int32(0))
			DeclareVarInst(stack, "float", fTemp84, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp57)))
			DeclareVarInst(stack, "float", fTemp85, BinopInst("+", LoadVarInst(stack, fTemp84), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp86, CastInst("int", LoadVarInst(stack, fTemp85)))
			DeclareVarInst(stack, "int", iTemp87, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp86))))))
			DeclareVarInst(stack, "float", fTemp88, FunCallInst("floorf", LoadVarInst(stack, fTemp85)))
			DeclareVarInst(stack, "float", fTemp89, BinopInst("+", LoadVarInst(stack, fTemp84), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp88))))
			DeclareVarInst(stack, "float", fTemp90, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp89)))
			DeclareVarInst(stack, "float", fTemp91, BinopInst("+", LoadVarInst(stack, fTemp84), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp88))))
			DeclareVarInst(stack, "float", fTemp92, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp91))))
			DeclareVarInst(stack, "float", fTemp93, BinopInst("+", LoadVarInst(stack, fTemp84), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp88))))
			DeclareVarInst(stack, "float", fTemp94, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp93))))
			DeclareVarInst(stack, "float", fTemp95, BinopInst("+", LoadVarInst(stack, fTemp84), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp88))))
			DeclareVarInst(stack, "float", fTemp96, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp95))))
			DeclareVarInst(stack, "float", fTemp97, BinopInst("-", LoadVarInst(stack, fTemp84), LoadVarInst(stack, fTemp88)))
			DeclareVarInst(stack, "int", iTemp98, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp86), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp99, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp93)))
			DeclareVarInst(stack, "float", fTemp100, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp95))))
			DeclareVarInst(stack, "int", iTemp101, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp86), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp102, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp91)))
			DeclareVarInst(stack, "float", fTemp103, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp93))))
			DeclareVarInst(stack, "float", fTemp104, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp95))))
			DeclareVarInst(stack, "float", fTemp105, BinopInst("*", LoadVarInst(stack, fTemp89), LoadVarInst(stack, fTemp91)))
			DeclareVarInst(stack, "int", iTemp106, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp86), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp107, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp95)))
			DeclareVarInst(stack, "float", fTemp108, BinopInst("*", LoadVarInst(stack, fTemp105), LoadVarInst(stack, fTemp93)))
			DeclareVarInst(stack, "int", iTemp109, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp86), Int32(4)))))))
			StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec60[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp90)), LoadVarInst(stack, fTemp92)), LoadVarInst(stack, fTemp94)), LoadVarInst(stack, fTemp96)), BinopInst("*", LoadVarInst(stack, fTemp97), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp89), LoadVarInst(struct, fRec60[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp98), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp99)), LoadVarInst(stack, fTemp100))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec60[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp101), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp102)), LoadVarInst(stack, fTemp103)), LoadVarInst(stack, fTemp104))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp105), LoadVarInst(struct, fRec60[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp106), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp107)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp108), LoadVarInst(struct, fRec60[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp109), Int32(2))), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp110, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow4)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec54[Int32(1)]), LoadVarInst(struct, fVec2[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp111, BinopInst("*", LoadVarInst(stack, fTemp110), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp110))), Float(0.75f)))))))
			DeclareVarInst(stack, "float", fRec55, BinopInst("+", LoadVarInst(struct, fRec54[Int32(1)]), LoadVarInst(stack, fTemp111)))
			DeclareVarInst(stack, "float", fTemp112, BinopInst("+", LoadVarInst(struct, fVec2[Int32(1)]), LoadVarInst(stack, fTemp111)))
			StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp112))
			DeclareVarInst(stack, "float", fRec56, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp64), LoadVarInst(stack, fTemp66)), LoadVarInst(stack, fTemp68)), LoadVarInst(stack, fTemp70)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp61)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp71), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp82), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp83)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp76), LoadVarInst(stack, fTemp77)), LoadVarInst(stack, fTemp78)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp75)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp63), LoadVarInst(stack, fTemp73)), LoadVarInst(stack, fTemp74)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp72)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp79), LoadVarInst(stack, fTemp81)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp80)), Int32(2047))]))))))))
			DeclareVarInst(stack, "int", iRec57, LoadVarInst(stack, iRec61))
			StoreVarInst(struct, fRec50[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec55))
			DeclareVarInst(stack, "float", fRec51, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp90), LoadVarInst(stack, fTemp92)), LoadVarInst(stack, fTemp94)), LoadVarInst(stack, fTemp96)), LoadVarInst(struct, fRec50[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp97), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp105), LoadVarInst(stack, fTemp107)), LoadVarInst(struct, fRec50[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp106), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp102), LoadVarInst(stack, fTemp103)), LoadVarInst(stack, fTemp104)), LoadVarInst(struct, fRec50[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp101), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp89), LoadVarInst(stack, fTemp99)), LoadVarInst(stack, fTemp100)), LoadVarInst(struct, fRec50[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp98), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp108), LoadVarInst(struct, fRec50[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp109), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec52[Int32(0)], LoadVarInst(stack, fRec56))
			DeclareVarInst(stack, "int", iRec53, LoadVarInst(stack, iRec57))
			StoreVarInst(struct, fRec48[Int32(0)], LoadVarInst(struct, fRec52[Int32(1)]))
			DeclareVarInst(stack, "int", iRec49, LoadVarInst(stack, iRec53))
			StoreVarInst(struct, fRec46[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec48[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec46[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec46[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp113, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec46[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec46[Int32(2)])))))
			DeclareVarInst(stack, "float", fRec44, LoadVarInst(stack, fTemp113))
			DeclareVarInst(stack, "float", fRec45, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec49)), LoadVarInst(stack, fTemp113)))
			StoreVarInst(struct, iRec38[Int32(0)], LoadVarInst(stack, iRec43))
			DeclareVarInst(stack, "float", fRec39, LoadVarInst(stack, fRec47))
			DeclareVarInst(stack, "float", fRec40, LoadVarInst(stack, fRec44))
			DeclareVarInst(stack, "float", fRec41, LoadVarInst(stack, fRec45))
			StoreVarInst(struct, fRec34[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec39))
			DeclareVarInst(stack, "float", fRec35, LoadVarInst(stack, fRec51))
			DeclareVarInst(stack, "float", fRec36, LoadVarInst(stack, fRec40))
			DeclareVarInst(stack, "float", fRec37, LoadVarInst(stack, fRec41))
			StoreVarInst(struct, fRec32[Int32(0)], LoadVarInst(stack, fRec35))
			DeclareVarInst(stack, "float", fRec33, LoadVarInst(stack, fRec37))
			StoreVarInst(struct, iRec72[Int32(0)], Int32(0))
			DeclareVarInst(stack, "int", iRec73, LoadVarInst(struct, iRec72[Int32(1)]))
			DeclareVarInst(stack, "float", fRec77, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec68[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec78[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec78[Int32(1)]), LoadVarInst(struct, fRec78[Int32(3)])))))))
			StoreVarInst(struct, fRec88[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec88[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp114, BinopInst("+", LoadVarInst(struct, fRec88[Int32(0)]), Float(-0.0799999982f)))
			DeclareVarInst(stack, "float", fTemp115, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp114)))
			DeclareVarInst(stack, "float", fTemp116, BinopInst("+", LoadVarInst(stack, fTemp115), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp117, CastInst("int", LoadVarInst(stack, fTemp116)))
			DeclareVarInst(stack, "int", iTemp118, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp117))))))
			DeclareVarInst(stack, "float", fTemp119, FunCallInst("floorf", LoadVarInst(stack, fTemp116)))
			DeclareVarInst(stack, "float", fTemp120, BinopInst("+", LoadVarInst(stack, fTemp115), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp119))))
			DeclareVarInst(stack, "float", fTemp121, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp120)))
			DeclareVarInst(stack, "float", fTemp122, BinopInst("+", LoadVarInst(stack, fTemp115), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp119))))
			DeclareVarInst(stack, "float", fTemp123, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp122))))
			DeclareVarInst(stack, "float", fTemp124, BinopInst("+", LoadVarInst(stack, fTemp115), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp119))))
			DeclareVarInst(stack, "float", fTemp125, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp124))))
			DeclareVarInst(stack, "float", fTemp126, BinopInst("+", LoadVarInst(stack, fTemp115), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp119))))
			DeclareVarInst(stack, "float", fTemp127, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp126))))
			DeclareVarInst(stack, "float", fTemp128, BinopInst("-", LoadVarInst(stack, fTemp115), LoadVarInst(stack, fTemp119)))
			DeclareVarInst(stack, "int", iTemp129, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp117), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp130, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp124)))
			DeclareVarInst(stack, "float", fTemp131, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp126))))
			DeclareVarInst(stack, "int", iTemp132, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp117), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp133, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp122)))
			DeclareVarInst(stack, "float", fTemp134, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp124))))
			DeclareVarInst(stack, "float", fTemp135, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp126))))
			DeclareVarInst(stack, "float", fTemp136, BinopInst("*", LoadVarInst(stack, fTemp120), LoadVarInst(stack, fTemp122)))
			DeclareVarInst(stack, "int", iTemp137, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp117), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp138, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp126)))
			DeclareVarInst(stack, "float", fTemp139, BinopInst("*", LoadVarInst(stack, fTemp136), LoadVarInst(stack, fTemp124)))
			DeclareVarInst(stack, "int", iTemp140, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp117), Int32(4)))))))
			StoreVarInst(struct, fRec84[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec64[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp118), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp121)), LoadVarInst(stack, fTemp123)), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp127)), BinopInst("*", LoadVarInst(stack, fTemp128), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp120), LoadVarInst(struct, fRec64[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp129), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp130)), LoadVarInst(stack, fTemp131))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec64[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp132), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp133)), LoadVarInst(stack, fTemp134)), LoadVarInst(stack, fTemp135))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp136), LoadVarInst(struct, fRec64[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp137), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp138)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp139), LoadVarInst(struct, fRec64[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp140), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec89[Int32(0)], LoadVarInst(struct, fRec62[Int32(1)]))
			StoreVarInst(struct, fRec90[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec89[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec89[Int32(1)]), LoadVarInst(struct, fRec89[Int32(3)])))))))
			DeclareVarInst(stack, "int", iRec91, Int32(0))
			DeclareVarInst(stack, "float", fTemp141, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp114)))
			DeclareVarInst(stack, "float", fTemp142, BinopInst("+", LoadVarInst(stack, fTemp141), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp143, CastInst("int", LoadVarInst(stack, fTemp142)))
			DeclareVarInst(stack, "int", iTemp144, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp143))))))
			DeclareVarInst(stack, "float", fTemp145, FunCallInst("floorf", LoadVarInst(stack, fTemp142)))
			DeclareVarInst(stack, "float", fTemp146, BinopInst("+", LoadVarInst(stack, fTemp141), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp145))))
			DeclareVarInst(stack, "float", fTemp147, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp146)))
			DeclareVarInst(stack, "float", fTemp148, BinopInst("+", LoadVarInst(stack, fTemp141), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp145))))
			DeclareVarInst(stack, "float", fTemp149, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp148))))
			DeclareVarInst(stack, "float", fTemp150, BinopInst("+", LoadVarInst(stack, fTemp141), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp145))))
			DeclareVarInst(stack, "float", fTemp151, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp150))))
			DeclareVarInst(stack, "float", fTemp152, BinopInst("+", LoadVarInst(stack, fTemp141), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp145))))
			DeclareVarInst(stack, "float", fTemp153, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp152))))
			DeclareVarInst(stack, "float", fTemp154, BinopInst("-", LoadVarInst(stack, fTemp141), LoadVarInst(stack, fTemp145)))
			DeclareVarInst(stack, "int", iTemp155, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp143), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp156, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp150)))
			DeclareVarInst(stack, "float", fTemp157, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp152))))
			DeclareVarInst(stack, "int", iTemp158, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp143), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp159, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp148)))
			DeclareVarInst(stack, "float", fTemp160, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp150))))
			DeclareVarInst(stack, "float", fTemp161, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp152))))
			DeclareVarInst(stack, "float", fTemp162, BinopInst("*", LoadVarInst(stack, fTemp146), LoadVarInst(stack, fTemp148)))
			DeclareVarInst(stack, "int", iTemp163, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp143), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp164, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp152)))
			DeclareVarInst(stack, "float", fTemp165, BinopInst("*", LoadVarInst(stack, fTemp162), LoadVarInst(stack, fTemp150)))
			DeclareVarInst(stack, "int", iTemp166, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp143), Int32(4)))))))
			StoreVarInst(struct, fVec4[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec90[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp144), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp147)), LoadVarInst(stack, fTemp149)), LoadVarInst(stack, fTemp151)), LoadVarInst(stack, fTemp153)), BinopInst("*", LoadVarInst(stack, fTemp154), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp146), LoadVarInst(struct, fRec90[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp155), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp156)), LoadVarInst(stack, fTemp157))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec90[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp158), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp159)), LoadVarInst(stack, fTemp160)), LoadVarInst(stack, fTemp161))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp162), LoadVarInst(struct, fRec90[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp163), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp164)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp165), LoadVarInst(struct, fRec90[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp166), Int32(2))), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp167, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow6)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec84[Int32(1)]), LoadVarInst(struct, fVec4[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp168, BinopInst("*", LoadVarInst(stack, fTemp167), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp167))), Float(0.75f)))))))
			DeclareVarInst(stack, "float", fRec85, BinopInst("+", LoadVarInst(struct, fRec84[Int32(1)]), LoadVarInst(stack, fTemp168)))
			DeclareVarInst(stack, "float", fTemp169, BinopInst("+", LoadVarInst(struct, fVec4[Int32(1)]), LoadVarInst(stack, fTemp168)))
			StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp169))
			DeclareVarInst(stack, "float", fRec86, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp121), LoadVarInst(stack, fTemp123)), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp127)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp118)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp128), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp139), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp140)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp133), LoadVarInst(stack, fTemp134)), LoadVarInst(stack, fTemp135)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp132)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp120), LoadVarInst(stack, fTemp130)), LoadVarInst(stack, fTemp131)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp129)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp136), LoadVarInst(stack, fTemp138)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp137)), Int32(2047))]))))))))
			DeclareVarInst(stack, "int", iRec87, LoadVarInst(stack, iRec91))
			StoreVarInst(struct, fRec80[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec85))
			DeclareVarInst(stack, "float", fRec81, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp147), LoadVarInst(stack, fTemp149)), LoadVarInst(stack, fTemp151)), LoadVarInst(stack, fTemp153)), LoadVarInst(struct, fRec80[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp144), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp154), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp162), LoadVarInst(stack, fTemp164)), LoadVarInst(struct, fRec80[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp163), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp159), LoadVarInst(stack, fTemp160)), LoadVarInst(stack, fTemp161)), LoadVarInst(struct, fRec80[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp158), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp146), LoadVarInst(stack, fTemp156)), LoadVarInst(stack, fTemp157)), LoadVarInst(struct, fRec80[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp155), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp165), LoadVarInst(struct, fRec80[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp166), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec82[Int32(0)], LoadVarInst(stack, fRec86))
			DeclareVarInst(stack, "int", iRec83, LoadVarInst(stack, iRec87))
			StoreVarInst(struct, fRec78[Int32(0)], LoadVarInst(struct, fRec82[Int32(1)]))
			DeclareVarInst(stack, "int", iRec79, LoadVarInst(stack, iRec83))
			StoreVarInst(struct, fRec76[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec78[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec76[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec76[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp170, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec76[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec76[Int32(2)])))))
			DeclareVarInst(stack, "float", fRec74, LoadVarInst(stack, fTemp170))
			DeclareVarInst(stack, "float", fRec75, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec79)), LoadVarInst(stack, fTemp170)))
			StoreVarInst(struct, iRec68[Int32(0)], LoadVarInst(stack, iRec73))
			DeclareVarInst(stack, "float", fRec69, LoadVarInst(stack, fRec77))
			DeclareVarInst(stack, "float", fRec70, LoadVarInst(stack, fRec74))
			DeclareVarInst(stack, "float", fRec71, LoadVarInst(stack, fRec75))
			StoreVarInst(struct, fRec64[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec69))
			DeclareVarInst(stack, "float", fRec65, LoadVarInst(stack, fRec81))
			DeclareVarInst(stack, "float", fRec66, LoadVarInst(stack, fRec70))
			DeclareVarInst(stack, "float", fRec67, LoadVarInst(stack, fRec71))
			StoreVarInst(struct, fRec62[Int32(0)], LoadVarInst(stack, fRec65))
			DeclareVarInst(stack, "float", fRec63, LoadVarInst(stack, fRec67))
			StoreVarInst(struct, iRec102[Int32(0)], Int32(0))
			DeclareVarInst(stack, "int", iRec103, LoadVarInst(struct, iRec102[Int32(1)]))
			DeclareVarInst(stack, "float", fRec107, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec98[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec108[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec108[Int32(1)]), LoadVarInst(struct, fRec108[Int32(3)])))))))
			StoreVarInst(struct, fRec118[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec118[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp171, BinopInst("+", LoadVarInst(struct, fRec118[Int32(0)]), Float(-0.0799999982f)))
			DeclareVarInst(stack, "float", fTemp172, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp171)))
			DeclareVarInst(stack, "float", fTemp173, BinopInst("+", LoadVarInst(stack, fTemp172), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp174, CastInst("int", LoadVarInst(stack, fTemp173)))
			DeclareVarInst(stack, "int", iTemp175, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp174))))))
			DeclareVarInst(stack, "float", fTemp176, FunCallInst("floorf", LoadVarInst(stack, fTemp173)))
			DeclareVarInst(stack, "float", fTemp177, BinopInst("+", LoadVarInst(stack, fTemp172), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp176))))
			DeclareVarInst(stack, "float", fTemp178, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp177)))
			DeclareVarInst(stack, "float", fTemp179, BinopInst("+", LoadVarInst(stack, fTemp172), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp176))))
			DeclareVarInst(stack, "float", fTemp180, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp179))))
			DeclareVarInst(stack, "float", fTemp181, BinopInst("+", LoadVarInst(stack, fTemp172), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp176))))
			DeclareVarInst(stack, "float", fTemp182, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp181))))
			DeclareVarInst(stack, "float", fTemp183, BinopInst("+", LoadVarInst(stack, fTemp172), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp176))))
			DeclareVarInst(stack, "float", fTemp184, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp183))))
			DeclareVarInst(stack, "float", fTemp185, BinopInst("-", LoadVarInst(stack, fTemp172), LoadVarInst(stack, fTemp176)))
			DeclareVarInst(stack, "int", iTemp186, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp174), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp187, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp181)))
			DeclareVarInst(stack, "float", fTemp188, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp183))))
			DeclareVarInst(stack, "int", iTemp189, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp174), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp190, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp179)))
			DeclareVarInst(stack, "float", fTemp191, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp181))))
			DeclareVarInst(stack, "float", fTemp192, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp183))))
			DeclareVarInst(stack, "float", fTemp193, BinopInst("*", LoadVarInst(stack, fTemp177), LoadVarInst(stack, fTemp179)))
			DeclareVarInst(stack, "int", iTemp194, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp174), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp195, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp183)))
			DeclareVarInst(stack, "float", fTemp196, BinopInst("*", LoadVarInst(stack, fTemp193), LoadVarInst(stack, fTemp181)))
			DeclareVarInst(stack, "int", iTemp197, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp174), Int32(4)))))))
			StoreVarInst(struct, fRec114[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec94[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp175), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp178)), LoadVarInst(stack, fTemp180)), LoadVarInst(stack, fTemp182)), LoadVarInst(stack, fTemp184)), BinopInst("*", LoadVarInst(stack, fTemp185), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp177), LoadVarInst(struct, fRec94[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp186), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp187)), LoadVarInst(stack, fTemp188))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec94[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp189), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp190)), LoadVarInst(stack, fTemp191)), LoadVarInst(stack, fTemp192))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp193), LoadVarInst(struct, fRec94[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp194), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp195)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp196), LoadVarInst(struct, fRec94[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp197), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec119[Int32(0)], LoadVarInst(struct, fRec92[Int32(1)]))
			StoreVarInst(struct, fRec120[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec119[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec119[Int32(1)]), LoadVarInst(struct, fRec119[Int32(3)])))))))
			DeclareVarInst(stack, "int", iRec121, Int32(0))
			DeclareVarInst(stack, "float", fTemp198, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp171)))
			DeclareVarInst(stack, "float", fTemp199, BinopInst("+", LoadVarInst(stack, fTemp198), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp200, CastInst("int", LoadVarInst(stack, fTemp199)))
			DeclareVarInst(stack, "int", iTemp201, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp200))))))
			DeclareVarInst(stack, "float", fTemp202, FunCallInst("floorf", LoadVarInst(stack, fTemp199)))
			DeclareVarInst(stack, "float", fTemp203, BinopInst("+", LoadVarInst(stack, fTemp198), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp202))))
			DeclareVarInst(stack, "float", fTemp204, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp203)))
			DeclareVarInst(stack, "float", fTemp205, BinopInst("+", LoadVarInst(stack, fTemp198), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp202))))
			DeclareVarInst(stack, "float", fTemp206, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp205))))
			DeclareVarInst(stack, "float", fTemp207, BinopInst("+", LoadVarInst(stack, fTemp198), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp202))))
			DeclareVarInst(stack, "float", fTemp208, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp207))))
			DeclareVarInst(stack, "float", fTemp209, BinopInst("+", LoadVarInst(stack, fTemp198), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp202))))
			DeclareVarInst(stack, "float", fTemp210, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp209))))
			DeclareVarInst(stack, "float", fTemp211, BinopInst("-", LoadVarInst(stack, fTemp198), LoadVarInst(stack, fTemp202)))
			DeclareVarInst(stack, "int", iTemp212, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp200), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp213, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp207)))
			DeclareVarInst(stack, "float", fTemp214, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp209))))
			DeclareVarInst(stack, "int", iTemp215, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp200), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp216, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp205)))
			DeclareVarInst(stack, "float", fTemp217, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp207))))
			DeclareVarInst(stack, "float", fTemp218, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp209))))
			DeclareVarInst(stack, "float", fTemp219, BinopInst("*", LoadVarInst(stack, fTemp203), LoadVarInst(stack, fTemp205)))
			DeclareVarInst(stack, "int", iTemp220, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp200), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp221, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp209)))
			DeclareVarInst(stack, "float", fTemp222, BinopInst("*", LoadVarInst(stack, fTemp219), LoadVarInst(stack, fTemp207)))
			DeclareVarInst(stack, "int", iTemp223, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp200), Int32(4)))))))
			StoreVarInst(struct, fVec6[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec120[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp201), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp204)), LoadVarInst(stack, fTemp206)), LoadVarInst(stack, fTemp208)), LoadVarInst(stack, fTemp210)), BinopInst("*", LoadVarInst(stack, fTemp211), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp203), LoadVarInst(struct, fRec120[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp212), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp213)), LoadVarInst(stack, fTemp214))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec120[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp215), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp216)), LoadVarInst(stack, fTemp217)), LoadVarInst(stack, fTemp218))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp219), LoadVarInst(struct, fRec120[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp220), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp221)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp222), LoadVarInst(struct, fRec120[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp223), Int32(2))), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp224, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow8)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec114[Int32(1)]), LoadVarInst(struct, fVec6[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp225, BinopInst("*", LoadVarInst(stack, fTemp224), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp224))), Float(0.75f)))))))
			DeclareVarInst(stack, "float", fRec115, BinopInst("+", LoadVarInst(struct, fRec114[Int32(1)]), LoadVarInst(stack, fTemp225)))
			DeclareVarInst(stack, "float", fTemp226, BinopInst("+", LoadVarInst(struct, fVec6[Int32(1)]), LoadVarInst(stack, fTemp225)))
			StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp226))
			DeclareVarInst(stack, "float", fRec116, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp178), LoadVarInst(stack, fTemp180)), LoadVarInst(stack, fTemp182)), LoadVarInst(stack, fTemp184)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp175)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp185), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp196), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp197)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp190), LoadVarInst(stack, fTemp191)), LoadVarInst(stack, fTemp192)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp189)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp177), LoadVarInst(stack, fTemp187)), LoadVarInst(stack, fTemp188)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp186)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp193), LoadVarInst(stack, fTemp195)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp194)), Int32(2047))]))))))))
			DeclareVarInst(stack, "int", iRec117, LoadVarInst(stack, iRec121))
			StoreVarInst(struct, fRec110[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec115))
			DeclareVarInst(stack, "float", fRec111, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp204), LoadVarInst(stack, fTemp206)), LoadVarInst(stack, fTemp208)), LoadVarInst(stack, fTemp210)), LoadVarInst(struct, fRec110[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp201), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp211), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp219), LoadVarInst(stack, fTemp221)), LoadVarInst(struct, fRec110[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp220), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp216), LoadVarInst(stack, fTemp217)), LoadVarInst(stack, fTemp218)), LoadVarInst(struct, fRec110[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp215), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp203), LoadVarInst(stack, fTemp213)), LoadVarInst(stack, fTemp214)), LoadVarInst(struct, fRec110[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp212), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp222), LoadVarInst(struct, fRec110[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp223), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec112[Int32(0)], LoadVarInst(stack, fRec116))
			DeclareVarInst(stack, "int", iRec113, LoadVarInst(stack, iRec117))
			StoreVarInst(struct, fRec108[Int32(0)], LoadVarInst(struct, fRec112[Int32(1)]))
			DeclareVarInst(stack, "int", iRec109, LoadVarInst(stack, iRec113))
			StoreVarInst(struct, fRec106[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec108[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec106[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec106[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp227, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec106[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec106[Int32(2)])))))
			DeclareVarInst(stack, "float", fRec104, LoadVarInst(stack, fTemp227))
			DeclareVarInst(stack, "float", fRec105, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec109)), LoadVarInst(stack, fTemp227)))
			StoreVarInst(struct, iRec98[Int32(0)], LoadVarInst(stack, iRec103))
			DeclareVarInst(stack, "float", fRec99, LoadVarInst(stack, fRec107))
			DeclareVarInst(stack, "float", fRec100, LoadVarInst(stack, fRec104))
			DeclareVarInst(stack, "float", fRec101, LoadVarInst(stack, fRec105))
			StoreVarInst(struct, fRec94[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec99))
			DeclareVarInst(stack, "float", fRec95, LoadVarInst(stack, fRec111))
			DeclareVarInst(stack, "float", fRec96, LoadVarInst(stack, fRec100))
			DeclareVarInst(stack, "float", fRec97, LoadVarInst(stack, fRec101))
			StoreVarInst(struct, fRec92[Int32(0)], LoadVarInst(stack, fRec95))
			DeclareVarInst(stack, "float", fRec93, LoadVarInst(stack, fRec97))
			DeclareVarInst(stack, "float", fTemp228, BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec1), LoadVarInst(stack, fRec33)), LoadVarInst(stack, fRec63)), LoadVarInst(stack, fRec93)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp228)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp228)))
			StoreVarInst(struct, iRec10[Int32(1)], LoadVarInst(struct, iRec10[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j0, Int32(3))
				BinopInst(">", LoadVarInst(loop, j0), Int32(0))
				StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec29[LoadVarInst(loop, j0)], LoadVarInst(struct, fRec29[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j1, Int32(3))
				BinopInst(">", LoadVarInst(loop, j1), Int32(0))
				StoreVarInst(loop, j1, BinopInst("-", LoadVarInst(loop, j1), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec16[LoadVarInst(loop, j1)], LoadVarInst(struct, fRec16[BinopInst("-", LoadVarInst(loop, j1), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fRec14[Int32(2)], LoadVarInst(struct, fRec14[Int32(1)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, iRec6[Int32(1)], LoadVarInst(struct, iRec6[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, iRec42[Int32(1)], LoadVarInst(struct, iRec42[Int32(0)]))
			StoreVarInst(struct, fRec58[Int32(1)], LoadVarInst(struct, fRec58[Int32(0)]))
			StoreVarInst(struct, fRec54[Int32(1)], LoadVarInst(struct, fRec54[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j2, Int32(3))
				BinopInst(">", LoadVarInst(loop, j2), Int32(0))
				StoreVarInst(loop, j2, BinopInst("-", LoadVarInst(loop, j2), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec59[LoadVarInst(loop, j2)], LoadVarInst(struct, fRec59[BinopInst("-", LoadVarInst(loop, j2), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec52[Int32(1)], LoadVarInst(struct, fRec52[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j3, Int32(3))
				BinopInst(">", LoadVarInst(loop, j3), Int32(0))
				StoreVarInst(loop, j3, BinopInst("-", LoadVarInst(loop, j3), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec48[LoadVarInst(loop, j3)], LoadVarInst(struct, fRec48[BinopInst("-", LoadVarInst(loop, j3), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fRec46[Int32(2)], LoadVarInst(struct, fRec46[Int32(1)]))
			StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
			StoreVarInst(struct, iRec38[Int32(1)], LoadVarInst(struct, iRec38[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, iRec72[Int32(1)], LoadVarInst(struct, iRec72[Int32(0)]))
			StoreVarInst(struct, fRec88[Int32(1)], LoadVarInst(struct, fRec88[Int32(0)]))
			StoreVarInst(struct, fRec84[Int32(1)], LoadVarInst(struct, fRec84[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j4, Int32(3))
				BinopInst(">", LoadVarInst(loop, j4), Int32(0))
				StoreVarInst(loop, j4, BinopInst("-", LoadVarInst(loop, j4), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec89[LoadVarInst(loop, j4)], LoadVarInst(struct, fRec89[BinopInst("-", LoadVarInst(loop, j4), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
			StoreVarInst(struct, fRec82[Int32(1)], LoadVarInst(struct, fRec82[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j5, Int32(3))
				BinopInst(">", LoadVarInst(loop, j5), Int32(0))
				StoreVarInst(loop, j5, BinopInst("-", LoadVarInst(loop, j5), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec78[LoadVarInst(loop, j5)], LoadVarInst(struct, fRec78[BinopInst("-", LoadVarInst(loop, j5), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fRec76[Int32(2)], LoadVarInst(struct, fRec76[Int32(1)]))
			StoreVarInst(struct, fRec76[Int32(1)], LoadVarInst(struct, fRec76[Int32(0)]))
			StoreVarInst(struct, iRec68[Int32(1)], LoadVarInst(struct, iRec68[Int32(0)]))
			StoreVarInst(struct, fRec62[Int32(1)], LoadVarInst(struct, fRec62[Int32(0)]))
			StoreVarInst(struct, iRec102[Int32(1)], LoadVarInst(struct, iRec102[Int32(0)]))
			StoreVarInst(struct, fRec118[Int32(1)], LoadVarInst(struct, fRec118[Int32(0)]))
			StoreVarInst(struct, fRec114[Int32(1)], LoadVarInst(struct, fRec114[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j6, Int32(3))
				BinopInst(">", LoadVarInst(loop, j6), Int32(0))
				StoreVarInst(loop, j6, BinopInst("-", LoadVarInst(loop, j6), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec119[LoadVarInst(loop, j6)], LoadVarInst(struct, fRec119[BinopInst("-", LoadVarInst(loop, j6), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
			StoreVarInst(struct, fRec112[Int32(1)], LoadVarInst(struct, fRec112[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j7, Int32(3))
				BinopInst(">", LoadVarInst(loop, j7), Int32(0))
				StoreVarInst(loop, j7, BinopInst("-", LoadVarInst(loop, j7), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec108[LoadVarInst(loop, j7)], LoadVarInst(struct, fRec108[BinopInst("-", LoadVarInst(loop, j7), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fRec106[Int32(2)], LoadVarInst(struct, fRec106[Int32(1)]))
			StoreVarInst(struct, fRec106[Int32(1)], LoadVarInst(struct, fRec106[Int32(0)]))
			StoreVarInst(struct, iRec98[Int32(1)], LoadVarInst(struct, iRec98[Int32(0)]))
			StoreVarInst(struct, fRec92[Int32(1)], LoadVarInst(struct, fRec92[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 64 bytes
Heap size real = 131516 bytes
Heap size = 131588 bytes
Stack size in compute = 52 bytes

