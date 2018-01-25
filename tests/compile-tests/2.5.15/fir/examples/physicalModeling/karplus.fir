======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("karplus")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("params")
	AddMetaDeclareInst(fHslider1, "0", "")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddHorizontalSlider("freq", fHslider1, 440.0f, 50.0f, 1000.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider2, "1", "")
	AddMetaDeclareInst(fHslider2, "hidden", "1")
	AddMetaDeclareInst(fHslider2, "midi", "pitchwheel")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddHorizontalSlider("bend", fHslider2, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider0, "1", "")
	AddMetaDeclareInst(fHslider0, "midi", "ctrl 1")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddHorizontalSlider("damping", fHslider0, 0.00999999978f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider4, "2", "")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddHorizontalSlider("gain", fHslider4, 0.800000012f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider3, "3", "")
	AddMetaDeclareInst(fHslider3, "hidden", "1")
	AddMetaDeclareInst(fHslider3, "midi", "ctrl 64")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddHorizontalSlider("sustain", fHslider3, 0.0f, 0.0f, 1.0f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(fButton0, "1", "")
	AddButtonInst("gate"fButton0)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec7[2048])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fVec1[2048])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec0[3])
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
	StoreVarInst(struct, fConst1, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.01f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.80000000000000004f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2048))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2048))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 9
Store = 0
Binop = 4
Numbers = 4
Declare = 8
Cast = 6
Select = 0
Loop = 0
Funcall = 1

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("/", Float(340.0f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider3)))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst("==", LoadVarInst(stack, fSlow3), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fHslider4)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 129
Store = 20
Binop = 110
Numbers = 70
Declare = 40
Cast = 21
Select = 0
Loop = 1
Funcall = 11

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec11[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fRec1[Int32(2)])), BinopInst("+", BinopInst("*", Float(0.200000003f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec11[Int32(0)]))), Float(0.800000012f)))))
		StoreVarInst(struct, fRec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp0))
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow3))
		DeclareVarInst(stack, "int", iTemp1, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fVec0[Int32(1)])), LoadVarInst(stack, iSlow4)))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp1))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp1)), LoadVarInst(struct, fRec12[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("+", BinopInst("/", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec12[Int32(0)])), Float(-0.0500000007f))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp4, CastInst("int", LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "int", iTemp5, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp4)))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp6, FunCallInst("floorf", LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp6))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp7)))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp6))))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp9))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp6))))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp11))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp6))))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "float", fTemp15, BinopInst("-", LoadVarInst(stack, fTemp2), LoadVarInst(stack, fTemp6)))
		DeclareVarInst(stack, "int", iTemp16, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(2))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "int", iTemp19, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(1))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp9)))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp11))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp9)))
		DeclareVarInst(stack, "int", iTemp24, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(3))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13)))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "int", iTemp27, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(4))))))), Int32(1)))
		DeclareVarInst(stack, "float", fRec8, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp5)), Int32(2047))]), LoadVarInst(stack, fTemp8)), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fRec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp16)), Int32(2047))])), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp19)), Int32(2047))]), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(struct, fRec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp24)), Int32(2047))])), LoadVarInst(stack, fTemp25)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fRec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp27)), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(stack, fSlow5), CastInst("float", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fVec0[Int32(1)])), Float(0.0f)))))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), LoadVarInst(stack, fTemp28)))
		StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp29))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp5)), Int32(2047))])))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp25)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp24)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp20), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp19)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp16)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp27)), Int32(2047))]))))))
		DeclareVarInst(stack, "float", fRec9, BinopInst("+", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp31)))
		DeclareVarInst(stack, "float", fRec10, BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp0), LoadVarInst(stack, fTemp30)), LoadVarInst(stack, fTemp31)))
		StoreVarInst(struct, fRec3[Int32(0)], LoadVarInst(stack, fRec8))
		DeclareVarInst(stack, "float", fRec4, BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec3[Int32(1)])))
		DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
		DeclareVarInst(stack, "float", fRec6, LoadVarInst(stack, fRec10))
		StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec4))
		StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(stack, fRec5))
		DeclareVarInst(stack, "float", fRec2, LoadVarInst(stack, fRec6))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec2)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec2)))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec7[2048])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fVec1[2048])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, float, fRec1[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.01f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.80000000000000004f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2048))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2048))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("/", Float(340.0f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider3)))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst("==", LoadVarInst(stack, fSlow3), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fHslider4)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec11[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fRec1[Int32(2)])), BinopInst("+", BinopInst("*", Float(0.200000003f), BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec11[Int32(0)]))), Float(0.800000012f)))))
			StoreVarInst(struct, fRec7[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp0))
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fSlow3))
			DeclareVarInst(stack, "int", iTemp1, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fVec0[Int32(1)])), LoadVarInst(stack, iSlow4)))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp1))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp1)), LoadVarInst(struct, fRec12[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("+", BinopInst("/", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec12[Int32(0)])), Float(-0.0500000007f))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp4, CastInst("int", LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "int", iTemp5, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp4)))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp6, FunCallInst("floorf", LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp6))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp7)))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp6))))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp9))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp6))))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp11))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp6))))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "float", fTemp15, BinopInst("-", LoadVarInst(stack, fTemp2), LoadVarInst(stack, fTemp6)))
			DeclareVarInst(stack, "int", iTemp16, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(2))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "int", iTemp19, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(1))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp9)))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp11))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp9)))
			DeclareVarInst(stack, "int", iTemp24, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(3))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13)))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "int", iTemp27, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst1), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(4))))))), Int32(1)))
			DeclareVarInst(stack, "float", fRec8, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp5)), Int32(2047))]), LoadVarInst(stack, fTemp8)), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fRec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp16)), Int32(2047))])), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp19)), Int32(2047))]), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(struct, fRec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp24)), Int32(2047))])), LoadVarInst(stack, fTemp25)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fRec7[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp27)), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(stack, fSlow5), CastInst("float", BinopInst(">", BinopInst("-", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fVec0[Int32(1)])), Float(0.0f)))))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), LoadVarInst(stack, fTemp28)))
			StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp29))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp5)), Int32(2047))])))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp25)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp24)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp20), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp19)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18)), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp16)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp27)), Int32(2047))]))))))
			DeclareVarInst(stack, "float", fRec9, BinopInst("+", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp31)))
			DeclareVarInst(stack, "float", fRec10, BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp0), LoadVarInst(stack, fTemp30)), LoadVarInst(stack, fTemp31)))
			StoreVarInst(struct, fRec3[Int32(0)], LoadVarInst(stack, fRec8))
			DeclareVarInst(stack, "float", fRec4, BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec3[Int32(1)])))
			DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
			DeclareVarInst(stack, "float", fRec6, LoadVarInst(stack, fRec10))
			StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec4))
			StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(stack, fRec5))
			DeclareVarInst(stack, "float", fRec2, LoadVarInst(stack, fRec6))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec2)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec2)))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 16476 bytes
Heap size = 16484 bytes
Stack size in compute = 40 bytes

