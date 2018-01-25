======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("vocal")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("midi")
	AddMetaDeclareInst(fHslider5, "0", "")
	AddMetaDeclareInst(fHslider5, "style", "knob")
	AddHorizontalSlider("freq", fHslider5, 440.0f, 50.0f, 1000.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider6, "1", "")
	AddMetaDeclareInst(fHslider6, "hidden", "1")
	AddMetaDeclareInst(fHslider6, "midi", "pitchwheel")
	AddMetaDeclareInst(fHslider6, "style", "knob")
	AddHorizontalSlider("bend", fHslider6, 1.0f, 0.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider2, "2", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddHorizontalSlider("gain", fHslider2, 0.899999976f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider3, "3", "")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddHorizontalSlider("envAttack", fHslider3, 10.0f, 0.0f, 30.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider1, "4", "")
	AddMetaDeclareInst(fHslider1, "hidden", "1")
	AddMetaDeclareInst(fHslider1, "midi", "ctrl 64")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddHorizontalSlider("sustain", fHslider1, 0.0f, 0.0f, 1.0f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("otherParams")
	AddMetaDeclareInst(fHslider9, "0", "")
	AddMetaDeclareInst(fHslider9, "style", "knob")
	AddHorizontalSlider("voiceType", fHslider9, 0.0f, 0.0f, 4.0f, 1.0f)
	AddMetaDeclareInst(fHslider10, "1", "")
	AddMetaDeclareInst(fHslider10, "midi", "ctrl 1")
	AddMetaDeclareInst(fHslider10, "style", "knob")
	AddHorizontalSlider("vowel", fHslider10, 0.0f, 0.0f, 4.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider4, "2", "")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddHorizontalSlider("fricative", fHslider4, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider8, "3", "")
	AddMetaDeclareInst(fHslider8, "style", "knob")
	AddHorizontalSlider("vibratoFreq", fHslider8, 6.0f, 1.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider7, "4", "")
	AddMetaDeclareInst(fHslider7, "style", "knob")
	AddHorizontalSlider("vibratoGain", fHslider7, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider0, "5", "")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddHorizontalSlider("outGain", fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(fButton0, "2", "")
	AddButtonInst("gate"fButton0)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, int, iRec8[2])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider10)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, float, fRec12[3])
	DeclareVarInst(struct, float, fRec13[3])
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, float, fRec15[3])
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.90000000000000002f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(10.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(6.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider10, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l3)], Float(0.0f))
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
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec8[LoadVarInst(loop, l8)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(3))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(3))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(3))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(3))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(3))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 28
Store = 0
Binop = 20
Numbers = 19
Declare = 22
Cast = 12
Select = 0
Loop = 0
Funcall = 4

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider3))))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow1), CastInst("float", LoadVarInst(struct, fHslider2))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider4))))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fHslider5)))
	DeclareVarInst(stack, "int", iSlow6, BinopInst("==", LoadVarInst(stack, fSlow1), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow7, CastInst("float", LoadVarInst(struct, fHslider6)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", Float(0.100000001f), CastInst("float", LoadVarInst(struct, fHslider7))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", LoadVarInst(struct, fConst3), CastInst("float", LoadVarInst(struct, fHslider8))))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("sinf", LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow11, FunCallInst("cosf", LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow10)))
	DeclareVarInst(stack, "float", fSlow13, CastInst("float", LoadVarInst(struct, fHslider9)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(5.0f), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider10))))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", Float(5.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow13))))
	DeclareVarInst(stack, "int", iSlow17, BinopInst("==", Select2Inst(BinopInst("==", LoadVarInst(stack, fSlow13), Float(0.0f)) Int32(1) Select2Inst(BinopInst("==", LoadVarInst(stack, fSlow13), Float(3.0f)) Int32(1) Int32(0))), Int32(0)))
	DeclareVarInst(stack, "int", iSlow18, BinopInst("!=", LoadVarInst(stack, fSlow13), Float(2.0f)))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("*", Float(2.0f), LoadVarInst(stack, fSlow5)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 1223
Store = 42
Binop = 804
Numbers = 1019
Declare = 123
Cast = 7
Select = 0
Loop = 1
Funcall = 12

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow1))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec1[Int32(1)]))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec2[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow6)))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), BinopInst("*", LoadVarInst(struct, fRec5[Int32(1)]), CastInst("float", LoadVarInst(stack, iTemp0)))), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0)))))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec7[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec6[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp1, BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec7[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec6[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp1))))
		DeclareVarInst(stack, "float", fTemp2, FunCallInst("max_f", Float(1.00000001e-07f), FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("*", LoadVarInst(struct, fRec5[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec6[Int32(0)])), Float(1.0f)))))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp2))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(stack, fTemp3), Float(-1.0f)))
		DeclareVarInst(stack, "int", iTemp5, BinopInst("<", LoadVarInst(stack, fTemp4), Float(0.0f)))
		StoreVarInst(struct, fRec3[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp5) LoadVarInst(stack, fTemp3) LoadVarInst(stack, fTemp4)))
		DeclareVarInst(stack, "float", fRec4, Select2Inst(LoadVarInst(stack, iTemp5) LoadVarInst(stack, fTemp3) BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("*", LoadVarInst(stack, fTemp4), BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp2)))))))
		StoreVarInst(struct, iRec8[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec8[Int32(1)])), Int32(12345)))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("+", BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec2[Int32(0)])), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(stack, fRec4)), Float(-1.0f))), BinopInst("*", Float(4.65661287e-10f), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), CastInst("float", LoadVarInst(struct, iRec8[Int32(0)])))))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow15), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec9[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec9[Int32(0)])))
		DeclareVarInst(stack, "int", iTemp8, BinopInst("<", LoadVarInst(stack, fTemp7), Float(23.0f)))
		DeclareVarInst(stack, "int", iTemp9, BinopInst("<", LoadVarInst(stack, fTemp7), Float(24.0f)))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-23.0f))))
		DeclareVarInst(stack, "int", iTemp11, BinopInst("<", LoadVarInst(stack, fTemp7), Float(22.0f)))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-22.0f))))
		DeclareVarInst(stack, "int", iTemp13, BinopInst("<", LoadVarInst(stack, fTemp7), Float(21.0f)))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-21.0f))))
		DeclareVarInst(stack, "int", iTemp15, BinopInst("<", LoadVarInst(stack, fTemp7), Float(20.0f)))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-20.0f))))
		DeclareVarInst(stack, "int", iTemp17, BinopInst("<", LoadVarInst(stack, fTemp7), Float(19.0f)))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-19.0f))))
		DeclareVarInst(stack, "int", iTemp19, BinopInst("<", LoadVarInst(stack, fTemp7), Float(18.0f)))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-18.0f))))
		DeclareVarInst(stack, "int", iTemp21, BinopInst("<", LoadVarInst(stack, fTemp7), Float(17.0f)))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-17.0f))))
		DeclareVarInst(stack, "int", iTemp23, BinopInst("<", LoadVarInst(stack, fTemp7), Float(16.0f)))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-16.0f))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("*", Float(80.0f), LoadVarInst(stack, fTemp24)))
		DeclareVarInst(stack, "int", iTemp26, BinopInst("<", LoadVarInst(stack, fTemp7), Float(15.0f)))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-15.0f))))
		DeclareVarInst(stack, "int", iTemp28, BinopInst("<", LoadVarInst(stack, fTemp7), Float(14.0f)))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-14.0f))))
		DeclareVarInst(stack, "int", iTemp30, BinopInst("<", LoadVarInst(stack, fTemp7), Float(13.0f)))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-13.0f))))
		DeclareVarInst(stack, "int", iTemp32, BinopInst("<", LoadVarInst(stack, fTemp7), Float(12.0f)))
		DeclareVarInst(stack, "float", fTemp33, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-12.0f))))
		DeclareVarInst(stack, "int", iTemp34, BinopInst("<", LoadVarInst(stack, fTemp7), Float(11.0f)))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-11.0f))))
		DeclareVarInst(stack, "int", iTemp36, BinopInst("<", LoadVarInst(stack, fTemp7), Float(10.0f)))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-10.0f))))
		DeclareVarInst(stack, "int", iTemp38, BinopInst("<", LoadVarInst(stack, fTemp7), Float(9.0f)))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-9.0f))))
		DeclareVarInst(stack, "int", iTemp40, BinopInst("<", LoadVarInst(stack, fTemp7), Float(8.0f)))
		DeclareVarInst(stack, "float", fTemp41, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-8.0f))))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp41)))
		DeclareVarInst(stack, "int", iTemp43, BinopInst("<", LoadVarInst(stack, fTemp7), Float(7.0f)))
		DeclareVarInst(stack, "float", fTemp44, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-7.0f))))
		DeclareVarInst(stack, "int", iTemp45, BinopInst("<", LoadVarInst(stack, fTemp7), Float(6.0f)))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-6.0f))))
		DeclareVarInst(stack, "int", iTemp47, BinopInst("<", LoadVarInst(stack, fTemp7), Float(5.0f)))
		DeclareVarInst(stack, "float", fTemp48, BinopInst("-", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(stack, fSlow16)))
		DeclareVarInst(stack, "int", iTemp49, BinopInst("<", LoadVarInst(stack, fTemp7), Float(4.0f)))
		DeclareVarInst(stack, "float", fTemp50, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-4.0f))))
		DeclareVarInst(stack, "int", iTemp51, BinopInst("<", LoadVarInst(stack, fTemp7), Float(3.0f)))
		DeclareVarInst(stack, "float", fTemp52, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-3.0f))))
		DeclareVarInst(stack, "int", iTemp53, BinopInst("<", LoadVarInst(stack, fTemp7), Float(2.0f)))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-2.0f))))
		DeclareVarInst(stack, "int", iTemp55, BinopInst("<", LoadVarInst(stack, fTemp7), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp56, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-1.0f))))
		DeclareVarInst(stack, "int", iTemp57, BinopInst("<", LoadVarInst(stack, fTemp7), Float(0.0f)))
		DeclareVarInst(stack, "float", fTemp58, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(800.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(800.0f), BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp7))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("-", Float(400.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp56))) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp54)), Float(350.0f)) Float(450.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(450.0f), BinopInst("*", Float(125.0f), LoadVarInst(stack, fTemp52))) Float(325.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(275.0f), LoadVarInst(stack, fTemp50)), Float(325.0f)) Float(600.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(600.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp48))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("-", Float(400.0f), BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp46))) Float(250.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp44)), Float(250.0f)) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(400.0f), LoadVarInst(stack, fTemp42)) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(310.0f), LoadVarInst(stack, fTemp39)), Float(350.0f)) Float(660.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(660.0f), BinopInst("*", Float(220.0f), LoadVarInst(stack, fTemp37))) Float(440.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(440.0f), BinopInst("*", Float(170.0f), LoadVarInst(stack, fTemp35))) Float(270.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(160.0f), LoadVarInst(stack, fTemp33)), Float(270.0f)) Float(430.0f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("-", Float(430.0f), BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp31))) Float(370.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(430.0f), LoadVarInst(stack, fTemp29)), Float(370.0f)) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(800.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp27))) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(350.0f), LoadVarInst(stack, fTemp25)) Float(270.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(180.0f), LoadVarInst(stack, fTemp22)), Float(270.0f)) Float(450.0f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(450.0f), BinopInst("*", Float(125.0f), LoadVarInst(stack, fTemp20))) Float(325.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("*", Float(325.0f), BinopInst("+", LoadVarInst(stack, fTemp18), Float(1.0f))) Float(650.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(650.0f), BinopInst("*", Float(250.0f), LoadVarInst(stack, fTemp16))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(400.0f), BinopInst("*", Float(110.0f), LoadVarInst(stack, fTemp14))) Float(290.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(110.0f), LoadVarInst(stack, fTemp12)), Float(290.0f)) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(400.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp10))) Float(350.0f))))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec10[Int32(1)]))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec10[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp1))))
		DeclareVarInst(stack, "float", fTemp59, BinopInst("*", LoadVarInst(struct, fRec5[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec10[Int32(0)])), Float(1.0f))))
		DeclareVarInst(stack, "float", fTemp60, BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fTemp59)))
		DeclareVarInst(stack, "float", fTemp61, Select2Inst(BinopInst("<=", LoadVarInst(stack, fTemp58), LoadVarInst(stack, fTemp60)) LoadVarInst(stack, fTemp60) LoadVarInst(stack, fTemp58)))
		DeclareVarInst(stack, "float", fTemp62, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp61))))
		DeclareVarInst(stack, "float", fTemp63, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp62)))
		DeclareVarInst(stack, "float", fTemp64, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp16)))
		DeclareVarInst(stack, "float", fTemp65, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp27)))
		DeclareVarInst(stack, "float", fTemp66, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp37)))
		DeclareVarInst(stack, "float", fTemp67, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp50)))
		DeclareVarInst(stack, "float", fTemp68, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp52)))
		DeclareVarInst(stack, "float", fTemp69, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp54)))
		DeclareVarInst(stack, "float", fTemp70, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp7)))
		DeclareVarInst(stack, "float", fTemp71, BinopInst("/", Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(80.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp70)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("-", Float(60.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp56))) Float(50.0f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", LoadVarInst(stack, fTemp69), Float(50.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(70.0f), LoadVarInst(stack, fTemp68)) Float(50.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", LoadVarInst(stack, fTemp67), Float(50.0f)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp48))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp46)), Float(40.0f)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp44))) Float(40.0f))) Float(40.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("*", Float(40.0f), BinopInst("+", LoadVarInst(stack, fTemp39), Float(1.0f))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp66)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp35))) Float(40.0f))) Float(40.0f)) Float(40.0f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("*", Float(40.0f), BinopInst("+", LoadVarInst(stack, fTemp29), Float(1.0f))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp65)) Float(60.0f))) Float(60.0f)) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp22))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp20)), Float(40.0f)) Float(50.0f))) Float(50.0f)) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("+", LoadVarInst(stack, fTemp64), Float(50.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp14))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp12)), Float(40.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp10))) Float(40.0f))), LoadVarInst(stack, fTemp61)))
		DeclareVarInst(stack, "float", fTemp72, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp63), LoadVarInst(stack, fTemp71)), LoadVarInst(stack, fTemp62)), Float(1.0f)))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp6), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp63), LoadVarInst(stack, fTemp71)), LoadVarInst(stack, fTemp62)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp62))))))), LoadVarInst(stack, fTemp72))))
		DeclareVarInst(stack, "float", fTemp73, BinopInst("+", BinopInst("*", Float(0.000839999993f), BinopInst("-", Float(1000.0f), LoadVarInst(stack, fTemp60))), Float(0.800000012f)))
		DeclareVarInst(stack, "float", fTemp74, BinopInst("+", BinopInst("*", Float(0.00366666657f), BinopInst("-", Float(400.0f), LoadVarInst(stack, fTemp60))), Float(3.0f)))
		DeclareVarInst(stack, "float", fTemp75, Select2Inst(LoadVarInst(stack, iSlow17) LoadVarInst(stack, fTemp74) LoadVarInst(stack, fTemp73)))
		DeclareVarInst(stack, "float", fTemp76, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(1150.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("+", BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp7)), Float(1150.0f)) Float(1600.0f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp56)), Float(1600.0f)) Float(1700.0f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(1700.0f), BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp54))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp52))) Float(700.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(340.0f), LoadVarInst(stack, fTemp50)), Float(700.0f)) Float(1040.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", BinopInst("*", Float(580.0f), LoadVarInst(stack, fTemp48)), Float(1040.0f)) Float(1620.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp46)), Float(1620.0f)) Float(1750.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(1750.0f), BinopInst("*", Float(1000.0f), LoadVarInst(stack, fTemp44))) Float(750.0f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(750.0f), BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp41))) Float(600.0f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(520.0f), LoadVarInst(stack, fTemp39)), Float(600.0f)) Float(1120.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(680.0f), LoadVarInst(stack, fTemp37)), Float(1120.0f)) Float(1800.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp35)), Float(1800.0f)) Float(1850.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(1850.0f), BinopInst("*", Float(1030.0f), LoadVarInst(stack, fTemp33))) Float(820.0f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("-", Float(820.0f), BinopInst("*", Float(190.0f), LoadVarInst(stack, fTemp31))) Float(630.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(520.0f), LoadVarInst(stack, fTemp29)), Float(630.0f)) Float(1150.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("+", BinopInst("*", Float(850.0f), LoadVarInst(stack, fTemp27)), Float(1150.0f)) Float(2000.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(140.0f), LoadVarInst(stack, fTemp24)), Float(2000.0f)) Float(2140.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(2140.0f), BinopInst("*", Float(1340.0f), LoadVarInst(stack, fTemp22))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp20))) Float(700.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(380.0f), LoadVarInst(stack, fTemp18)), Float(700.0f)) Float(1080.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("+", BinopInst("*", Float(620.0f), LoadVarInst(stack, fTemp16)), Float(1080.0f)) Float(1700.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("+", BinopInst("*", Float(170.0f), LoadVarInst(stack, fTemp14)), Float(1700.0f)) Float(1870.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("-", Float(1870.0f), BinopInst("*", Float(1070.0f), LoadVarInst(stack, fTemp12))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(800.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp10))) Float(600.0f))))
		DeclareVarInst(stack, "float", fTemp77, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow19), LoadVarInst(stack, fTemp59)), Float(30.0f)))
		DeclareVarInst(stack, "float", fTemp78, Select2Inst(LoadVarInst(stack, iSlow18) Select2Inst(BinopInst("&", BinopInst(">=", LoadVarInst(stack, fTemp76), Float(1300.0f)), BinopInst(">=", LoadVarInst(stack, fTemp60), Float(200.0f))) BinopInst("-", LoadVarInst(stack, fTemp76), BinopInst("*", Float(0.000952380942f), BinopInst("*", BinopInst("+", LoadVarInst(stack, fTemp60), Float(-200.0f)), BinopInst("+", LoadVarInst(stack, fTemp76), Float(-1300.0f))))) Select2Inst(BinopInst("<=", LoadVarInst(stack, fTemp76), LoadVarInst(stack, fTemp77)) LoadVarInst(stack, fTemp77) LoadVarInst(stack, fTemp76))) LoadVarInst(stack, fTemp76)))
		DeclareVarInst(stack, "float", fTemp79, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp78))))
		DeclareVarInst(stack, "float", fTemp80, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp79)))
		DeclareVarInst(stack, "float", fTemp81, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "float", fTemp82, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp16)))
		DeclareVarInst(stack, "float", fTemp83, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp39)))
		DeclareVarInst(stack, "float", fTemp84, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp48)))
		DeclareVarInst(stack, "float", fTemp85, BinopInst("/", Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(90.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp7))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("+", BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp56)), Float(80.0f)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(100.0f), LoadVarInst(stack, fTemp69)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp68)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", LoadVarInst(stack, fTemp67), Float(60.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", LoadVarInst(stack, fTemp84), Float(70.0f)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp46)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp44))) Float(80.0f))) Float(80.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", LoadVarInst(stack, fTemp83), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp66)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp35)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp33))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp31))) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp29)), Float(60.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp27)), Float(90.0f)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(100.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp24))) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp22))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp20))) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp18)), Float(60.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp82)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp14)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp81)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp10))) Float(60.0f))), LoadVarInst(stack, fTemp78)))
		DeclareVarInst(stack, "float", fTemp86, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp80), LoadVarInst(stack, fTemp85)), LoadVarInst(stack, fTemp79)), Float(1.0f)))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp6), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec12[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp80), LoadVarInst(stack, fTemp85)), LoadVarInst(stack, fTemp79)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp79))))))), LoadVarInst(stack, fTemp86))))
		DeclareVarInst(stack, "float", fTemp87, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(0.630957007f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(0.630957007f), BinopInst("*", Float(0.567861021f), LoadVarInst(stack, fTemp7))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("+", BinopInst("*", Float(0.0369039997f), LoadVarInst(stack, fTemp56)), Float(0.0630960017f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(0.254812986f), LoadVarInst(stack, fTemp54)), Float(0.100000001f)) Float(0.35481301f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.103624001f), LoadVarInst(stack, fTemp52))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp50)), Float(0.251188993f)) Float(0.446684003f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(0.446684003f), BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp48))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.219566002f), LoadVarInst(stack, fTemp46))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(0.250214994f), LoadVarInst(stack, fTemp44)), Float(0.0316229984f)) Float(0.281838f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(0.281838f), BinopInst("*", Float(0.181838006f), LoadVarInst(stack, fTemp41))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp39)), Float(0.100000001f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.301661015f), LoadVarInst(stack, fTemp37))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.136429995f), LoadVarInst(stack, fTemp35))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(0.253131986f), LoadVarInst(stack, fTemp33)), Float(0.0630960017f)) Float(0.316228002f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("-", Float(0.316228002f), BinopInst("*", Float(0.216227993f), LoadVarInst(stack, fTemp31))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp29)), Float(0.100000001f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp27))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(0.151188999f), LoadVarInst(stack, fTemp24)), Float(0.100000001f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.0306490008f), LoadVarInst(stack, fTemp22)), Float(0.251188993f)) Float(0.281838f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(0.281838f), BinopInst("*", Float(0.123349003f), LoadVarInst(stack, fTemp20))) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(0.342698008f), LoadVarInst(stack, fTemp18)), Float(0.158489004f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.301661015f), LoadVarInst(stack, fTemp16))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.0216979999f), LoadVarInst(stack, fTemp14))) Float(0.177827999f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(0.138400003f), LoadVarInst(stack, fTemp12)), Float(0.177827999f)) Float(0.316228002f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(0.316228002f), BinopInst("*", Float(0.216227993f), LoadVarInst(stack, fTemp10))) Float(0.100000001f))))
		DeclareVarInst(stack, "float", fTemp88, Select2Inst(LoadVarInst(stack, iSlow17) BinopInst("*", LoadVarInst(stack, fTemp74), LoadVarInst(stack, fTemp87)) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp87))))
		DeclareVarInst(stack, "float", fTemp89, BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp90, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp18)))
		DeclareVarInst(stack, "float", fTemp91, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp37)))
		DeclareVarInst(stack, "float", fTemp92, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(2800.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(2800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp7))) Float(2700.0f))) Float(2700.0f)) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp54)), Float(2700.0f)) Float(2830.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(2830.0f), BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp52))) Float(2530.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(2530.0f), BinopInst("*", Float(280.0f), LoadVarInst(stack, fTemp50))) Float(2250.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp48)), Float(2250.0f)) Float(2400.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp46)), Float(2400.0f)) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(2600.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp44))) Float(2400.0f))) Float(2400.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp39)), Float(2400.0f)) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(2750.0f), LoadVarInst(stack, fTemp91)) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp35)), Float(2700.0f)) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(2900.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp33))) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp31)), Float(2700.0f)) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp29)), Float(2750.0f)) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(2900.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp27))) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp24)), Float(2800.0f)) Float(2950.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(2950.0f), BinopInst("*", Float(120.0f), LoadVarInst(stack, fTemp22))) Float(2830.0f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(2830.0f), BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp20))) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(2700.0f), LoadVarInst(stack, fTemp90)) Float(2650.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(2650.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp16))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp14)), Float(2600.0f)) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("-", Float(2800.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp12))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("+", LoadVarInst(stack, fTemp89), Float(2600.0f)) Float(2700.0f))))
		DeclareVarInst(stack, "float", fTemp93, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp92))))
		DeclareVarInst(stack, "float", fTemp94, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp93)))
		DeclareVarInst(stack, "float", fTemp95, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp29)))
		DeclareVarInst(stack, "float", fTemp96, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp37)))
		DeclareVarInst(stack, "float", fTemp97, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp39)))
		DeclareVarInst(stack, "float", fTemp98, BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp50)))
		DeclareVarInst(stack, "float", fTemp99, BinopInst("/", Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Float(120.0f) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp69)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("+", BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp52)), Float(100.0f)) Float(170.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(170.0f), LoadVarInst(stack, fTemp98)) Float(110.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(110.0f), LoadVarInst(stack, fTemp84)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", LoadVarInst(stack, fTemp97), Float(100.0f)) Float(120.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp96)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", LoadVarInst(stack, fTemp95), Float(100.0f)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(120.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp24))) Float(100.0f))) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("+", BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp20)), Float(100.0f)) Float(170.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(170.0f), LoadVarInst(stack, fTemp90)) Float(120.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp64)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)), LoadVarInst(stack, fTemp92)))
		DeclareVarInst(stack, "float", fTemp100, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp94), LoadVarInst(stack, fTemp99)), LoadVarInst(stack, fTemp93)), Float(1.0f)))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp6), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec13[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp94), LoadVarInst(stack, fTemp99)), LoadVarInst(stack, fTemp93)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec13[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp93))))))), LoadVarInst(stack, fTemp100))))
		DeclareVarInst(stack, "float", fTemp101, Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.0293140002f), LoadVarInst(stack, fTemp22)), Float(0.0501190014f)) Float(0.0794330016f)))
		DeclareVarInst(stack, "float", fTemp102, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(0.100000001f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp7))) Float(0.0316229984f))) Float(0.0316229984f)) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(0.126865998f), LoadVarInst(stack, fTemp54)), Float(0.0316229984f)) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.158489004f), BinopInst("*", Float(0.126865998f), LoadVarInst(stack, fTemp52))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(0.323190004f), LoadVarInst(stack, fTemp50)), Float(0.0316229984f)) Float(0.35481301f))) Float(0.35481301f)) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.196324006f), LoadVarInst(stack, fTemp46))) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(0.158489004f), BinopInst("*", Float(0.0693639964f), LoadVarInst(stack, fTemp44))) Float(0.0891249999f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(0.0891249999f), BinopInst("*", Float(0.0640060008f), LoadVarInst(stack, fTemp41))) Float(0.0251189992f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(0.0456760004f), LoadVarInst(stack, fTemp39)), Float(0.0251189992f)) Float(0.0707949996f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(0.0550980009f), LoadVarInst(stack, fTemp37)), Float(0.0707949996f)) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(0.125892997f), BinopInst("*", Float(0.0627970025f), LoadVarInst(stack, fTemp35))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(0.0630960017f), BinopInst("*", Float(0.0129770003f), LoadVarInst(stack, fTemp33))) Float(0.0501190014f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("+", BinopInst("*", Float(0.020676f), LoadVarInst(stack, fTemp31)), Float(0.0501190014f)) Float(0.0707949996f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("-", Float(0.0707949996f), BinopInst("*", Float(0.0456760004f), LoadVarInst(stack, fTemp29))) Float(0.0251189992f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("+", BinopInst("*", Float(0.152709007f), LoadVarInst(stack, fTemp27)), Float(0.0251189992f)) Float(0.177827999f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(0.177827999f), BinopInst("*", Float(0.127709001f), LoadVarInst(stack, fTemp24))) Float(0.0501190014f))) LoadVarInst(stack, fTemp101)) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0616500005f), LoadVarInst(stack, fTemp20))) Float(0.0177829992f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(0.428900987f), LoadVarInst(stack, fTemp18)), Float(0.0177829992f)) Float(0.446684003f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(0.446684003f), BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp16))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.125295997f), LoadVarInst(stack, fTemp14))) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(0.125295997f), LoadVarInst(stack, fTemp12)), Float(0.125892997f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.109935001f), LoadVarInst(stack, fTemp10))) Float(0.141253993f))))
		DeclareVarInst(stack, "float", fTemp103, Select2Inst(LoadVarInst(stack, iSlow17) BinopInst("*", LoadVarInst(stack, fTemp74), LoadVarInst(stack, fTemp102)) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp102))))
		DeclareVarInst(stack, "float", fTemp104, BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp48)))
		DeclareVarInst(stack, "float", fTemp105, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(3500.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(3500.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp7))) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("+", BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp56)), Float(3300.0f)) Float(3700.0f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(3700.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp54))) Float(3500.0f))) Float(3500.0f)) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(3500.0f), BinopInst("*", Float(1050.0f), LoadVarInst(stack, fTemp50))) Float(2450.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", LoadVarInst(stack, fTemp104), Float(2450.0f)) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(250.0f), LoadVarInst(stack, fTemp46)), Float(2800.0f)) Float(3050.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(3050.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp44))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("+", BinopInst("*", Float(75.0f), LoadVarInst(stack, fTemp41)), Float(2600.0f)) Float(2675.0f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(325.0f), LoadVarInst(stack, fTemp39)), Float(2675.0f)) Float(3000.0f))) Float(3000.0f)) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp35)), Float(3000.0f)) Float(3350.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(3350.0f), BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp33))) Float(3000.0f))) Float(3000.0f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp29)), Float(3000.0f)) Float(3900.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(3900.0f), BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp27))) Float(3600.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp24)), Float(3600.0f)) Float(3900.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(3900.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp22))) Float(3800.0f))) Float(3800.0f)) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(3800.0f), BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp18))) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp16)), Float(2900.0f)) Float(3200.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp14)), Float(3200.0f)) Float(3250.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("-", Float(3250.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp12))) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("+", LoadVarInst(stack, fTemp89), Float(2800.0f)) Float(2900.0f))))
		DeclareVarInst(stack, "float", fTemp106, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp105))))
		DeclareVarInst(stack, "float", fTemp107, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp106)))
		DeclareVarInst(stack, "float", fTemp108, BinopInst("/", Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(130.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("+", LoadVarInst(stack, fTemp70), Float(130.0f)) Float(150.0f))) Float(150.0f)) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(150.0f), LoadVarInst(stack, fTemp69)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp52)), Float(130.0f)) Float(180.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(180.0f), LoadVarInst(stack, fTemp98)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", LoadVarInst(stack, fTemp83), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp66)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp29)), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("+", LoadVarInst(stack, fTemp65), Float(130.0f)) Float(150.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(150.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp24))) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp20)), Float(120.0f)) Float(180.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(180.0f), LoadVarInst(stack, fTemp90)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp82)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", LoadVarInst(stack, fTemp81), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(130.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp10))) Float(120.0f))), LoadVarInst(stack, fTemp105)))
		DeclareVarInst(stack, "float", fTemp109, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp107), LoadVarInst(stack, fTemp108)), LoadVarInst(stack, fTemp106)), Float(1.0f)))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp6), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec14[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp107), LoadVarInst(stack, fTemp108)), LoadVarInst(stack, fTemp106)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec14[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp106))))))), LoadVarInst(stack, fTemp109))))
		DeclareVarInst(stack, "float", fTemp110, Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0841509998f), LoadVarInst(stack, fTemp35))) Float(0.0158489998f)))
		DeclareVarInst(stack, "float", fTemp111, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(0.0158489998f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("+", BinopInst("*", Float(0.00193400006f), LoadVarInst(stack, fTemp7)), Float(0.0158489998f)) Float(0.0177829992f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("-", Float(0.0177829992f), BinopInst("*", Float(0.00193400006f), LoadVarInst(stack, fTemp56))) Float(0.0158489998f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(0.0239620004f), LoadVarInst(stack, fTemp54)), Float(0.0158489998f)) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.0398110002f), BinopInst("*", Float(0.0298110005f), LoadVarInst(stack, fTemp52))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(0.344812989f), LoadVarInst(stack, fTemp50)), Float(0.00999999978f)) Float(0.35481301f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.103624001f), LoadVarInst(stack, fTemp48))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.171755999f), LoadVarInst(stack, fTemp46))) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(0.0205669999f), LoadVarInst(stack, fTemp44)), Float(0.0794330016f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0601890013f), LoadVarInst(stack, fTemp41))) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(0.0232849997f), LoadVarInst(stack, fTemp39)), Float(0.0398110002f)) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(0.0369039997f), LoadVarInst(stack, fTemp37)), Float(0.0630960017f)) Float(0.100000001f))) LoadVarInst(stack, fTemp110)) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(0.0635839999f), LoadVarInst(stack, fTemp33)), Float(0.0158489998f)) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0478099994f), LoadVarInst(stack, fTemp31))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp29)), Float(0.0316229984f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0900000036f), LoadVarInst(stack, fTemp27))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(0.0401189998f), LoadVarInst(stack, fTemp24)), Float(0.00999999978f)) Float(0.0501190014f))) LoadVarInst(stack, fTemp101)) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0694330037f), LoadVarInst(stack, fTemp20))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(0.388107002f), LoadVarInst(stack, fTemp18)), Float(0.00999999978f)) Float(0.398106992f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(0.398106992f), BinopInst("*", Float(0.198580995f), LoadVarInst(stack, fTemp16))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.099526003f), LoadVarInst(stack, fTemp14))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(0.151188999f), LoadVarInst(stack, fTemp12)), Float(0.100000001f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.0516630001f), LoadVarInst(stack, fTemp10))) Float(0.199525997f))))
		DeclareVarInst(stack, "float", fTemp112, Select2Inst(LoadVarInst(stack, iSlow17) BinopInst("*", LoadVarInst(stack, fTemp74), LoadVarInst(stack, fTemp111)) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp111))))
		DeclareVarInst(stack, "float", fTemp113, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Float(4950.0f) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(4950.0f), BinopInst("*", Float(2200.0f), LoadVarInst(stack, fTemp50))) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", LoadVarInst(stack, fTemp104), Float(2750.0f)) Float(3100.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(240.0f), LoadVarInst(stack, fTemp46)), Float(3100.0f)) Float(3340.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(3340.0f), BinopInst("*", Float(440.0f), LoadVarInst(stack, fTemp44))) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("+", LoadVarInst(stack, fTemp42), Float(2900.0f)) Float(2950.0f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp39)), Float(2950.0f)) Float(3350.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(3350.0f), LoadVarInst(stack, fTemp91)) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(290.0f), LoadVarInst(stack, fTemp35)), Float(3300.0f)) Float(3590.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(3590.0f), BinopInst("*", Float(290.0f), LoadVarInst(stack, fTemp33))) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp31)), Float(3300.0f)) Float(3400.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(1550.0f), LoadVarInst(stack, fTemp29)), Float(3400.0f)) Float(4950.0f))) Float(4950.0f)) Float(4950.0f)) Float(4950.0f)) Float(4950.0f)) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(4950.0f), BinopInst("*", Float(1700.0f), LoadVarInst(stack, fTemp18))) Float(3250.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("+", BinopInst("*", Float(330.0f), LoadVarInst(stack, fTemp16)), Float(3250.0f)) Float(3580.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(3580.0f), BinopInst("*", Float(40.0f), LoadVarInst(stack, fTemp14))) Float(3540.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("-", Float(3540.0f), BinopInst("*", Float(540.0f), LoadVarInst(stack, fTemp12))) Float(3000.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp10)), Float(3000.0f)) Float(3300.0f))))
		DeclareVarInst(stack, "float", fTemp114, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp113))))
		DeclareVarInst(stack, "float", fTemp115, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp114)))
		DeclareVarInst(stack, "float", fTemp116, BinopInst("/", Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(140.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp7)), Float(140.0f)) Float(200.0f))) Float(200.0f)) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(200.0f), BinopInst("*", Float(65.0f), LoadVarInst(stack, fTemp54))) Float(135.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("+", BinopInst("*", Float(65.0f), LoadVarInst(stack, fTemp52)), Float(135.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(200.0f), BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp50))) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp84)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", LoadVarInst(stack, fTemp97), Float(120.0f)) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(140.0f), LoadVarInst(stack, fTemp96)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", LoadVarInst(stack, fTemp95), Float(120.0f)) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp27)), Float(140.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(200.0f), LoadVarInst(stack, fTemp25)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("+", BinopInst("*", Float(80.0f), LoadVarInst(stack, fTemp20)), Float(120.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(200.0f), BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp18))) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(140.0f), LoadVarInst(stack, fTemp64)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(15.0f), LoadVarInst(stack, fTemp12)), Float(120.0f)) Float(135.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(135.0f), BinopInst("*", Float(15.0f), LoadVarInst(stack, fTemp10))) Float(120.0f))), LoadVarInst(stack, fTemp113)))
		DeclareVarInst(stack, "float", fTemp117, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp115), LoadVarInst(stack, fTemp116)), LoadVarInst(stack, fTemp114)), Float(1.0f)))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp6), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec15[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp115), LoadVarInst(stack, fTemp116)), LoadVarInst(stack, fTemp114)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec15[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp114))))))), LoadVarInst(stack, fTemp117))))
		DeclareVarInst(stack, "float", fTemp118, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Float(0.00100000005f) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(0.000777999987f), LoadVarInst(stack, fTemp54)), Float(0.00100000005f)) Float(0.00177800003f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.00177800003f), BinopInst("*", Float(0.001147f), LoadVarInst(stack, fTemp52))) Float(0.000630999974f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(0.0993689969f), LoadVarInst(stack, fTemp50)), Float(0.000630999974f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", BinopInst("*", Float(0.0258930009f), LoadVarInst(stack, fTemp48)), Float(0.100000001f)) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("-", Float(0.125892997f), BinopInst("*", Float(0.0860819966f), LoadVarInst(stack, fTemp46))) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(0.0398110002f), BinopInst("*", Float(0.0298110005f), LoadVarInst(stack, fTemp44))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("+", BinopInst("*", Float(0.00584900007f), LoadVarInst(stack, fTemp41)), Float(0.00999999978f)) Float(0.0158489998f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("-", Float(0.0158489998f), BinopInst("*", Float(0.00325999991f), LoadVarInst(stack, fTemp39))) Float(0.0125890002f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(0.0874110013f), LoadVarInst(stack, fTemp37)), Float(0.0125890002f)) Float(0.100000001f))) LoadVarInst(stack, fTemp110)) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(0.00410400005f), LoadVarInst(stack, fTemp33)), Float(0.0158489998f)) Float(0.0199529994f))) Float(0.0199529994f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("-", Float(0.0199529994f), BinopInst("*", Float(0.0167909991f), LoadVarInst(stack, fTemp29))) Float(0.0031620001f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(0.0031620001f), BinopInst("*", Float(0.00157700002f), LoadVarInst(stack, fTemp27))) Float(0.00158499996f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(0.00472499989f), LoadVarInst(stack, fTemp24)), Float(0.00158499996f)) Float(0.00631000008f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(0.00631000008f), BinopInst("*", Float(0.00314799999f), LoadVarInst(stack, fTemp22))) Float(0.0031620001f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(0.0031620001f), BinopInst("*", Float(0.00216199993f), LoadVarInst(stack, fTemp20))) Float(0.00100000005f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(0.0784329996f), LoadVarInst(stack, fTemp18)), Float(0.00100000005f)) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("+", BinopInst("*", Float(0.0205669999f), LoadVarInst(stack, fTemp16)), Float(0.0794330016f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp14))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(0.0184959993f), LoadVarInst(stack, fTemp12)), Float(0.0316229984f)) Float(0.0501190014f))) Float(0.0501190014f)))
		DeclareVarInst(stack, "float", fTemp119, Select2Inst(LoadVarInst(stack, iSlow17) BinopInst("*", LoadVarInst(stack, fTemp74), LoadVarInst(stack, fTemp118)) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp118))))
		DeclareVarInst(stack, "float", fTemp120, BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(stack, fTemp75), LoadVarInst(stack, fTemp62)))), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(stack, fTemp75)), LoadVarInst(stack, fTemp62))), LoadVarInst(stack, fTemp72)), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec12[Int32(2)]), BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(stack, fTemp88), LoadVarInst(stack, fTemp79)))), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(stack, fTemp88)), LoadVarInst(stack, fTemp79))), LoadVarInst(stack, fTemp86))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec13[Int32(2)]), BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(stack, fTemp103), LoadVarInst(stack, fTemp93)))), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(stack, fTemp103)), LoadVarInst(stack, fTemp93))), LoadVarInst(stack, fTemp100))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec14[Int32(2)]), BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(stack, fTemp112), LoadVarInst(stack, fTemp106)))), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec14[Int32(0)]), LoadVarInst(stack, fTemp112)), LoadVarInst(stack, fTemp106))), LoadVarInst(stack, fTemp109))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec15[Int32(2)]), BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(stack, fTemp119), LoadVarInst(stack, fTemp114)))), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fTemp119)), LoadVarInst(stack, fTemp114))), LoadVarInst(stack, fTemp117)))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp120)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp120)))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, iRec8[Int32(1)], LoadVarInst(struct, iRec8[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(2)], LoadVarInst(struct, fRec12[Int32(1)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(2)], LoadVarInst(struct, fRec13[Int32(1)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(2)], LoadVarInst(struct, fRec14[Int32(1)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(2)], LoadVarInst(struct, fRec15[Int32(1)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fButton0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, int, iRec8[2])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider10)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, float, fRec12[3])
	DeclareVarInst(struct, float, fRec13[3])
	DeclareVarInst(struct, float, fRec14[3])
	DeclareVarInst(struct, float, fRec15[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.90000000000000002f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(10.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(6.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider10, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l3)], Float(0.0f))
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
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec8[LoadVarInst(loop, l8)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(3))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(3))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(3))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(3))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(3))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider3))))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow1), CastInst("float", LoadVarInst(struct, fHslider2))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider4))))
	DeclareVarInst(stack, "float", fSlow5, CastInst("float", LoadVarInst(struct, fHslider5)))
	DeclareVarInst(stack, "int", iSlow6, BinopInst("==", LoadVarInst(stack, fSlow1), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow7, CastInst("float", LoadVarInst(struct, fHslider6)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", Float(0.100000001f), CastInst("float", LoadVarInst(struct, fHslider7))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", LoadVarInst(struct, fConst3), CastInst("float", LoadVarInst(struct, fHslider8))))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("sinf", LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow11, FunCallInst("cosf", LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow10)))
	DeclareVarInst(stack, "float", fSlow13, CastInst("float", LoadVarInst(struct, fHslider9)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(5.0f), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider10))))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", Float(5.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow13))))
	DeclareVarInst(stack, "int", iSlow17, BinopInst("==", Select2Inst(BinopInst("==", LoadVarInst(stack, fSlow13), Float(0.0f)) Int32(1) Select2Inst(BinopInst("==", LoadVarInst(stack, fSlow13), Float(3.0f)) Int32(1) Int32(0))), Int32(0)))
	DeclareVarInst(stack, "int", iSlow18, BinopInst("!=", LoadVarInst(stack, fSlow13), Float(2.0f)))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("*", Float(2.0f), LoadVarInst(stack, fSlow5)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow1))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec1[Int32(1)]))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec2[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow6)))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), BinopInst("*", LoadVarInst(struct, fRec5[Int32(1)]), CastInst("float", LoadVarInst(stack, iTemp0)))), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0)))))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec7[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec6[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp1, BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec7[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec6[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp1))))
			DeclareVarInst(stack, "float", fTemp2, FunCallInst("max_f", Float(1.00000001e-07f), FunCallInst("fabsf", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("*", LoadVarInst(struct, fRec5[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec6[Int32(0)])), Float(1.0f)))))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp2))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(stack, fTemp3), Float(-1.0f)))
			DeclareVarInst(stack, "int", iTemp5, BinopInst("<", LoadVarInst(stack, fTemp4), Float(0.0f)))
			StoreVarInst(struct, fRec3[Int32(0)], Select2Inst(LoadVarInst(stack, iTemp5) LoadVarInst(stack, fTemp3) LoadVarInst(stack, fTemp4)))
			DeclareVarInst(stack, "float", fRec4, Select2Inst(LoadVarInst(stack, iTemp5) LoadVarInst(stack, fTemp3) BinopInst("+", LoadVarInst(stack, fTemp3), BinopInst("*", LoadVarInst(stack, fTemp4), BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(struct, fConst0), LoadVarInst(stack, fTemp2)))))))
			StoreVarInst(struct, iRec8[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec8[Int32(1)])), Int32(12345)))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("+", BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec2[Int32(0)])), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(stack, fRec4)), Float(-1.0f))), BinopInst("*", Float(4.65661287e-10f), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), CastInst("float", LoadVarInst(struct, iRec8[Int32(0)])))))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow15), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec9[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec9[Int32(0)])))
			DeclareVarInst(stack, "int", iTemp8, BinopInst("<", LoadVarInst(stack, fTemp7), Float(23.0f)))
			DeclareVarInst(stack, "int", iTemp9, BinopInst("<", LoadVarInst(stack, fTemp7), Float(24.0f)))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-23.0f))))
			DeclareVarInst(stack, "int", iTemp11, BinopInst("<", LoadVarInst(stack, fTemp7), Float(22.0f)))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-22.0f))))
			DeclareVarInst(stack, "int", iTemp13, BinopInst("<", LoadVarInst(stack, fTemp7), Float(21.0f)))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-21.0f))))
			DeclareVarInst(stack, "int", iTemp15, BinopInst("<", LoadVarInst(stack, fTemp7), Float(20.0f)))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-20.0f))))
			DeclareVarInst(stack, "int", iTemp17, BinopInst("<", LoadVarInst(stack, fTemp7), Float(19.0f)))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-19.0f))))
			DeclareVarInst(stack, "int", iTemp19, BinopInst("<", LoadVarInst(stack, fTemp7), Float(18.0f)))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-18.0f))))
			DeclareVarInst(stack, "int", iTemp21, BinopInst("<", LoadVarInst(stack, fTemp7), Float(17.0f)))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-17.0f))))
			DeclareVarInst(stack, "int", iTemp23, BinopInst("<", LoadVarInst(stack, fTemp7), Float(16.0f)))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-16.0f))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("*", Float(80.0f), LoadVarInst(stack, fTemp24)))
			DeclareVarInst(stack, "int", iTemp26, BinopInst("<", LoadVarInst(stack, fTemp7), Float(15.0f)))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-15.0f))))
			DeclareVarInst(stack, "int", iTemp28, BinopInst("<", LoadVarInst(stack, fTemp7), Float(14.0f)))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-14.0f))))
			DeclareVarInst(stack, "int", iTemp30, BinopInst("<", LoadVarInst(stack, fTemp7), Float(13.0f)))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-13.0f))))
			DeclareVarInst(stack, "int", iTemp32, BinopInst("<", LoadVarInst(stack, fTemp7), Float(12.0f)))
			DeclareVarInst(stack, "float", fTemp33, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-12.0f))))
			DeclareVarInst(stack, "int", iTemp34, BinopInst("<", LoadVarInst(stack, fTemp7), Float(11.0f)))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-11.0f))))
			DeclareVarInst(stack, "int", iTemp36, BinopInst("<", LoadVarInst(stack, fTemp7), Float(10.0f)))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-10.0f))))
			DeclareVarInst(stack, "int", iTemp38, BinopInst("<", LoadVarInst(stack, fTemp7), Float(9.0f)))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-9.0f))))
			DeclareVarInst(stack, "int", iTemp40, BinopInst("<", LoadVarInst(stack, fTemp7), Float(8.0f)))
			DeclareVarInst(stack, "float", fTemp41, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-8.0f))))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp41)))
			DeclareVarInst(stack, "int", iTemp43, BinopInst("<", LoadVarInst(stack, fTemp7), Float(7.0f)))
			DeclareVarInst(stack, "float", fTemp44, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-7.0f))))
			DeclareVarInst(stack, "int", iTemp45, BinopInst("<", LoadVarInst(stack, fTemp7), Float(6.0f)))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-6.0f))))
			DeclareVarInst(stack, "int", iTemp47, BinopInst("<", LoadVarInst(stack, fTemp7), Float(5.0f)))
			DeclareVarInst(stack, "float", fTemp48, BinopInst("-", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(stack, fSlow16)))
			DeclareVarInst(stack, "int", iTemp49, BinopInst("<", LoadVarInst(stack, fTemp7), Float(4.0f)))
			DeclareVarInst(stack, "float", fTemp50, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-4.0f))))
			DeclareVarInst(stack, "int", iTemp51, BinopInst("<", LoadVarInst(stack, fTemp7), Float(3.0f)))
			DeclareVarInst(stack, "float", fTemp52, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-3.0f))))
			DeclareVarInst(stack, "int", iTemp53, BinopInst("<", LoadVarInst(stack, fTemp7), Float(2.0f)))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-2.0f))))
			DeclareVarInst(stack, "int", iTemp55, BinopInst("<", LoadVarInst(stack, fTemp7), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp56, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("+", LoadVarInst(struct, fRec9[Int32(0)]), Float(-1.0f))))
			DeclareVarInst(stack, "int", iTemp57, BinopInst("<", LoadVarInst(stack, fTemp7), Float(0.0f)))
			DeclareVarInst(stack, "float", fTemp58, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(800.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(800.0f), BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp7))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("-", Float(400.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp56))) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp54)), Float(350.0f)) Float(450.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(450.0f), BinopInst("*", Float(125.0f), LoadVarInst(stack, fTemp52))) Float(325.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(275.0f), LoadVarInst(stack, fTemp50)), Float(325.0f)) Float(600.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(600.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp48))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("-", Float(400.0f), BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp46))) Float(250.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp44)), Float(250.0f)) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(400.0f), LoadVarInst(stack, fTemp42)) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(310.0f), LoadVarInst(stack, fTemp39)), Float(350.0f)) Float(660.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(660.0f), BinopInst("*", Float(220.0f), LoadVarInst(stack, fTemp37))) Float(440.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(440.0f), BinopInst("*", Float(170.0f), LoadVarInst(stack, fTemp35))) Float(270.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(160.0f), LoadVarInst(stack, fTemp33)), Float(270.0f)) Float(430.0f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("-", Float(430.0f), BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp31))) Float(370.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(430.0f), LoadVarInst(stack, fTemp29)), Float(370.0f)) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(800.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp27))) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(350.0f), LoadVarInst(stack, fTemp25)) Float(270.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(180.0f), LoadVarInst(stack, fTemp22)), Float(270.0f)) Float(450.0f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(450.0f), BinopInst("*", Float(125.0f), LoadVarInst(stack, fTemp20))) Float(325.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("*", Float(325.0f), BinopInst("+", LoadVarInst(stack, fTemp18), Float(1.0f))) Float(650.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(650.0f), BinopInst("*", Float(250.0f), LoadVarInst(stack, fTemp16))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(400.0f), BinopInst("*", Float(110.0f), LoadVarInst(stack, fTemp14))) Float(290.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(110.0f), LoadVarInst(stack, fTemp12)), Float(290.0f)) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(400.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp10))) Float(350.0f))))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec10[Int32(1)]))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec11[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec10[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp1))))
			DeclareVarInst(stack, "float", fTemp59, BinopInst("*", LoadVarInst(struct, fRec5[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(struct, fRec10[Int32(0)])), Float(1.0f))))
			DeclareVarInst(stack, "float", fTemp60, BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(stack, fTemp59)))
			DeclareVarInst(stack, "float", fTemp61, Select2Inst(BinopInst("<=", LoadVarInst(stack, fTemp58), LoadVarInst(stack, fTemp60)) LoadVarInst(stack, fTemp60) LoadVarInst(stack, fTemp58)))
			DeclareVarInst(stack, "float", fTemp62, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp61))))
			DeclareVarInst(stack, "float", fTemp63, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp62)))
			DeclareVarInst(stack, "float", fTemp64, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp16)))
			DeclareVarInst(stack, "float", fTemp65, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp27)))
			DeclareVarInst(stack, "float", fTemp66, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp37)))
			DeclareVarInst(stack, "float", fTemp67, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp50)))
			DeclareVarInst(stack, "float", fTemp68, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp52)))
			DeclareVarInst(stack, "float", fTemp69, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp54)))
			DeclareVarInst(stack, "float", fTemp70, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp7)))
			DeclareVarInst(stack, "float", fTemp71, BinopInst("/", Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(80.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp70)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("-", Float(60.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp56))) Float(50.0f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", LoadVarInst(stack, fTemp69), Float(50.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(70.0f), LoadVarInst(stack, fTemp68)) Float(50.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", LoadVarInst(stack, fTemp67), Float(50.0f)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp48))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp46)), Float(40.0f)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp44))) Float(40.0f))) Float(40.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("*", Float(40.0f), BinopInst("+", LoadVarInst(stack, fTemp39), Float(1.0f))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp66)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp35))) Float(40.0f))) Float(40.0f)) Float(40.0f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("*", Float(40.0f), BinopInst("+", LoadVarInst(stack, fTemp29), Float(1.0f))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp65)) Float(60.0f))) Float(60.0f)) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp22))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp20)), Float(40.0f)) Float(50.0f))) Float(50.0f)) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("+", LoadVarInst(stack, fTemp64), Float(50.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp14))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp12)), Float(40.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp10))) Float(40.0f))), LoadVarInst(stack, fTemp61)))
			DeclareVarInst(stack, "float", fTemp72, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp63), LoadVarInst(stack, fTemp71)), LoadVarInst(stack, fTemp62)), Float(1.0f)))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp6), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp63), LoadVarInst(stack, fTemp71)), LoadVarInst(stack, fTemp62)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec0[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp62))))))), LoadVarInst(stack, fTemp72))))
			DeclareVarInst(stack, "float", fTemp73, BinopInst("+", BinopInst("*", Float(0.000839999993f), BinopInst("-", Float(1000.0f), LoadVarInst(stack, fTemp60))), Float(0.800000012f)))
			DeclareVarInst(stack, "float", fTemp74, BinopInst("+", BinopInst("*", Float(0.00366666657f), BinopInst("-", Float(400.0f), LoadVarInst(stack, fTemp60))), Float(3.0f)))
			DeclareVarInst(stack, "float", fTemp75, Select2Inst(LoadVarInst(stack, iSlow17) LoadVarInst(stack, fTemp74) LoadVarInst(stack, fTemp73)))
			DeclareVarInst(stack, "float", fTemp76, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(1150.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("+", BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp7)), Float(1150.0f)) Float(1600.0f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp56)), Float(1600.0f)) Float(1700.0f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(1700.0f), BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp54))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp52))) Float(700.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(340.0f), LoadVarInst(stack, fTemp50)), Float(700.0f)) Float(1040.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", BinopInst("*", Float(580.0f), LoadVarInst(stack, fTemp48)), Float(1040.0f)) Float(1620.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp46)), Float(1620.0f)) Float(1750.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(1750.0f), BinopInst("*", Float(1000.0f), LoadVarInst(stack, fTemp44))) Float(750.0f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(750.0f), BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp41))) Float(600.0f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(520.0f), LoadVarInst(stack, fTemp39)), Float(600.0f)) Float(1120.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(680.0f), LoadVarInst(stack, fTemp37)), Float(1120.0f)) Float(1800.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp35)), Float(1800.0f)) Float(1850.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(1850.0f), BinopInst("*", Float(1030.0f), LoadVarInst(stack, fTemp33))) Float(820.0f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("-", Float(820.0f), BinopInst("*", Float(190.0f), LoadVarInst(stack, fTemp31))) Float(630.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(520.0f), LoadVarInst(stack, fTemp29)), Float(630.0f)) Float(1150.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("+", BinopInst("*", Float(850.0f), LoadVarInst(stack, fTemp27)), Float(1150.0f)) Float(2000.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(140.0f), LoadVarInst(stack, fTemp24)), Float(2000.0f)) Float(2140.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(2140.0f), BinopInst("*", Float(1340.0f), LoadVarInst(stack, fTemp22))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp20))) Float(700.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(380.0f), LoadVarInst(stack, fTemp18)), Float(700.0f)) Float(1080.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("+", BinopInst("*", Float(620.0f), LoadVarInst(stack, fTemp16)), Float(1080.0f)) Float(1700.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("+", BinopInst("*", Float(170.0f), LoadVarInst(stack, fTemp14)), Float(1700.0f)) Float(1870.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("-", Float(1870.0f), BinopInst("*", Float(1070.0f), LoadVarInst(stack, fTemp12))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(800.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp10))) Float(600.0f))))
			DeclareVarInst(stack, "float", fTemp77, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow19), LoadVarInst(stack, fTemp59)), Float(30.0f)))
			DeclareVarInst(stack, "float", fTemp78, Select2Inst(LoadVarInst(stack, iSlow18) Select2Inst(BinopInst("&", BinopInst(">=", LoadVarInst(stack, fTemp76), Float(1300.0f)), BinopInst(">=", LoadVarInst(stack, fTemp60), Float(200.0f))) BinopInst("-", LoadVarInst(stack, fTemp76), BinopInst("*", Float(0.000952380942f), BinopInst("*", BinopInst("+", LoadVarInst(stack, fTemp60), Float(-200.0f)), BinopInst("+", LoadVarInst(stack, fTemp76), Float(-1300.0f))))) Select2Inst(BinopInst("<=", LoadVarInst(stack, fTemp76), LoadVarInst(stack, fTemp77)) LoadVarInst(stack, fTemp77) LoadVarInst(stack, fTemp76))) LoadVarInst(stack, fTemp76)))
			DeclareVarInst(stack, "float", fTemp79, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp78))))
			DeclareVarInst(stack, "float", fTemp80, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp79)))
			DeclareVarInst(stack, "float", fTemp81, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "float", fTemp82, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp16)))
			DeclareVarInst(stack, "float", fTemp83, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp39)))
			DeclareVarInst(stack, "float", fTemp84, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp48)))
			DeclareVarInst(stack, "float", fTemp85, BinopInst("/", Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(90.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp7))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("+", BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp56)), Float(80.0f)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(100.0f), LoadVarInst(stack, fTemp69)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp68)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", LoadVarInst(stack, fTemp67), Float(60.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", LoadVarInst(stack, fTemp84), Float(70.0f)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp46)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp44))) Float(80.0f))) Float(80.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", LoadVarInst(stack, fTemp83), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp66)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp35)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp33))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp31))) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp29)), Float(60.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp27)), Float(90.0f)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(100.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp24))) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp22))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp20))) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp18)), Float(60.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp82)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp14)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp81)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp10))) Float(60.0f))), LoadVarInst(stack, fTemp78)))
			DeclareVarInst(stack, "float", fTemp86, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp80), LoadVarInst(stack, fTemp85)), LoadVarInst(stack, fTemp79)), Float(1.0f)))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp6), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec12[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp80), LoadVarInst(stack, fTemp85)), LoadVarInst(stack, fTemp79)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp79))))))), LoadVarInst(stack, fTemp86))))
			DeclareVarInst(stack, "float", fTemp87, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(0.630957007f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(0.630957007f), BinopInst("*", Float(0.567861021f), LoadVarInst(stack, fTemp7))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("+", BinopInst("*", Float(0.0369039997f), LoadVarInst(stack, fTemp56)), Float(0.0630960017f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(0.254812986f), LoadVarInst(stack, fTemp54)), Float(0.100000001f)) Float(0.35481301f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.103624001f), LoadVarInst(stack, fTemp52))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp50)), Float(0.251188993f)) Float(0.446684003f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(0.446684003f), BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp48))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.219566002f), LoadVarInst(stack, fTemp46))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(0.250214994f), LoadVarInst(stack, fTemp44)), Float(0.0316229984f)) Float(0.281838f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(0.281838f), BinopInst("*", Float(0.181838006f), LoadVarInst(stack, fTemp41))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp39)), Float(0.100000001f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.301661015f), LoadVarInst(stack, fTemp37))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.136429995f), LoadVarInst(stack, fTemp35))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(0.253131986f), LoadVarInst(stack, fTemp33)), Float(0.0630960017f)) Float(0.316228002f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("-", Float(0.316228002f), BinopInst("*", Float(0.216227993f), LoadVarInst(stack, fTemp31))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp29)), Float(0.100000001f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp27))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(0.151188999f), LoadVarInst(stack, fTemp24)), Float(0.100000001f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.0306490008f), LoadVarInst(stack, fTemp22)), Float(0.251188993f)) Float(0.281838f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(0.281838f), BinopInst("*", Float(0.123349003f), LoadVarInst(stack, fTemp20))) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(0.342698008f), LoadVarInst(stack, fTemp18)), Float(0.158489004f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.301661015f), LoadVarInst(stack, fTemp16))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.0216979999f), LoadVarInst(stack, fTemp14))) Float(0.177827999f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(0.138400003f), LoadVarInst(stack, fTemp12)), Float(0.177827999f)) Float(0.316228002f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(0.316228002f), BinopInst("*", Float(0.216227993f), LoadVarInst(stack, fTemp10))) Float(0.100000001f))))
			DeclareVarInst(stack, "float", fTemp88, Select2Inst(LoadVarInst(stack, iSlow17) BinopInst("*", LoadVarInst(stack, fTemp74), LoadVarInst(stack, fTemp87)) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp87))))
			DeclareVarInst(stack, "float", fTemp89, BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp90, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp18)))
			DeclareVarInst(stack, "float", fTemp91, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp37)))
			DeclareVarInst(stack, "float", fTemp92, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(2800.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(2800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp7))) Float(2700.0f))) Float(2700.0f)) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp54)), Float(2700.0f)) Float(2830.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(2830.0f), BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp52))) Float(2530.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(2530.0f), BinopInst("*", Float(280.0f), LoadVarInst(stack, fTemp50))) Float(2250.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp48)), Float(2250.0f)) Float(2400.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp46)), Float(2400.0f)) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(2600.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp44))) Float(2400.0f))) Float(2400.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp39)), Float(2400.0f)) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(2750.0f), LoadVarInst(stack, fTemp91)) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp35)), Float(2700.0f)) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(2900.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp33))) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp31)), Float(2700.0f)) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp29)), Float(2750.0f)) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(2900.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp27))) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp24)), Float(2800.0f)) Float(2950.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(2950.0f), BinopInst("*", Float(120.0f), LoadVarInst(stack, fTemp22))) Float(2830.0f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(2830.0f), BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp20))) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(2700.0f), LoadVarInst(stack, fTemp90)) Float(2650.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(2650.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp16))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp14)), Float(2600.0f)) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("-", Float(2800.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp12))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("+", LoadVarInst(stack, fTemp89), Float(2600.0f)) Float(2700.0f))))
			DeclareVarInst(stack, "float", fTemp93, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp92))))
			DeclareVarInst(stack, "float", fTemp94, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp93)))
			DeclareVarInst(stack, "float", fTemp95, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp29)))
			DeclareVarInst(stack, "float", fTemp96, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp37)))
			DeclareVarInst(stack, "float", fTemp97, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp39)))
			DeclareVarInst(stack, "float", fTemp98, BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp50)))
			DeclareVarInst(stack, "float", fTemp99, BinopInst("/", Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Float(120.0f) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp69)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("+", BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp52)), Float(100.0f)) Float(170.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(170.0f), LoadVarInst(stack, fTemp98)) Float(110.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(110.0f), LoadVarInst(stack, fTemp84)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", LoadVarInst(stack, fTemp97), Float(100.0f)) Float(120.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp96)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", LoadVarInst(stack, fTemp95), Float(100.0f)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(120.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp24))) Float(100.0f))) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("+", BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp20)), Float(100.0f)) Float(170.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(170.0f), LoadVarInst(stack, fTemp90)) Float(120.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp64)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)), LoadVarInst(stack, fTemp92)))
			DeclareVarInst(stack, "float", fTemp100, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp94), LoadVarInst(stack, fTemp99)), LoadVarInst(stack, fTemp93)), Float(1.0f)))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp6), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec13[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp94), LoadVarInst(stack, fTemp99)), LoadVarInst(stack, fTemp93)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec13[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp93))))))), LoadVarInst(stack, fTemp100))))
			DeclareVarInst(stack, "float", fTemp101, Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.0293140002f), LoadVarInst(stack, fTemp22)), Float(0.0501190014f)) Float(0.0794330016f)))
			DeclareVarInst(stack, "float", fTemp102, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(0.100000001f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp7))) Float(0.0316229984f))) Float(0.0316229984f)) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(0.126865998f), LoadVarInst(stack, fTemp54)), Float(0.0316229984f)) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.158489004f), BinopInst("*", Float(0.126865998f), LoadVarInst(stack, fTemp52))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(0.323190004f), LoadVarInst(stack, fTemp50)), Float(0.0316229984f)) Float(0.35481301f))) Float(0.35481301f)) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.196324006f), LoadVarInst(stack, fTemp46))) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(0.158489004f), BinopInst("*", Float(0.0693639964f), LoadVarInst(stack, fTemp44))) Float(0.0891249999f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(0.0891249999f), BinopInst("*", Float(0.0640060008f), LoadVarInst(stack, fTemp41))) Float(0.0251189992f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(0.0456760004f), LoadVarInst(stack, fTemp39)), Float(0.0251189992f)) Float(0.0707949996f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(0.0550980009f), LoadVarInst(stack, fTemp37)), Float(0.0707949996f)) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(0.125892997f), BinopInst("*", Float(0.0627970025f), LoadVarInst(stack, fTemp35))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(0.0630960017f), BinopInst("*", Float(0.0129770003f), LoadVarInst(stack, fTemp33))) Float(0.0501190014f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("+", BinopInst("*", Float(0.020676f), LoadVarInst(stack, fTemp31)), Float(0.0501190014f)) Float(0.0707949996f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("-", Float(0.0707949996f), BinopInst("*", Float(0.0456760004f), LoadVarInst(stack, fTemp29))) Float(0.0251189992f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("+", BinopInst("*", Float(0.152709007f), LoadVarInst(stack, fTemp27)), Float(0.0251189992f)) Float(0.177827999f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(0.177827999f), BinopInst("*", Float(0.127709001f), LoadVarInst(stack, fTemp24))) Float(0.0501190014f))) LoadVarInst(stack, fTemp101)) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0616500005f), LoadVarInst(stack, fTemp20))) Float(0.0177829992f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(0.428900987f), LoadVarInst(stack, fTemp18)), Float(0.0177829992f)) Float(0.446684003f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(0.446684003f), BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp16))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.125295997f), LoadVarInst(stack, fTemp14))) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(0.125295997f), LoadVarInst(stack, fTemp12)), Float(0.125892997f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.109935001f), LoadVarInst(stack, fTemp10))) Float(0.141253993f))))
			DeclareVarInst(stack, "float", fTemp103, Select2Inst(LoadVarInst(stack, iSlow17) BinopInst("*", LoadVarInst(stack, fTemp74), LoadVarInst(stack, fTemp102)) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp102))))
			DeclareVarInst(stack, "float", fTemp104, BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp48)))
			DeclareVarInst(stack, "float", fTemp105, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(3500.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("-", Float(3500.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp7))) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("+", BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp56)), Float(3300.0f)) Float(3700.0f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(3700.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp54))) Float(3500.0f))) Float(3500.0f)) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(3500.0f), BinopInst("*", Float(1050.0f), LoadVarInst(stack, fTemp50))) Float(2450.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", LoadVarInst(stack, fTemp104), Float(2450.0f)) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(250.0f), LoadVarInst(stack, fTemp46)), Float(2800.0f)) Float(3050.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(3050.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp44))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("+", BinopInst("*", Float(75.0f), LoadVarInst(stack, fTemp41)), Float(2600.0f)) Float(2675.0f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(325.0f), LoadVarInst(stack, fTemp39)), Float(2675.0f)) Float(3000.0f))) Float(3000.0f)) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp35)), Float(3000.0f)) Float(3350.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(3350.0f), BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp33))) Float(3000.0f))) Float(3000.0f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp29)), Float(3000.0f)) Float(3900.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(3900.0f), BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp27))) Float(3600.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp24)), Float(3600.0f)) Float(3900.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(3900.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp22))) Float(3800.0f))) Float(3800.0f)) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(3800.0f), BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp18))) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp16)), Float(2900.0f)) Float(3200.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp14)), Float(3200.0f)) Float(3250.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("-", Float(3250.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp12))) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("+", LoadVarInst(stack, fTemp89), Float(2800.0f)) Float(2900.0f))))
			DeclareVarInst(stack, "float", fTemp106, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp105))))
			DeclareVarInst(stack, "float", fTemp107, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp106)))
			DeclareVarInst(stack, "float", fTemp108, BinopInst("/", Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(130.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("+", LoadVarInst(stack, fTemp70), Float(130.0f)) Float(150.0f))) Float(150.0f)) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(150.0f), LoadVarInst(stack, fTemp69)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp52)), Float(130.0f)) Float(180.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(180.0f), LoadVarInst(stack, fTemp98)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", LoadVarInst(stack, fTemp83), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp66)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp29)), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("+", LoadVarInst(stack, fTemp65), Float(130.0f)) Float(150.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(150.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp24))) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp20)), Float(120.0f)) Float(180.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(180.0f), LoadVarInst(stack, fTemp90)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp82)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", LoadVarInst(stack, fTemp81), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(130.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp10))) Float(120.0f))), LoadVarInst(stack, fTemp105)))
			DeclareVarInst(stack, "float", fTemp109, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp107), LoadVarInst(stack, fTemp108)), LoadVarInst(stack, fTemp106)), Float(1.0f)))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp6), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec14[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp107), LoadVarInst(stack, fTemp108)), LoadVarInst(stack, fTemp106)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec14[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp106))))))), LoadVarInst(stack, fTemp109))))
			DeclareVarInst(stack, "float", fTemp110, Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0841509998f), LoadVarInst(stack, fTemp35))) Float(0.0158489998f)))
			DeclareVarInst(stack, "float", fTemp111, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(0.0158489998f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("+", BinopInst("*", Float(0.00193400006f), LoadVarInst(stack, fTemp7)), Float(0.0158489998f)) Float(0.0177829992f))) Select2Inst(LoadVarInst(stack, iTemp53) BinopInst("-", Float(0.0177829992f), BinopInst("*", Float(0.00193400006f), LoadVarInst(stack, fTemp56))) Float(0.0158489998f))) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(0.0239620004f), LoadVarInst(stack, fTemp54)), Float(0.0158489998f)) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.0398110002f), BinopInst("*", Float(0.0298110005f), LoadVarInst(stack, fTemp52))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(0.344812989f), LoadVarInst(stack, fTemp50)), Float(0.00999999978f)) Float(0.35481301f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.103624001f), LoadVarInst(stack, fTemp48))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.171755999f), LoadVarInst(stack, fTemp46))) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(0.0205669999f), LoadVarInst(stack, fTemp44)), Float(0.0794330016f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0601890013f), LoadVarInst(stack, fTemp41))) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(0.0232849997f), LoadVarInst(stack, fTemp39)), Float(0.0398110002f)) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(0.0369039997f), LoadVarInst(stack, fTemp37)), Float(0.0630960017f)) Float(0.100000001f))) LoadVarInst(stack, fTemp110)) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(0.0635839999f), LoadVarInst(stack, fTemp33)), Float(0.0158489998f)) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0478099994f), LoadVarInst(stack, fTemp31))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp29)), Float(0.0316229984f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0900000036f), LoadVarInst(stack, fTemp27))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(0.0401189998f), LoadVarInst(stack, fTemp24)), Float(0.00999999978f)) Float(0.0501190014f))) LoadVarInst(stack, fTemp101)) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0694330037f), LoadVarInst(stack, fTemp20))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(0.388107002f), LoadVarInst(stack, fTemp18)), Float(0.00999999978f)) Float(0.398106992f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(0.398106992f), BinopInst("*", Float(0.198580995f), LoadVarInst(stack, fTemp16))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.099526003f), LoadVarInst(stack, fTemp14))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(0.151188999f), LoadVarInst(stack, fTemp12)), Float(0.100000001f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.0516630001f), LoadVarInst(stack, fTemp10))) Float(0.199525997f))))
			DeclareVarInst(stack, "float", fTemp112, Select2Inst(LoadVarInst(stack, iSlow17) BinopInst("*", LoadVarInst(stack, fTemp74), LoadVarInst(stack, fTemp111)) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp111))))
			DeclareVarInst(stack, "float", fTemp113, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Float(4950.0f) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(4950.0f), BinopInst("*", Float(2200.0f), LoadVarInst(stack, fTemp50))) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", LoadVarInst(stack, fTemp104), Float(2750.0f)) Float(3100.0f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("+", BinopInst("*", Float(240.0f), LoadVarInst(stack, fTemp46)), Float(3100.0f)) Float(3340.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(3340.0f), BinopInst("*", Float(440.0f), LoadVarInst(stack, fTemp44))) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("+", LoadVarInst(stack, fTemp42), Float(2900.0f)) Float(2950.0f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp39)), Float(2950.0f)) Float(3350.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(3350.0f), LoadVarInst(stack, fTemp91)) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(290.0f), LoadVarInst(stack, fTemp35)), Float(3300.0f)) Float(3590.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(3590.0f), BinopInst("*", Float(290.0f), LoadVarInst(stack, fTemp33))) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp28) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp31)), Float(3300.0f)) Float(3400.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(1550.0f), LoadVarInst(stack, fTemp29)), Float(3400.0f)) Float(4950.0f))) Float(4950.0f)) Float(4950.0f)) Float(4950.0f)) Float(4950.0f)) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(4950.0f), BinopInst("*", Float(1700.0f), LoadVarInst(stack, fTemp18))) Float(3250.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("+", BinopInst("*", Float(330.0f), LoadVarInst(stack, fTemp16)), Float(3250.0f)) Float(3580.0f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(3580.0f), BinopInst("*", Float(40.0f), LoadVarInst(stack, fTemp14))) Float(3540.0f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("-", Float(3540.0f), BinopInst("*", Float(540.0f), LoadVarInst(stack, fTemp12))) Float(3000.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp10)), Float(3000.0f)) Float(3300.0f))))
			DeclareVarInst(stack, "float", fTemp114, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst4), LoadVarInst(stack, fTemp113))))
			DeclareVarInst(stack, "float", fTemp115, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp114)))
			DeclareVarInst(stack, "float", fTemp116, BinopInst("/", Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Select2Inst(LoadVarInst(stack, iTemp55) Select2Inst(LoadVarInst(stack, iTemp57) Float(140.0f) Select2Inst(LoadVarInst(stack, iTemp55) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp7)), Float(140.0f)) Float(200.0f))) Float(200.0f)) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("-", Float(200.0f), BinopInst("*", Float(65.0f), LoadVarInst(stack, fTemp54))) Float(135.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("+", BinopInst("*", Float(65.0f), LoadVarInst(stack, fTemp52)), Float(135.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(200.0f), BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp50))) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp84)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("+", LoadVarInst(stack, fTemp97), Float(120.0f)) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(140.0f), LoadVarInst(stack, fTemp96)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", LoadVarInst(stack, fTemp95), Float(120.0f)) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp27)), Float(140.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("-", Float(200.0f), LoadVarInst(stack, fTemp25)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("+", BinopInst("*", Float(80.0f), LoadVarInst(stack, fTemp20)), Float(120.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("-", Float(200.0f), BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp18))) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("-", Float(140.0f), LoadVarInst(stack, fTemp64)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(15.0f), LoadVarInst(stack, fTemp12)), Float(120.0f)) Float(135.0f))) Select2Inst(LoadVarInst(stack, iTemp9) BinopInst("-", Float(135.0f), BinopInst("*", Float(15.0f), LoadVarInst(stack, fTemp10))) Float(120.0f))), LoadVarInst(stack, fTemp113)))
			DeclareVarInst(stack, "float", fTemp117, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp115), LoadVarInst(stack, fTemp116)), LoadVarInst(stack, fTemp114)), Float(1.0f)))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp6), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec15[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp115), LoadVarInst(stack, fTemp116)), LoadVarInst(stack, fTemp114)), Float(1.0f))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec15[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp114))))))), LoadVarInst(stack, fTemp117))))
			DeclareVarInst(stack, "float", fTemp118, Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Select2Inst(LoadVarInst(stack, iTemp13) Select2Inst(LoadVarInst(stack, iTemp15) Select2Inst(LoadVarInst(stack, iTemp17) Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp21) Select2Inst(LoadVarInst(stack, iTemp23) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp28) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp36) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp43) Select2Inst(LoadVarInst(stack, iTemp45) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp51) Select2Inst(LoadVarInst(stack, iTemp53) Float(0.00100000005f) Select2Inst(LoadVarInst(stack, iTemp51) BinopInst("+", BinopInst("*", Float(0.000777999987f), LoadVarInst(stack, fTemp54)), Float(0.00100000005f)) Float(0.00177800003f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.00177800003f), BinopInst("*", Float(0.001147f), LoadVarInst(stack, fTemp52))) Float(0.000630999974f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(0.0993689969f), LoadVarInst(stack, fTemp50)), Float(0.000630999974f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp45) BinopInst("+", BinopInst("*", Float(0.0258930009f), LoadVarInst(stack, fTemp48)), Float(0.100000001f)) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp43) BinopInst("-", Float(0.125892997f), BinopInst("*", Float(0.0860819966f), LoadVarInst(stack, fTemp46))) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(0.0398110002f), BinopInst("*", Float(0.0298110005f), LoadVarInst(stack, fTemp44))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("+", BinopInst("*", Float(0.00584900007f), LoadVarInst(stack, fTemp41)), Float(0.00999999978f)) Float(0.0158489998f))) Select2Inst(LoadVarInst(stack, iTemp36) BinopInst("-", Float(0.0158489998f), BinopInst("*", Float(0.00325999991f), LoadVarInst(stack, fTemp39))) Float(0.0125890002f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(0.0874110013f), LoadVarInst(stack, fTemp37)), Float(0.0125890002f)) Float(0.100000001f))) LoadVarInst(stack, fTemp110)) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(0.00410400005f), LoadVarInst(stack, fTemp33)), Float(0.0158489998f)) Float(0.0199529994f))) Float(0.0199529994f)) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("-", Float(0.0199529994f), BinopInst("*", Float(0.0167909991f), LoadVarInst(stack, fTemp29))) Float(0.0031620001f))) Select2Inst(LoadVarInst(stack, iTemp23) BinopInst("-", Float(0.0031620001f), BinopInst("*", Float(0.00157700002f), LoadVarInst(stack, fTemp27))) Float(0.00158499996f))) Select2Inst(LoadVarInst(stack, iTemp21) BinopInst("+", BinopInst("*", Float(0.00472499989f), LoadVarInst(stack, fTemp24)), Float(0.00158499996f)) Float(0.00631000008f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(0.00631000008f), BinopInst("*", Float(0.00314799999f), LoadVarInst(stack, fTemp22))) Float(0.0031620001f))) Select2Inst(LoadVarInst(stack, iTemp17) BinopInst("-", Float(0.0031620001f), BinopInst("*", Float(0.00216199993f), LoadVarInst(stack, fTemp20))) Float(0.00100000005f))) Select2Inst(LoadVarInst(stack, iTemp15) BinopInst("+", BinopInst("*", Float(0.0784329996f), LoadVarInst(stack, fTemp18)), Float(0.00100000005f)) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp13) BinopInst("+", BinopInst("*", Float(0.0205669999f), LoadVarInst(stack, fTemp16)), Float(0.0794330016f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp11) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp14))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp8) BinopInst("+", BinopInst("*", Float(0.0184959993f), LoadVarInst(stack, fTemp12)), Float(0.0316229984f)) Float(0.0501190014f))) Float(0.0501190014f)))
			DeclareVarInst(stack, "float", fTemp119, Select2Inst(LoadVarInst(stack, iSlow17) BinopInst("*", LoadVarInst(stack, fTemp74), LoadVarInst(stack, fTemp118)) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp118))))
			DeclareVarInst(stack, "float", fTemp120, BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(stack, fTemp75), LoadVarInst(stack, fTemp62)))), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(stack, fTemp75)), LoadVarInst(stack, fTemp62))), LoadVarInst(stack, fTemp72)), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec12[Int32(2)]), BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(stack, fTemp88), LoadVarInst(stack, fTemp79)))), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(stack, fTemp88)), LoadVarInst(stack, fTemp79))), LoadVarInst(stack, fTemp86))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec13[Int32(2)]), BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(stack, fTemp103), LoadVarInst(stack, fTemp93)))), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(stack, fTemp103)), LoadVarInst(stack, fTemp93))), LoadVarInst(stack, fTemp100))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec14[Int32(2)]), BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(stack, fTemp112), LoadVarInst(stack, fTemp106)))), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec14[Int32(0)]), LoadVarInst(stack, fTemp112)), LoadVarInst(stack, fTemp106))), LoadVarInst(stack, fTemp109))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec15[Int32(2)]), BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(stack, fTemp119), LoadVarInst(stack, fTemp114)))), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(stack, fTemp119)), LoadVarInst(stack, fTemp114))), LoadVarInst(stack, fTemp117)))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp120)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp120)))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, iRec8[Int32(1)], LoadVarInst(struct, iRec8[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(2)], LoadVarInst(struct, fRec12[Int32(1)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(2)], LoadVarInst(struct, fRec13[Int32(1)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(2)], LoadVarInst(struct, fRec14[Int32(1)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(2)], LoadVarInst(struct, fRec15[Int32(1)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 16 bytes
Heap size real = 208 bytes
Heap size = 228 bytes
Stack size in compute = 96 bytes

