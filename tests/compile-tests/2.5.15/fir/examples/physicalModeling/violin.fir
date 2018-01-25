======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("violin")
	AddMetaDeclareInst(0, "0", "")
	OpenVerticalBox("string")
	AddMetaDeclareInst(fHslider2, "0", "")
	AddHorizontalSlider("length", fHslider2, 0.75f, 0.0f, 2.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenVerticalBox("bow")
	AddMetaDeclareInst(fHslider3, "0", "")
	AddHorizontalSlider("velocity", fHslider3, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider4, "1", "")
	AddHorizontalSlider("pressure", fHslider4, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider1, "2", "")
	AddHorizontalSlider("position", fHslider1, 0.699999988f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddHorizontalSlider("outGain", fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f)
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
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iRec10[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec29[4])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec30[2048])
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fVec1[2048])
	DeclareVarInst(struct, float, fRec18[2048])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec16[4])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, int, iRec6[2])
	DeclareVarInst(struct, float, fRec2[2048])
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
	StoreVarInst(struct, fConst1, FunCallInst("tanf", BinopInst("/", Float(1570.79639f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst1)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(0.5f)), LoadVarInst(struct, fConst1)), Float(1.0f))))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(-0.5f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst7, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst1))))))
	StoreVarInst(struct, fConst8, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst2)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.69999999999999996f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.75f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.5f)))
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
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l4)], Float(0.0f))
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
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 7
Store = 0
Binop = 4
Numbers = 4
Declare = 7
Cast = 5
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider4))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 249
Store = 37
Binop = 206
Numbers = 130
Declare = 79
Cast = 26
Select = 0
Loop = 3
Funcall = 25

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec10[Int32(0)], Int32(0))
		DeclareVarInst(stack, "int", iRec11, LoadVarInst(struct, iRec10[Int32(1)]))
		DeclareVarInst(stack, "float", fRec15, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec6[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec16[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fRec16[Int32(3)])))))))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec26[Int32(1)]))))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec27[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("+", LoadVarInst(struct, fRec27[Int32(0)]), Float(-0.0799999982f)))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec26[Int32(0)])), LoadVarInst(stack, fTemp0))))
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
		StoreVarInst(struct, fRec28[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec28[Int32(1)]))))
		StoreVarInst(struct, fRec29[Int32(0)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec30[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec29[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec29[Int32(1)]), LoadVarInst(struct, fRec29[Int32(3)])))))))
		DeclareVarInst(stack, "int", iRec31, Int32(0))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("*", LoadVarInst(struct, fRec26[Int32(0)]), LoadVarInst(stack, fTemp0))))
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
		DeclareVarInst(stack, "float", fTemp53, BinopInst("-", LoadVarInst(struct, fRec28[Int32(0)]), BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fVec0[Int32(1)]))))
		StoreVarInst(struct, fRec32[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec32[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("*", LoadVarInst(stack, fTemp53), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", BinopInst("-", Float(5.0f), BinopInst("*", Float(4.0f), LoadVarInst(struct, fRec32[Int32(0)]))), LoadVarInst(stack, fTemp53))), Float(0.75f)))))))
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
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(struct, fRec14[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec14[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp56, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec14[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec14[Int32(2)])))))
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
		DeclareVarInst(stack, "float", fTemp57, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fRec1)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp57)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp57)))
		StoreVarInst(struct, iRec10[Int32(1)], LoadVarInst(struct, iRec10[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
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
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iRec10[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec29[4])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec30[2048])
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fVec1[2048])
	DeclareVarInst(struct, float, fRec18[2048])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec16[4])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, int, iRec6[2])
	DeclareVarInst(struct, float, fRec2[2048])
	DeclareVarInst(struct, float, fRec0[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, FunCallInst("tanf", BinopInst("/", Float(1570.79639f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst1)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(0.5f)), LoadVarInst(struct, fConst1)), Float(1.0f))))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(-0.5f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst7, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst1))))))
	StoreVarInst(struct, fConst8, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst2)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.69999999999999996f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.75f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.5f)))
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
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l4)], Float(0.0f))
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
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider4))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec10[Int32(0)], Int32(0))
			DeclareVarInst(stack, "int", iRec11, LoadVarInst(struct, iRec10[Int32(1)]))
			DeclareVarInst(stack, "float", fRec15, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec6[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec16[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fRec16[Int32(3)])))))))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec26[Int32(1)]))))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec27[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("+", LoadVarInst(struct, fRec27[Int32(0)]), Float(-0.0799999982f)))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec26[Int32(0)])), LoadVarInst(stack, fTemp0))))
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
			StoreVarInst(struct, fRec28[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec28[Int32(1)]))))
			StoreVarInst(struct, fRec29[Int32(0)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec30[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec29[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec29[Int32(1)]), LoadVarInst(struct, fRec29[Int32(3)])))))))
			DeclareVarInst(stack, "int", iRec31, Int32(0))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("*", LoadVarInst(struct, fRec26[Int32(0)]), LoadVarInst(stack, fTemp0))))
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
			DeclareVarInst(stack, "float", fTemp53, BinopInst("-", LoadVarInst(struct, fRec28[Int32(0)]), BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fVec0[Int32(1)]))))
			StoreVarInst(struct, fRec32[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec32[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("*", LoadVarInst(stack, fTemp53), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", BinopInst("-", Float(5.0f), BinopInst("*", Float(4.0f), LoadVarInst(struct, fRec32[Int32(0)]))), LoadVarInst(stack, fTemp53))), Float(0.75f)))))))
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
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(struct, fRec14[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst7), LoadVarInst(struct, fRec14[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp56, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec14[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec14[Int32(2)])))))
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
			DeclareVarInst(stack, "float", fTemp57, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fRec1)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp57)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp57)))
			StoreVarInst(struct, iRec10[Int32(1)], LoadVarInst(struct, iRec10[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
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
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 16 bytes
Heap size real = 32932 bytes
Heap size = 32956 bytes
Stack size in compute = 36 bytes

