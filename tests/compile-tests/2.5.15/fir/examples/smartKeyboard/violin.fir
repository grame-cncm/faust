======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("violin")
	AddHorizontalSlider("kb0bend", fHslider1, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("kb0fingers", fHslider2, 0.0f, 0.0f, 10.0f, 1.0f)
	AddHorizontalSlider("kb0freq", fHslider0, 220.0f, 20.0f, 10000.0f, 0.00999999978f)
	AddHorizontalSlider("kb1bend", fHslider6, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("kb1fingers", fHslider7, 0.0f, 0.0f, 10.0f, 1.0f)
	AddHorizontalSlider("kb1freq", fHslider5, 330.0f, 20.0f, 10000.0f, 0.00999999978f)
	AddHorizontalSlider("kb2bend", fHslider9, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("kb2fingers", fHslider10, 0.0f, 0.0f, 10.0f, 1.0f)
	AddHorizontalSlider("kb2freq", fHslider8, 440.0f, 20.0f, 10000.0f, 0.00999999978f)
	AddHorizontalSlider("kb3bend", fHslider12, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddHorizontalSlider("kb3fingers", fHslider13, 0.0f, 0.0f, 10.0f, 1.0f)
	AddHorizontalSlider("kb3freq", fHslider11, 550.0f, 20.0f, 10000.0f, 0.00999999978f)
	AddHorizontalSlider("kb4k0x", fHslider3, 0.0f, 0.0f, 1.0f, 1.0f)
	AddHorizontalSlider("kb4k0y", fHslider4, 0.0f, 0.0f, 1.0f, 1.0f)
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
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec32[2])
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
	DeclareVarInst(struct, int, iRec43[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec59[2])
	DeclareVarInst(struct, float, fRec55[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec60[4])
	DeclareVarInst(struct, float, fRec61[2048])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fVec3[2048])
	DeclareVarInst(struct, float, fRec51[2048])
	DeclareVarInst(struct, float, fRec53[2])
	DeclareVarInst(struct, float, fRec49[4])
	DeclareVarInst(struct, float, fRec47[3])
	DeclareVarInst(struct, int, iRec39[2])
	DeclareVarInst(struct, float, fRec35[2048])
	DeclareVarInst(struct, float, fRec33[2])
	DeclareVarInst(struct, int, iRec73[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, float, fRec89[2])
	DeclareVarInst(struct, float, fRec85[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider10)
	DeclareVarInst(struct, float, fRec90[4])
	DeclareVarInst(struct, float, fRec91[2048])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, float, fVec5[2048])
	DeclareVarInst(struct, float, fRec81[2048])
	DeclareVarInst(struct, float, fRec83[2])
	DeclareVarInst(struct, float, fRec79[4])
	DeclareVarInst(struct, float, fRec77[3])
	DeclareVarInst(struct, int, iRec69[2])
	DeclareVarInst(struct, float, fRec65[2048])
	DeclareVarInst(struct, float, fRec63[2])
	DeclareVarInst(struct, int, iRec103[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider11)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider12)
	DeclareVarInst(struct, float, fRec119[2])
	DeclareVarInst(struct, float, fRec115[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider13)
	DeclareVarInst(struct, float, fRec120[4])
	DeclareVarInst(struct, float, fRec121[2048])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, float, fVec7[2048])
	DeclareVarInst(struct, float, fRec111[2048])
	DeclareVarInst(struct, float, fRec113[2])
	DeclareVarInst(struct, float, fRec109[4])
	DeclareVarInst(struct, float, fRec107[3])
	DeclareVarInst(struct, int, iRec99[2])
	DeclareVarInst(struct, float, fRec95[2048])
	DeclareVarInst(struct, float, fRec93[2])
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
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(330.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider10, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider11, CastInst("FAUSTFLOAT", Double(550.0f)))
	StoreVarInst(struct, fHslider12, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider13, CastInst("FAUSTFLOAT", Double(0.0f)))
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
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2048))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2048))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(4))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(3))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[LoadVarInst(loop, l14)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2048))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec43[LoadVarInst(loop, l17)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec55[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(4))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2048))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec61[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2048))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2048))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec53[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(4))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(3))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec39[LoadVarInst(loop, l28)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2048))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec73[LoadVarInst(loop, l31)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec89[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec85[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(4))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec90[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2048))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec91[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2048))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2048))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec81[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(2))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec83[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(4))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec79[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(3))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec77[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec69[LoadVarInst(loop, l42)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(2048))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec65[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(2))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec63[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(2))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec103[LoadVarInst(loop, l45)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec119[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(2))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec115[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(4))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec120[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2048))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec121[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(2048))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2048))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec111[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(2))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec113[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(4))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec109[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(3))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec107[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(2))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec99[LoadVarInst(loop, l56)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(2048))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec95[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(2))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec93[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 16
Store = 0
Binop = 14
Numbers = 10
Declare = 12
Cast = 18
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "int", iSlow1, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider2))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider4))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider5)), CastInst("float", LoadVarInst(struct, fHslider6)))))
	DeclareVarInst(stack, "int", iSlow5, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider7))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider8)), CastInst("float", LoadVarInst(struct, fHslider9)))))
	DeclareVarInst(stack, "int", iSlow7, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider10))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider11)), CastInst("float", LoadVarInst(struct, fHslider12)))))
	DeclareVarInst(stack, "int", iSlow9, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider13))), Int32(0)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 937
Store = 118
Binop = 787
Numbers = 477
Declare = 307
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
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", Float(0.00100000005f), FunCallInst("min_f", Float(1.0f), BinopInst("*", Float(8000.0f), FunCallInst("fabsf", BinopInst("-", LoadVarInst(struct, fRec28[Int32(0)]), LoadVarInst(struct, fRec28[Int32(1)]))))))))
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
		StoreVarInst(struct, fRec32[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec32[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("-", Float(5.0f), BinopInst("*", Float(4.0f), LoadVarInst(struct, fRec32[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp55, BinopInst("*", LoadVarInst(stack, fTemp53), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(stack, fTemp53))), Float(0.75f)))))))
		DeclareVarInst(stack, "float", fRec23, BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(stack, fTemp55)))
		DeclareVarInst(stack, "float", fTemp56, BinopInst("+", LoadVarInst(struct, fVec0[Int32(1)]), LoadVarInst(stack, fTemp55)))
		StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp56))
		DeclareVarInst(stack, "float", fRec24, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp9)), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp4)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp14), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp26)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp18)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fTemp16)), LoadVarInst(stack, fTemp17)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp15)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(stack, fTemp24)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp23)), Int32(2047))]))))))))
		DeclareVarInst(stack, "int", iRec25, LoadVarInst(stack, iRec31))
		StoreVarInst(struct, fRec18[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec23))
		DeclareVarInst(stack, "float", fRec19, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp37)), LoadVarInst(stack, fTemp39)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp30), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp40), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(stack, fTemp50)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp49), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp45), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp44), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp32), LoadVarInst(stack, fTemp42)), LoadVarInst(stack, fTemp43)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp41), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp52), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(stack, fRec24))
		DeclareVarInst(stack, "int", iRec21, LoadVarInst(stack, iRec25))
		StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(struct, fRec20[Int32(1)]))
		DeclareVarInst(stack, "int", iRec17, LoadVarInst(stack, iRec21))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec14[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec14[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp57, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec14[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec14[Int32(2)])))))
		DeclareVarInst(stack, "float", fRec12, LoadVarInst(stack, fTemp57))
		DeclareVarInst(stack, "float", fRec13, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec17)), LoadVarInst(stack, fTemp57)))
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
		StoreVarInst(struct, iRec43[Int32(0)], Int32(0))
		DeclareVarInst(stack, "int", iRec44, LoadVarInst(struct, iRec43[Int32(1)]))
		DeclareVarInst(stack, "float", fRec48, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec39[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec49[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec49[Int32(1)]), LoadVarInst(struct, fRec49[Int32(3)])))))))
		StoreVarInst(struct, fRec59[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec59[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp58, BinopInst("+", LoadVarInst(struct, fRec59[Int32(0)]), Float(-0.0799999982f)))
		DeclareVarInst(stack, "float", fTemp59, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp58)))
		DeclareVarInst(stack, "float", fTemp60, BinopInst("+", LoadVarInst(stack, fTemp59), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp61, CastInst("int", LoadVarInst(stack, fTemp60)))
		DeclareVarInst(stack, "int", iTemp62, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp61))))))
		DeclareVarInst(stack, "float", fTemp63, FunCallInst("floorf", LoadVarInst(stack, fTemp60)))
		DeclareVarInst(stack, "float", fTemp64, BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp63))))
		DeclareVarInst(stack, "float", fTemp65, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp64)))
		DeclareVarInst(stack, "float", fTemp66, BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp63))))
		DeclareVarInst(stack, "float", fTemp67, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp66))))
		DeclareVarInst(stack, "float", fTemp68, BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp63))))
		DeclareVarInst(stack, "float", fTemp69, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp68))))
		DeclareVarInst(stack, "float", fTemp70, BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp63))))
		DeclareVarInst(stack, "float", fTemp71, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp70))))
		DeclareVarInst(stack, "float", fTemp72, BinopInst("-", LoadVarInst(stack, fTemp59), LoadVarInst(stack, fTemp63)))
		DeclareVarInst(stack, "int", iTemp73, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp61), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp74, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp68)))
		DeclareVarInst(stack, "float", fTemp75, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp70))))
		DeclareVarInst(stack, "int", iTemp76, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp61), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp77, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp66)))
		DeclareVarInst(stack, "float", fTemp78, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp68))))
		DeclareVarInst(stack, "float", fTemp79, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp70))))
		DeclareVarInst(stack, "float", fTemp80, BinopInst("*", LoadVarInst(stack, fTemp64), LoadVarInst(stack, fTemp66)))
		DeclareVarInst(stack, "int", iTemp81, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp61), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp82, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp70)))
		DeclareVarInst(stack, "float", fTemp83, BinopInst("*", LoadVarInst(stack, fTemp80), LoadVarInst(stack, fTemp68)))
		DeclareVarInst(stack, "int", iTemp84, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp61), Int32(4)))))))
		StoreVarInst(struct, fRec55[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec35[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp62), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp65)), LoadVarInst(stack, fTemp67)), LoadVarInst(stack, fTemp69)), LoadVarInst(stack, fTemp71)), BinopInst("*", LoadVarInst(stack, fTemp72), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp64), LoadVarInst(struct, fRec35[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp73), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp74)), LoadVarInst(stack, fTemp75))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec35[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp76), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp77)), LoadVarInst(stack, fTemp78)), LoadVarInst(stack, fTemp79))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp80), LoadVarInst(struct, fRec35[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp81), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp82)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp83), LoadVarInst(struct, fRec35[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp84), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec60[Int32(0)], LoadVarInst(struct, fRec33[Int32(1)]))
		StoreVarInst(struct, fRec61[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec60[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec60[Int32(1)]), LoadVarInst(struct, fRec60[Int32(3)])))))))
		DeclareVarInst(stack, "int", iRec62, Int32(0))
		DeclareVarInst(stack, "float", fTemp85, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp58)))
		DeclareVarInst(stack, "float", fTemp86, BinopInst("+", LoadVarInst(stack, fTemp85), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp87, CastInst("int", LoadVarInst(stack, fTemp86)))
		DeclareVarInst(stack, "int", iTemp88, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp87))))))
		DeclareVarInst(stack, "float", fTemp89, FunCallInst("floorf", LoadVarInst(stack, fTemp86)))
		DeclareVarInst(stack, "float", fTemp90, BinopInst("+", LoadVarInst(stack, fTemp85), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp89))))
		DeclareVarInst(stack, "float", fTemp91, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp90)))
		DeclareVarInst(stack, "float", fTemp92, BinopInst("+", LoadVarInst(stack, fTemp85), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp89))))
		DeclareVarInst(stack, "float", fTemp93, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp92))))
		DeclareVarInst(stack, "float", fTemp94, BinopInst("+", LoadVarInst(stack, fTemp85), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp89))))
		DeclareVarInst(stack, "float", fTemp95, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp94))))
		DeclareVarInst(stack, "float", fTemp96, BinopInst("+", LoadVarInst(stack, fTemp85), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp89))))
		DeclareVarInst(stack, "float", fTemp97, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp96))))
		DeclareVarInst(stack, "float", fTemp98, BinopInst("-", LoadVarInst(stack, fTemp85), LoadVarInst(stack, fTemp89)))
		DeclareVarInst(stack, "int", iTemp99, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp100, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp94)))
		DeclareVarInst(stack, "float", fTemp101, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp96))))
		DeclareVarInst(stack, "int", iTemp102, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp103, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp92)))
		DeclareVarInst(stack, "float", fTemp104, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp94))))
		DeclareVarInst(stack, "float", fTemp105, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp96))))
		DeclareVarInst(stack, "float", fTemp106, BinopInst("*", LoadVarInst(stack, fTemp90), LoadVarInst(stack, fTemp92)))
		DeclareVarInst(stack, "int", iTemp107, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp108, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp96)))
		DeclareVarInst(stack, "float", fTemp109, BinopInst("*", LoadVarInst(stack, fTemp106), LoadVarInst(stack, fTemp94)))
		DeclareVarInst(stack, "int", iTemp110, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(4)))))))
		StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec61[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp88), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp91)), LoadVarInst(stack, fTemp93)), LoadVarInst(stack, fTemp95)), LoadVarInst(stack, fTemp97)), BinopInst("*", LoadVarInst(stack, fTemp98), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp90), LoadVarInst(struct, fRec61[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp99), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp100)), LoadVarInst(stack, fTemp101))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec61[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp102), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp103)), LoadVarInst(stack, fTemp104)), LoadVarInst(stack, fTemp105))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp106), LoadVarInst(struct, fRec61[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp107), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp108)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp109), LoadVarInst(struct, fRec61[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp110), Int32(2))), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp111, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow5)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec55[Int32(1)]), LoadVarInst(struct, fVec2[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp112, BinopInst("*", LoadVarInst(stack, fTemp111), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(stack, fTemp111))), Float(0.75f)))))))
		DeclareVarInst(stack, "float", fRec56, BinopInst("+", LoadVarInst(struct, fRec55[Int32(1)]), LoadVarInst(stack, fTemp112)))
		DeclareVarInst(stack, "float", fTemp113, BinopInst("+", LoadVarInst(struct, fVec2[Int32(1)]), LoadVarInst(stack, fTemp112)))
		StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp113))
		DeclareVarInst(stack, "float", fRec57, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp65), LoadVarInst(stack, fTemp67)), LoadVarInst(stack, fTemp69)), LoadVarInst(stack, fTemp71)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp62)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp72), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp83), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp84)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp77), LoadVarInst(stack, fTemp78)), LoadVarInst(stack, fTemp79)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp76)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp64), LoadVarInst(stack, fTemp74)), LoadVarInst(stack, fTemp75)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp73)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp80), LoadVarInst(stack, fTemp82)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp81)), Int32(2047))]))))))))
		DeclareVarInst(stack, "int", iRec58, LoadVarInst(stack, iRec62))
		StoreVarInst(struct, fRec51[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec56))
		DeclareVarInst(stack, "float", fRec52, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp91), LoadVarInst(stack, fTemp93)), LoadVarInst(stack, fTemp95)), LoadVarInst(stack, fTemp97)), LoadVarInst(struct, fRec51[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp88), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp98), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp106), LoadVarInst(stack, fTemp108)), LoadVarInst(struct, fRec51[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp107), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp103), LoadVarInst(stack, fTemp104)), LoadVarInst(stack, fTemp105)), LoadVarInst(struct, fRec51[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp102), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp90), LoadVarInst(stack, fTemp100)), LoadVarInst(stack, fTemp101)), LoadVarInst(struct, fRec51[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp99), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp109), LoadVarInst(struct, fRec51[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp110), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec53[Int32(0)], LoadVarInst(stack, fRec57))
		DeclareVarInst(stack, "int", iRec54, LoadVarInst(stack, iRec58))
		StoreVarInst(struct, fRec49[Int32(0)], LoadVarInst(struct, fRec53[Int32(1)]))
		DeclareVarInst(stack, "int", iRec50, LoadVarInst(stack, iRec54))
		StoreVarInst(struct, fRec47[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec49[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec47[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec47[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp114, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec47[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec47[Int32(2)])))))
		DeclareVarInst(stack, "float", fRec45, LoadVarInst(stack, fTemp114))
		DeclareVarInst(stack, "float", fRec46, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec50)), LoadVarInst(stack, fTemp114)))
		StoreVarInst(struct, iRec39[Int32(0)], LoadVarInst(stack, iRec44))
		DeclareVarInst(stack, "float", fRec40, LoadVarInst(stack, fRec48))
		DeclareVarInst(stack, "float", fRec41, LoadVarInst(stack, fRec45))
		DeclareVarInst(stack, "float", fRec42, LoadVarInst(stack, fRec46))
		StoreVarInst(struct, fRec35[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec40))
		DeclareVarInst(stack, "float", fRec36, LoadVarInst(stack, fRec52))
		DeclareVarInst(stack, "float", fRec37, LoadVarInst(stack, fRec41))
		DeclareVarInst(stack, "float", fRec38, LoadVarInst(stack, fRec42))
		StoreVarInst(struct, fRec33[Int32(0)], LoadVarInst(stack, fRec36))
		DeclareVarInst(stack, "float", fRec34, LoadVarInst(stack, fRec38))
		StoreVarInst(struct, iRec73[Int32(0)], Int32(0))
		DeclareVarInst(stack, "int", iRec74, LoadVarInst(struct, iRec73[Int32(1)]))
		DeclareVarInst(stack, "float", fRec78, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec69[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec79[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec79[Int32(1)]), LoadVarInst(struct, fRec79[Int32(3)])))))))
		StoreVarInst(struct, fRec89[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec89[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp115, BinopInst("+", LoadVarInst(struct, fRec89[Int32(0)]), Float(-0.0799999982f)))
		DeclareVarInst(stack, "float", fTemp116, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp115)))
		DeclareVarInst(stack, "float", fTemp117, BinopInst("+", LoadVarInst(stack, fTemp116), Float(-1.49999499f)))
		DeclareVarInst(stack, "float", fTemp118, FunCallInst("floorf", LoadVarInst(stack, fTemp117)))
		DeclareVarInst(stack, "float", fTemp119, BinopInst("+", LoadVarInst(stack, fTemp116), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp118))))
		DeclareVarInst(stack, "float", fTemp120, BinopInst("+", LoadVarInst(stack, fTemp116), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp118))))
		DeclareVarInst(stack, "float", fTemp121, BinopInst("+", LoadVarInst(stack, fTemp116), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp118))))
		DeclareVarInst(stack, "float", fTemp122, BinopInst("*", BinopInst("*", BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp119))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp120)))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp121)))))
		DeclareVarInst(stack, "int", iTemp123, CastInst("int", LoadVarInst(stack, fTemp117)))
		DeclareVarInst(stack, "int", iTemp124, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp123))))))
		DeclareVarInst(stack, "float", fTemp125, BinopInst("+", LoadVarInst(stack, fTemp116), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp118))))
		DeclareVarInst(stack, "float", fTemp126, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp125)))
		DeclareVarInst(stack, "int", iTemp127, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp123), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp128, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp119)))
		DeclareVarInst(stack, "float", fTemp129, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp120))))
		DeclareVarInst(stack, "float", fTemp130, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp121))))
		DeclareVarInst(stack, "int", iTemp131, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp123), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp132, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp120)))
		DeclareVarInst(stack, "float", fTemp133, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp121))))
		DeclareVarInst(stack, "int", iTemp134, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp123), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp135, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp121)))
		DeclareVarInst(stack, "int", iTemp136, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp123), Int32(4)))))))
		DeclareVarInst(stack, "float", fTemp137, BinopInst("-", LoadVarInst(stack, fTemp116), LoadVarInst(stack, fTemp118)))
		StoreVarInst(struct, fRec85[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp122), LoadVarInst(struct, fRec65[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp124), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp126)), BinopInst("*", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec65[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp127), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp128)), LoadVarInst(stack, fTemp129)), LoadVarInst(stack, fTemp130)), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec65[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp131), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp132)), LoadVarInst(stack, fTemp133)), LoadVarInst(stack, fTemp125)))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec65[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp134), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp135)), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp119)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp120), LoadVarInst(struct, fRec65[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp136), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp119)))), LoadVarInst(stack, fTemp137))))
		StoreVarInst(struct, fRec90[Int32(0)], LoadVarInst(struct, fRec63[Int32(1)]))
		StoreVarInst(struct, fRec91[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec90[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec90[Int32(1)]), LoadVarInst(struct, fRec90[Int32(3)])))))))
		DeclareVarInst(stack, "int", iRec92, Int32(0))
		DeclareVarInst(stack, "float", fTemp138, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp115)))
		DeclareVarInst(stack, "float", fTemp139, BinopInst("+", LoadVarInst(stack, fTemp138), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp140, CastInst("int", LoadVarInst(stack, fTemp139)))
		DeclareVarInst(stack, "int", iTemp141, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp140))))))
		DeclareVarInst(stack, "float", fTemp142, FunCallInst("floorf", LoadVarInst(stack, fTemp139)))
		DeclareVarInst(stack, "float", fTemp143, BinopInst("+", LoadVarInst(stack, fTemp138), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp142))))
		DeclareVarInst(stack, "float", fTemp144, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp143)))
		DeclareVarInst(stack, "float", fTemp145, BinopInst("+", LoadVarInst(stack, fTemp138), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp142))))
		DeclareVarInst(stack, "float", fTemp146, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp145))))
		DeclareVarInst(stack, "float", fTemp147, BinopInst("+", LoadVarInst(stack, fTemp138), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp142))))
		DeclareVarInst(stack, "float", fTemp148, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp147))))
		DeclareVarInst(stack, "float", fTemp149, BinopInst("+", LoadVarInst(stack, fTemp138), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp142))))
		DeclareVarInst(stack, "float", fTemp150, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp149))))
		DeclareVarInst(stack, "float", fTemp151, BinopInst("-", LoadVarInst(stack, fTemp138), LoadVarInst(stack, fTemp142)))
		DeclareVarInst(stack, "int", iTemp152, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp140), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp153, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp147)))
		DeclareVarInst(stack, "float", fTemp154, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp149))))
		DeclareVarInst(stack, "int", iTemp155, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp140), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp156, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp145)))
		DeclareVarInst(stack, "float", fTemp157, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp147))))
		DeclareVarInst(stack, "float", fTemp158, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp149))))
		DeclareVarInst(stack, "float", fTemp159, BinopInst("*", LoadVarInst(stack, fTemp143), LoadVarInst(stack, fTemp145)))
		DeclareVarInst(stack, "int", iTemp160, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp140), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp161, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp149)))
		DeclareVarInst(stack, "float", fTemp162, BinopInst("*", LoadVarInst(stack, fTemp159), LoadVarInst(stack, fTemp147)))
		DeclareVarInst(stack, "int", iTemp163, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp140), Int32(4)))))))
		StoreVarInst(struct, fVec4[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec91[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp141), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp144)), LoadVarInst(stack, fTemp146)), LoadVarInst(stack, fTemp148)), LoadVarInst(stack, fTemp150)), BinopInst("*", LoadVarInst(stack, fTemp151), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp143), LoadVarInst(struct, fRec91[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp152), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp153)), LoadVarInst(stack, fTemp154))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec91[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp155), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp156)), LoadVarInst(stack, fTemp157)), LoadVarInst(stack, fTemp158))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp159), LoadVarInst(struct, fRec91[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp160), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp161)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp162), LoadVarInst(struct, fRec91[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp163), Int32(2))), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp164, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow7)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec85[Int32(1)]), LoadVarInst(struct, fVec4[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp165, BinopInst("*", LoadVarInst(stack, fTemp164), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(stack, fTemp164))), Float(0.75f)))))))
		DeclareVarInst(stack, "float", fRec86, BinopInst("+", LoadVarInst(struct, fRec85[Int32(1)]), LoadVarInst(stack, fTemp165)))
		DeclareVarInst(stack, "float", fTemp166, BinopInst("+", LoadVarInst(struct, fVec4[Int32(1)]), LoadVarInst(stack, fTemp165)))
		StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp166))
		DeclareVarInst(stack, "float", fRec87, BinopInst("+", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp122), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp124)), Int32(2047))])), LoadVarInst(stack, fTemp126)), BinopInst("*", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp128), LoadVarInst(stack, fTemp129)), LoadVarInst(stack, fTemp130)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp127)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp132), LoadVarInst(stack, fTemp133)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp131)), Int32(2047))])), LoadVarInst(stack, fTemp125)))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp135), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp134)), Int32(2047))])), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp119)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp120), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp136)), Int32(2047))])), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp119)))), LoadVarInst(stack, fTemp137))))
		DeclareVarInst(stack, "int", iRec88, LoadVarInst(stack, iRec92))
		StoreVarInst(struct, fRec81[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec86))
		DeclareVarInst(stack, "float", fRec82, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp144), LoadVarInst(stack, fTemp146)), LoadVarInst(stack, fTemp148)), LoadVarInst(stack, fTemp150)), LoadVarInst(struct, fRec81[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp141), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp151), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp159), LoadVarInst(stack, fTemp161)), LoadVarInst(struct, fRec81[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp160), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp156), LoadVarInst(stack, fTemp157)), LoadVarInst(stack, fTemp158)), LoadVarInst(struct, fRec81[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp155), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp143), LoadVarInst(stack, fTemp153)), LoadVarInst(stack, fTemp154)), LoadVarInst(struct, fRec81[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp152), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp162), LoadVarInst(struct, fRec81[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp163), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec83[Int32(0)], LoadVarInst(stack, fRec87))
		DeclareVarInst(stack, "int", iRec84, LoadVarInst(stack, iRec88))
		StoreVarInst(struct, fRec79[Int32(0)], LoadVarInst(struct, fRec83[Int32(1)]))
		DeclareVarInst(stack, "int", iRec80, LoadVarInst(stack, iRec84))
		StoreVarInst(struct, fRec77[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec79[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec77[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec77[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp167, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec77[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec77[Int32(2)])))))
		DeclareVarInst(stack, "float", fRec75, LoadVarInst(stack, fTemp167))
		DeclareVarInst(stack, "float", fRec76, BinopInst("+", LoadVarInst(stack, fTemp167), CastInst("float", LoadVarInst(stack, iRec80))))
		StoreVarInst(struct, iRec69[Int32(0)], LoadVarInst(stack, iRec74))
		DeclareVarInst(stack, "float", fRec70, LoadVarInst(stack, fRec78))
		DeclareVarInst(stack, "float", fRec71, LoadVarInst(stack, fRec75))
		DeclareVarInst(stack, "float", fRec72, LoadVarInst(stack, fRec76))
		StoreVarInst(struct, fRec65[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec70))
		DeclareVarInst(stack, "float", fRec66, LoadVarInst(stack, fRec82))
		DeclareVarInst(stack, "float", fRec67, LoadVarInst(stack, fRec71))
		DeclareVarInst(stack, "float", fRec68, LoadVarInst(stack, fRec72))
		StoreVarInst(struct, fRec63[Int32(0)], LoadVarInst(stack, fRec66))
		DeclareVarInst(stack, "float", fRec64, LoadVarInst(stack, fRec68))
		StoreVarInst(struct, iRec103[Int32(0)], Int32(0))
		DeclareVarInst(stack, "int", iRec104, LoadVarInst(struct, iRec103[Int32(1)]))
		DeclareVarInst(stack, "float", fRec108, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec99[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec109[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec109[Int32(1)]), LoadVarInst(struct, fRec109[Int32(3)])))))))
		StoreVarInst(struct, fRec119[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec119[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp168, BinopInst("+", LoadVarInst(struct, fRec119[Int32(0)]), Float(-0.0799999982f)))
		DeclareVarInst(stack, "float", fTemp169, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp168)))
		DeclareVarInst(stack, "float", fTemp170, BinopInst("+", LoadVarInst(stack, fTemp169), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp171, CastInst("int", LoadVarInst(stack, fTemp170)))
		DeclareVarInst(stack, "int", iTemp172, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp171))))))
		DeclareVarInst(stack, "float", fTemp173, FunCallInst("floorf", LoadVarInst(stack, fTemp170)))
		DeclareVarInst(stack, "float", fTemp174, BinopInst("+", LoadVarInst(stack, fTemp169), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp173))))
		DeclareVarInst(stack, "float", fTemp175, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp174)))
		DeclareVarInst(stack, "float", fTemp176, BinopInst("+", LoadVarInst(stack, fTemp169), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp173))))
		DeclareVarInst(stack, "float", fTemp177, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp176))))
		DeclareVarInst(stack, "float", fTemp178, BinopInst("+", LoadVarInst(stack, fTemp169), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp173))))
		DeclareVarInst(stack, "float", fTemp179, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp178))))
		DeclareVarInst(stack, "float", fTemp180, BinopInst("+", LoadVarInst(stack, fTemp169), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp173))))
		DeclareVarInst(stack, "float", fTemp181, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp180))))
		DeclareVarInst(stack, "float", fTemp182, BinopInst("-", LoadVarInst(stack, fTemp169), LoadVarInst(stack, fTemp173)))
		DeclareVarInst(stack, "int", iTemp183, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp171), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp184, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp178)))
		DeclareVarInst(stack, "float", fTemp185, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp180))))
		DeclareVarInst(stack, "int", iTemp186, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp171), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp187, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp176)))
		DeclareVarInst(stack, "float", fTemp188, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp178))))
		DeclareVarInst(stack, "float", fTemp189, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp180))))
		DeclareVarInst(stack, "float", fTemp190, BinopInst("*", LoadVarInst(stack, fTemp174), LoadVarInst(stack, fTemp176)))
		DeclareVarInst(stack, "int", iTemp191, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp171), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp192, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp180)))
		DeclareVarInst(stack, "float", fTemp193, BinopInst("*", LoadVarInst(stack, fTemp190), LoadVarInst(stack, fTemp178)))
		DeclareVarInst(stack, "int", iTemp194, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp171), Int32(4)))))))
		StoreVarInst(struct, fRec115[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec95[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp172), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp175)), LoadVarInst(stack, fTemp177)), LoadVarInst(stack, fTemp179)), LoadVarInst(stack, fTemp181)), BinopInst("*", LoadVarInst(stack, fTemp182), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp174), LoadVarInst(struct, fRec95[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp183), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp184)), LoadVarInst(stack, fTemp185))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec95[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp186), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp187)), LoadVarInst(stack, fTemp188)), LoadVarInst(stack, fTemp189))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp190), LoadVarInst(struct, fRec95[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp191), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp192)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp193), LoadVarInst(struct, fRec95[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp194), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec120[Int32(0)], LoadVarInst(struct, fRec93[Int32(1)]))
		StoreVarInst(struct, fRec121[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec120[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec120[Int32(1)]), LoadVarInst(struct, fRec120[Int32(3)])))))))
		DeclareVarInst(stack, "int", iRec122, Int32(0))
		DeclareVarInst(stack, "float", fTemp195, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp168)))
		DeclareVarInst(stack, "float", fTemp196, BinopInst("+", LoadVarInst(stack, fTemp195), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp197, CastInst("int", LoadVarInst(stack, fTemp196)))
		DeclareVarInst(stack, "int", iTemp198, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp197))))))
		DeclareVarInst(stack, "float", fTemp199, FunCallInst("floorf", LoadVarInst(stack, fTemp196)))
		DeclareVarInst(stack, "float", fTemp200, BinopInst("+", LoadVarInst(stack, fTemp195), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp199))))
		DeclareVarInst(stack, "float", fTemp201, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp200)))
		DeclareVarInst(stack, "float", fTemp202, BinopInst("+", LoadVarInst(stack, fTemp195), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp199))))
		DeclareVarInst(stack, "float", fTemp203, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp202))))
		DeclareVarInst(stack, "float", fTemp204, BinopInst("+", LoadVarInst(stack, fTemp195), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp199))))
		DeclareVarInst(stack, "float", fTemp205, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp204))))
		DeclareVarInst(stack, "float", fTemp206, BinopInst("+", LoadVarInst(stack, fTemp195), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp199))))
		DeclareVarInst(stack, "float", fTemp207, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp206))))
		DeclareVarInst(stack, "float", fTemp208, BinopInst("-", LoadVarInst(stack, fTemp195), LoadVarInst(stack, fTemp199)))
		DeclareVarInst(stack, "int", iTemp209, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp197), Int32(2)))))))
		DeclareVarInst(stack, "float", fTemp210, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp204)))
		DeclareVarInst(stack, "float", fTemp211, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp206))))
		DeclareVarInst(stack, "int", iTemp212, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp197), Int32(1)))))))
		DeclareVarInst(stack, "float", fTemp213, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp202)))
		DeclareVarInst(stack, "float", fTemp214, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp204))))
		DeclareVarInst(stack, "float", fTemp215, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp206))))
		DeclareVarInst(stack, "float", fTemp216, BinopInst("*", LoadVarInst(stack, fTemp200), LoadVarInst(stack, fTemp202)))
		DeclareVarInst(stack, "int", iTemp217, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp197), Int32(3)))))))
		DeclareVarInst(stack, "float", fTemp218, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp206)))
		DeclareVarInst(stack, "float", fTemp219, BinopInst("*", LoadVarInst(stack, fTemp216), LoadVarInst(stack, fTemp204)))
		DeclareVarInst(stack, "int", iTemp220, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp197), Int32(4)))))))
		StoreVarInst(struct, fVec6[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec121[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp198), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp201)), LoadVarInst(stack, fTemp203)), LoadVarInst(stack, fTemp205)), LoadVarInst(stack, fTemp207)), BinopInst("*", LoadVarInst(stack, fTemp208), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp200), LoadVarInst(struct, fRec121[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp209), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp210)), LoadVarInst(stack, fTemp211))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec121[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp212), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp213)), LoadVarInst(stack, fTemp214)), LoadVarInst(stack, fTemp215))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp216), LoadVarInst(struct, fRec121[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp217), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp218)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp219), LoadVarInst(struct, fRec121[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp220), Int32(2))), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp221, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow9)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec115[Int32(1)]), LoadVarInst(struct, fVec6[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp222, BinopInst("*", LoadVarInst(stack, fTemp221), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(stack, fTemp221))), Float(0.75f)))))))
		DeclareVarInst(stack, "float", fRec116, BinopInst("+", LoadVarInst(struct, fRec115[Int32(1)]), LoadVarInst(stack, fTemp222)))
		DeclareVarInst(stack, "float", fTemp223, BinopInst("+", LoadVarInst(struct, fVec6[Int32(1)]), LoadVarInst(stack, fTemp222)))
		StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp223))
		DeclareVarInst(stack, "float", fRec117, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp175), LoadVarInst(stack, fTemp177)), LoadVarInst(stack, fTemp179)), LoadVarInst(stack, fTemp181)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp172)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp182), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp193), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp194)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp187), LoadVarInst(stack, fTemp188)), LoadVarInst(stack, fTemp189)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp186)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp174), LoadVarInst(stack, fTemp184)), LoadVarInst(stack, fTemp185)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp183)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp190), LoadVarInst(stack, fTemp192)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp191)), Int32(2047))]))))))))
		DeclareVarInst(stack, "int", iRec118, LoadVarInst(stack, iRec122))
		StoreVarInst(struct, fRec111[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec116))
		DeclareVarInst(stack, "float", fRec112, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp201), LoadVarInst(stack, fTemp203)), LoadVarInst(stack, fTemp205)), LoadVarInst(stack, fTemp207)), LoadVarInst(struct, fRec111[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp198), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp208), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp216), LoadVarInst(stack, fTemp218)), LoadVarInst(struct, fRec111[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp217), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp213), LoadVarInst(stack, fTemp214)), LoadVarInst(stack, fTemp215)), LoadVarInst(struct, fRec111[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp212), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp200), LoadVarInst(stack, fTemp210)), LoadVarInst(stack, fTemp211)), LoadVarInst(struct, fRec111[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp209), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp219), LoadVarInst(struct, fRec111[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp220), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec113[Int32(0)], LoadVarInst(stack, fRec117))
		DeclareVarInst(stack, "int", iRec114, LoadVarInst(stack, iRec118))
		StoreVarInst(struct, fRec109[Int32(0)], LoadVarInst(struct, fRec113[Int32(1)]))
		DeclareVarInst(stack, "int", iRec110, LoadVarInst(stack, iRec114))
		StoreVarInst(struct, fRec107[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec109[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec107[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec107[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp224, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec107[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec107[Int32(2)])))))
		DeclareVarInst(stack, "float", fRec105, LoadVarInst(stack, fTemp224))
		DeclareVarInst(stack, "float", fRec106, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec110)), LoadVarInst(stack, fTemp224)))
		StoreVarInst(struct, iRec99[Int32(0)], LoadVarInst(stack, iRec104))
		DeclareVarInst(stack, "float", fRec100, LoadVarInst(stack, fRec108))
		DeclareVarInst(stack, "float", fRec101, LoadVarInst(stack, fRec105))
		DeclareVarInst(stack, "float", fRec102, LoadVarInst(stack, fRec106))
		StoreVarInst(struct, fRec95[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec100))
		DeclareVarInst(stack, "float", fRec96, LoadVarInst(stack, fRec112))
		DeclareVarInst(stack, "float", fRec97, LoadVarInst(stack, fRec101))
		DeclareVarInst(stack, "float", fRec98, LoadVarInst(stack, fRec102))
		StoreVarInst(struct, fRec93[Int32(0)], LoadVarInst(stack, fRec96))
		DeclareVarInst(stack, "float", fRec94, LoadVarInst(stack, fRec98))
		DeclareVarInst(stack, "float", fTemp225, BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec1), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec64)), LoadVarInst(stack, fRec94)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp225)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp225)))
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
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
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
		StoreVarInst(struct, iRec43[Int32(1)], LoadVarInst(struct, iRec43[Int32(0)]))
		StoreVarInst(struct, fRec59[Int32(1)], LoadVarInst(struct, fRec59[Int32(0)]))
		StoreVarInst(struct, fRec55[Int32(1)], LoadVarInst(struct, fRec55[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j2, Int32(3))
			BinopInst(">", LoadVarInst(loop, j2), Int32(0))
			StoreVarInst(loop, j2, BinopInst("-", LoadVarInst(loop, j2), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec60[LoadVarInst(loop, j2)], LoadVarInst(struct, fRec60[BinopInst("-", LoadVarInst(loop, j2), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec53[Int32(1)], LoadVarInst(struct, fRec53[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j3, Int32(3))
			BinopInst(">", LoadVarInst(loop, j3), Int32(0))
			StoreVarInst(loop, j3, BinopInst("-", LoadVarInst(loop, j3), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec49[LoadVarInst(loop, j3)], LoadVarInst(struct, fRec49[BinopInst("-", LoadVarInst(loop, j3), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fRec47[Int32(2)], LoadVarInst(struct, fRec47[Int32(1)]))
		StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
		StoreVarInst(struct, iRec39[Int32(1)], LoadVarInst(struct, iRec39[Int32(0)]))
		StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
		StoreVarInst(struct, iRec73[Int32(1)], LoadVarInst(struct, iRec73[Int32(0)]))
		StoreVarInst(struct, fRec89[Int32(1)], LoadVarInst(struct, fRec89[Int32(0)]))
		StoreVarInst(struct, fRec85[Int32(1)], LoadVarInst(struct, fRec85[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j4, Int32(3))
			BinopInst(">", LoadVarInst(loop, j4), Int32(0))
			StoreVarInst(loop, j4, BinopInst("-", LoadVarInst(loop, j4), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec90[LoadVarInst(loop, j4)], LoadVarInst(struct, fRec90[BinopInst("-", LoadVarInst(loop, j4), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
		StoreVarInst(struct, fRec83[Int32(1)], LoadVarInst(struct, fRec83[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j5, Int32(3))
			BinopInst(">", LoadVarInst(loop, j5), Int32(0))
			StoreVarInst(loop, j5, BinopInst("-", LoadVarInst(loop, j5), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec79[LoadVarInst(loop, j5)], LoadVarInst(struct, fRec79[BinopInst("-", LoadVarInst(loop, j5), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fRec77[Int32(2)], LoadVarInst(struct, fRec77[Int32(1)]))
		StoreVarInst(struct, fRec77[Int32(1)], LoadVarInst(struct, fRec77[Int32(0)]))
		StoreVarInst(struct, iRec69[Int32(1)], LoadVarInst(struct, iRec69[Int32(0)]))
		StoreVarInst(struct, fRec63[Int32(1)], LoadVarInst(struct, fRec63[Int32(0)]))
		StoreVarInst(struct, iRec103[Int32(1)], LoadVarInst(struct, iRec103[Int32(0)]))
		StoreVarInst(struct, fRec119[Int32(1)], LoadVarInst(struct, fRec119[Int32(0)]))
		StoreVarInst(struct, fRec115[Int32(1)], LoadVarInst(struct, fRec115[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j6, Int32(3))
			BinopInst(">", LoadVarInst(loop, j6), Int32(0))
			StoreVarInst(loop, j6, BinopInst("-", LoadVarInst(loop, j6), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec120[LoadVarInst(loop, j6)], LoadVarInst(struct, fRec120[BinopInst("-", LoadVarInst(loop, j6), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
		StoreVarInst(struct, fRec113[Int32(1)], LoadVarInst(struct, fRec113[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j7, Int32(3))
			BinopInst(">", LoadVarInst(loop, j7), Int32(0))
			StoreVarInst(loop, j7, BinopInst("-", LoadVarInst(loop, j7), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec109[LoadVarInst(loop, j7)], LoadVarInst(struct, fRec109[BinopInst("-", LoadVarInst(loop, j7), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fRec107[Int32(2)], LoadVarInst(struct, fRec107[Int32(1)]))
		StoreVarInst(struct, fRec107[Int32(1)], LoadVarInst(struct, fRec107[Int32(0)]))
		StoreVarInst(struct, iRec99[Int32(1)], LoadVarInst(struct, iRec99[Int32(0)]))
		StoreVarInst(struct, fRec93[Int32(1)], LoadVarInst(struct, fRec93[Int32(0)]))
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
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec32[2])
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
	DeclareVarInst(struct, int, iRec43[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec59[2])
	DeclareVarInst(struct, float, fRec55[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec60[4])
	DeclareVarInst(struct, float, fRec61[2048])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fVec3[2048])
	DeclareVarInst(struct, float, fRec51[2048])
	DeclareVarInst(struct, float, fRec53[2])
	DeclareVarInst(struct, float, fRec49[4])
	DeclareVarInst(struct, float, fRec47[3])
	DeclareVarInst(struct, int, iRec39[2])
	DeclareVarInst(struct, float, fRec35[2048])
	DeclareVarInst(struct, float, fRec33[2])
	DeclareVarInst(struct, int, iRec73[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, float, fRec89[2])
	DeclareVarInst(struct, float, fRec85[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider10)
	DeclareVarInst(struct, float, fRec90[4])
	DeclareVarInst(struct, float, fRec91[2048])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, float, fVec5[2048])
	DeclareVarInst(struct, float, fRec81[2048])
	DeclareVarInst(struct, float, fRec83[2])
	DeclareVarInst(struct, float, fRec79[4])
	DeclareVarInst(struct, float, fRec77[3])
	DeclareVarInst(struct, int, iRec69[2])
	DeclareVarInst(struct, float, fRec65[2048])
	DeclareVarInst(struct, float, fRec63[2])
	DeclareVarInst(struct, int, iRec103[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider11)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider12)
	DeclareVarInst(struct, float, fRec119[2])
	DeclareVarInst(struct, float, fRec115[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider13)
	DeclareVarInst(struct, float, fRec120[4])
	DeclareVarInst(struct, float, fRec121[2048])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, float, fVec7[2048])
	DeclareVarInst(struct, float, fRec111[2048])
	DeclareVarInst(struct, float, fRec113[2])
	DeclareVarInst(struct, float, fRec109[4])
	DeclareVarInst(struct, float, fRec107[3])
	DeclareVarInst(struct, int, iRec99[2])
	DeclareVarInst(struct, float, fRec95[2048])
	DeclareVarInst(struct, float, fRec93[2])
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
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(330.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider10, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider11, CastInst("FAUSTFLOAT", Double(550.0f)))
	StoreVarInst(struct, fHslider12, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider13, CastInst("FAUSTFLOAT", Double(0.0f)))
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
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2048))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2048))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(4))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(3))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[LoadVarInst(loop, l14)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2048))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec43[LoadVarInst(loop, l17)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec55[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(4))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2048))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec61[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2048))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2048))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec53[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(4))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(3))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec39[LoadVarInst(loop, l28)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2048))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec73[LoadVarInst(loop, l31)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec89[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec85[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(4))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec90[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2048))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec91[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2048))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2048))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec81[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(2))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec83[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(4))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec79[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(3))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec77[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec69[LoadVarInst(loop, l42)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(2048))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec65[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(2))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec63[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(2))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec103[LoadVarInst(loop, l45)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec119[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(2))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec115[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(4))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec120[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2048))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec121[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(2048))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2048))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec111[LoadVarInst(loop, l52)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(2))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec113[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(4))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec109[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(3))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec107[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(2))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec99[LoadVarInst(loop, l56)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(2048))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec95[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(2))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec93[LoadVarInst(loop, l58)], Float(0.0f))
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
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider4))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider5)), CastInst("float", LoadVarInst(struct, fHslider6)))))
	DeclareVarInst(stack, "int", iSlow5, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider7))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider8)), CastInst("float", LoadVarInst(struct, fHslider9)))))
	DeclareVarInst(stack, "int", iSlow7, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider10))), Int32(0)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("/", Float(0.340000004f), BinopInst("*", CastInst("float", LoadVarInst(struct, fHslider11)), CastInst("float", LoadVarInst(struct, fHslider12)))))
	DeclareVarInst(stack, "int", iSlow9, BinopInst(">", CastInst("int", CastInst("float", LoadVarInst(struct, fHslider13))), Int32(0)))
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
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", Float(0.00100000005f), FunCallInst("min_f", Float(1.0f), BinopInst("*", Float(8000.0f), FunCallInst("fabsf", BinopInst("-", LoadVarInst(struct, fRec28[Int32(0)]), LoadVarInst(struct, fRec28[Int32(1)]))))))))
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
			StoreVarInst(struct, fRec32[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec32[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("-", Float(5.0f), BinopInst("*", Float(4.0f), LoadVarInst(struct, fRec32[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp55, BinopInst("*", LoadVarInst(stack, fTemp53), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(stack, fTemp53))), Float(0.75f)))))))
			DeclareVarInst(stack, "float", fRec23, BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(stack, fTemp55)))
			DeclareVarInst(stack, "float", fTemp56, BinopInst("+", LoadVarInst(struct, fVec0[Int32(1)]), LoadVarInst(stack, fTemp55)))
			StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp56))
			DeclareVarInst(stack, "float", fRec24, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp9)), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp4)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp14), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp26)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp18)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp6), LoadVarInst(stack, fTemp16)), LoadVarInst(stack, fTemp17)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp15)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(stack, fTemp24)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp23)), Int32(2047))]))))))))
			DeclareVarInst(stack, "int", iRec25, LoadVarInst(stack, iRec31))
			StoreVarInst(struct, fRec18[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec23))
			DeclareVarInst(stack, "float", fRec19, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp37)), LoadVarInst(stack, fTemp39)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp30), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp40), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(stack, fTemp50)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp49), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp45), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp44), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp32), LoadVarInst(stack, fTemp42)), LoadVarInst(stack, fTemp43)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp41), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp52), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(stack, fRec24))
			DeclareVarInst(stack, "int", iRec21, LoadVarInst(stack, iRec25))
			StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(struct, fRec20[Int32(1)]))
			DeclareVarInst(stack, "int", iRec17, LoadVarInst(stack, iRec21))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec14[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec14[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp57, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec14[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec14[Int32(2)])))))
			DeclareVarInst(stack, "float", fRec12, LoadVarInst(stack, fTemp57))
			DeclareVarInst(stack, "float", fRec13, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec17)), LoadVarInst(stack, fTemp57)))
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
			StoreVarInst(struct, iRec43[Int32(0)], Int32(0))
			DeclareVarInst(stack, "int", iRec44, LoadVarInst(struct, iRec43[Int32(1)]))
			DeclareVarInst(stack, "float", fRec48, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec39[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec49[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec49[Int32(1)]), LoadVarInst(struct, fRec49[Int32(3)])))))))
			StoreVarInst(struct, fRec59[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec59[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp58, BinopInst("+", LoadVarInst(struct, fRec59[Int32(0)]), Float(-0.0799999982f)))
			DeclareVarInst(stack, "float", fTemp59, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp58)))
			DeclareVarInst(stack, "float", fTemp60, BinopInst("+", LoadVarInst(stack, fTemp59), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp61, CastInst("int", LoadVarInst(stack, fTemp60)))
			DeclareVarInst(stack, "int", iTemp62, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp61))))))
			DeclareVarInst(stack, "float", fTemp63, FunCallInst("floorf", LoadVarInst(stack, fTemp60)))
			DeclareVarInst(stack, "float", fTemp64, BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp63))))
			DeclareVarInst(stack, "float", fTemp65, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp64)))
			DeclareVarInst(stack, "float", fTemp66, BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp63))))
			DeclareVarInst(stack, "float", fTemp67, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp66))))
			DeclareVarInst(stack, "float", fTemp68, BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp63))))
			DeclareVarInst(stack, "float", fTemp69, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp68))))
			DeclareVarInst(stack, "float", fTemp70, BinopInst("+", LoadVarInst(stack, fTemp59), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp63))))
			DeclareVarInst(stack, "float", fTemp71, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp70))))
			DeclareVarInst(stack, "float", fTemp72, BinopInst("-", LoadVarInst(stack, fTemp59), LoadVarInst(stack, fTemp63)))
			DeclareVarInst(stack, "int", iTemp73, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp61), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp74, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp68)))
			DeclareVarInst(stack, "float", fTemp75, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp70))))
			DeclareVarInst(stack, "int", iTemp76, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp61), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp77, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp66)))
			DeclareVarInst(stack, "float", fTemp78, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp68))))
			DeclareVarInst(stack, "float", fTemp79, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp70))))
			DeclareVarInst(stack, "float", fTemp80, BinopInst("*", LoadVarInst(stack, fTemp64), LoadVarInst(stack, fTemp66)))
			DeclareVarInst(stack, "int", iTemp81, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp61), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp82, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp70)))
			DeclareVarInst(stack, "float", fTemp83, BinopInst("*", LoadVarInst(stack, fTemp80), LoadVarInst(stack, fTemp68)))
			DeclareVarInst(stack, "int", iTemp84, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp61), Int32(4)))))))
			StoreVarInst(struct, fRec55[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec35[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp62), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp65)), LoadVarInst(stack, fTemp67)), LoadVarInst(stack, fTemp69)), LoadVarInst(stack, fTemp71)), BinopInst("*", LoadVarInst(stack, fTemp72), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp64), LoadVarInst(struct, fRec35[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp73), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp74)), LoadVarInst(stack, fTemp75))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec35[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp76), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp77)), LoadVarInst(stack, fTemp78)), LoadVarInst(stack, fTemp79))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp80), LoadVarInst(struct, fRec35[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp81), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp82)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp83), LoadVarInst(struct, fRec35[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp84), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec60[Int32(0)], LoadVarInst(struct, fRec33[Int32(1)]))
			StoreVarInst(struct, fRec61[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec60[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec60[Int32(1)]), LoadVarInst(struct, fRec60[Int32(3)])))))))
			DeclareVarInst(stack, "int", iRec62, Int32(0))
			DeclareVarInst(stack, "float", fTemp85, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp58)))
			DeclareVarInst(stack, "float", fTemp86, BinopInst("+", LoadVarInst(stack, fTemp85), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp87, CastInst("int", LoadVarInst(stack, fTemp86)))
			DeclareVarInst(stack, "int", iTemp88, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp87))))))
			DeclareVarInst(stack, "float", fTemp89, FunCallInst("floorf", LoadVarInst(stack, fTemp86)))
			DeclareVarInst(stack, "float", fTemp90, BinopInst("+", LoadVarInst(stack, fTemp85), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp89))))
			DeclareVarInst(stack, "float", fTemp91, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp90)))
			DeclareVarInst(stack, "float", fTemp92, BinopInst("+", LoadVarInst(stack, fTemp85), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp89))))
			DeclareVarInst(stack, "float", fTemp93, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp92))))
			DeclareVarInst(stack, "float", fTemp94, BinopInst("+", LoadVarInst(stack, fTemp85), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp89))))
			DeclareVarInst(stack, "float", fTemp95, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp94))))
			DeclareVarInst(stack, "float", fTemp96, BinopInst("+", LoadVarInst(stack, fTemp85), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp89))))
			DeclareVarInst(stack, "float", fTemp97, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp96))))
			DeclareVarInst(stack, "float", fTemp98, BinopInst("-", LoadVarInst(stack, fTemp85), LoadVarInst(stack, fTemp89)))
			DeclareVarInst(stack, "int", iTemp99, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp100, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp94)))
			DeclareVarInst(stack, "float", fTemp101, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp96))))
			DeclareVarInst(stack, "int", iTemp102, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp103, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp92)))
			DeclareVarInst(stack, "float", fTemp104, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp94))))
			DeclareVarInst(stack, "float", fTemp105, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp96))))
			DeclareVarInst(stack, "float", fTemp106, BinopInst("*", LoadVarInst(stack, fTemp90), LoadVarInst(stack, fTemp92)))
			DeclareVarInst(stack, "int", iTemp107, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp108, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp96)))
			DeclareVarInst(stack, "float", fTemp109, BinopInst("*", LoadVarInst(stack, fTemp106), LoadVarInst(stack, fTemp94)))
			DeclareVarInst(stack, "int", iTemp110, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp87), Int32(4)))))))
			StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec61[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp88), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp91)), LoadVarInst(stack, fTemp93)), LoadVarInst(stack, fTemp95)), LoadVarInst(stack, fTemp97)), BinopInst("*", LoadVarInst(stack, fTemp98), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp90), LoadVarInst(struct, fRec61[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp99), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp100)), LoadVarInst(stack, fTemp101))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec61[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp102), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp103)), LoadVarInst(stack, fTemp104)), LoadVarInst(stack, fTemp105))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp106), LoadVarInst(struct, fRec61[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp107), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp108)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp109), LoadVarInst(struct, fRec61[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp110), Int32(2))), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp111, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow5)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec55[Int32(1)]), LoadVarInst(struct, fVec2[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp112, BinopInst("*", LoadVarInst(stack, fTemp111), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(stack, fTemp111))), Float(0.75f)))))))
			DeclareVarInst(stack, "float", fRec56, BinopInst("+", LoadVarInst(struct, fRec55[Int32(1)]), LoadVarInst(stack, fTemp112)))
			DeclareVarInst(stack, "float", fTemp113, BinopInst("+", LoadVarInst(struct, fVec2[Int32(1)]), LoadVarInst(stack, fTemp112)))
			StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp113))
			DeclareVarInst(stack, "float", fRec57, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp65), LoadVarInst(stack, fTemp67)), LoadVarInst(stack, fTemp69)), LoadVarInst(stack, fTemp71)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp62)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp72), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp83), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp84)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp77), LoadVarInst(stack, fTemp78)), LoadVarInst(stack, fTemp79)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp76)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp64), LoadVarInst(stack, fTemp74)), LoadVarInst(stack, fTemp75)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp73)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp80), LoadVarInst(stack, fTemp82)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp81)), Int32(2047))]))))))))
			DeclareVarInst(stack, "int", iRec58, LoadVarInst(stack, iRec62))
			StoreVarInst(struct, fRec51[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec56))
			DeclareVarInst(stack, "float", fRec52, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp91), LoadVarInst(stack, fTemp93)), LoadVarInst(stack, fTemp95)), LoadVarInst(stack, fTemp97)), LoadVarInst(struct, fRec51[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp88), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp98), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp106), LoadVarInst(stack, fTemp108)), LoadVarInst(struct, fRec51[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp107), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp103), LoadVarInst(stack, fTemp104)), LoadVarInst(stack, fTemp105)), LoadVarInst(struct, fRec51[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp102), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp90), LoadVarInst(stack, fTemp100)), LoadVarInst(stack, fTemp101)), LoadVarInst(struct, fRec51[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp99), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp109), LoadVarInst(struct, fRec51[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp110), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec53[Int32(0)], LoadVarInst(stack, fRec57))
			DeclareVarInst(stack, "int", iRec54, LoadVarInst(stack, iRec58))
			StoreVarInst(struct, fRec49[Int32(0)], LoadVarInst(struct, fRec53[Int32(1)]))
			DeclareVarInst(stack, "int", iRec50, LoadVarInst(stack, iRec54))
			StoreVarInst(struct, fRec47[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec49[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec47[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec47[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp114, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec47[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec47[Int32(2)])))))
			DeclareVarInst(stack, "float", fRec45, LoadVarInst(stack, fTemp114))
			DeclareVarInst(stack, "float", fRec46, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec50)), LoadVarInst(stack, fTemp114)))
			StoreVarInst(struct, iRec39[Int32(0)], LoadVarInst(stack, iRec44))
			DeclareVarInst(stack, "float", fRec40, LoadVarInst(stack, fRec48))
			DeclareVarInst(stack, "float", fRec41, LoadVarInst(stack, fRec45))
			DeclareVarInst(stack, "float", fRec42, LoadVarInst(stack, fRec46))
			StoreVarInst(struct, fRec35[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec40))
			DeclareVarInst(stack, "float", fRec36, LoadVarInst(stack, fRec52))
			DeclareVarInst(stack, "float", fRec37, LoadVarInst(stack, fRec41))
			DeclareVarInst(stack, "float", fRec38, LoadVarInst(stack, fRec42))
			StoreVarInst(struct, fRec33[Int32(0)], LoadVarInst(stack, fRec36))
			DeclareVarInst(stack, "float", fRec34, LoadVarInst(stack, fRec38))
			StoreVarInst(struct, iRec73[Int32(0)], Int32(0))
			DeclareVarInst(stack, "int", iRec74, LoadVarInst(struct, iRec73[Int32(1)]))
			DeclareVarInst(stack, "float", fRec78, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec69[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec79[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec79[Int32(1)]), LoadVarInst(struct, fRec79[Int32(3)])))))))
			StoreVarInst(struct, fRec89[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec89[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp115, BinopInst("+", LoadVarInst(struct, fRec89[Int32(0)]), Float(-0.0799999982f)))
			DeclareVarInst(stack, "float", fTemp116, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp115)))
			DeclareVarInst(stack, "float", fTemp117, BinopInst("+", LoadVarInst(stack, fTemp116), Float(-1.49999499f)))
			DeclareVarInst(stack, "float", fTemp118, FunCallInst("floorf", LoadVarInst(stack, fTemp117)))
			DeclareVarInst(stack, "float", fTemp119, BinopInst("+", LoadVarInst(stack, fTemp116), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp118))))
			DeclareVarInst(stack, "float", fTemp120, BinopInst("+", LoadVarInst(stack, fTemp116), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp118))))
			DeclareVarInst(stack, "float", fTemp121, BinopInst("+", LoadVarInst(stack, fTemp116), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp118))))
			DeclareVarInst(stack, "float", fTemp122, BinopInst("*", BinopInst("*", BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp119))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp120)))), BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp121)))))
			DeclareVarInst(stack, "int", iTemp123, CastInst("int", LoadVarInst(stack, fTemp117)))
			DeclareVarInst(stack, "int", iTemp124, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp123))))))
			DeclareVarInst(stack, "float", fTemp125, BinopInst("+", LoadVarInst(stack, fTemp116), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp118))))
			DeclareVarInst(stack, "float", fTemp126, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp125)))
			DeclareVarInst(stack, "int", iTemp127, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp123), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp128, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp119)))
			DeclareVarInst(stack, "float", fTemp129, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp120))))
			DeclareVarInst(stack, "float", fTemp130, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp121))))
			DeclareVarInst(stack, "int", iTemp131, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp123), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp132, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp120)))
			DeclareVarInst(stack, "float", fTemp133, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp121))))
			DeclareVarInst(stack, "int", iTemp134, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp123), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp135, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp121)))
			DeclareVarInst(stack, "int", iTemp136, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp123), Int32(4)))))))
			DeclareVarInst(stack, "float", fTemp137, BinopInst("-", LoadVarInst(stack, fTemp116), LoadVarInst(stack, fTemp118)))
			StoreVarInst(struct, fRec85[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp122), LoadVarInst(struct, fRec65[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp124), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp126)), BinopInst("*", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec65[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp127), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp128)), LoadVarInst(stack, fTemp129)), LoadVarInst(stack, fTemp130)), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec65[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp131), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp132)), LoadVarInst(stack, fTemp133)), LoadVarInst(stack, fTemp125)))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec65[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp134), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp135)), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp119)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp120), LoadVarInst(struct, fRec65[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp136), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp119)))), LoadVarInst(stack, fTemp137))))
			StoreVarInst(struct, fRec90[Int32(0)], LoadVarInst(struct, fRec63[Int32(1)]))
			StoreVarInst(struct, fRec91[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec90[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec90[Int32(1)]), LoadVarInst(struct, fRec90[Int32(3)])))))))
			DeclareVarInst(stack, "int", iRec92, Int32(0))
			DeclareVarInst(stack, "float", fTemp138, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp115)))
			DeclareVarInst(stack, "float", fTemp139, BinopInst("+", LoadVarInst(stack, fTemp138), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp140, CastInst("int", LoadVarInst(stack, fTemp139)))
			DeclareVarInst(stack, "int", iTemp141, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp140))))))
			DeclareVarInst(stack, "float", fTemp142, FunCallInst("floorf", LoadVarInst(stack, fTemp139)))
			DeclareVarInst(stack, "float", fTemp143, BinopInst("+", LoadVarInst(stack, fTemp138), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp142))))
			DeclareVarInst(stack, "float", fTemp144, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp143)))
			DeclareVarInst(stack, "float", fTemp145, BinopInst("+", LoadVarInst(stack, fTemp138), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp142))))
			DeclareVarInst(stack, "float", fTemp146, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp145))))
			DeclareVarInst(stack, "float", fTemp147, BinopInst("+", LoadVarInst(stack, fTemp138), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp142))))
			DeclareVarInst(stack, "float", fTemp148, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp147))))
			DeclareVarInst(stack, "float", fTemp149, BinopInst("+", LoadVarInst(stack, fTemp138), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp142))))
			DeclareVarInst(stack, "float", fTemp150, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp149))))
			DeclareVarInst(stack, "float", fTemp151, BinopInst("-", LoadVarInst(stack, fTemp138), LoadVarInst(stack, fTemp142)))
			DeclareVarInst(stack, "int", iTemp152, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp140), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp153, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp147)))
			DeclareVarInst(stack, "float", fTemp154, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp149))))
			DeclareVarInst(stack, "int", iTemp155, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp140), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp156, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp145)))
			DeclareVarInst(stack, "float", fTemp157, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp147))))
			DeclareVarInst(stack, "float", fTemp158, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp149))))
			DeclareVarInst(stack, "float", fTemp159, BinopInst("*", LoadVarInst(stack, fTemp143), LoadVarInst(stack, fTemp145)))
			DeclareVarInst(stack, "int", iTemp160, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp140), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp161, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp149)))
			DeclareVarInst(stack, "float", fTemp162, BinopInst("*", LoadVarInst(stack, fTemp159), LoadVarInst(stack, fTemp147)))
			DeclareVarInst(stack, "int", iTemp163, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp140), Int32(4)))))))
			StoreVarInst(struct, fVec4[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec91[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp141), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp144)), LoadVarInst(stack, fTemp146)), LoadVarInst(stack, fTemp148)), LoadVarInst(stack, fTemp150)), BinopInst("*", LoadVarInst(stack, fTemp151), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp143), LoadVarInst(struct, fRec91[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp152), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp153)), LoadVarInst(stack, fTemp154))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec91[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp155), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp156)), LoadVarInst(stack, fTemp157)), LoadVarInst(stack, fTemp158))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp159), LoadVarInst(struct, fRec91[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp160), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp161)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp162), LoadVarInst(struct, fRec91[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp163), Int32(2))), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp164, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow7)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec85[Int32(1)]), LoadVarInst(struct, fVec4[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp165, BinopInst("*", LoadVarInst(stack, fTemp164), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(stack, fTemp164))), Float(0.75f)))))))
			DeclareVarInst(stack, "float", fRec86, BinopInst("+", LoadVarInst(struct, fRec85[Int32(1)]), LoadVarInst(stack, fTemp165)))
			DeclareVarInst(stack, "float", fTemp166, BinopInst("+", LoadVarInst(struct, fVec4[Int32(1)]), LoadVarInst(stack, fTemp165)))
			StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp166))
			DeclareVarInst(stack, "float", fRec87, BinopInst("+", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp122), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp124)), Int32(2047))])), LoadVarInst(stack, fTemp126)), BinopInst("*", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp128), LoadVarInst(stack, fTemp129)), LoadVarInst(stack, fTemp130)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp127)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp132), LoadVarInst(stack, fTemp133)), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp131)), Int32(2047))])), LoadVarInst(stack, fTemp125)))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp135), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp134)), Int32(2047))])), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp119)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp120), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp136)), Int32(2047))])), LoadVarInst(stack, fTemp125)), LoadVarInst(stack, fTemp119)))), LoadVarInst(stack, fTemp137))))
			DeclareVarInst(stack, "int", iRec88, LoadVarInst(stack, iRec92))
			StoreVarInst(struct, fRec81[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec86))
			DeclareVarInst(stack, "float", fRec82, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp144), LoadVarInst(stack, fTemp146)), LoadVarInst(stack, fTemp148)), LoadVarInst(stack, fTemp150)), LoadVarInst(struct, fRec81[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp141), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp151), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp159), LoadVarInst(stack, fTemp161)), LoadVarInst(struct, fRec81[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp160), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp156), LoadVarInst(stack, fTemp157)), LoadVarInst(stack, fTemp158)), LoadVarInst(struct, fRec81[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp155), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp143), LoadVarInst(stack, fTemp153)), LoadVarInst(stack, fTemp154)), LoadVarInst(struct, fRec81[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp152), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp162), LoadVarInst(struct, fRec81[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp163), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec83[Int32(0)], LoadVarInst(stack, fRec87))
			DeclareVarInst(stack, "int", iRec84, LoadVarInst(stack, iRec88))
			StoreVarInst(struct, fRec79[Int32(0)], LoadVarInst(struct, fRec83[Int32(1)]))
			DeclareVarInst(stack, "int", iRec80, LoadVarInst(stack, iRec84))
			StoreVarInst(struct, fRec77[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec79[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec77[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec77[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp167, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec77[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec77[Int32(2)])))))
			DeclareVarInst(stack, "float", fRec75, LoadVarInst(stack, fTemp167))
			DeclareVarInst(stack, "float", fRec76, BinopInst("+", LoadVarInst(stack, fTemp167), CastInst("float", LoadVarInst(stack, iRec80))))
			StoreVarInst(struct, iRec69[Int32(0)], LoadVarInst(stack, iRec74))
			DeclareVarInst(stack, "float", fRec70, LoadVarInst(stack, fRec78))
			DeclareVarInst(stack, "float", fRec71, LoadVarInst(stack, fRec75))
			DeclareVarInst(stack, "float", fRec72, LoadVarInst(stack, fRec76))
			StoreVarInst(struct, fRec65[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec70))
			DeclareVarInst(stack, "float", fRec66, LoadVarInst(stack, fRec82))
			DeclareVarInst(stack, "float", fRec67, LoadVarInst(stack, fRec71))
			DeclareVarInst(stack, "float", fRec68, LoadVarInst(stack, fRec72))
			StoreVarInst(struct, fRec63[Int32(0)], LoadVarInst(stack, fRec66))
			DeclareVarInst(stack, "float", fRec64, LoadVarInst(stack, fRec68))
			StoreVarInst(struct, iRec103[Int32(0)], Int32(0))
			DeclareVarInst(stack, "int", iRec104, LoadVarInst(struct, iRec103[Int32(1)]))
			DeclareVarInst(stack, "float", fRec108, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec99[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec109[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec109[Int32(1)]), LoadVarInst(struct, fRec109[Int32(3)])))))))
			StoreVarInst(struct, fRec119[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec119[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp168, BinopInst("+", LoadVarInst(struct, fRec119[Int32(0)]), Float(-0.0799999982f)))
			DeclareVarInst(stack, "float", fTemp169, BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp168)))
			DeclareVarInst(stack, "float", fTemp170, BinopInst("+", LoadVarInst(stack, fTemp169), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp171, CastInst("int", LoadVarInst(stack, fTemp170)))
			DeclareVarInst(stack, "int", iTemp172, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp171))))))
			DeclareVarInst(stack, "float", fTemp173, FunCallInst("floorf", LoadVarInst(stack, fTemp170)))
			DeclareVarInst(stack, "float", fTemp174, BinopInst("+", LoadVarInst(stack, fTemp169), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp173))))
			DeclareVarInst(stack, "float", fTemp175, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp174)))
			DeclareVarInst(stack, "float", fTemp176, BinopInst("+", LoadVarInst(stack, fTemp169), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp173))))
			DeclareVarInst(stack, "float", fTemp177, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp176))))
			DeclareVarInst(stack, "float", fTemp178, BinopInst("+", LoadVarInst(stack, fTemp169), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp173))))
			DeclareVarInst(stack, "float", fTemp179, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp178))))
			DeclareVarInst(stack, "float", fTemp180, BinopInst("+", LoadVarInst(stack, fTemp169), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp173))))
			DeclareVarInst(stack, "float", fTemp181, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp180))))
			DeclareVarInst(stack, "float", fTemp182, BinopInst("-", LoadVarInst(stack, fTemp169), LoadVarInst(stack, fTemp173)))
			DeclareVarInst(stack, "int", iTemp183, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp171), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp184, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp178)))
			DeclareVarInst(stack, "float", fTemp185, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp180))))
			DeclareVarInst(stack, "int", iTemp186, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp171), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp187, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp176)))
			DeclareVarInst(stack, "float", fTemp188, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp178))))
			DeclareVarInst(stack, "float", fTemp189, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp180))))
			DeclareVarInst(stack, "float", fTemp190, BinopInst("*", LoadVarInst(stack, fTemp174), LoadVarInst(stack, fTemp176)))
			DeclareVarInst(stack, "int", iTemp191, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp171), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp192, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp180)))
			DeclareVarInst(stack, "float", fTemp193, BinopInst("*", LoadVarInst(stack, fTemp190), LoadVarInst(stack, fTemp178)))
			DeclareVarInst(stack, "int", iTemp194, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp171), Int32(4)))))))
			StoreVarInst(struct, fRec115[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec95[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp172), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp175)), LoadVarInst(stack, fTemp177)), LoadVarInst(stack, fTemp179)), LoadVarInst(stack, fTemp181)), BinopInst("*", LoadVarInst(stack, fTemp182), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp174), LoadVarInst(struct, fRec95[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp183), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp184)), LoadVarInst(stack, fTemp185))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec95[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp186), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp187)), LoadVarInst(stack, fTemp188)), LoadVarInst(stack, fTemp189))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp190), LoadVarInst(struct, fRec95[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp191), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp192)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp193), LoadVarInst(struct, fRec95[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp194), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec120[Int32(0)], LoadVarInst(struct, fRec93[Int32(1)]))
			StoreVarInst(struct, fRec121[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec120[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec120[Int32(1)]), LoadVarInst(struct, fRec120[Int32(3)])))))))
			DeclareVarInst(stack, "int", iRec122, Int32(0))
			DeclareVarInst(stack, "float", fTemp195, BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp168)))
			DeclareVarInst(stack, "float", fTemp196, BinopInst("+", LoadVarInst(stack, fTemp195), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp197, CastInst("int", LoadVarInst(stack, fTemp196)))
			DeclareVarInst(stack, "int", iTemp198, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp197))))))
			DeclareVarInst(stack, "float", fTemp199, FunCallInst("floorf", LoadVarInst(stack, fTemp196)))
			DeclareVarInst(stack, "float", fTemp200, BinopInst("+", LoadVarInst(stack, fTemp195), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp199))))
			DeclareVarInst(stack, "float", fTemp201, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp200)))
			DeclareVarInst(stack, "float", fTemp202, BinopInst("+", LoadVarInst(stack, fTemp195), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp199))))
			DeclareVarInst(stack, "float", fTemp203, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp202))))
			DeclareVarInst(stack, "float", fTemp204, BinopInst("+", LoadVarInst(stack, fTemp195), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp199))))
			DeclareVarInst(stack, "float", fTemp205, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp204))))
			DeclareVarInst(stack, "float", fTemp206, BinopInst("+", LoadVarInst(stack, fTemp195), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp199))))
			DeclareVarInst(stack, "float", fTemp207, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp206))))
			DeclareVarInst(stack, "float", fTemp208, BinopInst("-", LoadVarInst(stack, fTemp195), LoadVarInst(stack, fTemp199)))
			DeclareVarInst(stack, "int", iTemp209, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp197), Int32(2)))))))
			DeclareVarInst(stack, "float", fTemp210, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp204)))
			DeclareVarInst(stack, "float", fTemp211, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp206))))
			DeclareVarInst(stack, "int", iTemp212, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp197), Int32(1)))))))
			DeclareVarInst(stack, "float", fTemp213, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp202)))
			DeclareVarInst(stack, "float", fTemp214, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp204))))
			DeclareVarInst(stack, "float", fTemp215, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp206))))
			DeclareVarInst(stack, "float", fTemp216, BinopInst("*", LoadVarInst(stack, fTemp200), LoadVarInst(stack, fTemp202)))
			DeclareVarInst(stack, "int", iTemp217, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp197), Int32(3)))))))
			DeclareVarInst(stack, "float", fTemp218, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp206)))
			DeclareVarInst(stack, "float", fTemp219, BinopInst("*", LoadVarInst(stack, fTemp216), LoadVarInst(stack, fTemp204)))
			DeclareVarInst(stack, "int", iTemp220, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp197), Int32(4)))))))
			StoreVarInst(struct, fVec6[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec121[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp198), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp201)), LoadVarInst(stack, fTemp203)), LoadVarInst(stack, fTemp205)), LoadVarInst(stack, fTemp207)), BinopInst("*", LoadVarInst(stack, fTemp208), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp200), LoadVarInst(struct, fRec121[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp209), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp210)), LoadVarInst(stack, fTemp211))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec121[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp212), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp213)), LoadVarInst(stack, fTemp214)), LoadVarInst(stack, fTemp215))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp216), LoadVarInst(struct, fRec121[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp217), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp218)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp219), LoadVarInst(struct, fRec121[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp220), Int32(2))), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp221, BinopInst("-", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow9)), LoadVarInst(struct, fRec27[Int32(0)])), BinopInst("+", LoadVarInst(struct, fRec115[Int32(1)]), LoadVarInst(struct, fVec6[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp222, BinopInst("*", LoadVarInst(stack, fTemp221), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(stack, fTemp221))), Float(0.75f)))))))
			DeclareVarInst(stack, "float", fRec116, BinopInst("+", LoadVarInst(struct, fRec115[Int32(1)]), LoadVarInst(stack, fTemp222)))
			DeclareVarInst(stack, "float", fTemp223, BinopInst("+", LoadVarInst(struct, fVec6[Int32(1)]), LoadVarInst(stack, fTemp222)))
			StoreVarInst(struct, fVec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp223))
			DeclareVarInst(stack, "float", fRec117, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp175), LoadVarInst(stack, fTemp177)), LoadVarInst(stack, fTemp179)), LoadVarInst(stack, fTemp181)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp172)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp182), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp193), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp194)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp187), LoadVarInst(stack, fTemp188)), LoadVarInst(stack, fTemp189)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp186)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp174), LoadVarInst(stack, fTemp184)), LoadVarInst(stack, fTemp185)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp183)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp190), LoadVarInst(stack, fTemp192)), LoadVarInst(struct, fVec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp191)), Int32(2047))]))))))))
			DeclareVarInst(stack, "int", iRec118, LoadVarInst(stack, iRec122))
			StoreVarInst(struct, fRec111[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec116))
			DeclareVarInst(stack, "float", fRec112, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp201), LoadVarInst(stack, fTemp203)), LoadVarInst(stack, fTemp205)), LoadVarInst(stack, fTemp207)), LoadVarInst(struct, fRec111[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp198), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp208), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp216), LoadVarInst(stack, fTemp218)), LoadVarInst(struct, fRec111[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp217), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp213), LoadVarInst(stack, fTemp214)), LoadVarInst(stack, fTemp215)), LoadVarInst(struct, fRec111[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp212), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp200), LoadVarInst(stack, fTemp210)), LoadVarInst(stack, fTemp211)), LoadVarInst(struct, fRec111[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp209), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp219), LoadVarInst(struct, fRec111[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp220), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec113[Int32(0)], LoadVarInst(stack, fRec117))
			DeclareVarInst(stack, "int", iRec114, LoadVarInst(stack, iRec118))
			StoreVarInst(struct, fRec109[Int32(0)], LoadVarInst(struct, fRec113[Int32(1)]))
			DeclareVarInst(stack, "int", iRec110, LoadVarInst(stack, iRec114))
			StoreVarInst(struct, fRec107[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec109[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec107[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec107[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp224, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec107[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec107[Int32(2)])))))
			DeclareVarInst(stack, "float", fRec105, LoadVarInst(stack, fTemp224))
			DeclareVarInst(stack, "float", fRec106, BinopInst("+", CastInst("float", LoadVarInst(stack, iRec110)), LoadVarInst(stack, fTemp224)))
			StoreVarInst(struct, iRec99[Int32(0)], LoadVarInst(stack, iRec104))
			DeclareVarInst(stack, "float", fRec100, LoadVarInst(stack, fRec108))
			DeclareVarInst(stack, "float", fRec101, LoadVarInst(stack, fRec105))
			DeclareVarInst(stack, "float", fRec102, LoadVarInst(stack, fRec106))
			StoreVarInst(struct, fRec95[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec100))
			DeclareVarInst(stack, "float", fRec96, LoadVarInst(stack, fRec112))
			DeclareVarInst(stack, "float", fRec97, LoadVarInst(stack, fRec101))
			DeclareVarInst(stack, "float", fRec98, LoadVarInst(stack, fRec102))
			StoreVarInst(struct, fRec93[Int32(0)], LoadVarInst(stack, fRec96))
			DeclareVarInst(stack, "float", fRec94, LoadVarInst(stack, fRec98))
			DeclareVarInst(stack, "float", fTemp225, BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fRec1), LoadVarInst(stack, fRec34)), LoadVarInst(stack, fRec64)), LoadVarInst(stack, fRec94)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp225)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp225)))
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
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
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
			StoreVarInst(struct, iRec43[Int32(1)], LoadVarInst(struct, iRec43[Int32(0)]))
			StoreVarInst(struct, fRec59[Int32(1)], LoadVarInst(struct, fRec59[Int32(0)]))
			StoreVarInst(struct, fRec55[Int32(1)], LoadVarInst(struct, fRec55[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j2, Int32(3))
				BinopInst(">", LoadVarInst(loop, j2), Int32(0))
				StoreVarInst(loop, j2, BinopInst("-", LoadVarInst(loop, j2), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec60[LoadVarInst(loop, j2)], LoadVarInst(struct, fRec60[BinopInst("-", LoadVarInst(loop, j2), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec53[Int32(1)], LoadVarInst(struct, fRec53[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j3, Int32(3))
				BinopInst(">", LoadVarInst(loop, j3), Int32(0))
				StoreVarInst(loop, j3, BinopInst("-", LoadVarInst(loop, j3), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec49[LoadVarInst(loop, j3)], LoadVarInst(struct, fRec49[BinopInst("-", LoadVarInst(loop, j3), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fRec47[Int32(2)], LoadVarInst(struct, fRec47[Int32(1)]))
			StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
			StoreVarInst(struct, iRec39[Int32(1)], LoadVarInst(struct, iRec39[Int32(0)]))
			StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
			StoreVarInst(struct, iRec73[Int32(1)], LoadVarInst(struct, iRec73[Int32(0)]))
			StoreVarInst(struct, fRec89[Int32(1)], LoadVarInst(struct, fRec89[Int32(0)]))
			StoreVarInst(struct, fRec85[Int32(1)], LoadVarInst(struct, fRec85[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j4, Int32(3))
				BinopInst(">", LoadVarInst(loop, j4), Int32(0))
				StoreVarInst(loop, j4, BinopInst("-", LoadVarInst(loop, j4), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec90[LoadVarInst(loop, j4)], LoadVarInst(struct, fRec90[BinopInst("-", LoadVarInst(loop, j4), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
			StoreVarInst(struct, fRec83[Int32(1)], LoadVarInst(struct, fRec83[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j5, Int32(3))
				BinopInst(">", LoadVarInst(loop, j5), Int32(0))
				StoreVarInst(loop, j5, BinopInst("-", LoadVarInst(loop, j5), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec79[LoadVarInst(loop, j5)], LoadVarInst(struct, fRec79[BinopInst("-", LoadVarInst(loop, j5), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fRec77[Int32(2)], LoadVarInst(struct, fRec77[Int32(1)]))
			StoreVarInst(struct, fRec77[Int32(1)], LoadVarInst(struct, fRec77[Int32(0)]))
			StoreVarInst(struct, iRec69[Int32(1)], LoadVarInst(struct, iRec69[Int32(0)]))
			StoreVarInst(struct, fRec63[Int32(1)], LoadVarInst(struct, fRec63[Int32(0)]))
			StoreVarInst(struct, iRec103[Int32(1)], LoadVarInst(struct, iRec103[Int32(0)]))
			StoreVarInst(struct, fRec119[Int32(1)], LoadVarInst(struct, fRec119[Int32(0)]))
			StoreVarInst(struct, fRec115[Int32(1)], LoadVarInst(struct, fRec115[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j6, Int32(3))
				BinopInst(">", LoadVarInst(loop, j6), Int32(0))
				StoreVarInst(loop, j6, BinopInst("-", LoadVarInst(loop, j6), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec120[LoadVarInst(loop, j6)], LoadVarInst(struct, fRec120[BinopInst("-", LoadVarInst(loop, j6), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
			StoreVarInst(struct, fRec113[Int32(1)], LoadVarInst(struct, fRec113[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j7, Int32(3))
				BinopInst(">", LoadVarInst(loop, j7), Int32(0))
				StoreVarInst(loop, j7, BinopInst("-", LoadVarInst(loop, j7), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec109[LoadVarInst(loop, j7)], LoadVarInst(struct, fRec109[BinopInst("-", LoadVarInst(loop, j7), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fRec107[Int32(2)], LoadVarInst(struct, fRec107[Int32(1)]))
			StoreVarInst(struct, fRec107[Int32(1)], LoadVarInst(struct, fRec107[Int32(0)]))
			StoreVarInst(struct, iRec99[Int32(1)], LoadVarInst(struct, iRec99[Int32(0)]))
			StoreVarInst(struct, fRec93[Int32(1)], LoadVarInst(struct, fRec93[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 64 bytes
Heap size real = 131528 bytes
Heap size = 131600 bytes
Stack size in compute = 56 bytes

