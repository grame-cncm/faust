======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("violin")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("midi")
	AddMetaDeclareInst(fHslider2, "0", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddHorizontalSlider("freq", fHslider2, 440.0f, 50.0f, 1000.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider3, "1", "")
	AddMetaDeclareInst(fHslider3, "hidden", "1")
	AddMetaDeclareInst(fHslider3, "midi", "pitchwheel")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddHorizontalSlider("bend", fHslider3, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider7, "2", "")
	AddMetaDeclareInst(fHslider7, "style", "knob")
	AddHorizontalSlider("gain", fHslider7, 0.600000024f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider8, "3", "")
	AddMetaDeclareInst(fHslider8, "style", "knob")
	AddHorizontalSlider("envAttack", fHslider8, 1.0f, 0.0f, 30.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider4, "4", "")
	AddMetaDeclareInst(fHslider4, "hidden", "1")
	AddMetaDeclareInst(fHslider4, "midi", "ctrl 64")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddHorizontalSlider("sustain", fHslider4, 0.0f, 0.0f, 1.0f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("bow")
	AddMetaDeclareInst(fHslider9, "0", "")
	AddMetaDeclareInst(fHslider9, "midi", "ctrl 1")
	AddMetaDeclareInst(fHslider9, "style", "knob")
	AddHorizontalSlider("pressure", fHslider9, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider1, "1", "")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddHorizontalSlider("position", fHslider1, 0.699999988f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("otherParams")
	AddMetaDeclareInst(fHslider6, "0", "")
	AddMetaDeclareInst(fHslider6, "style", "knob")
	AddHorizontalSlider("vibratoFrequency", fHslider6, 6.0f, 1.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider5, "1", "")
	AddMetaDeclareInst(fHslider5, "style", "knob")
	AddHorizontalSlider("vibratoGain", fHslider5, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider0, "2", "")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddHorizontalSlider("outGain", fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(fButton0, "3", "")
	AddButtonInst("gate"fButton0)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
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
	DeclareVarInst(struct, int, iVec0[2])
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
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec31[4])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec32[2048])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, float, fVec3[2048])
	DeclareVarInst(struct, float, fRec18[2048])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec16[4])
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, "float", fConst10)
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
	StoreVarInst(struct, fConst6, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst8, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(-0.5f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst9, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst1))))))
	StoreVarInst(struct, fConst10, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst2)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.69999999999999996f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(6.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.59999999999999998f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(0.5f)))
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
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l2)], Float(0.0f))
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
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(4))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2048))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2048))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2048))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(4))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(3))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[LoadVarInst(loop, l18)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2048))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 21
Store = 0
Binop = 13
Numbers = 9
Declare = 16
Cast = 11
Select = 0
Loop = 0
Funcall = 4

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", Float(340.0f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fHslider3)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider4)))))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("==", LoadVarInst(stack, fSlow4), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fHslider5))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", LoadVarInst(struct, fConst6), CastInst("float", LoadVarInst(struct, fHslider6))))
	DeclareVarInst(stack, "float", fSlow8, FunCallInst("sinf", LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow9, FunCallInst("cosf", LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow11, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst7), CastInst("float", LoadVarInst(struct, fHslider8))))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow4), CastInst("float", LoadVarInst(struct, fHslider7))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow11))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider9))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 273
Store = 45
Binop = 225
Numbers = 142
Declare = 80
Cast = 39
Select = 0
Loop = 3
Funcall = 25

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec10[Int32(0)], Int32(0))
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		DeclareVarInst(stack, "int", iRec11, LoadVarInst(struct, iRec10[Int32(1)]))
		DeclareVarInst(stack, "float", fRec15, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec6[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec16[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fRec16[Int32(3)])))))))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec26[Int32(1)]))))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow4))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow5)))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec27[Int32(1)])))))
		StoreVarInst(struct, fRec28[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec29[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec28[Int32(1)]))))
		StoreVarInst(struct, fRec29[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec29[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec28[Int32(1)]))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
		StoreVarInst(struct, fRec30[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow12), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec30[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("+", BinopInst("/", LoadVarInst(stack, fSlow2), BinopInst("*", LoadVarInst(struct, fRec27[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow6), BinopInst("*", LoadVarInst(struct, fRec28[Int32(0)]), LoadVarInst(struct, fRec30[Int32(0)]))), Float(1.0f)))), Float(-0.0799999982f)))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec26[Int32(0)])), LoadVarInst(stack, fTemp1))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp4, CastInst("int", LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "int", iTemp5, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp4)))))))
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
		DeclareVarInst(stack, "int", iTemp16, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(2))))))))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "int", iTemp19, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(1))))))))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp9)))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp11))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp9)))
		DeclareVarInst(stack, "int", iTemp24, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(3))))))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13)))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "int", iTemp27, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(4))))))))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp5), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp8)), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp16), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp19), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp24), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp25)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp27), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec31[Int32(0)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec32[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec31[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec31[Int32(1)]), LoadVarInst(struct, fRec31[Int32(3)])))))))
		DeclareVarInst(stack, "int", iRec33, Int32(0))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("*", LoadVarInst(struct, fRec26[Int32(0)]), LoadVarInst(stack, fTemp1))))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("+", LoadVarInst(stack, fTemp28), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp30, CastInst("int", LoadVarInst(stack, fTemp29)))
		DeclareVarInst(stack, "int", iTemp31, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp30)))))))
		DeclareVarInst(stack, "float", fTemp32, FunCallInst("floorf", LoadVarInst(stack, fTemp29)))
		DeclareVarInst(stack, "float", fTemp33, BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp32))))
		DeclareVarInst(stack, "float", fTemp34, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp33)))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp32))))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp35))))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp32))))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp37))))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp32))))
		DeclareVarInst(stack, "float", fTemp40, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp39))))
		DeclareVarInst(stack, "float", fTemp41, BinopInst("-", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp32)))
		DeclareVarInst(stack, "int", iTemp42, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp30), Int32(2))))))))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp37)))
		DeclareVarInst(stack, "float", fTemp44, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp39))))
		DeclareVarInst(stack, "int", iTemp45, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp30), Int32(1))))))))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp35)))
		DeclareVarInst(stack, "float", fTemp47, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp37))))
		DeclareVarInst(stack, "float", fTemp48, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp39))))
		DeclareVarInst(stack, "float", fTemp49, BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(stack, fTemp35)))
		DeclareVarInst(stack, "int", iTemp50, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp30), Int32(3))))))))
		DeclareVarInst(stack, "float", fTemp51, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp39)))
		DeclareVarInst(stack, "float", fTemp52, BinopInst("*", LoadVarInst(stack, fTemp49), LoadVarInst(stack, fTemp37)))
		DeclareVarInst(stack, "int", iTemp53, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp30), Int32(4))))))))
		StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp31), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp34)), LoadVarInst(stack, fTemp36)), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), BinopInst("*", LoadVarInst(stack, fTemp41), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp42), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp43)), LoadVarInst(stack, fTemp44))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp45), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47)), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp49), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp50), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp51)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp52), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp53), Int32(2))), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("-", LoadVarInst(struct, fRec30[Int32(0)]), BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fVec2[Int32(1)]))))
		StoreVarInst(struct, fRec34[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow13), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec34[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp55, BinopInst("*", LoadVarInst(stack, fTemp54), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", BinopInst("-", Float(5.0f), BinopInst("*", Float(4.0f), LoadVarInst(struct, fRec34[Int32(0)]))), LoadVarInst(stack, fTemp54))), Float(0.75f)))))))
		DeclareVarInst(stack, "float", fRec23, BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(stack, fTemp55)))
		DeclareVarInst(stack, "float", fTemp56, BinopInst("+", LoadVarInst(struct, fVec2[Int32(1)]), LoadVarInst(stack, fTemp55)))
		StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp56))
		DeclareVarInst(stack, "float", fRec24, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp5)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp27)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp20), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp19)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp16)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp25)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp24)), Int32(2047))]))))))))
		DeclareVarInst(stack, "int", iRec25, LoadVarInst(stack, iRec33))
		StoreVarInst(struct, fRec18[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec23))
		DeclareVarInst(stack, "float", fRec19, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp34), LoadVarInst(stack, fTemp36)), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp31), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp41), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp49), LoadVarInst(stack, fTemp51)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp50), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp46), LoadVarInst(stack, fTemp47)), LoadVarInst(stack, fTemp48)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp45), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(stack, fTemp43)), LoadVarInst(stack, fTemp44)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp42), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp52), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp53), Int32(1))), Int32(2047))])))))))
		StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(stack, fRec24))
		DeclareVarInst(stack, "int", iRec21, LoadVarInst(stack, iRec25))
		StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(struct, fRec20[Int32(1)]))
		DeclareVarInst(stack, "int", iRec17, LoadVarInst(stack, iRec21))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec14[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec14[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp57, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec14[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst10), LoadVarInst(struct, fRec14[Int32(2)])))))
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
		DeclareVarInst(stack, "float", fTemp58, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fRec1)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp58)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp58)))
		StoreVarInst(struct, iRec10[Int32(1)], LoadVarInst(struct, iRec10[Int32(0)]))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
		StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j0, Int32(3))
			BinopInst(">", LoadVarInst(loop, j0), Int32(0))
			StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec31[LoadVarInst(loop, j0)], LoadVarInst(struct, fRec31[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
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
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "expf", "float", dummy0)
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
	DeclareVarInst(struct, int, iVec0[2])
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
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec31[4])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec32[2048])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, float, fVec3[2048])
	DeclareVarInst(struct, float, fRec18[2048])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec16[4])
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, "float", fConst10)
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
	StoreVarInst(struct, fConst6, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst8, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(struct, fConst2), Float(-0.5f)), LoadVarInst(struct, fConst1)), Float(1.0f)))
	StoreVarInst(struct, fConst9, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst1))))))
	StoreVarInst(struct, fConst10, BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst2)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.69999999999999996f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(6.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.59999999999999998f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(0.5f)))
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
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l2)], Float(0.0f))
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
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(4))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2048))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2048))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2048))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(4))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(3))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[LoadVarInst(loop, l18)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2048))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", Float(340.0f), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fHslider3)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider4)))))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("==", LoadVarInst(stack, fSlow4), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fHslider5))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", LoadVarInst(struct, fConst6), CastInst("float", LoadVarInst(struct, fHslider6))))
	DeclareVarInst(stack, "float", fSlow8, FunCallInst("sinf", LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow9, FunCallInst("cosf", LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow11, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst7), CastInst("float", LoadVarInst(struct, fHslider8))))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow4), CastInst("float", LoadVarInst(struct, fHslider7))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow11))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider9))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec10[Int32(0)], Int32(0))
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			DeclareVarInst(stack, "int", iRec11, LoadVarInst(struct, iRec10[Int32(1)]))
			DeclareVarInst(stack, "float", fRec15, BinopInst("-", CastInst("float", LoadVarInst(struct, iRec6[Int32(1)])), BinopInst("*", Float(0.989264667f), BinopInst("+", BinopInst("*", Float(0.600000024f), LoadVarInst(struct, fRec16[Int32(2)])), BinopInst("*", Float(0.200000003f), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fRec16[Int32(3)])))))))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec26[Int32(1)]))))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow4))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow5)))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec27[Int32(1)])))))
			StoreVarInst(struct, fRec28[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec29[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec28[Int32(1)]))))
			StoreVarInst(struct, fRec29[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec29[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec28[Int32(1)]))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
			StoreVarInst(struct, fRec30[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow12), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec30[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("+", BinopInst("/", LoadVarInst(stack, fSlow2), BinopInst("*", LoadVarInst(struct, fRec27[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow6), BinopInst("*", LoadVarInst(struct, fRec28[Int32(0)]), LoadVarInst(struct, fRec30[Int32(0)]))), Float(1.0f)))), Float(-0.0799999982f)))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec26[Int32(0)])), LoadVarInst(stack, fTemp1))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp4, CastInst("int", LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "int", iTemp5, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp4)))))))
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
			DeclareVarInst(stack, "int", iTemp16, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(2))))))))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "int", iTemp19, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(1))))))))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp9)))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp11))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp9)))
			DeclareVarInst(stack, "int", iTemp24, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(3))))))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13)))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "int", iTemp27, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp4), Int32(4))))))))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp5), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp8)), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp16), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp19), Int32(1))), Int32(2047))]), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp24), Int32(1))), Int32(2047))])), LoadVarInst(stack, fTemp25)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp27), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec31[Int32(0)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec32[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("-", Float(0.0f), BinopInst("*", Float(0.99880147f), BinopInst("+", BinopInst("*", Float(0.800000012f), LoadVarInst(struct, fRec31[Int32(2)])), BinopInst("*", Float(0.100000001f), BinopInst("+", LoadVarInst(struct, fRec31[Int32(1)]), LoadVarInst(struct, fRec31[Int32(3)])))))))
			DeclareVarInst(stack, "int", iRec33, Int32(0))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("*", LoadVarInst(struct, fConst5), BinopInst("*", LoadVarInst(struct, fRec26[Int32(0)]), LoadVarInst(stack, fTemp1))))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("+", LoadVarInst(stack, fTemp28), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp30, CastInst("int", LoadVarInst(stack, fTemp29)))
			DeclareVarInst(stack, "int", iTemp31, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp30)))))))
			DeclareVarInst(stack, "float", fTemp32, FunCallInst("floorf", LoadVarInst(stack, fTemp29)))
			DeclareVarInst(stack, "float", fTemp33, BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp32))))
			DeclareVarInst(stack, "float", fTemp34, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp33)))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp32))))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp35))))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp32))))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp37))))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp32))))
			DeclareVarInst(stack, "float", fTemp40, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp39))))
			DeclareVarInst(stack, "float", fTemp41, BinopInst("-", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp32)))
			DeclareVarInst(stack, "int", iTemp42, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp30), Int32(2))))))))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp37)))
			DeclareVarInst(stack, "float", fTemp44, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp39))))
			DeclareVarInst(stack, "int", iTemp45, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp30), Int32(1))))))))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp35)))
			DeclareVarInst(stack, "float", fTemp47, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp37))))
			DeclareVarInst(stack, "float", fTemp48, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp39))))
			DeclareVarInst(stack, "float", fTemp49, BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(stack, fTemp35)))
			DeclareVarInst(stack, "int", iTemp50, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp30), Int32(3))))))))
			DeclareVarInst(stack, "float", fTemp51, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp39)))
			DeclareVarInst(stack, "float", fTemp52, BinopInst("*", LoadVarInst(stack, fTemp49), LoadVarInst(stack, fTemp37)))
			DeclareVarInst(stack, "int", iTemp53, CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst4), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp30), Int32(4))))))))
			StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp31), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp34)), LoadVarInst(stack, fTemp36)), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), BinopInst("*", LoadVarInst(stack, fTemp41), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp42), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp43)), LoadVarInst(stack, fTemp44))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp45), Int32(2))), Int32(2047))]), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47)), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp49), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp50), Int32(2))), Int32(2047))])), LoadVarInst(stack, fTemp51)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp52), LoadVarInst(struct, fRec32[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp53), Int32(2))), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("-", LoadVarInst(struct, fRec30[Int32(0)]), BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fVec2[Int32(1)]))))
			StoreVarInst(struct, fRec34[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow13), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec34[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp55, BinopInst("*", LoadVarInst(stack, fTemp54), FunCallInst("min_f", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower4_f", BinopInst("+", FunCallInst("fabsf", BinopInst("*", BinopInst("-", Float(5.0f), BinopInst("*", Float(4.0f), LoadVarInst(struct, fRec34[Int32(0)]))), LoadVarInst(stack, fTemp54))), Float(0.75f)))))))
			DeclareVarInst(stack, "float", fRec23, BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(stack, fTemp55)))
			DeclareVarInst(stack, "float", fTemp56, BinopInst("+", LoadVarInst(struct, fVec2[Int32(1)]), LoadVarInst(stack, fTemp55)))
			StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp56))
			DeclareVarInst(stack, "float", fRec24, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp5)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp27)), Int32(2047))]))), BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp20), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp19)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp16)), Int32(2047))])))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp25)), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp24)), Int32(2047))]))))))))
			DeclareVarInst(stack, "int", iRec25, LoadVarInst(stack, iRec33))
			StoreVarInst(struct, fRec18[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec23))
			DeclareVarInst(stack, "float", fRec19, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp34), LoadVarInst(stack, fTemp36)), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp31), Int32(1))), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp41), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp49), LoadVarInst(stack, fTemp51)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp50), Int32(1))), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp46), LoadVarInst(stack, fTemp47)), LoadVarInst(stack, fTemp48)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp45), Int32(1))), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(stack, fTemp43)), LoadVarInst(stack, fTemp44)), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp42), Int32(1))), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp52), LoadVarInst(struct, fRec18[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp53), Int32(1))), Int32(2047))])))))))
			StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(stack, fRec24))
			DeclareVarInst(stack, "int", iRec21, LoadVarInst(stack, iRec25))
			StoreVarInst(struct, fRec16[Int32(0)], LoadVarInst(struct, fRec20[Int32(1)]))
			DeclareVarInst(stack, "int", iRec17, LoadVarInst(stack, iRec21))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec14[Int32(2)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec14[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp57, BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec14[Int32(0)])), BinopInst("*", LoadVarInst(struct, fConst10), LoadVarInst(struct, fRec14[Int32(2)])))))
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
			DeclareVarInst(stack, "float", fTemp58, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fRec1)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp58)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp58)))
			StoreVarInst(struct, iRec10[Int32(1)], LoadVarInst(struct, iRec10[Int32(0)]))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
			StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j0, Int32(3))
				BinopInst(">", LoadVarInst(loop, j0), Int32(0))
				StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec31[LoadVarInst(loop, j0)], LoadVarInst(struct, fRec31[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
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
Heap size int* = 24 bytes
Heap size real = 32988 bytes
Heap size = 33020 bytes
Stack size in compute = 72 bytes

