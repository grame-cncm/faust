======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("clarinet")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("midi")
	AddMetaDeclareInst(fHslider8, "0", "")
	AddMetaDeclareInst(fHslider8, "style", "knob")
	AddHorizontalSlider("freq", fHslider8, 440.0f, 50.0f, 1000.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider9, "1", "")
	AddMetaDeclareInst(fHslider9, "hidden", "1")
	AddMetaDeclareInst(fHslider9, "midi", "pitchwheel")
	AddMetaDeclareInst(fHslider9, "style", "knob")
	AddHorizontalSlider("bend", fHslider9, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider5, "2", "")
	AddMetaDeclareInst(fHslider5, "style", "knob")
	AddHorizontalSlider("gain", fHslider5, 0.600000024f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider6, "3", "")
	AddMetaDeclareInst(fHslider6, "style", "knob")
	AddHorizontalSlider("envAttack", fHslider6, 1.0f, 0.0f, 30.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider4, "4", "")
	AddMetaDeclareInst(fHslider4, "hidden", "1")
	AddMetaDeclareInst(fHslider4, "midi", "ctrl 64")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddHorizontalSlider("sustain", fHslider4, 0.0f, 0.0f, 1.0f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("otherParams")
	AddMetaDeclareInst(fHslider7, "0", "")
	AddMetaDeclareInst(fHslider7, "midi", "ctrl 1")
	AddMetaDeclareInst(fHslider7, "style", "knob")
	AddHorizontalSlider("reedStiffness", fHslider7, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider1, "1", "")
	AddMetaDeclareInst(fHslider1, "midi", "ctrl 3")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddHorizontalSlider("bellOpening", fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider3, "2", "")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddHorizontalSlider("vibratoFreq", fHslider3, 5.0f, 1.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider2, "3", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddHorizontalSlider("vibratoGain", fHslider2, 0.25f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider0, "4", "")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddHorizontalSlider("outGain", fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(fButton0, "2", "")
	AddButtonInst("gate"fButton0)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iRec6[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, int, iRec21[2])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, float, fRec20[3])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec15[2048])
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec11[2])
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, FunCallInst("tanf", BinopInst("/", Float(6283.18555f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst3)))
	StoreVarInst(struct, fConst5, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst4), Float(1.41421354f)), LoadVarInst(struct, fConst3)), Float(1.0f)))
	StoreVarInst(struct, fConst6, BinopInst("/", Float(0.0500000007f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst8, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst3))))))
	StoreVarInst(struct, fConst9, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst4), Float(-1.41421354f)), LoadVarInst(struct, fConst3)), Float(1.0f)))
	StoreVarInst(struct, fConst10, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst11, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.25f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(0.59999999999999998f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(1.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec21[LoadVarInst(loop, l7)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2048))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l13)], Float(0.0f))
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
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 22
Store = 0
Binop = 14
Numbers = 10
Declare = 17
Cast = 11
Select = 0
Loop = 0
Funcall = 4

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("sinf", LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("cosf", LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "float", fSlow8, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider4)))))
	DeclareVarInst(stack, "float", fSlow9, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider6))))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow8), CastInst("float", LoadVarInst(struct, fHslider5))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("+", BinopInst("*", Float(0.25999999f), CastInst("float", LoadVarInst(struct, fHslider7))), Float(-0.439999998f)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("/", Float(170.0f), CastInst("float", LoadVarInst(struct, fHslider8))))
	DeclareVarInst(stack, "float", fSlow13, CastInst("float", LoadVarInst(struct, fHslider9)))
	DeclareVarInst(stack, "int", iSlow14, BinopInst("==", LoadVarInst(stack, fSlow8), Float(0.0f)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 168
Store = 35
Binop = 138
Numbers = 93
Declare = 42
Cast = 24
Select = 0
Loop = 1
Funcall = 13

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec6[Int32(0)], Int32(0))
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec13[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec11[Int32(1)]))))
		DeclareVarInst(stack, "float", fRec10, BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), CastInst("float", LoadVarInst(struct, iRec6[Int32(1)]))))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec17[Int32(1)]))))
		StoreVarInst(struct, fRec18[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec17[Int32(1)]))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec17[Int32(0)])))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow8))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow10), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec19[Int32(1)]))))
		StoreVarInst(struct, iRec21[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec21[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec21[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec20[Int32(2)]))))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(struct, fRec19[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("+", LoadVarInst(struct, fRec20[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec20[Int32(1)]))))), Float(1.0f))))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(stack, fTemp0)), LoadVarInst(stack, fTemp1)))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec14[Int32(1)])))
		StoreVarInst(struct, fRec15[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp0), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(stack, fTemp2), FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(stack, fTemp2)), Float(0.699999988f)))))))
		DeclareVarInst(stack, "int", iRec16, Int32(0))
		DeclareVarInst(stack, "int", iTemp3, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow14)))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp3))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp3)), LoadVarInst(struct, fRec22[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(struct, fConst11), BinopInst("+", BinopInst("/", LoadVarInst(stack, fSlow12), BinopInst("*", LoadVarInst(struct, fRec22[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(struct, fRec19[Int32(0)]), LoadVarInst(struct, fRec17[Int32(0)]))), Float(1.0f)))), Float(-0.0500000007f))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(stack, fTemp4), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp6, CastInst("int", LoadVarInst(stack, fTemp5)))
		DeclareVarInst(stack, "int", iTemp7, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp6)))))), Int32(1)))
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
		DeclareVarInst(stack, "int", iTemp18, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(2))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13)))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp15))))
		DeclareVarInst(stack, "int", iTemp21, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(1))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp15))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "int", iTemp26, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(3))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp15)))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp13)))
		DeclareVarInst(stack, "int", iTemp29, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(4))))))), Int32(1)))
		StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp7)), Int32(2047))]), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp16)), BinopInst("*", LoadVarInst(stack, fTemp17), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp18)), Int32(2047))])), LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp20))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp21)), Int32(2047))]), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp26)), Int32(2047))])), LoadVarInst(stack, fTemp27)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp29)), Int32(2047))])))))))
		StoreVarInst(struct, fRec11[Int32(0)], LoadVarInst(struct, fVec2[Int32(1)]))
		DeclareVarInst(stack, "int", iRec12, LoadVarInst(stack, iRec16))
		DeclareVarInst(stack, "float", fRec7, LoadVarInst(stack, fRec10))
		DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec11[Int32(0)]))
		DeclareVarInst(stack, "float", fRec9, BinopInst("+", LoadVarInst(struct, fRec11[Int32(0)]), CastInst("float", LoadVarInst(stack, iRec12))))
		StoreVarInst(struct, fRec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec7))
		DeclareVarInst(stack, "float", fRec3, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp16)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp7)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp17), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp27)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp26)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp21)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp20)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp18)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp29)), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fRec4, LoadVarInst(stack, fRec8))
		DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
		StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec3))
		DeclareVarInst(stack, "float", fRec1, LoadVarInst(stack, fRec5))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fRec1)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp30)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp30)))
		StoreVarInst(struct, iRec6[Int32(1)], LoadVarInst(struct, iRec6[Int32(0)]))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, iRec21[Int32(1)], LoadVarInst(struct, iRec21[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(2)], LoadVarInst(struct, fRec20[Int32(1)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iRec6[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, int, iRec21[2])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, float, fRec20[3])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec15[2048])
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec2[2048])
	DeclareVarInst(struct, float, fRec0[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, FunCallInst("tanf", BinopInst("/", Float(6283.18555f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst3)))
	StoreVarInst(struct, fConst5, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst4), Float(1.41421354f)), LoadVarInst(struct, fConst3)), Float(1.0f)))
	StoreVarInst(struct, fConst6, BinopInst("/", Float(0.0500000007f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst8, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst3))))))
	StoreVarInst(struct, fConst9, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst4), Float(-1.41421354f)), LoadVarInst(struct, fConst3)), Float(1.0f)))
	StoreVarInst(struct, fConst10, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst11, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.25f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(0.59999999999999998f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(1.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec21[LoadVarInst(loop, l7)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2048))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l13)], Float(0.0f))
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
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("sinf", LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("cosf", LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow5)))
	DeclareVarInst(stack, "float", fSlow8, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider4)))))
	DeclareVarInst(stack, "float", fSlow9, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider6))))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow8), CastInst("float", LoadVarInst(struct, fHslider5))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("+", BinopInst("*", Float(0.25999999f), CastInst("float", LoadVarInst(struct, fHslider7))), Float(-0.439999998f)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("/", Float(170.0f), CastInst("float", LoadVarInst(struct, fHslider8))))
	DeclareVarInst(stack, "float", fSlow13, CastInst("float", LoadVarInst(struct, fHslider9)))
	DeclareVarInst(stack, "int", iSlow14, BinopInst("==", LoadVarInst(stack, fSlow8), Float(0.0f)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[Int32(0)], Int32(0))
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec13[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec11[Int32(1)]))))
			DeclareVarInst(stack, "float", fRec10, BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), CastInst("float", LoadVarInst(struct, iRec6[Int32(1)]))))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec17[Int32(1)]))))
			StoreVarInst(struct, fRec18[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec17[Int32(1)]))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec17[Int32(0)])))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow8))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow10), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec19[Int32(1)]))))
			StoreVarInst(struct, iRec21[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec21[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec21[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec20[Int32(2)]))))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(struct, fRec19[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("+", LoadVarInst(struct, fRec20[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec20[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec20[Int32(1)]))))), Float(1.0f))))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(stack, fTemp0)), LoadVarInst(stack, fTemp1)))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec14[Int32(1)])))
			StoreVarInst(struct, fRec15[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp0), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(stack, fTemp2), FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(stack, fTemp2)), Float(0.699999988f)))))))
			DeclareVarInst(stack, "int", iRec16, Int32(0))
			DeclareVarInst(stack, "int", iTemp3, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow14)))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp3))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp3)), LoadVarInst(struct, fRec22[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(struct, fConst11), BinopInst("+", BinopInst("/", LoadVarInst(stack, fSlow12), BinopInst("*", LoadVarInst(struct, fRec22[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(struct, fRec19[Int32(0)]), LoadVarInst(struct, fRec17[Int32(0)]))), Float(1.0f)))), Float(-0.0500000007f))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(stack, fTemp4), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp6, CastInst("int", LoadVarInst(stack, fTemp5)))
			DeclareVarInst(stack, "int", iTemp7, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp6)))))), Int32(1)))
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
			DeclareVarInst(stack, "int", iTemp18, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(2))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13)))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp15))))
			DeclareVarInst(stack, "int", iTemp21, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(1))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp15))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "int", iTemp26, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(3))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp15)))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp13)))
			DeclareVarInst(stack, "int", iTemp29, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp6), Int32(4))))))), Int32(1)))
			StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp7)), Int32(2047))]), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp16)), BinopInst("*", LoadVarInst(stack, fTemp17), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp18)), Int32(2047))])), LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp20))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp21)), Int32(2047))]), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp26)), Int32(2047))])), LoadVarInst(stack, fTemp27)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp29)), Int32(2047))])))))))
			StoreVarInst(struct, fRec11[Int32(0)], LoadVarInst(struct, fVec2[Int32(1)]))
			DeclareVarInst(stack, "int", iRec12, LoadVarInst(stack, iRec16))
			DeclareVarInst(stack, "float", fRec7, LoadVarInst(stack, fRec10))
			DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec11[Int32(0)]))
			DeclareVarInst(stack, "float", fRec9, BinopInst("+", LoadVarInst(struct, fRec11[Int32(0)]), CastInst("float", LoadVarInst(stack, iRec12))))
			StoreVarInst(struct, fRec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec7))
			DeclareVarInst(stack, "float", fRec3, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp16)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp7)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp17), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp27)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp26)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp22), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp21)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp20)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp18)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp29)), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fRec4, LoadVarInst(stack, fRec8))
			DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
			StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec3))
			DeclareVarInst(stack, "float", fRec1, LoadVarInst(stack, fRec5))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fRec1)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp30)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp30)))
			StoreVarInst(struct, iRec6[Int32(1)], LoadVarInst(struct, iRec6[Int32(0)]))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, iRec21[Int32(1)], LoadVarInst(struct, iRec21[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(2)], LoadVarInst(struct, fRec20[Int32(1)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 24 bytes
Heap size real = 16568 bytes
Heap size = 16600 bytes
Stack size in compute = 76 bytes

