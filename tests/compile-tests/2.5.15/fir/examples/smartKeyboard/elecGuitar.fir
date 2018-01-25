======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("elecGuitar")
	AddMetaDeclareInst(fHslider2, "midi", "pitchwheel")
	AddHorizontalSlider("bend", fHslider2, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("freq", fHslider1, 300.0f, 50.0f, 2000.0f, 0.00999999978f)
	AddHorizontalSlider("gain", fHslider3, 1.0f, 0.0f, 1.0f, 0.00999999978f)
	AddButtonInst("gate"fButton0)
	AddMetaDeclareInst(fHslider0, "midi", "ctrl 64")
	AddHorizontalSlider("sustain", fHslider0, 0.0f, 0.0f, 1.0f, 1.0f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, float, fRec33[4])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec34[2048])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, int, iRec37[2])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, float, fRec36[3])
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec38[2])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, float, fVec3[3])
	DeclareVarInst(struct, float, fRec32[512])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fRec14[2048])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec11[4])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec2[512])
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
	StoreVarInst(struct, fConst1, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.000294117635f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00117647054f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(15.707963f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("*", Float(0.00400000019f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, BinopInst("*", Float(0.00200000009f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(500.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(300.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(1.0f)))
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
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(4))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2048))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec37[LoadVarInst(loop, l8)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(3))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(512))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2048))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(4))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(512))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 8
Store = 0
Binop = 2
Numbers = 2
Declare = 7
Cast = 5
Select = 0
Loop = 0
Funcall = 1

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "int", iSlow1, BinopInst("==", LoadVarInst(stack, fSlow0), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fHslider3)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 297
Store = 48
Binop = 246
Numbers = 165
Declare = 89
Cast = 39
Select = 0
Loop = 3
Funcall = 27

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fRec10, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.997305274f), BinopInst("+", BinopInst("*", Float(0.899999976f), LoadVarInst(struct, fRec11[Int32(2)])), BinopInst("*", Float(0.0500000007f), BinopInst("+", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(struct, fRec11[Int32(3)])))))))
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow0))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fVec0[Int32(1)])), LoadVarInst(stack, iSlow1)))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0)))))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fTemp1)), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec13[Int32(1)])))))
		StoreVarInst(struct, fRec30[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fTemp1)), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec30[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp2, FunCallInst("max_f", Float(60.0f), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec30[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", BinopInst("/", Float(340.0f), LoadVarInst(stack, fTemp2)), Float(-0.109999999f)))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(stack, fTemp4), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp6, CastInst("int", LoadVarInst(stack, fTemp5)))
		DeclareVarInst(stack, "int", iTemp7, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp6)))))))
		DeclareVarInst(stack, "float", fTemp8, FunCallInst("floorf", LoadVarInst(stack, fTemp5)))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp8))))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp9)))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp8))))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp11))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp8))))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "float", fTemp15, BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp8))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp15))))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("-", LoadVarInst(stack, fTemp4), LoadVarInst(stack, fTemp8)))
		DeclareVarInst(stack, "int", iTemp18, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(2))))))))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13)))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp15))))
		DeclareVarInst(stack, "int", iTemp21, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(1))))))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp15))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "int", iTemp26, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(3))))))))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp15)))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp13)))
		DeclareVarInst(stack, "int", iTemp29, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(4))))))))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp7), Int32(1))), Int32(511))]), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp16)), BinopInst("*", LoadVarInst(stack, fTemp17), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp18), Int32(1))), Int32(511))])), LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp20))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp21), Int32(1))), Int32(511))]), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp26), Int32(1))), Int32(511))])), LoadVarInst(stack, fTemp27)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp29), Int32(1))), Int32(511))])))))))
		StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec31[Int32(1)])), BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fRec26[Int32(1)]))))
		DeclareVarInst(stack, "float", fRec27, LoadVarInst(struct, fRec31[Int32(0)]))
		StoreVarInst(struct, fRec33[Int32(0)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec34[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.997305274f), BinopInst("+", BinopInst("*", Float(0.899999976f), LoadVarInst(struct, fRec33[Int32(2)])), BinopInst("*", Float(0.0500000007f), BinopInst("+", LoadVarInst(struct, fRec33[Int32(1)]), LoadVarInst(struct, fRec33[Int32(3)])))))))
		DeclareVarInst(stack, "int", iRec35, Int32(0))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(stack, fTemp30), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp32, CastInst("int", LoadVarInst(stack, fTemp31)))
		DeclareVarInst(stack, "int", iTemp33, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp32)))))))
		DeclareVarInst(stack, "float", fTemp34, FunCallInst("floorf", LoadVarInst(stack, fTemp31)))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp35)))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp37))))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fTemp40, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp39))))
		DeclareVarInst(stack, "float", fTemp41, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp41))))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("-", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp34)))
		DeclareVarInst(stack, "int", iTemp44, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp32), Int32(2))))))))
		DeclareVarInst(stack, "float", fTemp45, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp39)))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp41))))
		DeclareVarInst(stack, "int", iTemp47, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp32), Int32(1))))))))
		DeclareVarInst(stack, "float", fTemp48, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp37)))
		DeclareVarInst(stack, "float", fTemp49, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp39))))
		DeclareVarInst(stack, "float", fTemp50, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp41))))
		DeclareVarInst(stack, "float", fTemp51, BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(stack, fTemp37)))
		DeclareVarInst(stack, "int", iTemp52, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp32), Int32(3))))))))
		DeclareVarInst(stack, "float", fTemp53, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp41)))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(stack, fTemp39)))
		DeclareVarInst(stack, "int", iTemp55, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp32), Int32(4))))))))
		StoreVarInst(struct, fVec1[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp33), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp36)), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp42)), BinopInst("*", LoadVarInst(stack, fTemp43), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp44), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp47), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp48)), LoadVarInst(stack, fTemp49)), LoadVarInst(stack, fTemp50))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp52), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp53)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp55), Int32(2))), Int32(2047))])))))))
		StoreVarInst(struct, iRec37[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec37[Int32(1)])), Int32(12345)))
		DeclareVarInst(stack, "float", fTemp56, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp2))))
		DeclareVarInst(stack, "float", fTemp57, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp56)))
		DeclareVarInst(stack, "float", fTemp58, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp57), Float(1.41421354f)), LoadVarInst(stack, fTemp56)), Float(1.0f)))
		StoreVarInst(struct, fRec36[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec37[Int32(0)]))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec36[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp57), Float(-1.41421354f)), LoadVarInst(stack, fTemp56)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp56))))))), LoadVarInst(stack, fTemp58))))
		DeclareVarInst(stack, "float", fTemp59, FunCallInst("mydsp_faustpower2_f", BinopInst("-", Float(1.0f), BinopInst("*", Float(0.000500000024f), LoadVarInst(stack, fTemp2)))))
		StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp59))
		DeclareVarInst(stack, "float", fTemp60, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp59)))
		StoreVarInst(struct, fRec38[Int32(0)], Select2Inst(BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fVec0[Int32(1)])), Float(0.0f)), Int32(0)) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp60), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec38[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("-", LoadVarInst(stack, fTemp59), LoadVarInst(struct, fVec2[Int32(1)])))), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp61, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp59)))
		DeclareVarInst(stack, "int", iTemp62, BinopInst("<", LoadVarInst(struct, fRec38[Int32(0)]), LoadVarInst(stack, fTemp61)))
		DeclareVarInst(stack, "float", fTemp63, BinopInst("*", LoadVarInst(stack, fSlow4), BinopInst("/", BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec36[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec36[Int32(1)])))), Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec38[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp62) BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("/", LoadVarInst(struct, fRec38[Int32(0)]), LoadVarInst(stack, fTemp59))) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec38[Int32(0)]), LoadVarInst(stack, fTemp60)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec38[Int32(0)]), LoadVarInst(stack, fTemp61))), LoadVarInst(stack, fTemp59))), Float(1.0f)) Float(0.0f)))), LoadVarInst(stack, fTemp58))))
		DeclareVarInst(stack, "float", fTemp64, BinopInst("+", LoadVarInst(struct, fVec1[Int32(1)]), LoadVarInst(stack, fTemp63)))
		StoreVarInst(struct, fVec3[Int32(0)], LoadVarInst(stack, fTemp64))
		StoreVarInst(struct, fRec32[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], BinopInst("+", BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(1)), Int32(511))])), BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fVec3[Int32(2)]))))
		DeclareVarInst(stack, "float", fRec28, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp16)), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp7)), Int32(511))])), BinopInst("*", LoadVarInst(stack, fTemp17), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp29)), Int32(511))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24)), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp21)), Int32(511))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp20)), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp18)), Int32(511))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp27)), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp26)), Int32(511))]))))))))
		DeclareVarInst(stack, "float", fRec29, BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), BinopInst("+", CastInst("float", LoadVarInst(stack, iRec35)), LoadVarInst(struct, fVec3[Int32(1)]))))
		StoreVarInst(struct, fRec22[Int32(0)], LoadVarInst(stack, fRec27))
		DeclareVarInst(stack, "float", fRec23, LoadVarInst(struct, fRec22[Int32(1)]))
		DeclareVarInst(stack, "float", fRec24, LoadVarInst(stack, fRec28))
		DeclareVarInst(stack, "float", fRec25, LoadVarInst(stack, fRec29))
		StoreVarInst(struct, fRec18[Int32(0)], LoadVarInst(stack, fRec23))
		DeclareVarInst(stack, "float", fRec19, BinopInst("+", LoadVarInst(stack, fTemp63), LoadVarInst(struct, fRec18[Int32(1)])))
		DeclareVarInst(stack, "float", fRec20, LoadVarInst(stack, fRec24))
		DeclareVarInst(stack, "float", fRec21, LoadVarInst(stack, fRec25))
		StoreVarInst(struct, fRec14[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec19))
		DeclareVarInst(stack, "float", fRec15, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp42)), LoadVarInst(struct, fRec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp33), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp43), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(stack, fTemp53)), LoadVarInst(struct, fRec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp52), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(stack, fTemp49)), LoadVarInst(stack, fTemp50)), LoadVarInst(struct, fRec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp47), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46)), LoadVarInst(struct, fRec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp44), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(struct, fRec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp55), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(stack, fRec20))
		DeclareVarInst(stack, "float", fRec17, LoadVarInst(stack, fRec21))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(struct, fRec16[Int32(1)])))
		DeclareVarInst(stack, "float", fRec12, LoadVarInst(stack, fRec17))
		StoreVarInst(struct, fRec6[Int32(0)], LoadVarInst(stack, fRec10))
		DeclareVarInst(stack, "float", fRec7, BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(struct, fRec6[Int32(1)])))
		DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec11[Int32(0)]))
		DeclareVarInst(stack, "float", fRec9, LoadVarInst(stack, fRec12))
		StoreVarInst(struct, fRec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fRec7))
		DeclareVarInst(stack, "float", fRec3, LoadVarInst(stack, fRec15))
		DeclareVarInst(stack, "float", fRec4, LoadVarInst(stack, fRec8))
		DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
		StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec3))
		DeclareVarInst(stack, "float", fRec1, LoadVarInst(stack, fRec5))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec1)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec1)))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j0, Int32(3))
			BinopInst(">", LoadVarInst(loop, j0), Int32(0))
			StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec33[LoadVarInst(loop, j0)], LoadVarInst(struct, fRec33[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, iRec37[Int32(1)], LoadVarInst(struct, iRec37[Int32(0)]))
		StoreVarInst(struct, fRec36[Int32(2)], LoadVarInst(struct, fRec36[Int32(1)]))
		StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
		StoreVarInst(struct, fVec3[Int32(2)], LoadVarInst(struct, fVec3[Int32(1)]))
		StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j1, Int32(3))
			BinopInst(">", LoadVarInst(loop, j1), Int32(0))
			StoreVarInst(loop, j1, BinopInst("-", LoadVarInst(loop, j1), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec11[LoadVarInst(loop, j1)], LoadVarInst(struct, fRec11[BinopInst("-", LoadVarInst(loop, j1), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, float, fRec33[4])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec34[2048])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, int, iRec37[2])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, float, fRec36[3])
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec38[2])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, float, fVec3[3])
	DeclareVarInst(struct, float, fRec32[512])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fRec14[2048])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec11[4])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec2[512])
	DeclareVarInst(struct, float, fRec0[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.000294117635f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00117647054f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(15.707963f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("*", Float(0.00400000019f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, BinopInst("*", Float(0.00200000009f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(500.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(300.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(1.0f)))
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
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(4))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2048))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec37[LoadVarInst(loop, l8)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(3))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(512))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2048))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(4))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(512))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "int", iSlow1, BinopInst("==", LoadVarInst(stack, fSlow0), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fHslider3)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fRec10, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.997305274f), BinopInst("+", BinopInst("*", Float(0.899999976f), LoadVarInst(struct, fRec11[Int32(2)])), BinopInst("*", Float(0.0500000007f), BinopInst("+", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(struct, fRec11[Int32(3)])))))))
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow0))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fVec0[Int32(1)])), LoadVarInst(stack, iSlow1)))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0)))))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fTemp1)), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec13[Int32(1)])))))
			StoreVarInst(struct, fRec30[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(stack, fTemp1)), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec30[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp2, FunCallInst("max_f", Float(60.0f), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec30[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", BinopInst("/", Float(340.0f), LoadVarInst(stack, fTemp2)), Float(-0.109999999f)))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(stack, fTemp4), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp6, CastInst("int", LoadVarInst(stack, fTemp5)))
			DeclareVarInst(stack, "int", iTemp7, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp6)))))))
			DeclareVarInst(stack, "float", fTemp8, FunCallInst("floorf", LoadVarInst(stack, fTemp5)))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp8))))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp9)))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp8))))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp11))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp8))))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "float", fTemp15, BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp8))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp15))))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("-", LoadVarInst(stack, fTemp4), LoadVarInst(stack, fTemp8)))
			DeclareVarInst(stack, "int", iTemp18, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(2))))))))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13)))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp15))))
			DeclareVarInst(stack, "int", iTemp21, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(1))))))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp15))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "int", iTemp26, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(3))))))))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp15)))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp13)))
			DeclareVarInst(stack, "int", iTemp29, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(4))))))))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp7), Int32(1))), Int32(511))]), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp16)), BinopInst("*", LoadVarInst(stack, fTemp17), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp18), Int32(1))), Int32(511))])), LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp20))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp21), Int32(1))), Int32(511))]), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp26), Int32(1))), Int32(511))])), LoadVarInst(stack, fTemp27)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp29), Int32(1))), Int32(511))])))))))
			StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec31[Int32(1)])), BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fRec26[Int32(1)]))))
			DeclareVarInst(stack, "float", fRec27, LoadVarInst(struct, fRec31[Int32(0)]))
			StoreVarInst(struct, fRec33[Int32(0)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec34[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.997305274f), BinopInst("+", BinopInst("*", Float(0.899999976f), LoadVarInst(struct, fRec33[Int32(2)])), BinopInst("*", Float(0.0500000007f), BinopInst("+", LoadVarInst(struct, fRec33[Int32(1)]), LoadVarInst(struct, fRec33[Int32(3)])))))))
			DeclareVarInst(stack, "int", iRec35, Int32(0))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(stack, fTemp30), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp32, CastInst("int", LoadVarInst(stack, fTemp31)))
			DeclareVarInst(stack, "int", iTemp33, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp32)))))))
			DeclareVarInst(stack, "float", fTemp34, FunCallInst("floorf", LoadVarInst(stack, fTemp31)))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp35)))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp37))))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fTemp40, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp39))))
			DeclareVarInst(stack, "float", fTemp41, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp41))))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("-", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp34)))
			DeclareVarInst(stack, "int", iTemp44, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp32), Int32(2))))))))
			DeclareVarInst(stack, "float", fTemp45, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp39)))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp41))))
			DeclareVarInst(stack, "int", iTemp47, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp32), Int32(1))))))))
			DeclareVarInst(stack, "float", fTemp48, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp37)))
			DeclareVarInst(stack, "float", fTemp49, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp39))))
			DeclareVarInst(stack, "float", fTemp50, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp41))))
			DeclareVarInst(stack, "float", fTemp51, BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(stack, fTemp37)))
			DeclareVarInst(stack, "int", iTemp52, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp32), Int32(3))))))))
			DeclareVarInst(stack, "float", fTemp53, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp41)))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(stack, fTemp39)))
			DeclareVarInst(stack, "int", iTemp55, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp32), Int32(4))))))))
			StoreVarInst(struct, fVec1[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp33), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp36)), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp42)), BinopInst("*", LoadVarInst(stack, fTemp43), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp44), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp47), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp48)), LoadVarInst(stack, fTemp49)), LoadVarInst(stack, fTemp50))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp52), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp53)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(struct, fRec34[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp55), Int32(2))), Int32(2047))])))))))
			StoreVarInst(struct, iRec37[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec37[Int32(1)])), Int32(12345)))
			DeclareVarInst(stack, "float", fTemp56, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp2))))
			DeclareVarInst(stack, "float", fTemp57, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp56)))
			DeclareVarInst(stack, "float", fTemp58, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp57), Float(1.41421354f)), LoadVarInst(stack, fTemp56)), Float(1.0f)))
			StoreVarInst(struct, fRec36[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec37[Int32(0)]))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec36[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp57), Float(-1.41421354f)), LoadVarInst(stack, fTemp56)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec36[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp56))))))), LoadVarInst(stack, fTemp58))))
			DeclareVarInst(stack, "float", fTemp59, FunCallInst("mydsp_faustpower2_f", BinopInst("-", Float(1.0f), BinopInst("*", Float(0.000500000024f), LoadVarInst(stack, fTemp2)))))
			StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp59))
			DeclareVarInst(stack, "float", fTemp60, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp59)))
			StoreVarInst(struct, fRec38[Int32(0)], Select2Inst(BinopInst(">", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fVec0[Int32(1)])), Float(0.0f)), Int32(0)) Float(0.0f) FunCallInst("min_f", LoadVarInst(stack, fTemp60), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec38[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("-", LoadVarInst(stack, fTemp59), LoadVarInst(struct, fVec2[Int32(1)])))), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp61, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp59)))
			DeclareVarInst(stack, "int", iTemp62, BinopInst("<", LoadVarInst(struct, fRec38[Int32(0)]), LoadVarInst(stack, fTemp61)))
			DeclareVarInst(stack, "float", fTemp63, BinopInst("*", LoadVarInst(stack, fSlow4), BinopInst("/", BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec36[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec36[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec36[Int32(1)])))), Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec38[Int32(0)]), Float(0.0f)) Float(0.0f) Select2Inst(LoadVarInst(stack, iTemp62) BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("/", LoadVarInst(struct, fRec38[Int32(0)]), LoadVarInst(stack, fTemp59))) Float(1.0f))) Select2Inst(BinopInst("<", LoadVarInst(struct, fRec38[Int32(0)]), LoadVarInst(stack, fTemp60)) BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("/", BinopInst("-", Float(0.0f), BinopInst("-", LoadVarInst(struct, fRec38[Int32(0)]), LoadVarInst(stack, fTemp61))), LoadVarInst(stack, fTemp59))), Float(1.0f)) Float(0.0f)))), LoadVarInst(stack, fTemp58))))
			DeclareVarInst(stack, "float", fTemp64, BinopInst("+", LoadVarInst(struct, fVec1[Int32(1)]), LoadVarInst(stack, fTemp63)))
			StoreVarInst(struct, fVec3[Int32(0)], LoadVarInst(stack, fTemp64))
			StoreVarInst(struct, fRec32[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], BinopInst("+", BinopInst("*", Float(0.0500000007f), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(1)), Int32(511))])), BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fVec3[Int32(2)]))))
			DeclareVarInst(stack, "float", fRec28, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp16)), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp7)), Int32(511))])), BinopInst("*", LoadVarInst(stack, fTemp17), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp29)), Int32(511))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24)), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp21)), Int32(511))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp20)), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp18)), Int32(511))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp27)), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp26)), Int32(511))]))))))))
			DeclareVarInst(stack, "float", fRec29, BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), BinopInst("+", CastInst("float", LoadVarInst(stack, iRec35)), LoadVarInst(struct, fVec3[Int32(1)]))))
			StoreVarInst(struct, fRec22[Int32(0)], LoadVarInst(stack, fRec27))
			DeclareVarInst(stack, "float", fRec23, LoadVarInst(struct, fRec22[Int32(1)]))
			DeclareVarInst(stack, "float", fRec24, LoadVarInst(stack, fRec28))
			DeclareVarInst(stack, "float", fRec25, LoadVarInst(stack, fRec29))
			StoreVarInst(struct, fRec18[Int32(0)], LoadVarInst(stack, fRec23))
			DeclareVarInst(stack, "float", fRec19, BinopInst("+", LoadVarInst(stack, fTemp63), LoadVarInst(struct, fRec18[Int32(1)])))
			DeclareVarInst(stack, "float", fRec20, LoadVarInst(stack, fRec24))
			DeclareVarInst(stack, "float", fRec21, LoadVarInst(stack, fRec25))
			StoreVarInst(struct, fRec14[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec19))
			DeclareVarInst(stack, "float", fRec15, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp42)), LoadVarInst(struct, fRec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp33), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp43), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(stack, fTemp53)), LoadVarInst(struct, fRec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp52), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(stack, fTemp49)), LoadVarInst(stack, fTemp50)), LoadVarInst(struct, fRec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp47), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46)), LoadVarInst(struct, fRec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp44), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(struct, fRec14[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp55), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(stack, fRec20))
			DeclareVarInst(stack, "float", fRec17, LoadVarInst(stack, fRec21))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(struct, fRec16[Int32(1)])))
			DeclareVarInst(stack, "float", fRec12, LoadVarInst(stack, fRec17))
			StoreVarInst(struct, fRec6[Int32(0)], LoadVarInst(stack, fRec10))
			DeclareVarInst(stack, "float", fRec7, BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(struct, fRec6[Int32(1)])))
			DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec11[Int32(0)]))
			DeclareVarInst(stack, "float", fRec9, LoadVarInst(stack, fRec12))
			StoreVarInst(struct, fRec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fRec7))
			DeclareVarInst(stack, "float", fRec3, LoadVarInst(stack, fRec15))
			DeclareVarInst(stack, "float", fRec4, LoadVarInst(stack, fRec8))
			DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
			StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec3))
			DeclareVarInst(stack, "float", fRec1, LoadVarInst(stack, fRec5))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec1)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec1)))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j0, Int32(3))
				BinopInst(">", LoadVarInst(loop, j0), Int32(0))
				StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec33[LoadVarInst(loop, j0)], LoadVarInst(struct, fRec33[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, iRec37[Int32(1)], LoadVarInst(struct, iRec37[Int32(0)]))
			StoreVarInst(struct, fRec36[Int32(2)], LoadVarInst(struct, fRec36[Int32(1)]))
			StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
			StoreVarInst(struct, fVec3[Int32(2)], LoadVarInst(struct, fVec3[Int32(1)]))
			StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j1, Int32(3))
				BinopInst(">", LoadVarInst(loop, j1), Int32(0))
				StoreVarInst(loop, j1, BinopInst("-", LoadVarInst(loop, j1), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec11[LoadVarInst(loop, j1)], LoadVarInst(struct, fRec11[BinopInst("-", LoadVarInst(loop, j1), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 20692 bytes
Heap size = 20708 bytes
Stack size in compute = 36 bytes

