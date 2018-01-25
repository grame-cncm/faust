======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("flute")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("midi")
	AddMetaDeclareInst(fHslider6, "0", "")
	AddMetaDeclareInst(fHslider6, "style", "knob")
	AddHorizontalSlider("freq", fHslider6, 440.0f, 50.0f, 1000.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider7, "1", "")
	AddMetaDeclareInst(fHslider7, "hidden", "1")
	AddMetaDeclareInst(fHslider7, "midi", "pitchwheel")
	AddMetaDeclareInst(fHslider7, "style", "knob")
	AddHorizontalSlider("bend", fHslider7, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider4, "2", "")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddHorizontalSlider("gain", fHslider4, 0.899999976f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider5, "3", "")
	AddMetaDeclareInst(fHslider5, "style", "knob")
	AddHorizontalSlider("envAttack", fHslider5, 1.0f, 0.0f, 30.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider3, "4", "")
	AddMetaDeclareInst(fHslider3, "hidden", "1")
	AddMetaDeclareInst(fHslider3, "midi", "ctrl 64")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddHorizontalSlider("sustain", fHslider3, 0.0f, 0.0f, 1.0f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("otherParams")
	AddMetaDeclareInst(fHslider8, "0", "")
	AddMetaDeclareInst(fHslider8, "midi", "ctrl 1")
	AddMetaDeclareInst(fHslider8, "style", "knob")
	AddHorizontalSlider("mouthPosition", fHslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider2, "1", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddHorizontalSlider("vibratoFreq", fHslider2, 5.0f, 1.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider1, "2", "")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddHorizontalSlider("vibratoGain", fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider0, "3", "")
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
	DeclareVarInst(struct, int, iRec15[2])
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, int, iRec27[2])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, float, fRec26[3])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec29[2048])
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fVec3[2048])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec11[2048])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec3[2048])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec2[2])
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
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.90000000000000002f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(0.5f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec15[LoadVarInst(loop, l0)], Int32(0))
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
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l4)], Float(0.0f))
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
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec27[LoadVarInst(loop, l7)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2048))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2048))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2048))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2048))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 20
Store = 0
Binop = 12
Numbers = 8
Declare = 15
Cast = 10
Select = 0
Loop = 0
Funcall = 4

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.0399999991f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("sinf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("cosf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider3)))))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider5))))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow6), CastInst("float", LoadVarInst(struct, fHslider4))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow7))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("/", Float(340.0f), CastInst("float", LoadVarInst(struct, fHslider6))))
	DeclareVarInst(stack, "float", fSlow10, CastInst("float", LoadVarInst(struct, fHslider7)))
	DeclareVarInst(stack, "int", iSlow11, BinopInst("==", LoadVarInst(stack, fSlow6), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider8))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 261
Store = 47
Binop = 227
Numbers = 155
Declare = 74
Cast = 40
Select = 0
Loop = 1
Funcall = 25

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec15[Int32(0)], Int32(0))
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", Float(0.699999988f), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", Float(0.284999996f), LoadVarInst(struct, fRec20[Int32(1)]))))
		DeclareVarInst(stack, "float", fRec19, BinopInst("+", LoadVarInst(struct, fRec22[Int32(0)]), CastInst("float", LoadVarInst(struct, iRec15[Int32(1)]))))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec23[Int32(1)]))))
		StoreVarInst(struct, fRec24[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec23[Int32(1)]))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow6))
		StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec25[Int32(1)]))))
		StoreVarInst(struct, iRec27[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec27[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec27[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec26[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec26[Int32(2)]))))))
		StoreVarInst(struct, fRec28[Int32(0)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec29[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fRec28[Int32(1)])))
		DeclareVarInst(stack, "int", iRec30, Int32(0))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow11)))
		StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec31[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("+", BinopInst("/", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec31[Int32(0)])), Float(0.270000011f)))
		StoreVarInst(struct, fRec32[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow12), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec32[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", Float(0.400000006f), BinopInst("+", LoadVarInst(struct, fRec32[Int32(0)]), Float(-0.5f))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst11), BinopInst("*", LoadVarInst(stack, fTemp1), BinopInst("+", LoadVarInst(stack, fTemp2), Float(0.270000011f)))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(stack, fTemp3), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp5, CastInst("int", LoadVarInst(stack, fTemp4)))
		DeclareVarInst(stack, "int", iTemp6, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp5)))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp7, FunCallInst("floorf", LoadVarInst(stack, fTemp4)))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp7))))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp8)))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp7))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp10))))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp7))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp7))))
		DeclareVarInst(stack, "float", fTemp15, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp14))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("-", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp7)))
		DeclareVarInst(stack, "int", iTemp17, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(2))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp14))))
		DeclareVarInst(stack, "int", iTemp20, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(1))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp14))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "int", iTemp25, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(3))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp14)))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "int", iTemp28, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(4))))))), Int32(1)))
		StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp6)), Int32(2047))]), LoadVarInst(stack, fTemp9)), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(stack, fTemp15)), BinopInst("*", LoadVarInst(stack, fTemp16), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp17)), Int32(2047))])), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp19))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp20)), Int32(2047))]), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp25)), Int32(2047))])), LoadVarInst(stack, fTemp26)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp27), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp28)), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec23[Int32(0)])), BinopInst("*", LoadVarInst(struct, fRec25[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("+", LoadVarInst(struct, fRec26[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec26[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec26[Int32(1)]))))), Float(1.0f)))), BinopInst("*", Float(0.5f), LoadVarInst(struct, fVec2[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("+", BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec7[Int32(1)])), FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), BinopInst("*", LoadVarInst(stack, fTemp29), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp29)), Float(-1.0f)))))))
		StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp30))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("*", LoadVarInst(struct, fConst11), BinopInst("*", LoadVarInst(stack, fTemp1), BinopInst("-", Float(0.730000019f), LoadVarInst(stack, fTemp2)))))
		DeclareVarInst(stack, "float", fTemp32, BinopInst("+", LoadVarInst(stack, fTemp31), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp33, CastInst("int", LoadVarInst(stack, fTemp32)))
		DeclareVarInst(stack, "int", iTemp34, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp33)))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp35, FunCallInst("floorf", LoadVarInst(stack, fTemp32)))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(stack, fTemp31), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp35))))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp36)))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("+", LoadVarInst(stack, fTemp31), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp35))))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp38))))
		DeclareVarInst(stack, "float", fTemp40, BinopInst("+", LoadVarInst(stack, fTemp31), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp35))))
		DeclareVarInst(stack, "float", fTemp41, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp40))))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("+", LoadVarInst(stack, fTemp31), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp35))))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp42))))
		DeclareVarInst(stack, "float", fTemp44, BinopInst("-", LoadVarInst(stack, fTemp31), LoadVarInst(stack, fTemp35)))
		DeclareVarInst(stack, "int", iTemp45, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp33), Int32(2))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp40)))
		DeclareVarInst(stack, "float", fTemp47, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp42))))
		DeclareVarInst(stack, "int", iTemp48, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp33), Int32(1))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp49, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp38)))
		DeclareVarInst(stack, "float", fTemp50, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp40))))
		DeclareVarInst(stack, "float", fTemp51, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp42))))
		DeclareVarInst(stack, "float", fTemp52, BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp38)))
		DeclareVarInst(stack, "int", iTemp53, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp33), Int32(3))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp42)))
		DeclareVarInst(stack, "float", fTemp55, BinopInst("*", LoadVarInst(stack, fTemp52), LoadVarInst(stack, fTemp40)))
		DeclareVarInst(stack, "int", iTemp56, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp33), Int32(4))))))), Int32(1)))
		StoreVarInst(struct, fVec4[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp34)), Int32(2047))]), LoadVarInst(stack, fTemp37)), LoadVarInst(stack, fTemp39)), LoadVarInst(stack, fTemp41)), LoadVarInst(stack, fTemp43)), BinopInst("*", LoadVarInst(stack, fTemp44), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp45)), Int32(2047))])), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp48)), Int32(2047))]), LoadVarInst(stack, fTemp49)), LoadVarInst(stack, fTemp50)), LoadVarInst(stack, fTemp51))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp52), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp53)), Int32(2047))])), LoadVarInst(stack, fTemp54)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp55), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp56)), Int32(2047))])))))))
		StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(struct, fVec4[Int32(1)]))
		DeclareVarInst(stack, "int", iRec21, LoadVarInst(stack, iRec30))
		DeclareVarInst(stack, "float", fRec16, LoadVarInst(stack, fRec19))
		DeclareVarInst(stack, "float", fRec17, LoadVarInst(struct, fRec20[Int32(0)]))
		DeclareVarInst(stack, "float", fRec18, BinopInst("+", LoadVarInst(struct, fRec20[Int32(0)]), CastInst("float", LoadVarInst(stack, iRec21))))
		StoreVarInst(struct, fRec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec16))
		DeclareVarInst(stack, "float", fRec12, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp37), LoadVarInst(stack, fTemp39)), LoadVarInst(stack, fTemp41)), LoadVarInst(stack, fTemp43)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp34)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp44), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp52), LoadVarInst(stack, fTemp54)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp53)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp49), LoadVarInst(stack, fTemp50)), LoadVarInst(stack, fTemp51)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp48)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp45)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp55), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp56)), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fRec13, LoadVarInst(stack, fRec17))
		DeclareVarInst(stack, "float", fRec14, LoadVarInst(stack, fRec18))
		StoreVarInst(struct, fRec7[Int32(0)], LoadVarInst(stack, fRec12))
		DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec7[Int32(1)]))
		DeclareVarInst(stack, "float", fRec9, LoadVarInst(stack, fRec13))
		DeclareVarInst(stack, "float", fRec10, LoadVarInst(stack, fRec14))
		StoreVarInst(struct, fRec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec8))
		DeclareVarInst(stack, "float", fRec4, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(stack, fTemp15)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp6)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp16), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp26)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp25)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp20)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp19)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp17)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp27), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp28)), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
		DeclareVarInst(stack, "float", fRec6, LoadVarInst(stack, fRec10))
		StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(stack, fRec4))
		StoreVarInst(struct, fRec2[Int32(0)], LoadVarInst(stack, fRec6))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("*", Float(0.995000005f), LoadVarInst(struct, fRec0[Int32(1)]))), LoadVarInst(struct, fRec2[Int32(1)])))
		DeclareVarInst(stack, "float", fTemp57, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec0[Int32(0)])))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp57)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp57)))
		StoreVarInst(struct, iRec15[Int32(1)], LoadVarInst(struct, iRec15[Int32(0)]))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, iRec27[Int32(1)], LoadVarInst(struct, iRec27[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(2)], LoadVarInst(struct, fRec26[Int32(1)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
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
	DeclareVarInst(struct, int, iRec15[2])
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, int, iRec27[2])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, "float", fConst9)
	DeclareVarInst(struct, float, fRec26[3])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec29[2048])
	DeclareVarInst(struct, "float", fConst10)
	DeclareVarInst(struct, "float", fConst11)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fVec3[2048])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec11[2048])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec3[2048])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec2[2])
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
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.90000000000000002f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(0.5f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec15[LoadVarInst(loop, l0)], Int32(0))
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
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l4)], Float(0.0f))
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
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec27[LoadVarInst(loop, l7)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2048))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2048))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2048))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2048))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.0399999991f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("sinf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("cosf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider3)))))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider5))))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow6), CastInst("float", LoadVarInst(struct, fHslider4))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow7))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("/", Float(340.0f), CastInst("float", LoadVarInst(struct, fHslider6))))
	DeclareVarInst(stack, "float", fSlow10, CastInst("float", LoadVarInst(struct, fHslider7)))
	DeclareVarInst(stack, "int", iSlow11, BinopInst("==", LoadVarInst(stack, fSlow6), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider8))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec15[Int32(0)], Int32(0))
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", Float(0.699999988f), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", Float(0.284999996f), LoadVarInst(struct, fRec20[Int32(1)]))))
			DeclareVarInst(stack, "float", fRec19, BinopInst("+", LoadVarInst(struct, fRec22[Int32(0)]), CastInst("float", LoadVarInst(struct, iRec15[Int32(1)]))))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec23[Int32(1)]))))
			StoreVarInst(struct, fRec24[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec23[Int32(1)]))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow6))
			StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec25[Int32(1)]))))
			StoreVarInst(struct, iRec27[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec27[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec27[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fConst7), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(struct, fRec26[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst9), LoadVarInst(struct, fRec26[Int32(2)]))))))
			StoreVarInst(struct, fRec28[Int32(0)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec29[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fRec28[Int32(1)])))
			DeclareVarInst(stack, "int", iRec30, Int32(0))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow11)))
			StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0))))), BinopInst("*", Float(0.999000013f), BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp0)), LoadVarInst(struct, fRec31[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("+", BinopInst("/", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec31[Int32(0)])), Float(0.270000011f)))
			StoreVarInst(struct, fRec32[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow12), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec32[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", Float(0.400000006f), BinopInst("+", LoadVarInst(struct, fRec32[Int32(0)]), Float(-0.5f))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst11), BinopInst("*", LoadVarInst(stack, fTemp1), BinopInst("+", LoadVarInst(stack, fTemp2), Float(0.270000011f)))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(stack, fTemp3), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp5, CastInst("int", LoadVarInst(stack, fTemp4)))
			DeclareVarInst(stack, "int", iTemp6, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp5)))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp7, FunCallInst("floorf", LoadVarInst(stack, fTemp4)))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp7))))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp8)))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp7))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp10))))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp7))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp7))))
			DeclareVarInst(stack, "float", fTemp15, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp14))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("-", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp7)))
			DeclareVarInst(stack, "int", iTemp17, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(2))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp14))))
			DeclareVarInst(stack, "int", iTemp20, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(1))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp14))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "int", iTemp25, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(3))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp14)))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "int", iTemp28, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(4))))))), Int32(1)))
			StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp6)), Int32(2047))]), LoadVarInst(stack, fTemp9)), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(stack, fTemp15)), BinopInst("*", LoadVarInst(stack, fTemp16), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp17)), Int32(2047))])), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp19))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp20)), Int32(2047))]), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp25)), Int32(2047))])), LoadVarInst(stack, fTemp26)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp27), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp28)), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec23[Int32(0)])), BinopInst("*", LoadVarInst(struct, fRec25[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("+", LoadVarInst(struct, fRec26[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec26[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec26[Int32(1)]))))), Float(1.0f)))), BinopInst("*", Float(0.5f), LoadVarInst(struct, fVec2[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("+", BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec7[Int32(1)])), FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), BinopInst("*", LoadVarInst(stack, fTemp29), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp29)), Float(-1.0f)))))))
			StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp30))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("*", LoadVarInst(struct, fConst11), BinopInst("*", LoadVarInst(stack, fTemp1), BinopInst("-", Float(0.730000019f), LoadVarInst(stack, fTemp2)))))
			DeclareVarInst(stack, "float", fTemp32, BinopInst("+", LoadVarInst(stack, fTemp31), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp33, CastInst("int", LoadVarInst(stack, fTemp32)))
			DeclareVarInst(stack, "int", iTemp34, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp33)))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp35, FunCallInst("floorf", LoadVarInst(stack, fTemp32)))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(stack, fTemp31), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp35))))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp36)))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("+", LoadVarInst(stack, fTemp31), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp35))))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp38))))
			DeclareVarInst(stack, "float", fTemp40, BinopInst("+", LoadVarInst(stack, fTemp31), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp35))))
			DeclareVarInst(stack, "float", fTemp41, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp40))))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("+", LoadVarInst(stack, fTemp31), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp35))))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp42))))
			DeclareVarInst(stack, "float", fTemp44, BinopInst("-", LoadVarInst(stack, fTemp31), LoadVarInst(stack, fTemp35)))
			DeclareVarInst(stack, "int", iTemp45, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp33), Int32(2))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp40)))
			DeclareVarInst(stack, "float", fTemp47, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp42))))
			DeclareVarInst(stack, "int", iTemp48, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp33), Int32(1))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp49, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp38)))
			DeclareVarInst(stack, "float", fTemp50, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp40))))
			DeclareVarInst(stack, "float", fTemp51, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp42))))
			DeclareVarInst(stack, "float", fTemp52, BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp38)))
			DeclareVarInst(stack, "int", iTemp53, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp33), Int32(3))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp42)))
			DeclareVarInst(stack, "float", fTemp55, BinopInst("*", LoadVarInst(stack, fTemp52), LoadVarInst(stack, fTemp40)))
			DeclareVarInst(stack, "int", iTemp56, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst10), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp33), Int32(4))))))), Int32(1)))
			StoreVarInst(struct, fVec4[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp34)), Int32(2047))]), LoadVarInst(stack, fTemp37)), LoadVarInst(stack, fTemp39)), LoadVarInst(stack, fTemp41)), LoadVarInst(stack, fTemp43)), BinopInst("*", LoadVarInst(stack, fTemp44), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp45)), Int32(2047))])), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp48)), Int32(2047))]), LoadVarInst(stack, fTemp49)), LoadVarInst(stack, fTemp50)), LoadVarInst(stack, fTemp51))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp52), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp53)), Int32(2047))])), LoadVarInst(stack, fTemp54)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp55), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp56)), Int32(2047))])))))))
			StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(struct, fVec4[Int32(1)]))
			DeclareVarInst(stack, "int", iRec21, LoadVarInst(stack, iRec30))
			DeclareVarInst(stack, "float", fRec16, LoadVarInst(stack, fRec19))
			DeclareVarInst(stack, "float", fRec17, LoadVarInst(struct, fRec20[Int32(0)]))
			DeclareVarInst(stack, "float", fRec18, BinopInst("+", LoadVarInst(struct, fRec20[Int32(0)]), CastInst("float", LoadVarInst(stack, iRec21))))
			StoreVarInst(struct, fRec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec16))
			DeclareVarInst(stack, "float", fRec12, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp37), LoadVarInst(stack, fTemp39)), LoadVarInst(stack, fTemp41)), LoadVarInst(stack, fTemp43)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp34)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp44), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp52), LoadVarInst(stack, fTemp54)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp53)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp49), LoadVarInst(stack, fTemp50)), LoadVarInst(stack, fTemp51)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp48)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp47)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp45)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp55), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp56)), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fRec13, LoadVarInst(stack, fRec17))
			DeclareVarInst(stack, "float", fRec14, LoadVarInst(stack, fRec18))
			StoreVarInst(struct, fRec7[Int32(0)], LoadVarInst(stack, fRec12))
			DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec7[Int32(1)]))
			DeclareVarInst(stack, "float", fRec9, LoadVarInst(stack, fRec13))
			DeclareVarInst(stack, "float", fRec10, LoadVarInst(stack, fRec14))
			StoreVarInst(struct, fRec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec8))
			DeclareVarInst(stack, "float", fRec4, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(stack, fTemp15)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp6)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp16), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp26)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp25)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp20)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp19)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp17)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp27), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp28)), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
			DeclareVarInst(stack, "float", fRec6, LoadVarInst(stack, fRec10))
			StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(stack, fRec4))
			StoreVarInst(struct, fRec2[Int32(0)], LoadVarInst(stack, fRec6))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("*", Float(0.995000005f), LoadVarInst(struct, fRec0[Int32(1)]))), LoadVarInst(struct, fRec2[Int32(1)])))
			DeclareVarInst(stack, "float", fTemp57, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec0[Int32(0)])))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp57)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp57)))
			StoreVarInst(struct, iRec15[Int32(1)], LoadVarInst(struct, iRec15[Int32(0)]))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, iRec27[Int32(1)], LoadVarInst(struct, iRec27[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(2)], LoadVarInst(struct, fRec26[Int32(1)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 24 bytes
Heap size real = 32988 bytes
Heap size = 33020 bytes
Stack size in compute = 68 bytes

