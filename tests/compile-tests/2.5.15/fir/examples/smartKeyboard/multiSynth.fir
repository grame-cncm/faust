======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("multiSynth")
	AddMetaDeclareInst(fHslider5, "midi", "pitchwheel")
	AddHorizontalSlider("bend", fHslider5, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("freq", fHslider4, 300.0f, 50.0f, 2000.0f, 0.00999999978f)
	AddHorizontalSlider("gain", fHslider0, 1.0f, 0.0f, 1.0f, 0.00999999978f)
	AddButtonInst("gate"fButton0)
	AddHorizontalSlider("keyboard", fHslider3, 0.0f, 0.0f, 3.0f, 1.0f)
	AddMetaDeclareInst(fHslider1, "midi", "ctrl 64")
	AddHorizontalSlider("sustain", fHslider1, 0.0f, 0.0f, 1.0f, 1.0f)
	AddMetaDeclareInst(fHslider2, "midi", "ctrl 1")
	AddHorizontalSlider("y", fHslider2, 1.0f, 0.0f, 1.0f, 0.00100000005f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec4[4096])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fVec5[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec1[3])
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.25f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.5f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("/", Float(4.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(300.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(1.0f)))
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
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l2)], Float(0.0f))
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
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(4096))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(3))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 19
Store = 0
Binop = 11
Numbers = 8
Declare = 15
Cast = 8
Select = 0
Loop = 0
Funcall = 1

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider0)), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "int", iSlow3, CastInst("int", CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(2)))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "int", iSlow6, BinopInst("==", LoadVarInst(stack, fSlow0), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow7, CastInst("float", LoadVarInst(struct, fHslider5)))
	DeclareVarInst(stack, "int", iSlow8, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(1)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "int", iSlow10, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(3)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "int", iSlow12, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(0)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 131
Store = 36
Binop = 92
Numbers = 75
Declare = 26
Cast = 7
Select = 0
Loop = 1
Funcall = 14

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow0))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec3[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("+", BinopInst("*", Float(4000.0f), LoadVarInst(struct, fRec3[Int32(0)])), Float(50.0f)))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp0)))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(stack, fTemp1), Float(1.0f)))
		DeclareVarInst(stack, "int", iTemp3, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow6)))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), BinopInst("*", LoadVarInst(struct, fRec5[Int32(1)]), CastInst("float", LoadVarInst(stack, iTemp3)))), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp3)))))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec5[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp5, FunCallInst("max_f", LoadVarInst(stack, fTemp4), Float(23.4489498f)))
		DeclareVarInst(stack, "float", fTemp6, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp5))))
		StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp6))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(struct, fVec2[Int32(1)]))))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp7), FunCallInst("floorf", LoadVarInst(stack, fTemp7))))
		DeclareVarInst(stack, "float", fTemp8, FunCallInst("mydsp_faustpower2_f", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec4[Int32(0)])), Float(-1.0f))))
		StoreVarInst(struct, fVec3[Int32(0)], LoadVarInst(stack, fTemp8))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("/", BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec3[Int32(1)])), CastInst("float", LoadVarInst(struct, iVec0[Int32(1)]))), LoadVarInst(stack, fTemp6)))
		StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp9))
		DeclareVarInst(stack, "float", fTemp10, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp5)))))
		DeclareVarInst(stack, "int", iTemp11, CastInst("int", LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp12, FunCallInst("floorf", LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp9), BinopInst("*", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp11)), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp12), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp10))))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fTemp12)), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp11), Int32(1))), Int32(4095))])))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec6[Int32(1)])), LoadVarInst(stack, fTemp13)))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec5[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp15, FunCallInst("sinf", LoadVarInst(stack, fTemp14)))
		DeclareVarInst(stack, "float", fTemp16, FunCallInst("cosf", LoadVarInst(stack, fTemp14)))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(stack, fTemp15)), BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(stack, fTemp16))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(stack, fTemp16)), BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp15)))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp17, FunCallInst("max_f", Float(1.00000001e-07f), FunCallInst("fabsf", LoadVarInst(stack, fTemp4))))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(stack, fTemp17))))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("+", LoadVarInst(stack, fTemp18), Float(-1.0f)))
		DeclareVarInst(stack, "int", iTemp20, BinopInst("<", LoadVarInst(stack, fTemp19), Float(0.0f)))
		StoreVarInst(struct, fRec9[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp20) LoadVarInst(stack, fTemp18) LoadVarInst(stack, fTemp19)))
		DeclareVarInst(stack, "float", fRec10, Select2Inst(LoadVarInst(stack, iTemp20) LoadVarInst(stack, fTemp18) BinopInst("+", LoadVarInst(stack, fTemp18), BinopInst("*", BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp17))), LoadVarInst(stack, fTemp19)))))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("+", Select2Inst(LoadVarInst(stack, iSlow4) LoadVarInst(stack, fTemp13) Float(0.0f)), BinopInst("+", Select2Inst(LoadVarInst(stack, iSlow8) BinopInst("*", LoadVarInst(stack, fSlow9), BinopInst("*", LoadVarInst(struct, fRec5[Int32(0)]), LoadVarInst(struct, fRec6[Int32(0)]))) Float(0.0f)), BinopInst("+", Select2Inst(LoadVarInst(stack, iSlow10) LoadVarInst(struct, fRec7[Int32(0)]) Float(0.0f)), Select2Inst(LoadVarInst(stack, iSlow12) BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(stack, fRec10)), Float(-1.0f)) Float(0.0f))))))
		StoreVarInst(struct, fVec5[Int32(0)], LoadVarInst(stack, fTemp21))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp1)), LoadVarInst(stack, fTemp2)))), BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp21), LoadVarInst(struct, fVec5[Int32(1)])), LoadVarInst(stack, fTemp2))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp1), Float(1.0f)), LoadVarInst(stack, fTemp0)), Float(1.0f)))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp1), Float(-1.0f)), LoadVarInst(stack, fTemp0)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp0))))))), LoadVarInst(stack, fTemp22))))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", LoadVarInst(struct, fRec1[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec1[Int32(1)]))))), LoadVarInst(stack, fTemp22)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp23)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp23)))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fVec5[Int32(1)], LoadVarInst(struct, fVec5[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec4[4096])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fVec5[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec1[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.25f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.5f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("/", Float(4.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(300.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(1.0f)))
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
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l2)], Float(0.0f))
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
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(4096))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(3))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider0)), LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "int", iSlow3, CastInst("int", CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(2)))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "int", iSlow6, BinopInst("==", LoadVarInst(stack, fSlow0), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow7, CastInst("float", LoadVarInst(struct, fHslider5)))
	DeclareVarInst(stack, "int", iSlow8, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(1)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "int", iSlow10, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(3)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "int", iSlow12, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(0)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow0))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec3[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("+", BinopInst("*", Float(4000.0f), LoadVarInst(struct, fRec3[Int32(0)])), Float(50.0f)))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp0)))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(stack, fTemp1), Float(1.0f)))
			DeclareVarInst(stack, "int", iTemp3, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow6)))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), BinopInst("*", LoadVarInst(struct, fRec5[Int32(1)]), CastInst("float", LoadVarInst(stack, iTemp3)))), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp3)))))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec5[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp5, FunCallInst("max_f", LoadVarInst(stack, fTemp4), Float(23.4489498f)))
			DeclareVarInst(stack, "float", fTemp6, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp5))))
			StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp6))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), LoadVarInst(struct, fVec2[Int32(1)]))))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp7), FunCallInst("floorf", LoadVarInst(stack, fTemp7))))
			DeclareVarInst(stack, "float", fTemp8, FunCallInst("mydsp_faustpower2_f", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec4[Int32(0)])), Float(-1.0f))))
			StoreVarInst(struct, fVec3[Int32(0)], LoadVarInst(stack, fTemp8))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("/", BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec3[Int32(1)])), CastInst("float", LoadVarInst(struct, iVec0[Int32(1)]))), LoadVarInst(stack, fTemp6)))
			StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp9))
			DeclareVarInst(stack, "float", fTemp10, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp5)))))
			DeclareVarInst(stack, "int", iTemp11, CastInst("int", LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp12, FunCallInst("floorf", LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp9), BinopInst("*", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp11)), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp12), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp10))))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fTemp12)), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp11), Int32(1))), Int32(4095))])))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec6[Int32(1)])), LoadVarInst(stack, fTemp13)))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec5[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp15, FunCallInst("sinf", LoadVarInst(stack, fTemp14)))
			DeclareVarInst(stack, "float", fTemp16, FunCallInst("cosf", LoadVarInst(stack, fTemp14)))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(stack, fTemp15)), BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(stack, fTemp16))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(stack, fTemp16)), BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp15)))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp17, FunCallInst("max_f", Float(1.00000001e-07f), FunCallInst("fabsf", LoadVarInst(stack, fTemp4))))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("+", LoadVarInst(struct, fRec9[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(stack, fTemp17))))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("+", LoadVarInst(stack, fTemp18), Float(-1.0f)))
			DeclareVarInst(stack, "int", iTemp20, BinopInst("<", LoadVarInst(stack, fTemp19), Float(0.0f)))
			StoreVarInst(struct, fRec9[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp20) LoadVarInst(stack, fTemp18) LoadVarInst(stack, fTemp19)))
			DeclareVarInst(stack, "float", fRec10, Select2Inst(LoadVarInst(stack, iTemp20) LoadVarInst(stack, fTemp18) BinopInst("+", LoadVarInst(stack, fTemp18), BinopInst("*", BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp17))), LoadVarInst(stack, fTemp19)))))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("+", Select2Inst(LoadVarInst(stack, iSlow4) LoadVarInst(stack, fTemp13) Float(0.0f)), BinopInst("+", Select2Inst(LoadVarInst(stack, iSlow8) BinopInst("*", LoadVarInst(stack, fSlow9), BinopInst("*", LoadVarInst(struct, fRec5[Int32(0)]), LoadVarInst(struct, fRec6[Int32(0)]))) Float(0.0f)), BinopInst("+", Select2Inst(LoadVarInst(stack, iSlow10) LoadVarInst(struct, fRec7[Int32(0)]) Float(0.0f)), Select2Inst(LoadVarInst(stack, iSlow12) BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(stack, fRec10)), Float(-1.0f)) Float(0.0f))))))
			StoreVarInst(struct, fVec5[Int32(0)], LoadVarInst(stack, fTemp21))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp1)), LoadVarInst(stack, fTemp2)))), BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp21), LoadVarInst(struct, fVec5[Int32(1)])), LoadVarInst(stack, fTemp2))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp1), Float(1.0f)), LoadVarInst(stack, fTemp0)), Float(1.0f)))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp1), Float(-1.0f)), LoadVarInst(stack, fTemp0)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp0))))))), LoadVarInst(stack, fTemp22))))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", LoadVarInst(struct, fRec1[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec1[Int32(1)]))))), LoadVarInst(stack, fTemp22)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp23)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp23)))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fVec5[Int32(1)], LoadVarInst(struct, fVec5[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 16560 bytes
Heap size = 16576 bytes
Stack size in compute = 68 bytes

