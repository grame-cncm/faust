======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "sinf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, int, iRec11[2])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
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
					StoreVarInst(stack, rate, Int32(0))
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

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec11[LoadVarInst(loop, l15)], Int32(0))
			EndBlock
		EndForLoop
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 7
Store = 4
Binop = 5
Numbers = 7
Declare = 1
Cast = 1
Select = 0
Loop = 1
Funcall = 1

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec11[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec11[Int32(1)]), Int32(1)))
		StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], FunCallInst("sinf", BinopInst("*", Float(9.58738019e-05f), CastInst("float", BinopInst("+", LoadVarInst(struct, iRec11[Int32(0)]), Int32(-1))))))
		StoreVarInst(struct, iRec11[Int32(1)], LoadVarInst(struct, iRec11[Int32(0)]))
		EndBlock
	EndForLoop

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("vocal")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("midi")
	AddMetaDeclareInst(fHslider4, "0", "")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddHorizontalSlider("freq", fHslider4, 440.0f, 50.0f, 1000.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider5, "1", "")
	AddMetaDeclareInst(fHslider5, "hidden", "1")
	AddMetaDeclareInst(fHslider5, "midi", "pitchwheel")
	AddMetaDeclareInst(fHslider5, "style", "knob")
	AddHorizontalSlider("bend", fHslider5, 1.0f, 0.0f, 10.0f, 0.00999999978f)
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
	AddMetaDeclareInst(fHslider8, "1", "")
	AddMetaDeclareInst(fHslider8, "midi", "ctrl 1")
	AddMetaDeclareInst(fHslider8, "style", "knob")
	AddHorizontalSlider("vowel", fHslider8, 0.0f, 0.0f, 4.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider7, "3", "")
	AddMetaDeclareInst(fHslider7, "style", "knob")
	AddHorizontalSlider("vibratoFreq", fHslider7, 6.0f, 1.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider6, "4", "")
	AddMetaDeclareInst(fHslider6, "style", "knob")
	AddHorizontalSlider("vibratoGain", fHslider6, 0.5f, 0.0f, 1.0f, 0.00999999978f)
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
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst(static, float, ftbl0mydspSIG0[65536])
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
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, int, iVec3[2])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec17[3])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec21[3])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fRec25[3])
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec29[3])
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

======= Static Init ==========

BlockInst 
	DeclareVarInst(stack, mydspSIG0, sig0, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(stack, sig0), LoadVarInst(kFunArgs, samplingFreq)))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(stack, sig0), Int32(65536), LoadVarInst(static, ftbl0mydspSIG0)))
	EndBlock
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(stack, sig0)))
	EndBlock

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, FunCallInst("expf", BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst1))))
	StoreVarInst(struct, fConst6, BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.90000000000000002f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(10.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(6.0f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec3[LoadVarInst(loop, l8)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(3))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(3))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(3))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(3))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(3))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 34
Store = 0
Binop = 23
Numbers = 25
Declare = 27
Cast = 11
Select = 0
Loop = 0
Funcall = 4

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider3))))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(25.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow1), CastInst("float", LoadVarInst(struct, fHslider2))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2)))))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("==", LoadVarInst(stack, fSlow1), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fHslider5)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(0.100000001f), CastInst("float", LoadVarInst(struct, fHslider6))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", LoadVarInst(struct, fConst3), CastInst("float", LoadVarInst(struct, fHslider7))))
	DeclareVarInst(stack, "float", fSlow9, FunCallInst("sinf", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("cosf", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider8))))
	DeclareVarInst(stack, "float", fSlow13, CastInst("float", LoadVarInst(struct, fHslider9)))
	DeclareVarInst(stack, "int", iSlow14, Select2Inst(BinopInst("==", LoadVarInst(stack, fSlow13), Float(0.0f)) Int32(1) Select2Inst(BinopInst("==", LoadVarInst(stack, fSlow13), Float(3.0f)) Int32(1) Int32(0))))
	DeclareVarInst(stack, "int", iSlow15, BinopInst("*", Int32(5), LoadVarInst(stack, iSlow14)))
	DeclareVarInst(stack, "int", iSlow16, BinopInst(">=", LoadVarInst(stack, iSlow14), Int32(1)))
	DeclareVarInst(stack, "float", fSlow17, Select2Inst(LoadVarInst(stack, iSlow16) Float(174.610001f) Float(82.4100037f)))
	DeclareVarInst(stack, "float", fSlow18, Select2Inst(LoadVarInst(stack, iSlow16) Float(1046.5f) Float(523.25f)))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("-", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("*", Float(5.0f), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow21, BinopInst("*", Float(5.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow13))))
	DeclareVarInst(stack, "int", iSlow22, BinopInst("==", LoadVarInst(stack, iSlow14), Int32(0)))
	DeclareVarInst(stack, "int", iSlow23, BinopInst("!=", LoadVarInst(stack, fSlow13), Float(2.0f)))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", Float(2.0f), LoadVarInst(stack, fSlow4)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 1377
Store = 74
Binop = 908
Numbers = 1111
Declare = 170
Cast = 17
Select = 0
Loop = 1
Funcall = 16

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow1))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec0[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow5)))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), CastInst("float", LoadVarInst(stack, iTemp0)))), BinopInst("*", LoadVarInst(stack, fSlow6), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0)))))))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec4[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp1, BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec4[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp1))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec4[Int32(0)])), Float(1.0f))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(stack, fTemp2)))
		StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp3))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fVec2[Int32(1)]))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp4), FunCallInst("floorf", LoadVarInst(stack, fTemp4))))
		DeclareVarInst(stack, "int", iTemp5, BinopInst("<", BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec2[Int32(1)])), Float(0.0f)))
		StoreVarInst(struct, iVec3[Int32(0)], LoadVarInst(stack, iTemp5))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow12), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec7[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), CastInst("float", LoadVarInst(stack, iSlow15))))
		DeclareVarInst(stack, "int", iTemp7, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(5.0f)))
		DeclareVarInst(stack, "int", iTemp8, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(3.0f)))
		DeclareVarInst(stack, "int", iTemp9, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(2.0f)))
		DeclareVarInst(stack, "int", iTemp10, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(1.0f)))
		DeclareVarInst(stack, "int", iTemp11, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(4.0f)))
		DeclareVarInst(stack, "int", iTemp12, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(8.0f)))
		DeclareVarInst(stack, "int", iTemp13, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(7.0f)))
		DeclareVarInst(stack, "int", iTemp14, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(6.0f)))
		DeclareVarInst(stack, "float", fTemp15, Select2Inst(LoadVarInst(stack, iTemp7) Select2Inst(LoadVarInst(stack, iTemp12) Float(2.0f) Select2Inst(LoadVarInst(stack, iTemp13) Float(3.0f) Select2Inst(LoadVarInst(stack, iTemp14) Float(3.0f) Float(2.0f)))) Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Float(1.5f) Float(1.0f)) Select2Inst(LoadVarInst(stack, iTemp9) Float(1.25f) Select2Inst(LoadVarInst(stack, iTemp10) Float(1.25f) Float(1.0f))))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec8[Int32(1)]))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec8[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp1))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("*", LoadVarInst(stack, fSlow4), BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec8[Int32(0)])), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("+", LoadVarInst(stack, fTemp15), BinopInst("*", BinopInst("-", Select2Inst(LoadVarInst(stack, iTemp7) Select2Inst(LoadVarInst(stack, iTemp12) Float(12.0f) Select2Inst(LoadVarInst(stack, iTemp13) Float(12.0f) Select2Inst(LoadVarInst(stack, iTemp14) Float(12.0f) Float(15.0f)))) Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Float(4.0f) Float(10.0f)) Select2Inst(LoadVarInst(stack, iTemp9) Float(2.5f) Select2Inst(LoadVarInst(stack, iTemp10) Float(2.5f) Float(10.0f))))), LoadVarInst(stack, fTemp15)), Select2Inst(BinopInst("<=", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fSlow17)) Float(0.0f) Select2Inst(BinopInst(">=", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fSlow18)) Float(1.0f) BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fSlow17)), LoadVarInst(stack, fSlow19)))))))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("+", LoadVarInst(stack, fSlow20), LoadVarInst(struct, fRec7[Int32(0)])))
		DeclareVarInst(stack, "int", iTemp19, BinopInst("<", LoadVarInst(stack, fTemp18), Float(23.0f)))
		DeclareVarInst(stack, "int", iTemp20, BinopInst("<", LoadVarInst(stack, fTemp18), Float(24.0f)))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-23.0f))))
		DeclareVarInst(stack, "int", iTemp22, BinopInst("<", LoadVarInst(stack, fTemp18), Float(22.0f)))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-22.0f))))
		DeclareVarInst(stack, "int", iTemp24, BinopInst("<", LoadVarInst(stack, fTemp18), Float(21.0f)))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-21.0f))))
		DeclareVarInst(stack, "int", iTemp26, BinopInst("<", LoadVarInst(stack, fTemp18), Float(20.0f)))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-20.0f))))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp27)))
		DeclareVarInst(stack, "int", iTemp29, BinopInst("<", LoadVarInst(stack, fTemp18), Float(19.0f)))
		DeclareVarInst(stack, "int", iTemp30, BinopInst("<", LoadVarInst(stack, fTemp18), Float(18.0f)))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-18.0f))))
		DeclareVarInst(stack, "int", iTemp32, BinopInst("<", LoadVarInst(stack, fTemp18), Float(17.0f)))
		DeclareVarInst(stack, "float", fTemp33, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-17.0f))))
		DeclareVarInst(stack, "int", iTemp34, BinopInst("<", LoadVarInst(stack, fTemp18), Float(16.0f)))
		DeclareVarInst(stack, "int", iTemp35, BinopInst("<", LoadVarInst(stack, fTemp18), Float(15.0f)))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-15.0f))))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp36)))
		DeclareVarInst(stack, "int", iTemp38, BinopInst("<", LoadVarInst(stack, fTemp18), Float(14.0f)))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-14.0f))))
		DeclareVarInst(stack, "int", iTemp40, BinopInst("<", LoadVarInst(stack, fTemp18), Float(13.0f)))
		DeclareVarInst(stack, "int", iTemp41, BinopInst("<", LoadVarInst(stack, fTemp18), Float(12.0f)))
		DeclareVarInst(stack, "int", iTemp42, BinopInst("<", LoadVarInst(stack, fTemp18), Float(11.0f)))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-11.0f))))
		DeclareVarInst(stack, "int", iTemp44, BinopInst("<", LoadVarInst(stack, fTemp18), Float(10.0f)))
		DeclareVarInst(stack, "float", fTemp45, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-10.0f))))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp45)))
		DeclareVarInst(stack, "int", iTemp47, BinopInst("<", LoadVarInst(stack, fTemp18), Float(9.0f)))
		DeclareVarInst(stack, "float", fTemp48, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-9.0f))))
		DeclareVarInst(stack, "int", iTemp49, BinopInst("<", LoadVarInst(stack, fTemp18), Float(8.0f)))
		DeclareVarInst(stack, "int", iTemp50, BinopInst("<", LoadVarInst(stack, fTemp18), Float(7.0f)))
		DeclareVarInst(stack, "float", fTemp51, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-7.0f))))
		DeclareVarInst(stack, "int", iTemp52, BinopInst("<", LoadVarInst(stack, fTemp18), Float(6.0f)))
		DeclareVarInst(stack, "float", fTemp53, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-6.0f))))
		DeclareVarInst(stack, "int", iTemp54, BinopInst("<", LoadVarInst(stack, fTemp18), Float(5.0f)))
		DeclareVarInst(stack, "float", fTemp55, BinopInst("-", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(stack, fSlow21)))
		DeclareVarInst(stack, "int", iTemp56, BinopInst("<", LoadVarInst(stack, fTemp18), Float(4.0f)))
		DeclareVarInst(stack, "float", fTemp57, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-4.0f))))
		DeclareVarInst(stack, "float", fTemp58, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp57)))
		DeclareVarInst(stack, "int", iTemp59, BinopInst("<", LoadVarInst(stack, fTemp18), Float(3.0f)))
		DeclareVarInst(stack, "float", fTemp60, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-3.0f))))
		DeclareVarInst(stack, "float", fTemp61, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp60)))
		DeclareVarInst(stack, "int", iTemp62, BinopInst("<", LoadVarInst(stack, fTemp18), Float(2.0f)))
		DeclareVarInst(stack, "float", fTemp63, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-2.0f))))
		DeclareVarInst(stack, "float", fTemp64, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp63)))
		DeclareVarInst(stack, "int", iTemp65, BinopInst("<", LoadVarInst(stack, fTemp18), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp66, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-1.0f))))
		DeclareVarInst(stack, "int", iTemp67, BinopInst("<", LoadVarInst(stack, fTemp18), Float(0.0f)))
		DeclareVarInst(stack, "float", fTemp68, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp18)))
		DeclareVarInst(stack, "float", fTemp69, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(80.0f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp68)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp62) BinopInst("-", Float(60.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp66))) Float(50.0f))) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("+", LoadVarInst(stack, fTemp64), Float(50.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(70.0f), LoadVarInst(stack, fTemp61)) Float(50.0f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", LoadVarInst(stack, fTemp58), Float(50.0f)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp55))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("+", BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp53)), Float(40.0f)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp51))) Float(40.0f))) Float(40.0f)) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("*", Float(40.0f), BinopInst("+", LoadVarInst(stack, fTemp48), Float(1.0f))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp46)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp41) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp43))) Float(40.0f))) Float(40.0f)) Float(40.0f)) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("*", Float(40.0f), BinopInst("+", LoadVarInst(stack, fTemp39), Float(1.0f))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp37)) Float(60.0f))) Float(60.0f)) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp33))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp31)), Float(40.0f)) Float(50.0f))) Float(50.0f)) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("+", LoadVarInst(stack, fTemp28), Float(50.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp25))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp23)), Float(40.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp21))) Float(40.0f))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp69)))))
		DeclareVarInst(stack, "float", fTemp70, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec6[Int32(0)])))))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp69))))
		DeclareVarInst(stack, "float", fTemp71, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec10[Int32(0)])))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(struct, iVec3[Int32(1)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("+", LoadVarInst(stack, fTemp70), LoadVarInst(stack, fTemp71)))), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp70), LoadVarInst(stack, fTemp71)), LoadVarInst(struct, fRec1[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp72, BinopInst("+", BinopInst("*", Float(0.000839999993f), BinopInst("-", Float(1000.0f), LoadVarInst(stack, fTemp16))), Float(0.800000012f)))
		DeclareVarInst(stack, "float", fTemp73, BinopInst("+", BinopInst("*", Float(0.00366666657f), BinopInst("-", Float(400.0f), LoadVarInst(stack, fTemp16))), Float(3.0f)))
		DeclareVarInst(stack, "int", iTemp74, BinopInst("-", Int32(1), BinopInst(">", LoadVarInst(stack, iTemp5), Int32(0))))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow12), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec13[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp75, BinopInst("+", LoadVarInst(stack, fSlow20), LoadVarInst(struct, fRec13[Int32(0)])))
		DeclareVarInst(stack, "int", iTemp76, BinopInst("<", LoadVarInst(stack, fTemp75), Float(23.0f)))
		DeclareVarInst(stack, "int", iTemp77, BinopInst("<", LoadVarInst(stack, fTemp75), Float(24.0f)))
		DeclareVarInst(stack, "float", fTemp78, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-23.0f))))
		DeclareVarInst(stack, "int", iTemp79, BinopInst("<", LoadVarInst(stack, fTemp75), Float(22.0f)))
		DeclareVarInst(stack, "float", fTemp80, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-22.0f))))
		DeclareVarInst(stack, "int", iTemp81, BinopInst("<", LoadVarInst(stack, fTemp75), Float(21.0f)))
		DeclareVarInst(stack, "float", fTemp82, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-21.0f))))
		DeclareVarInst(stack, "int", iTemp83, BinopInst("<", LoadVarInst(stack, fTemp75), Float(20.0f)))
		DeclareVarInst(stack, "float", fTemp84, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-20.0f))))
		DeclareVarInst(stack, "int", iTemp85, BinopInst("<", LoadVarInst(stack, fTemp75), Float(19.0f)))
		DeclareVarInst(stack, "float", fTemp86, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-19.0f))))
		DeclareVarInst(stack, "int", iTemp87, BinopInst("<", LoadVarInst(stack, fTemp75), Float(18.0f)))
		DeclareVarInst(stack, "float", fTemp88, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-18.0f))))
		DeclareVarInst(stack, "int", iTemp89, BinopInst("<", LoadVarInst(stack, fTemp75), Float(17.0f)))
		DeclareVarInst(stack, "float", fTemp90, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-17.0f))))
		DeclareVarInst(stack, "int", iTemp91, BinopInst("<", LoadVarInst(stack, fTemp75), Float(16.0f)))
		DeclareVarInst(stack, "float", fTemp92, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-16.0f))))
		DeclareVarInst(stack, "int", iTemp93, BinopInst("<", LoadVarInst(stack, fTemp75), Float(15.0f)))
		DeclareVarInst(stack, "float", fTemp94, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-15.0f))))
		DeclareVarInst(stack, "int", iTemp95, BinopInst("<", LoadVarInst(stack, fTemp75), Float(14.0f)))
		DeclareVarInst(stack, "float", fTemp96, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-14.0f))))
		DeclareVarInst(stack, "int", iTemp97, BinopInst("<", LoadVarInst(stack, fTemp75), Float(13.0f)))
		DeclareVarInst(stack, "float", fTemp98, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-13.0f))))
		DeclareVarInst(stack, "int", iTemp99, BinopInst("<", LoadVarInst(stack, fTemp75), Float(12.0f)))
		DeclareVarInst(stack, "float", fTemp100, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-12.0f))))
		DeclareVarInst(stack, "int", iTemp101, BinopInst("<", LoadVarInst(stack, fTemp75), Float(11.0f)))
		DeclareVarInst(stack, "float", fTemp102, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-11.0f))))
		DeclareVarInst(stack, "int", iTemp103, BinopInst("<", LoadVarInst(stack, fTemp75), Float(10.0f)))
		DeclareVarInst(stack, "float", fTemp104, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-10.0f))))
		DeclareVarInst(stack, "int", iTemp105, BinopInst("<", LoadVarInst(stack, fTemp75), Float(9.0f)))
		DeclareVarInst(stack, "float", fTemp106, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-9.0f))))
		DeclareVarInst(stack, "int", iTemp107, BinopInst("<", LoadVarInst(stack, fTemp75), Float(8.0f)))
		DeclareVarInst(stack, "float", fTemp108, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-8.0f))))
		DeclareVarInst(stack, "float", fTemp109, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp108)))
		DeclareVarInst(stack, "int", iTemp110, BinopInst("<", LoadVarInst(stack, fTemp75), Float(7.0f)))
		DeclareVarInst(stack, "float", fTemp111, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-7.0f))))
		DeclareVarInst(stack, "int", iTemp112, BinopInst("<", LoadVarInst(stack, fTemp75), Float(6.0f)))
		DeclareVarInst(stack, "float", fTemp113, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-6.0f))))
		DeclareVarInst(stack, "int", iTemp114, BinopInst("<", LoadVarInst(stack, fTemp75), Float(5.0f)))
		DeclareVarInst(stack, "float", fTemp115, BinopInst("-", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(stack, fSlow21)))
		DeclareVarInst(stack, "int", iTemp116, BinopInst("<", LoadVarInst(stack, fTemp75), Float(4.0f)))
		DeclareVarInst(stack, "float", fTemp117, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-4.0f))))
		DeclareVarInst(stack, "int", iTemp118, BinopInst("<", LoadVarInst(stack, fTemp75), Float(3.0f)))
		DeclareVarInst(stack, "float", fTemp119, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-3.0f))))
		DeclareVarInst(stack, "int", iTemp120, BinopInst("<", LoadVarInst(stack, fTemp75), Float(2.0f)))
		DeclareVarInst(stack, "float", fTemp121, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-2.0f))))
		DeclareVarInst(stack, "int", iTemp122, BinopInst("<", LoadVarInst(stack, fTemp75), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp123, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-1.0f))))
		DeclareVarInst(stack, "int", iTemp124, BinopInst("<", LoadVarInst(stack, fTemp75), Float(0.0f)))
		DeclareVarInst(stack, "float", fTemp125, Select2Inst(LoadVarInst(stack, iTemp76) Select2Inst(LoadVarInst(stack, iTemp79) Select2Inst(LoadVarInst(stack, iTemp81) Select2Inst(LoadVarInst(stack, iTemp83) Select2Inst(LoadVarInst(stack, iTemp85) Select2Inst(LoadVarInst(stack, iTemp87) Select2Inst(LoadVarInst(stack, iTemp89) Select2Inst(LoadVarInst(stack, iTemp91) Select2Inst(LoadVarInst(stack, iTemp93) Select2Inst(LoadVarInst(stack, iTemp95) Select2Inst(LoadVarInst(stack, iTemp97) Select2Inst(LoadVarInst(stack, iTemp99) Select2Inst(LoadVarInst(stack, iTemp101) Select2Inst(LoadVarInst(stack, iTemp103) Select2Inst(LoadVarInst(stack, iTemp105) Select2Inst(LoadVarInst(stack, iTemp107) Select2Inst(LoadVarInst(stack, iTemp110) Select2Inst(LoadVarInst(stack, iTemp112) Select2Inst(LoadVarInst(stack, iTemp114) Select2Inst(LoadVarInst(stack, iTemp116) Select2Inst(LoadVarInst(stack, iTemp118) Select2Inst(LoadVarInst(stack, iTemp120) Select2Inst(LoadVarInst(stack, iTemp122) Select2Inst(LoadVarInst(stack, iTemp124) Float(800.0f) Select2Inst(LoadVarInst(stack, iTemp122) BinopInst("-", Float(800.0f), BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp75))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp120) BinopInst("-", Float(400.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp123))) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp118) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp121)), Float(350.0f)) Float(450.0f))) Select2Inst(LoadVarInst(stack, iTemp116) BinopInst("-", Float(450.0f), BinopInst("*", Float(125.0f), LoadVarInst(stack, fTemp119))) Float(325.0f))) Select2Inst(LoadVarInst(stack, iTemp114) BinopInst("+", BinopInst("*", Float(275.0f), LoadVarInst(stack, fTemp117)), Float(325.0f)) Float(600.0f))) Select2Inst(LoadVarInst(stack, iTemp112) BinopInst("-", Float(600.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp115))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp110) BinopInst("-", Float(400.0f), BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp113))) Float(250.0f))) Select2Inst(LoadVarInst(stack, iTemp107) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp111)), Float(250.0f)) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp105) BinopInst("-", Float(400.0f), LoadVarInst(stack, fTemp109)) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp103) BinopInst("+", BinopInst("*", Float(310.0f), LoadVarInst(stack, fTemp106)), Float(350.0f)) Float(660.0f))) Select2Inst(LoadVarInst(stack, iTemp101) BinopInst("-", Float(660.0f), BinopInst("*", Float(220.0f), LoadVarInst(stack, fTemp104))) Float(440.0f))) Select2Inst(LoadVarInst(stack, iTemp99) BinopInst("-", Float(440.0f), BinopInst("*", Float(170.0f), LoadVarInst(stack, fTemp102))) Float(270.0f))) Select2Inst(LoadVarInst(stack, iTemp97) BinopInst("+", BinopInst("*", Float(160.0f), LoadVarInst(stack, fTemp100)), Float(270.0f)) Float(430.0f))) Select2Inst(LoadVarInst(stack, iTemp95) BinopInst("-", Float(430.0f), BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp98))) Float(370.0f))) Select2Inst(LoadVarInst(stack, iTemp93) BinopInst("+", BinopInst("*", Float(430.0f), LoadVarInst(stack, fTemp96)), Float(370.0f)) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp91) BinopInst("-", Float(800.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp94))) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp89) BinopInst("-", Float(350.0f), BinopInst("*", Float(80.0f), LoadVarInst(stack, fTemp92))) Float(270.0f))) Select2Inst(LoadVarInst(stack, iTemp87) BinopInst("+", BinopInst("*", Float(180.0f), LoadVarInst(stack, fTemp90)), Float(270.0f)) Float(450.0f))) Select2Inst(LoadVarInst(stack, iTemp85) BinopInst("-", Float(450.0f), BinopInst("*", Float(125.0f), LoadVarInst(stack, fTemp88))) Float(325.0f))) Select2Inst(LoadVarInst(stack, iTemp83) BinopInst("*", Float(325.0f), BinopInst("+", LoadVarInst(stack, fTemp86), Float(1.0f))) Float(650.0f))) Select2Inst(LoadVarInst(stack, iTemp81) BinopInst("-", Float(650.0f), BinopInst("*", Float(250.0f), LoadVarInst(stack, fTemp84))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp79) BinopInst("-", Float(400.0f), BinopInst("*", Float(110.0f), LoadVarInst(stack, fTemp82))) Float(290.0f))) Select2Inst(LoadVarInst(stack, iTemp76) BinopInst("+", BinopInst("*", Float(110.0f), LoadVarInst(stack, fTemp80)), Float(290.0f)) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp77) BinopInst("-", Float(400.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp78))) Float(350.0f))))
		DeclareVarInst(stack, "float", fTemp126, BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec12[Int32(1)]), CastInst("float", LoadVarInst(stack, iTemp74))), BinopInst("*", LoadVarInst(struct, fConst7), Select2Inst(BinopInst("<=", LoadVarInst(stack, fTemp125), LoadVarInst(stack, fTemp3)) LoadVarInst(stack, fTemp3) LoadVarInst(stack, fTemp125)))))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp126), FunCallInst("floorf", LoadVarInst(stack, fTemp126))))
		DeclareVarInst(stack, "float", fTemp127, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-19.0f))))
		DeclareVarInst(stack, "float", fTemp128, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-16.0f))))
		DeclareVarInst(stack, "float", fTemp129, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-13.0f))))
		DeclareVarInst(stack, "float", fTemp130, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-12.0f))))
		DeclareVarInst(stack, "float", fTemp131, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-8.0f))))
		DeclareVarInst(stack, "float", fTemp132, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(0.630957007f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("-", Float(0.630957007f), BinopInst("*", Float(0.567861021f), LoadVarInst(stack, fTemp18))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp62) BinopInst("+", BinopInst("*", Float(0.0369039997f), LoadVarInst(stack, fTemp66)), Float(0.0630960017f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("+", BinopInst("*", Float(0.254812986f), LoadVarInst(stack, fTemp63)), Float(0.100000001f)) Float(0.35481301f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.103624001f), LoadVarInst(stack, fTemp60))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp57)), Float(0.251188993f)) Float(0.446684003f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("-", Float(0.446684003f), BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp55))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.219566002f), LoadVarInst(stack, fTemp53))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("+", BinopInst("*", Float(0.250214994f), LoadVarInst(stack, fTemp51)), Float(0.0316229984f)) Float(0.281838f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(0.281838f), BinopInst("*", Float(0.181838006f), LoadVarInst(stack, fTemp131))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp48)), Float(0.100000001f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.301661015f), LoadVarInst(stack, fTemp45))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp41) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.136429995f), LoadVarInst(stack, fTemp43))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(0.253131986f), LoadVarInst(stack, fTemp130)), Float(0.0630960017f)) Float(0.316228002f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(0.316228002f), BinopInst("*", Float(0.216227993f), LoadVarInst(stack, fTemp129))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp39)), Float(0.100000001f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp36))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(0.151188999f), LoadVarInst(stack, fTemp128)), Float(0.100000001f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(0.0306490008f), LoadVarInst(stack, fTemp33)), Float(0.251188993f)) Float(0.281838f))) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("-", Float(0.281838f), BinopInst("*", Float(0.123349003f), LoadVarInst(stack, fTemp31))) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.342698008f), LoadVarInst(stack, fTemp127)), Float(0.158489004f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.301661015f), LoadVarInst(stack, fTemp27))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.0216979999f), LoadVarInst(stack, fTemp25))) Float(0.177827999f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.138400003f), LoadVarInst(stack, fTemp23)), Float(0.177827999f)) Float(0.316228002f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(0.316228002f), BinopInst("*", Float(0.216227993f), LoadVarInst(stack, fTemp21))) Float(0.100000001f))))
		DeclareVarInst(stack, "float", fTemp133, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp23)))
		DeclareVarInst(stack, "float", fTemp134, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp27)))
		DeclareVarInst(stack, "float", fTemp135, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp48)))
		DeclareVarInst(stack, "float", fTemp136, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp55)))
		DeclareVarInst(stack, "float", fTemp137, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(90.0f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp18))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp62) BinopInst("+", BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp66)), Float(80.0f)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("-", Float(100.0f), LoadVarInst(stack, fTemp64)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp61)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", LoadVarInst(stack, fTemp58), Float(60.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("+", LoadVarInst(stack, fTemp136), Float(70.0f)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp53)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp51))) Float(80.0f))) Float(80.0f)) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", LoadVarInst(stack, fTemp135), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp46)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp41) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp43)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp130))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp129))) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp39)), Float(60.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp36)), Float(90.0f)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(100.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp128))) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp33))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp31))) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp127)), Float(60.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp134)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp25)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp133)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp21))) Float(60.0f))))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp137))))
		DeclareVarInst(stack, "float", fTemp138, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec14[Int32(0)])))))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp137)))))
		DeclareVarInst(stack, "float", fTemp139, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec15[Int32(0)])))))
		DeclareVarInst(stack, "float", fTemp140, Select2Inst(LoadVarInst(stack, iTemp76) Select2Inst(LoadVarInst(stack, iTemp79) Select2Inst(LoadVarInst(stack, iTemp81) Select2Inst(LoadVarInst(stack, iTemp83) Select2Inst(LoadVarInst(stack, iTemp85) Select2Inst(LoadVarInst(stack, iTemp87) Select2Inst(LoadVarInst(stack, iTemp89) Select2Inst(LoadVarInst(stack, iTemp91) Select2Inst(LoadVarInst(stack, iTemp93) Select2Inst(LoadVarInst(stack, iTemp95) Select2Inst(LoadVarInst(stack, iTemp97) Select2Inst(LoadVarInst(stack, iTemp99) Select2Inst(LoadVarInst(stack, iTemp101) Select2Inst(LoadVarInst(stack, iTemp103) Select2Inst(LoadVarInst(stack, iTemp105) Select2Inst(LoadVarInst(stack, iTemp107) Select2Inst(LoadVarInst(stack, iTemp110) Select2Inst(LoadVarInst(stack, iTemp112) Select2Inst(LoadVarInst(stack, iTemp114) Select2Inst(LoadVarInst(stack, iTemp116) Select2Inst(LoadVarInst(stack, iTemp118) Select2Inst(LoadVarInst(stack, iTemp120) Select2Inst(LoadVarInst(stack, iTemp122) Select2Inst(LoadVarInst(stack, iTemp124) Float(1150.0f) Select2Inst(LoadVarInst(stack, iTemp122) BinopInst("+", BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp75)), Float(1150.0f)) Float(1600.0f))) Select2Inst(LoadVarInst(stack, iTemp120) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp123)), Float(1600.0f)) Float(1700.0f))) Select2Inst(LoadVarInst(stack, iTemp118) BinopInst("-", Float(1700.0f), BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp121))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp116) BinopInst("-", Float(800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp119))) Float(700.0f))) Select2Inst(LoadVarInst(stack, iTemp114) BinopInst("+", BinopInst("*", Float(340.0f), LoadVarInst(stack, fTemp117)), Float(700.0f)) Float(1040.0f))) Select2Inst(LoadVarInst(stack, iTemp112) BinopInst("+", BinopInst("*", Float(580.0f), LoadVarInst(stack, fTemp115)), Float(1040.0f)) Float(1620.0f))) Select2Inst(LoadVarInst(stack, iTemp110) BinopInst("+", BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp113)), Float(1620.0f)) Float(1750.0f))) Select2Inst(LoadVarInst(stack, iTemp107) BinopInst("-", Float(1750.0f), BinopInst("*", Float(1000.0f), LoadVarInst(stack, fTemp111))) Float(750.0f))) Select2Inst(LoadVarInst(stack, iTemp105) BinopInst("-", Float(750.0f), BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp108))) Float(600.0f))) Select2Inst(LoadVarInst(stack, iTemp103) BinopInst("+", BinopInst("*", Float(520.0f), LoadVarInst(stack, fTemp106)), Float(600.0f)) Float(1120.0f))) Select2Inst(LoadVarInst(stack, iTemp101) BinopInst("+", BinopInst("*", Float(680.0f), LoadVarInst(stack, fTemp104)), Float(1120.0f)) Float(1800.0f))) Select2Inst(LoadVarInst(stack, iTemp99) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp102)), Float(1800.0f)) Float(1850.0f))) Select2Inst(LoadVarInst(stack, iTemp97) BinopInst("-", Float(1850.0f), BinopInst("*", Float(1030.0f), LoadVarInst(stack, fTemp100))) Float(820.0f))) Select2Inst(LoadVarInst(stack, iTemp95) BinopInst("-", Float(820.0f), BinopInst("*", Float(190.0f), LoadVarInst(stack, fTemp98))) Float(630.0f))) Select2Inst(LoadVarInst(stack, iTemp93) BinopInst("+", BinopInst("*", Float(520.0f), LoadVarInst(stack, fTemp96)), Float(630.0f)) Float(1150.0f))) Select2Inst(LoadVarInst(stack, iTemp91) BinopInst("+", BinopInst("*", Float(850.0f), LoadVarInst(stack, fTemp94)), Float(1150.0f)) Float(2000.0f))) Select2Inst(LoadVarInst(stack, iTemp89) BinopInst("+", BinopInst("*", Float(140.0f), LoadVarInst(stack, fTemp92)), Float(2000.0f)) Float(2140.0f))) Select2Inst(LoadVarInst(stack, iTemp87) BinopInst("-", Float(2140.0f), BinopInst("*", Float(1340.0f), LoadVarInst(stack, fTemp90))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp85) BinopInst("-", Float(800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp88))) Float(700.0f))) Select2Inst(LoadVarInst(stack, iTemp83) BinopInst("+", BinopInst("*", Float(380.0f), LoadVarInst(stack, fTemp86)), Float(700.0f)) Float(1080.0f))) Select2Inst(LoadVarInst(stack, iTemp81) BinopInst("+", BinopInst("*", Float(620.0f), LoadVarInst(stack, fTemp84)), Float(1080.0f)) Float(1700.0f))) Select2Inst(LoadVarInst(stack, iTemp79) BinopInst("+", BinopInst("*", Float(170.0f), LoadVarInst(stack, fTemp82)), Float(1700.0f)) Float(1870.0f))) Select2Inst(LoadVarInst(stack, iTemp76) BinopInst("-", Float(1870.0f), BinopInst("*", Float(1070.0f), LoadVarInst(stack, fTemp80))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp77) BinopInst("-", Float(800.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp78))) Float(600.0f))))
		DeclareVarInst(stack, "float", fTemp141, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(stack, fTemp2)), Float(30.0f)))
		DeclareVarInst(stack, "float", fTemp142, BinopInst("+", BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp74)), LoadVarInst(struct, fRec16[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), Select2Inst(LoadVarInst(stack, iSlow23) Select2Inst(BinopInst("&", BinopInst(">=", LoadVarInst(stack, fTemp140), Float(1300.0f)), BinopInst(">=", LoadVarInst(stack, fTemp3), Float(200.0f))) BinopInst("-", LoadVarInst(stack, fTemp140), BinopInst("*", Float(0.000952380942f), BinopInst("*", BinopInst("+", LoadVarInst(stack, fTemp3), Float(-200.0f)), BinopInst("+", LoadVarInst(stack, fTemp140), Float(-1300.0f))))) Select2Inst(BinopInst("<=", LoadVarInst(stack, fTemp140), LoadVarInst(stack, fTemp141)) LoadVarInst(stack, fTemp141) LoadVarInst(stack, fTemp140))) LoadVarInst(stack, fTemp140)))))
		StoreVarInst(struct, fRec16[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp142), FunCallInst("floorf", LoadVarInst(stack, fTemp142))))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(struct, iVec3[Int32(1)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec17[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("+", LoadVarInst(stack, fTemp139), LoadVarInst(stack, fTemp138)))), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp139), LoadVarInst(stack, fTemp138)), LoadVarInst(struct, fRec17[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp143, Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(0.0293140002f), LoadVarInst(stack, fTemp33)), Float(0.0501190014f)) Float(0.0794330016f)))
		DeclareVarInst(stack, "float", fTemp144, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(0.100000001f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp18))) Float(0.0316229984f))) Float(0.0316229984f)) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("+", BinopInst("*", Float(0.126865998f), LoadVarInst(stack, fTemp63)), Float(0.0316229984f)) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(0.158489004f), BinopInst("*", Float(0.126865998f), LoadVarInst(stack, fTemp60))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", BinopInst("*", Float(0.323190004f), LoadVarInst(stack, fTemp57)), Float(0.0316229984f)) Float(0.35481301f))) Float(0.35481301f)) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.196324006f), LoadVarInst(stack, fTemp53))) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.158489004f), BinopInst("*", Float(0.0693639964f), LoadVarInst(stack, fTemp51))) Float(0.0891249999f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(0.0891249999f), BinopInst("*", Float(0.0640060008f), LoadVarInst(stack, fTemp131))) Float(0.0251189992f))) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", BinopInst("*", Float(0.0456760004f), LoadVarInst(stack, fTemp48)), Float(0.0251189992f)) Float(0.0707949996f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("+", BinopInst("*", Float(0.0550980009f), LoadVarInst(stack, fTemp45)), Float(0.0707949996f)) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp41) BinopInst("-", Float(0.125892997f), BinopInst("*", Float(0.0627970025f), LoadVarInst(stack, fTemp43))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(0.0630960017f), BinopInst("*", Float(0.0129770003f), LoadVarInst(stack, fTemp130))) Float(0.0501190014f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("+", BinopInst("*", Float(0.020676f), LoadVarInst(stack, fTemp129)), Float(0.0501190014f)) Float(0.0707949996f))) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("-", Float(0.0707949996f), BinopInst("*", Float(0.0456760004f), LoadVarInst(stack, fTemp39))) Float(0.0251189992f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(0.152709007f), LoadVarInst(stack, fTemp36)), Float(0.0251189992f)) Float(0.177827999f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(0.177827999f), BinopInst("*", Float(0.127709001f), LoadVarInst(stack, fTemp128))) Float(0.0501190014f))) LoadVarInst(stack, fTemp143)) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0616500005f), LoadVarInst(stack, fTemp31))) Float(0.0177829992f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.428900987f), LoadVarInst(stack, fTemp127)), Float(0.0177829992f)) Float(0.446684003f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(0.446684003f), BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp27))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.125295997f), LoadVarInst(stack, fTemp25))) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.125295997f), LoadVarInst(stack, fTemp23)), Float(0.125892997f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.109935001f), LoadVarInst(stack, fTemp21))) Float(0.141253993f))))
		DeclareVarInst(stack, "float", fTemp145, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp127)))
		DeclareVarInst(stack, "float", fTemp146, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp39)))
		DeclareVarInst(stack, "float", fTemp147, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp45)))
		DeclareVarInst(stack, "float", fTemp148, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp48)))
		DeclareVarInst(stack, "float", fTemp149, BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp57)))
		DeclareVarInst(stack, "float", fTemp150, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Float(120.0f) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp64)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("+", BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp60)), Float(100.0f)) Float(170.0f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("-", Float(170.0f), LoadVarInst(stack, fTemp149)) Float(110.0f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("-", Float(110.0f), LoadVarInst(stack, fTemp136)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", LoadVarInst(stack, fTemp148), Float(100.0f)) Float(120.0f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp147)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", LoadVarInst(stack, fTemp146), Float(100.0f)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(120.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp128))) Float(100.0f))) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("+", BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp31)), Float(100.0f)) Float(170.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("-", Float(170.0f), LoadVarInst(stack, fTemp145)) Float(120.0f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp28)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)))
		StoreVarInst(struct, fRec18[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp150))))
		DeclareVarInst(stack, "float", fTemp151, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec18[Int32(0)])))))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp150)))))
		DeclareVarInst(stack, "float", fTemp152, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec19[Int32(0)])))))
		DeclareVarInst(stack, "float", fTemp153, BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp78)))
		DeclareVarInst(stack, "float", fTemp154, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp104)))
		DeclareVarInst(stack, "float", fTemp155, BinopInst("+", BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp74)), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), Select2Inst(LoadVarInst(stack, iTemp76) Select2Inst(LoadVarInst(stack, iTemp79) Select2Inst(LoadVarInst(stack, iTemp81) Select2Inst(LoadVarInst(stack, iTemp83) Select2Inst(LoadVarInst(stack, iTemp85) Select2Inst(LoadVarInst(stack, iTemp87) Select2Inst(LoadVarInst(stack, iTemp89) Select2Inst(LoadVarInst(stack, iTemp91) Select2Inst(LoadVarInst(stack, iTemp93) Select2Inst(LoadVarInst(stack, iTemp95) Select2Inst(LoadVarInst(stack, iTemp97) Select2Inst(LoadVarInst(stack, iTemp99) Select2Inst(LoadVarInst(stack, iTemp101) Select2Inst(LoadVarInst(stack, iTemp103) Select2Inst(LoadVarInst(stack, iTemp105) Select2Inst(LoadVarInst(stack, iTemp107) Select2Inst(LoadVarInst(stack, iTemp110) Select2Inst(LoadVarInst(stack, iTemp112) Select2Inst(LoadVarInst(stack, iTemp114) Select2Inst(LoadVarInst(stack, iTemp116) Select2Inst(LoadVarInst(stack, iTemp118) Select2Inst(LoadVarInst(stack, iTemp120) Select2Inst(LoadVarInst(stack, iTemp122) Select2Inst(LoadVarInst(stack, iTemp124) Float(2800.0f) Select2Inst(LoadVarInst(stack, iTemp122) BinopInst("-", Float(2800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp75))) Float(2700.0f))) Float(2700.0f)) Select2Inst(LoadVarInst(stack, iTemp118) BinopInst("+", BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp121)), Float(2700.0f)) Float(2830.0f))) Select2Inst(LoadVarInst(stack, iTemp116) BinopInst("-", Float(2830.0f), BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp119))) Float(2530.0f))) Select2Inst(LoadVarInst(stack, iTemp114) BinopInst("-", Float(2530.0f), BinopInst("*", Float(280.0f), LoadVarInst(stack, fTemp117))) Float(2250.0f))) Select2Inst(LoadVarInst(stack, iTemp112) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp115)), Float(2250.0f)) Float(2400.0f))) Select2Inst(LoadVarInst(stack, iTemp110) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp113)), Float(2400.0f)) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp107) BinopInst("-", Float(2600.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp111))) Float(2400.0f))) Float(2400.0f)) Select2Inst(LoadVarInst(stack, iTemp103) BinopInst("+", BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp106)), Float(2400.0f)) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp101) BinopInst("-", Float(2750.0f), LoadVarInst(stack, fTemp154)) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp99) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp102)), Float(2700.0f)) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp97) BinopInst("-", Float(2900.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp100))) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp95) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp98)), Float(2700.0f)) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp93) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp96)), Float(2750.0f)) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp91) BinopInst("-", Float(2900.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp94))) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp89) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp92)), Float(2800.0f)) Float(2950.0f))) Select2Inst(LoadVarInst(stack, iTemp87) BinopInst("-", Float(2950.0f), BinopInst("*", Float(120.0f), LoadVarInst(stack, fTemp90))) Float(2830.0f))) Select2Inst(LoadVarInst(stack, iTemp85) BinopInst("-", Float(2830.0f), BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp88))) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp83) BinopInst("-", Float(2700.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp86))) Float(2650.0f))) Select2Inst(LoadVarInst(stack, iTemp81) BinopInst("-", Float(2650.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp84))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp79) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp82)), Float(2600.0f)) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp76) BinopInst("-", Float(2800.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp80))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp77) BinopInst("+", LoadVarInst(stack, fTemp153), Float(2600.0f)) Float(2700.0f))))))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp155), FunCallInst("floorf", LoadVarInst(stack, fTemp155))))
		StoreVarInst(struct, fRec21[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(struct, iVec3[Int32(1)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec21[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("+", LoadVarInst(stack, fTemp152), LoadVarInst(stack, fTemp151)))), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp152), LoadVarInst(stack, fTemp151)), LoadVarInst(struct, fRec21[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp156, Select2Inst(LoadVarInst(stack, iTemp41) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0841509998f), LoadVarInst(stack, fTemp43))) Float(0.0158489998f)))
		DeclareVarInst(stack, "float", fTemp157, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(0.0158489998f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("+", BinopInst("*", Float(0.00193400006f), LoadVarInst(stack, fTemp18)), Float(0.0158489998f)) Float(0.0177829992f))) Select2Inst(LoadVarInst(stack, iTemp62) BinopInst("-", Float(0.0177829992f), BinopInst("*", Float(0.00193400006f), LoadVarInst(stack, fTemp66))) Float(0.0158489998f))) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("+", BinopInst("*", Float(0.0239620004f), LoadVarInst(stack, fTemp63)), Float(0.0158489998f)) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(0.0398110002f), BinopInst("*", Float(0.0298110005f), LoadVarInst(stack, fTemp60))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", BinopInst("*", Float(0.344812989f), LoadVarInst(stack, fTemp57)), Float(0.00999999978f)) Float(0.35481301f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.103624001f), LoadVarInst(stack, fTemp55))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.171755999f), LoadVarInst(stack, fTemp53))) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("+", BinopInst("*", Float(0.0205669999f), LoadVarInst(stack, fTemp51)), Float(0.0794330016f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0601890013f), LoadVarInst(stack, fTemp131))) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", BinopInst("*", Float(0.0232849997f), LoadVarInst(stack, fTemp48)), Float(0.0398110002f)) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("+", BinopInst("*", Float(0.0369039997f), LoadVarInst(stack, fTemp45)), Float(0.0630960017f)) Float(0.100000001f))) LoadVarInst(stack, fTemp156)) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(0.0635839999f), LoadVarInst(stack, fTemp130)), Float(0.0158489998f)) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0478099994f), LoadVarInst(stack, fTemp129))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp39)), Float(0.0316229984f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0900000036f), LoadVarInst(stack, fTemp36))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(0.0401189998f), LoadVarInst(stack, fTemp128)), Float(0.00999999978f)) Float(0.0501190014f))) LoadVarInst(stack, fTemp143)) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0694330037f), LoadVarInst(stack, fTemp31))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.388107002f), LoadVarInst(stack, fTemp127)), Float(0.00999999978f)) Float(0.398106992f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(0.398106992f), BinopInst("*", Float(0.198580995f), LoadVarInst(stack, fTemp27))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.099526003f), LoadVarInst(stack, fTemp25))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.151188999f), LoadVarInst(stack, fTemp23)), Float(0.100000001f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.0516630001f), LoadVarInst(stack, fTemp21))) Float(0.199525997f))))
		DeclareVarInst(stack, "float", fTemp158, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(130.0f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("+", LoadVarInst(stack, fTemp68), Float(130.0f)) Float(150.0f))) Float(150.0f)) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("-", Float(150.0f), LoadVarInst(stack, fTemp64)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp60)), Float(130.0f)) Float(180.0f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("-", Float(180.0f), LoadVarInst(stack, fTemp149)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", LoadVarInst(stack, fTemp135), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp46)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp39)), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", LoadVarInst(stack, fTemp37), Float(130.0f)) Float(150.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(150.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp128))) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp31)), Float(120.0f)) Float(180.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("-", Float(180.0f), LoadVarInst(stack, fTemp145)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp134)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", LoadVarInst(stack, fTemp133), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(130.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp21))) Float(120.0f))))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp158))))
		DeclareVarInst(stack, "float", fTemp159, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec22[Int32(0)])))))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp158)))))
		DeclareVarInst(stack, "float", fTemp160, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec23[Int32(0)])))))
		DeclareVarInst(stack, "float", fTemp161, BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp115)))
		DeclareVarInst(stack, "float", fTemp162, BinopInst("+", BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp74)), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), Select2Inst(LoadVarInst(stack, iTemp76) Select2Inst(LoadVarInst(stack, iTemp79) Select2Inst(LoadVarInst(stack, iTemp81) Select2Inst(LoadVarInst(stack, iTemp83) Select2Inst(LoadVarInst(stack, iTemp85) Select2Inst(LoadVarInst(stack, iTemp87) Select2Inst(LoadVarInst(stack, iTemp89) Select2Inst(LoadVarInst(stack, iTemp91) Select2Inst(LoadVarInst(stack, iTemp93) Select2Inst(LoadVarInst(stack, iTemp95) Select2Inst(LoadVarInst(stack, iTemp97) Select2Inst(LoadVarInst(stack, iTemp99) Select2Inst(LoadVarInst(stack, iTemp101) Select2Inst(LoadVarInst(stack, iTemp103) Select2Inst(LoadVarInst(stack, iTemp105) Select2Inst(LoadVarInst(stack, iTemp107) Select2Inst(LoadVarInst(stack, iTemp110) Select2Inst(LoadVarInst(stack, iTemp112) Select2Inst(LoadVarInst(stack, iTemp114) Select2Inst(LoadVarInst(stack, iTemp116) Select2Inst(LoadVarInst(stack, iTemp118) Select2Inst(LoadVarInst(stack, iTemp120) Select2Inst(LoadVarInst(stack, iTemp122) Select2Inst(LoadVarInst(stack, iTemp124) Float(3500.0f) Select2Inst(LoadVarInst(stack, iTemp122) BinopInst("-", Float(3500.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp75))) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp120) BinopInst("+", BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp123)), Float(3300.0f)) Float(3700.0f))) Select2Inst(LoadVarInst(stack, iTemp118) BinopInst("-", Float(3700.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp121))) Float(3500.0f))) Float(3500.0f)) Select2Inst(LoadVarInst(stack, iTemp114) BinopInst("-", Float(3500.0f), BinopInst("*", Float(1050.0f), LoadVarInst(stack, fTemp117))) Float(2450.0f))) Select2Inst(LoadVarInst(stack, iTemp112) BinopInst("+", LoadVarInst(stack, fTemp161), Float(2450.0f)) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp110) BinopInst("+", BinopInst("*", Float(250.0f), LoadVarInst(stack, fTemp113)), Float(2800.0f)) Float(3050.0f))) Select2Inst(LoadVarInst(stack, iTemp107) BinopInst("-", Float(3050.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp111))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp105) BinopInst("+", BinopInst("*", Float(75.0f), LoadVarInst(stack, fTemp108)), Float(2600.0f)) Float(2675.0f))) Select2Inst(LoadVarInst(stack, iTemp103) BinopInst("+", BinopInst("*", Float(325.0f), LoadVarInst(stack, fTemp106)), Float(2675.0f)) Float(3000.0f))) Float(3000.0f)) Select2Inst(LoadVarInst(stack, iTemp99) BinopInst("+", BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp102)), Float(3000.0f)) Float(3350.0f))) Select2Inst(LoadVarInst(stack, iTemp97) BinopInst("-", Float(3350.0f), BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp100))) Float(3000.0f))) Float(3000.0f)) Select2Inst(LoadVarInst(stack, iTemp93) BinopInst("+", BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp96)), Float(3000.0f)) Float(3900.0f))) Select2Inst(LoadVarInst(stack, iTemp91) BinopInst("-", Float(3900.0f), BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp94))) Float(3600.0f))) Select2Inst(LoadVarInst(stack, iTemp89) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp92)), Float(3600.0f)) Float(3900.0f))) Select2Inst(LoadVarInst(stack, iTemp87) BinopInst("-", Float(3900.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp90))) Float(3800.0f))) Float(3800.0f)) Select2Inst(LoadVarInst(stack, iTemp83) BinopInst("-", Float(3800.0f), BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp86))) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp81) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp84)), Float(2900.0f)) Float(3200.0f))) Select2Inst(LoadVarInst(stack, iTemp79) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp82)), Float(3200.0f)) Float(3250.0f))) Select2Inst(LoadVarInst(stack, iTemp76) BinopInst("-", Float(3250.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp80))) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp77) BinopInst("+", LoadVarInst(stack, fTemp153), Float(2800.0f)) Float(2900.0f))))))
		StoreVarInst(struct, fRec24[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp162), FunCallInst("floorf", LoadVarInst(stack, fTemp162))))
		StoreVarInst(struct, fRec25[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(struct, iVec3[Int32(1)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec25[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("+", LoadVarInst(stack, fTemp160), LoadVarInst(stack, fTemp159)))), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp160), LoadVarInst(stack, fTemp159)), LoadVarInst(struct, fRec25[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp163, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Float(0.00100000005f) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("+", BinopInst("*", Float(0.000777999987f), LoadVarInst(stack, fTemp63)), Float(0.00100000005f)) Float(0.00177800003f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(0.00177800003f), BinopInst("*", Float(0.001147f), LoadVarInst(stack, fTemp60))) Float(0.000630999974f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", BinopInst("*", Float(0.0993689969f), LoadVarInst(stack, fTemp57)), Float(0.000630999974f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("+", BinopInst("*", Float(0.0258930009f), LoadVarInst(stack, fTemp55)), Float(0.100000001f)) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("-", Float(0.125892997f), BinopInst("*", Float(0.0860819966f), LoadVarInst(stack, fTemp53))) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.0398110002f), BinopInst("*", Float(0.0298110005f), LoadVarInst(stack, fTemp51))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(0.00584900007f), LoadVarInst(stack, fTemp131)), Float(0.00999999978f)) Float(0.0158489998f))) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("-", Float(0.0158489998f), BinopInst("*", Float(0.00325999991f), LoadVarInst(stack, fTemp48))) Float(0.0125890002f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("+", BinopInst("*", Float(0.0874110013f), LoadVarInst(stack, fTemp45)), Float(0.0125890002f)) Float(0.100000001f))) LoadVarInst(stack, fTemp156)) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(0.00410400005f), LoadVarInst(stack, fTemp130)), Float(0.0158489998f)) Float(0.0199529994f))) Float(0.0199529994f)) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("-", Float(0.0199529994f), BinopInst("*", Float(0.0167909991f), LoadVarInst(stack, fTemp39))) Float(0.0031620001f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(0.0031620001f), BinopInst("*", Float(0.00157700002f), LoadVarInst(stack, fTemp36))) Float(0.00158499996f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(0.00472499989f), LoadVarInst(stack, fTemp128)), Float(0.00158499996f)) Float(0.00631000008f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(0.00631000008f), BinopInst("*", Float(0.00314799999f), LoadVarInst(stack, fTemp33))) Float(0.0031620001f))) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("-", Float(0.0031620001f), BinopInst("*", Float(0.00216199993f), LoadVarInst(stack, fTemp31))) Float(0.00100000005f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.0784329996f), LoadVarInst(stack, fTemp127)), Float(0.00100000005f)) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("+", BinopInst("*", Float(0.0205669999f), LoadVarInst(stack, fTemp27)), Float(0.0794330016f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp25))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.0184959993f), LoadVarInst(stack, fTemp23)), Float(0.0316229984f)) Float(0.0501190014f))) Float(0.0501190014f)))
		DeclareVarInst(stack, "float", fTemp164, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(140.0f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp18)), Float(140.0f)) Float(200.0f))) Float(200.0f)) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("-", Float(200.0f), BinopInst("*", Float(65.0f), LoadVarInst(stack, fTemp63))) Float(135.0f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("+", BinopInst("*", Float(65.0f), LoadVarInst(stack, fTemp60)), Float(135.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("-", Float(200.0f), BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp57))) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp136)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", LoadVarInst(stack, fTemp148), Float(120.0f)) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(140.0f), LoadVarInst(stack, fTemp147)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", LoadVarInst(stack, fTemp146), Float(120.0f)) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp36)), Float(140.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(200.0f), BinopInst("*", Float(80.0f), LoadVarInst(stack, fTemp128))) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("+", BinopInst("*", Float(80.0f), LoadVarInst(stack, fTemp31)), Float(120.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("-", Float(200.0f), BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp127))) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(140.0f), LoadVarInst(stack, fTemp28)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(15.0f), LoadVarInst(stack, fTemp23)), Float(120.0f)) Float(135.0f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(135.0f), BinopInst("*", Float(15.0f), LoadVarInst(stack, fTemp21))) Float(120.0f))))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec26[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp164))))
		DeclareVarInst(stack, "float", fTemp165, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec26[Int32(0)])))))
		StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp164)))))
		DeclareVarInst(stack, "float", fTemp166, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec27[Int32(0)])))))
		DeclareVarInst(stack, "float", fTemp167, BinopInst("+", BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp74)), LoadVarInst(struct, fRec28[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), Select2Inst(LoadVarInst(stack, iTemp76) Select2Inst(LoadVarInst(stack, iTemp79) Select2Inst(LoadVarInst(stack, iTemp81) Select2Inst(LoadVarInst(stack, iTemp83) Select2Inst(LoadVarInst(stack, iTemp85) Select2Inst(LoadVarInst(stack, iTemp87) Select2Inst(LoadVarInst(stack, iTemp89) Select2Inst(LoadVarInst(stack, iTemp91) Select2Inst(LoadVarInst(stack, iTemp93) Select2Inst(LoadVarInst(stack, iTemp95) Select2Inst(LoadVarInst(stack, iTemp97) Select2Inst(LoadVarInst(stack, iTemp99) Select2Inst(LoadVarInst(stack, iTemp101) Select2Inst(LoadVarInst(stack, iTemp103) Select2Inst(LoadVarInst(stack, iTemp105) Select2Inst(LoadVarInst(stack, iTemp107) Select2Inst(LoadVarInst(stack, iTemp110) Select2Inst(LoadVarInst(stack, iTemp112) Select2Inst(LoadVarInst(stack, iTemp114) Select2Inst(LoadVarInst(stack, iTemp116) Float(4950.0f) Select2Inst(LoadVarInst(stack, iTemp114) BinopInst("-", Float(4950.0f), BinopInst("*", Float(2200.0f), LoadVarInst(stack, fTemp117))) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp112) BinopInst("+", LoadVarInst(stack, fTemp161), Float(2750.0f)) Float(3100.0f))) Select2Inst(LoadVarInst(stack, iTemp110) BinopInst("+", BinopInst("*", Float(240.0f), LoadVarInst(stack, fTemp113)), Float(3100.0f)) Float(3340.0f))) Select2Inst(LoadVarInst(stack, iTemp107) BinopInst("-", Float(3340.0f), BinopInst("*", Float(440.0f), LoadVarInst(stack, fTemp111))) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp105) BinopInst("+", LoadVarInst(stack, fTemp109), Float(2900.0f)) Float(2950.0f))) Select2Inst(LoadVarInst(stack, iTemp103) BinopInst("+", BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp106)), Float(2950.0f)) Float(3350.0f))) Select2Inst(LoadVarInst(stack, iTemp101) BinopInst("-", Float(3350.0f), LoadVarInst(stack, fTemp154)) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp99) BinopInst("+", BinopInst("*", Float(290.0f), LoadVarInst(stack, fTemp102)), Float(3300.0f)) Float(3590.0f))) Select2Inst(LoadVarInst(stack, iTemp97) BinopInst("-", Float(3590.0f), BinopInst("*", Float(290.0f), LoadVarInst(stack, fTemp100))) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp95) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp98)), Float(3300.0f)) Float(3400.0f))) Select2Inst(LoadVarInst(stack, iTemp93) BinopInst("+", BinopInst("*", Float(1550.0f), LoadVarInst(stack, fTemp96)), Float(3400.0f)) Float(4950.0f))) Float(4950.0f)) Float(4950.0f)) Float(4950.0f)) Float(4950.0f)) Select2Inst(LoadVarInst(stack, iTemp83) BinopInst("-", Float(4950.0f), BinopInst("*", Float(1700.0f), LoadVarInst(stack, fTemp86))) Float(3250.0f))) Select2Inst(LoadVarInst(stack, iTemp81) BinopInst("+", BinopInst("*", Float(330.0f), LoadVarInst(stack, fTemp84)), Float(3250.0f)) Float(3580.0f))) Select2Inst(LoadVarInst(stack, iTemp79) BinopInst("-", Float(3580.0f), BinopInst("*", Float(40.0f), LoadVarInst(stack, fTemp82))) Float(3540.0f))) Select2Inst(LoadVarInst(stack, iTemp76) BinopInst("-", Float(3540.0f), BinopInst("*", Float(540.0f), LoadVarInst(stack, fTemp80))) Float(3000.0f))) Select2Inst(LoadVarInst(stack, iTemp77) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp78)), Float(3000.0f)) Float(3300.0f))))))
		StoreVarInst(struct, fRec28[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp167), FunCallInst("floorf", LoadVarInst(stack, fTemp167))))
		StoreVarInst(struct, fRec29[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(struct, iVec3[Int32(1)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec29[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("+", LoadVarInst(stack, fTemp166), LoadVarInst(stack, fTemp165)))), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp166), LoadVarInst(stack, fTemp165)), LoadVarInst(struct, fRec29[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp168, BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), Select2Inst(LoadVarInst(stack, iSlow22) LoadVarInst(stack, fTemp73) LoadVarInst(stack, fTemp72))), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp71), BinopInst("*", LoadVarInst(stack, fTemp70), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp71)))))), LoadVarInst(static, ftbl0mydspSIG0[CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec12[Int32(0)])))])), BinopInst("*", BinopInst("*", BinopInst("*", Select2Inst(LoadVarInst(stack, iSlow22) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp132)) BinopInst("*", LoadVarInst(stack, fTemp72), LoadVarInst(stack, fTemp132))), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp138), BinopInst("*", LoadVarInst(stack, fTemp139), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp138)))))), LoadVarInst(static, ftbl0mydspSIG0[CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec16[Int32(0)])))])), LoadVarInst(struct, fRec17[Int32(0)]))), BinopInst("*", BinopInst("*", BinopInst("*", Select2Inst(LoadVarInst(stack, iSlow22) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp144)) BinopInst("*", LoadVarInst(stack, fTemp72), LoadVarInst(stack, fTemp144))), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp151), BinopInst("*", LoadVarInst(stack, fTemp152), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp151)))))), LoadVarInst(static, ftbl0mydspSIG0[CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec20[Int32(0)])))])), LoadVarInst(struct, fRec21[Int32(0)]))), BinopInst("*", BinopInst("*", BinopInst("*", Select2Inst(LoadVarInst(stack, iSlow22) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp157)) BinopInst("*", LoadVarInst(stack, fTemp72), LoadVarInst(stack, fTemp157))), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp159), BinopInst("*", LoadVarInst(stack, fTemp160), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp159)))))), LoadVarInst(static, ftbl0mydspSIG0[CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec24[Int32(0)])))])), LoadVarInst(struct, fRec25[Int32(0)]))), BinopInst("*", BinopInst("*", BinopInst("*", Select2Inst(LoadVarInst(stack, iSlow22) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp163)) BinopInst("*", LoadVarInst(stack, fTemp72), LoadVarInst(stack, fTemp163))), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp165), BinopInst("*", LoadVarInst(stack, fTemp166), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp165)))))), LoadVarInst(static, ftbl0mydspSIG0[CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec28[Int32(0)])))])), LoadVarInst(struct, fRec29[Int32(0)]))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp168)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp168)))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, iVec3[Int32(1)], LoadVarInst(struct, iVec3[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(2)], LoadVarInst(struct, fRec17[Int32(1)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec21[Int32(2)], LoadVarInst(struct, fRec21[Int32(1)]))
		StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(2)], LoadVarInst(struct, fRec25[Int32(1)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec29[Int32(2)], LoadVarInst(struct, fRec29[Int32(1)]))
		StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
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
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst(static, float, ftbl0mydspSIG0[65536])
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
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, int, iVec3[2])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec17[3])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec21[3])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, float, fRec25[3])
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec29[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1000.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst5, FunCallInst("expf", BinopInst("-", Float(0.0f), LoadVarInst(struct, fConst1))))
	StoreVarInst(struct, fConst6, BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst5)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fButton0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.90000000000000002f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(10.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(440.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(6.0f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec3[LoadVarInst(loop, l8)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(3))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(3))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(3))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(3))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(3))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	DeclareVarInst(stack, mydspSIG0, sig0, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(stack, sig0), LoadVarInst(kFunArgs, samplingFreq)))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(stack, sig0), Int32(65536), LoadVarInst(static, ftbl0mydspSIG0)))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(stack, sig0)))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst(struct, int, iRec11[2])
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec11[LoadVarInst(loop, l15)], Int32(0))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec11[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec11[Int32(1)]), Int32(1)))
			StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], FunCallInst("sinf", BinopInst("*", Float(9.58738019e-05f), CastInst("float", BinopInst("+", LoadVarInst(struct, iRec11[Int32(0)]), Int32(-1))))))
			StoreVarInst(struct, iRec11[Int32(1)], LoadVarInst(struct, iRec11[Int32(0)]))
			EndBlock
		EndForLoop
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("min_f", Float(1.0f), BinopInst("+", CastInst("float", LoadVarInst(struct, fButton0)), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider3))))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(25.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fSlow1), CastInst("float", LoadVarInst(struct, fHslider2))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2)))))
	DeclareVarInst(stack, "float", fSlow4, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("==", LoadVarInst(stack, fSlow1), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fHslider5)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(0.100000001f), CastInst("float", LoadVarInst(struct, fHslider6))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", LoadVarInst(struct, fConst3), CastInst("float", LoadVarInst(struct, fHslider7))))
	DeclareVarInst(stack, "float", fSlow9, FunCallInst("sinf", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("cosf", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider8))))
	DeclareVarInst(stack, "float", fSlow13, CastInst("float", LoadVarInst(struct, fHslider9)))
	DeclareVarInst(stack, "int", iSlow14, Select2Inst(BinopInst("==", LoadVarInst(stack, fSlow13), Float(0.0f)) Int32(1) Select2Inst(BinopInst("==", LoadVarInst(stack, fSlow13), Float(3.0f)) Int32(1) Int32(0))))
	DeclareVarInst(stack, "int", iSlow15, BinopInst("*", Int32(5), LoadVarInst(stack, iSlow14)))
	DeclareVarInst(stack, "int", iSlow16, BinopInst(">=", LoadVarInst(stack, iSlow14), Int32(1)))
	DeclareVarInst(stack, "float", fSlow17, Select2Inst(LoadVarInst(stack, iSlow16) Float(174.610001f) Float(82.4100037f)))
	DeclareVarInst(stack, "float", fSlow18, Select2Inst(LoadVarInst(stack, iSlow16) Float(1046.5f) Float(523.25f)))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("-", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fSlow17)))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("*", Float(5.0f), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow21, BinopInst("*", Float(5.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow13))))
	DeclareVarInst(stack, "int", iSlow22, BinopInst("==", LoadVarInst(stack, iSlow14), Int32(0)))
	DeclareVarInst(stack, "int", iSlow23, BinopInst("!=", LoadVarInst(stack, fSlow13), Float(2.0f)))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", Float(2.0f), LoadVarInst(stack, fSlow4)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fSlow1))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(struct, fRec0[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("|", BinopInst("==", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fVec1[Int32(1)])), LoadVarInst(stack, iSlow5)))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), CastInst("float", LoadVarInst(stack, iTemp0)))), BinopInst("*", LoadVarInst(stack, fSlow6), BinopInst("-", Float(1.0f), BinopInst("*", Float(0.999000013f), CastInst("float", LoadVarInst(stack, iTemp0)))))))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec4[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp1, BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec4[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp1))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec4[Int32(0)])), Float(1.0f))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(stack, fTemp2)))
			StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp3))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fVec2[Int32(1)]))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp4), FunCallInst("floorf", LoadVarInst(stack, fTemp4))))
			DeclareVarInst(stack, "int", iTemp5, BinopInst("<", BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec2[Int32(1)])), Float(0.0f)))
			StoreVarInst(struct, iVec3[Int32(0)], LoadVarInst(stack, iTemp5))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow12), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec7[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), CastInst("float", LoadVarInst(stack, iSlow15))))
			DeclareVarInst(stack, "int", iTemp7, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(5.0f)))
			DeclareVarInst(stack, "int", iTemp8, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(3.0f)))
			DeclareVarInst(stack, "int", iTemp9, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(2.0f)))
			DeclareVarInst(stack, "int", iTemp10, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(1.0f)))
			DeclareVarInst(stack, "int", iTemp11, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(4.0f)))
			DeclareVarInst(stack, "int", iTemp12, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(8.0f)))
			DeclareVarInst(stack, "int", iTemp13, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(7.0f)))
			DeclareVarInst(stack, "int", iTemp14, BinopInst(">=", LoadVarInst(stack, fTemp6), Float(6.0f)))
			DeclareVarInst(stack, "float", fTemp15, Select2Inst(LoadVarInst(stack, iTemp7) Select2Inst(LoadVarInst(stack, iTemp12) Float(2.0f) Select2Inst(LoadVarInst(stack, iTemp13) Float(3.0f) Select2Inst(LoadVarInst(stack, iTemp14) Float(3.0f) Float(2.0f)))) Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Float(1.5f) Float(1.0f)) Select2Inst(LoadVarInst(stack, iTemp9) Float(1.25f) Select2Inst(LoadVarInst(stack, iTemp10) Float(1.25f) Float(1.0f))))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec8[Int32(1)]))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec8[Int32(1)]))), CastInst("float", LoadVarInst(stack, iTemp1))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("*", LoadVarInst(stack, fSlow4), BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(struct, fRec8[Int32(0)])), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("+", LoadVarInst(stack, fTemp15), BinopInst("*", BinopInst("-", Select2Inst(LoadVarInst(stack, iTemp7) Select2Inst(LoadVarInst(stack, iTemp12) Float(12.0f) Select2Inst(LoadVarInst(stack, iTemp13) Float(12.0f) Select2Inst(LoadVarInst(stack, iTemp14) Float(12.0f) Float(15.0f)))) Select2Inst(LoadVarInst(stack, iTemp8) Select2Inst(LoadVarInst(stack, iTemp11) Float(4.0f) Float(10.0f)) Select2Inst(LoadVarInst(stack, iTemp9) Float(2.5f) Select2Inst(LoadVarInst(stack, iTemp10) Float(2.5f) Float(10.0f))))), LoadVarInst(stack, fTemp15)), Select2Inst(BinopInst("<=", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fSlow17)) Float(0.0f) Select2Inst(BinopInst(">=", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fSlow18)) Float(1.0f) BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fSlow17)), LoadVarInst(stack, fSlow19)))))))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("+", LoadVarInst(stack, fSlow20), LoadVarInst(struct, fRec7[Int32(0)])))
			DeclareVarInst(stack, "int", iTemp19, BinopInst("<", LoadVarInst(stack, fTemp18), Float(23.0f)))
			DeclareVarInst(stack, "int", iTemp20, BinopInst("<", LoadVarInst(stack, fTemp18), Float(24.0f)))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-23.0f))))
			DeclareVarInst(stack, "int", iTemp22, BinopInst("<", LoadVarInst(stack, fTemp18), Float(22.0f)))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-22.0f))))
			DeclareVarInst(stack, "int", iTemp24, BinopInst("<", LoadVarInst(stack, fTemp18), Float(21.0f)))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-21.0f))))
			DeclareVarInst(stack, "int", iTemp26, BinopInst("<", LoadVarInst(stack, fTemp18), Float(20.0f)))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-20.0f))))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp27)))
			DeclareVarInst(stack, "int", iTemp29, BinopInst("<", LoadVarInst(stack, fTemp18), Float(19.0f)))
			DeclareVarInst(stack, "int", iTemp30, BinopInst("<", LoadVarInst(stack, fTemp18), Float(18.0f)))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-18.0f))))
			DeclareVarInst(stack, "int", iTemp32, BinopInst("<", LoadVarInst(stack, fTemp18), Float(17.0f)))
			DeclareVarInst(stack, "float", fTemp33, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-17.0f))))
			DeclareVarInst(stack, "int", iTemp34, BinopInst("<", LoadVarInst(stack, fTemp18), Float(16.0f)))
			DeclareVarInst(stack, "int", iTemp35, BinopInst("<", LoadVarInst(stack, fTemp18), Float(15.0f)))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-15.0f))))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp36)))
			DeclareVarInst(stack, "int", iTemp38, BinopInst("<", LoadVarInst(stack, fTemp18), Float(14.0f)))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-14.0f))))
			DeclareVarInst(stack, "int", iTemp40, BinopInst("<", LoadVarInst(stack, fTemp18), Float(13.0f)))
			DeclareVarInst(stack, "int", iTemp41, BinopInst("<", LoadVarInst(stack, fTemp18), Float(12.0f)))
			DeclareVarInst(stack, "int", iTemp42, BinopInst("<", LoadVarInst(stack, fTemp18), Float(11.0f)))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-11.0f))))
			DeclareVarInst(stack, "int", iTemp44, BinopInst("<", LoadVarInst(stack, fTemp18), Float(10.0f)))
			DeclareVarInst(stack, "float", fTemp45, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-10.0f))))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp45)))
			DeclareVarInst(stack, "int", iTemp47, BinopInst("<", LoadVarInst(stack, fTemp18), Float(9.0f)))
			DeclareVarInst(stack, "float", fTemp48, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-9.0f))))
			DeclareVarInst(stack, "int", iTemp49, BinopInst("<", LoadVarInst(stack, fTemp18), Float(8.0f)))
			DeclareVarInst(stack, "int", iTemp50, BinopInst("<", LoadVarInst(stack, fTemp18), Float(7.0f)))
			DeclareVarInst(stack, "float", fTemp51, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-7.0f))))
			DeclareVarInst(stack, "int", iTemp52, BinopInst("<", LoadVarInst(stack, fTemp18), Float(6.0f)))
			DeclareVarInst(stack, "float", fTemp53, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-6.0f))))
			DeclareVarInst(stack, "int", iTemp54, BinopInst("<", LoadVarInst(stack, fTemp18), Float(5.0f)))
			DeclareVarInst(stack, "float", fTemp55, BinopInst("-", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(stack, fSlow21)))
			DeclareVarInst(stack, "int", iTemp56, BinopInst("<", LoadVarInst(stack, fTemp18), Float(4.0f)))
			DeclareVarInst(stack, "float", fTemp57, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-4.0f))))
			DeclareVarInst(stack, "float", fTemp58, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp57)))
			DeclareVarInst(stack, "int", iTemp59, BinopInst("<", LoadVarInst(stack, fTemp18), Float(3.0f)))
			DeclareVarInst(stack, "float", fTemp60, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-3.0f))))
			DeclareVarInst(stack, "float", fTemp61, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp60)))
			DeclareVarInst(stack, "int", iTemp62, BinopInst("<", LoadVarInst(stack, fTemp18), Float(2.0f)))
			DeclareVarInst(stack, "float", fTemp63, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-2.0f))))
			DeclareVarInst(stack, "float", fTemp64, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp63)))
			DeclareVarInst(stack, "int", iTemp65, BinopInst("<", LoadVarInst(stack, fTemp18), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp66, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-1.0f))))
			DeclareVarInst(stack, "int", iTemp67, BinopInst("<", LoadVarInst(stack, fTemp18), Float(0.0f)))
			DeclareVarInst(stack, "float", fTemp68, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp18)))
			DeclareVarInst(stack, "float", fTemp69, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(80.0f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp68)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp62) BinopInst("-", Float(60.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp66))) Float(50.0f))) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("+", LoadVarInst(stack, fTemp64), Float(50.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(70.0f), LoadVarInst(stack, fTemp61)) Float(50.0f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", LoadVarInst(stack, fTemp58), Float(50.0f)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp55))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("+", BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp53)), Float(40.0f)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp51))) Float(40.0f))) Float(40.0f)) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("*", Float(40.0f), BinopInst("+", LoadVarInst(stack, fTemp48), Float(1.0f))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp46)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp41) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp43))) Float(40.0f))) Float(40.0f)) Float(40.0f)) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("*", Float(40.0f), BinopInst("+", LoadVarInst(stack, fTemp39), Float(1.0f))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp37)) Float(60.0f))) Float(60.0f)) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(60.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp33))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp31)), Float(40.0f)) Float(50.0f))) Float(50.0f)) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("+", LoadVarInst(stack, fTemp28), Float(50.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp25))) Float(40.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp23)), Float(40.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(70.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp21))) Float(40.0f))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp69)))))
			DeclareVarInst(stack, "float", fTemp70, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec6[Int32(0)])))))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp69))))
			DeclareVarInst(stack, "float", fTemp71, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec10[Int32(0)])))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(struct, iVec3[Int32(1)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("+", LoadVarInst(stack, fTemp70), LoadVarInst(stack, fTemp71)))), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp70), LoadVarInst(stack, fTemp71)), LoadVarInst(struct, fRec1[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp72, BinopInst("+", BinopInst("*", Float(0.000839999993f), BinopInst("-", Float(1000.0f), LoadVarInst(stack, fTemp16))), Float(0.800000012f)))
			DeclareVarInst(stack, "float", fTemp73, BinopInst("+", BinopInst("*", Float(0.00366666657f), BinopInst("-", Float(400.0f), LoadVarInst(stack, fTemp16))), Float(3.0f)))
			DeclareVarInst(stack, "int", iTemp74, BinopInst("-", Int32(1), BinopInst(">", LoadVarInst(stack, iTemp5), Int32(0))))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow12), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec13[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp75, BinopInst("+", LoadVarInst(stack, fSlow20), LoadVarInst(struct, fRec13[Int32(0)])))
			DeclareVarInst(stack, "int", iTemp76, BinopInst("<", LoadVarInst(stack, fTemp75), Float(23.0f)))
			DeclareVarInst(stack, "int", iTemp77, BinopInst("<", LoadVarInst(stack, fTemp75), Float(24.0f)))
			DeclareVarInst(stack, "float", fTemp78, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-23.0f))))
			DeclareVarInst(stack, "int", iTemp79, BinopInst("<", LoadVarInst(stack, fTemp75), Float(22.0f)))
			DeclareVarInst(stack, "float", fTemp80, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-22.0f))))
			DeclareVarInst(stack, "int", iTemp81, BinopInst("<", LoadVarInst(stack, fTemp75), Float(21.0f)))
			DeclareVarInst(stack, "float", fTemp82, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-21.0f))))
			DeclareVarInst(stack, "int", iTemp83, BinopInst("<", LoadVarInst(stack, fTemp75), Float(20.0f)))
			DeclareVarInst(stack, "float", fTemp84, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-20.0f))))
			DeclareVarInst(stack, "int", iTemp85, BinopInst("<", LoadVarInst(stack, fTemp75), Float(19.0f)))
			DeclareVarInst(stack, "float", fTemp86, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-19.0f))))
			DeclareVarInst(stack, "int", iTemp87, BinopInst("<", LoadVarInst(stack, fTemp75), Float(18.0f)))
			DeclareVarInst(stack, "float", fTemp88, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-18.0f))))
			DeclareVarInst(stack, "int", iTemp89, BinopInst("<", LoadVarInst(stack, fTemp75), Float(17.0f)))
			DeclareVarInst(stack, "float", fTemp90, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-17.0f))))
			DeclareVarInst(stack, "int", iTemp91, BinopInst("<", LoadVarInst(stack, fTemp75), Float(16.0f)))
			DeclareVarInst(stack, "float", fTemp92, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-16.0f))))
			DeclareVarInst(stack, "int", iTemp93, BinopInst("<", LoadVarInst(stack, fTemp75), Float(15.0f)))
			DeclareVarInst(stack, "float", fTemp94, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-15.0f))))
			DeclareVarInst(stack, "int", iTemp95, BinopInst("<", LoadVarInst(stack, fTemp75), Float(14.0f)))
			DeclareVarInst(stack, "float", fTemp96, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-14.0f))))
			DeclareVarInst(stack, "int", iTemp97, BinopInst("<", LoadVarInst(stack, fTemp75), Float(13.0f)))
			DeclareVarInst(stack, "float", fTemp98, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-13.0f))))
			DeclareVarInst(stack, "int", iTemp99, BinopInst("<", LoadVarInst(stack, fTemp75), Float(12.0f)))
			DeclareVarInst(stack, "float", fTemp100, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-12.0f))))
			DeclareVarInst(stack, "int", iTemp101, BinopInst("<", LoadVarInst(stack, fTemp75), Float(11.0f)))
			DeclareVarInst(stack, "float", fTemp102, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-11.0f))))
			DeclareVarInst(stack, "int", iTemp103, BinopInst("<", LoadVarInst(stack, fTemp75), Float(10.0f)))
			DeclareVarInst(stack, "float", fTemp104, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-10.0f))))
			DeclareVarInst(stack, "int", iTemp105, BinopInst("<", LoadVarInst(stack, fTemp75), Float(9.0f)))
			DeclareVarInst(stack, "float", fTemp106, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-9.0f))))
			DeclareVarInst(stack, "int", iTemp107, BinopInst("<", LoadVarInst(stack, fTemp75), Float(8.0f)))
			DeclareVarInst(stack, "float", fTemp108, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-8.0f))))
			DeclareVarInst(stack, "float", fTemp109, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp108)))
			DeclareVarInst(stack, "int", iTemp110, BinopInst("<", LoadVarInst(stack, fTemp75), Float(7.0f)))
			DeclareVarInst(stack, "float", fTemp111, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-7.0f))))
			DeclareVarInst(stack, "int", iTemp112, BinopInst("<", LoadVarInst(stack, fTemp75), Float(6.0f)))
			DeclareVarInst(stack, "float", fTemp113, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-6.0f))))
			DeclareVarInst(stack, "int", iTemp114, BinopInst("<", LoadVarInst(stack, fTemp75), Float(5.0f)))
			DeclareVarInst(stack, "float", fTemp115, BinopInst("-", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(stack, fSlow21)))
			DeclareVarInst(stack, "int", iTemp116, BinopInst("<", LoadVarInst(stack, fTemp75), Float(4.0f)))
			DeclareVarInst(stack, "float", fTemp117, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-4.0f))))
			DeclareVarInst(stack, "int", iTemp118, BinopInst("<", LoadVarInst(stack, fTemp75), Float(3.0f)))
			DeclareVarInst(stack, "float", fTemp119, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-3.0f))))
			DeclareVarInst(stack, "int", iTemp120, BinopInst("<", LoadVarInst(stack, fTemp75), Float(2.0f)))
			DeclareVarInst(stack, "float", fTemp121, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-2.0f))))
			DeclareVarInst(stack, "int", iTemp122, BinopInst("<", LoadVarInst(stack, fTemp75), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp123, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), Float(-1.0f))))
			DeclareVarInst(stack, "int", iTemp124, BinopInst("<", LoadVarInst(stack, fTemp75), Float(0.0f)))
			DeclareVarInst(stack, "float", fTemp125, Select2Inst(LoadVarInst(stack, iTemp76) Select2Inst(LoadVarInst(stack, iTemp79) Select2Inst(LoadVarInst(stack, iTemp81) Select2Inst(LoadVarInst(stack, iTemp83) Select2Inst(LoadVarInst(stack, iTemp85) Select2Inst(LoadVarInst(stack, iTemp87) Select2Inst(LoadVarInst(stack, iTemp89) Select2Inst(LoadVarInst(stack, iTemp91) Select2Inst(LoadVarInst(stack, iTemp93) Select2Inst(LoadVarInst(stack, iTemp95) Select2Inst(LoadVarInst(stack, iTemp97) Select2Inst(LoadVarInst(stack, iTemp99) Select2Inst(LoadVarInst(stack, iTemp101) Select2Inst(LoadVarInst(stack, iTemp103) Select2Inst(LoadVarInst(stack, iTemp105) Select2Inst(LoadVarInst(stack, iTemp107) Select2Inst(LoadVarInst(stack, iTemp110) Select2Inst(LoadVarInst(stack, iTemp112) Select2Inst(LoadVarInst(stack, iTemp114) Select2Inst(LoadVarInst(stack, iTemp116) Select2Inst(LoadVarInst(stack, iTemp118) Select2Inst(LoadVarInst(stack, iTemp120) Select2Inst(LoadVarInst(stack, iTemp122) Select2Inst(LoadVarInst(stack, iTemp124) Float(800.0f) Select2Inst(LoadVarInst(stack, iTemp122) BinopInst("-", Float(800.0f), BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp75))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp120) BinopInst("-", Float(400.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp123))) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp118) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp121)), Float(350.0f)) Float(450.0f))) Select2Inst(LoadVarInst(stack, iTemp116) BinopInst("-", Float(450.0f), BinopInst("*", Float(125.0f), LoadVarInst(stack, fTemp119))) Float(325.0f))) Select2Inst(LoadVarInst(stack, iTemp114) BinopInst("+", BinopInst("*", Float(275.0f), LoadVarInst(stack, fTemp117)), Float(325.0f)) Float(600.0f))) Select2Inst(LoadVarInst(stack, iTemp112) BinopInst("-", Float(600.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp115))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp110) BinopInst("-", Float(400.0f), BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp113))) Float(250.0f))) Select2Inst(LoadVarInst(stack, iTemp107) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp111)), Float(250.0f)) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp105) BinopInst("-", Float(400.0f), LoadVarInst(stack, fTemp109)) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp103) BinopInst("+", BinopInst("*", Float(310.0f), LoadVarInst(stack, fTemp106)), Float(350.0f)) Float(660.0f))) Select2Inst(LoadVarInst(stack, iTemp101) BinopInst("-", Float(660.0f), BinopInst("*", Float(220.0f), LoadVarInst(stack, fTemp104))) Float(440.0f))) Select2Inst(LoadVarInst(stack, iTemp99) BinopInst("-", Float(440.0f), BinopInst("*", Float(170.0f), LoadVarInst(stack, fTemp102))) Float(270.0f))) Select2Inst(LoadVarInst(stack, iTemp97) BinopInst("+", BinopInst("*", Float(160.0f), LoadVarInst(stack, fTemp100)), Float(270.0f)) Float(430.0f))) Select2Inst(LoadVarInst(stack, iTemp95) BinopInst("-", Float(430.0f), BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp98))) Float(370.0f))) Select2Inst(LoadVarInst(stack, iTemp93) BinopInst("+", BinopInst("*", Float(430.0f), LoadVarInst(stack, fTemp96)), Float(370.0f)) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp91) BinopInst("-", Float(800.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp94))) Float(350.0f))) Select2Inst(LoadVarInst(stack, iTemp89) BinopInst("-", Float(350.0f), BinopInst("*", Float(80.0f), LoadVarInst(stack, fTemp92))) Float(270.0f))) Select2Inst(LoadVarInst(stack, iTemp87) BinopInst("+", BinopInst("*", Float(180.0f), LoadVarInst(stack, fTemp90)), Float(270.0f)) Float(450.0f))) Select2Inst(LoadVarInst(stack, iTemp85) BinopInst("-", Float(450.0f), BinopInst("*", Float(125.0f), LoadVarInst(stack, fTemp88))) Float(325.0f))) Select2Inst(LoadVarInst(stack, iTemp83) BinopInst("*", Float(325.0f), BinopInst("+", LoadVarInst(stack, fTemp86), Float(1.0f))) Float(650.0f))) Select2Inst(LoadVarInst(stack, iTemp81) BinopInst("-", Float(650.0f), BinopInst("*", Float(250.0f), LoadVarInst(stack, fTemp84))) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp79) BinopInst("-", Float(400.0f), BinopInst("*", Float(110.0f), LoadVarInst(stack, fTemp82))) Float(290.0f))) Select2Inst(LoadVarInst(stack, iTemp76) BinopInst("+", BinopInst("*", Float(110.0f), LoadVarInst(stack, fTemp80)), Float(290.0f)) Float(400.0f))) Select2Inst(LoadVarInst(stack, iTemp77) BinopInst("-", Float(400.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp78))) Float(350.0f))))
			DeclareVarInst(stack, "float", fTemp126, BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec12[Int32(1)]), CastInst("float", LoadVarInst(stack, iTemp74))), BinopInst("*", LoadVarInst(struct, fConst7), Select2Inst(BinopInst("<=", LoadVarInst(stack, fTemp125), LoadVarInst(stack, fTemp3)) LoadVarInst(stack, fTemp3) LoadVarInst(stack, fTemp125)))))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp126), FunCallInst("floorf", LoadVarInst(stack, fTemp126))))
			DeclareVarInst(stack, "float", fTemp127, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-19.0f))))
			DeclareVarInst(stack, "float", fTemp128, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-16.0f))))
			DeclareVarInst(stack, "float", fTemp129, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-13.0f))))
			DeclareVarInst(stack, "float", fTemp130, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-12.0f))))
			DeclareVarInst(stack, "float", fTemp131, BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-8.0f))))
			DeclareVarInst(stack, "float", fTemp132, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(0.630957007f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("-", Float(0.630957007f), BinopInst("*", Float(0.567861021f), LoadVarInst(stack, fTemp18))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp62) BinopInst("+", BinopInst("*", Float(0.0369039997f), LoadVarInst(stack, fTemp66)), Float(0.0630960017f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("+", BinopInst("*", Float(0.254812986f), LoadVarInst(stack, fTemp63)), Float(0.100000001f)) Float(0.35481301f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.103624001f), LoadVarInst(stack, fTemp60))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp57)), Float(0.251188993f)) Float(0.446684003f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("-", Float(0.446684003f), BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp55))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.219566002f), LoadVarInst(stack, fTemp53))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("+", BinopInst("*", Float(0.250214994f), LoadVarInst(stack, fTemp51)), Float(0.0316229984f)) Float(0.281838f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(0.281838f), BinopInst("*", Float(0.181838006f), LoadVarInst(stack, fTemp131))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp48)), Float(0.100000001f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.301661015f), LoadVarInst(stack, fTemp45))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp41) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.136429995f), LoadVarInst(stack, fTemp43))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(0.253131986f), LoadVarInst(stack, fTemp130)), Float(0.0630960017f)) Float(0.316228002f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(0.316228002f), BinopInst("*", Float(0.216227993f), LoadVarInst(stack, fTemp129))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp39)), Float(0.100000001f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.401187003f), LoadVarInst(stack, fTemp36))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(0.151188999f), LoadVarInst(stack, fTemp128)), Float(0.100000001f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(0.0306490008f), LoadVarInst(stack, fTemp33)), Float(0.251188993f)) Float(0.281838f))) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("-", Float(0.281838f), BinopInst("*", Float(0.123349003f), LoadVarInst(stack, fTemp31))) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.342698008f), LoadVarInst(stack, fTemp127)), Float(0.158489004f)) Float(0.501187027f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(0.501187027f), BinopInst("*", Float(0.301661015f), LoadVarInst(stack, fTemp27))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.0216979999f), LoadVarInst(stack, fTemp25))) Float(0.177827999f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.138400003f), LoadVarInst(stack, fTemp23)), Float(0.177827999f)) Float(0.316228002f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(0.316228002f), BinopInst("*", Float(0.216227993f), LoadVarInst(stack, fTemp21))) Float(0.100000001f))))
			DeclareVarInst(stack, "float", fTemp133, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp23)))
			DeclareVarInst(stack, "float", fTemp134, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp27)))
			DeclareVarInst(stack, "float", fTemp135, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp48)))
			DeclareVarInst(stack, "float", fTemp136, BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp55)))
			DeclareVarInst(stack, "float", fTemp137, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(90.0f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp18))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp62) BinopInst("+", BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp66)), Float(80.0f)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("-", Float(100.0f), LoadVarInst(stack, fTemp64)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(80.0f), LoadVarInst(stack, fTemp61)) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", LoadVarInst(stack, fTemp58), Float(60.0f)) Float(70.0f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("+", LoadVarInst(stack, fTemp136), Float(70.0f)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp53)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp51))) Float(80.0f))) Float(80.0f)) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", LoadVarInst(stack, fTemp135), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp46)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp41) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp43)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp130))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp129))) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp39)), Float(60.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp36)), Float(90.0f)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(100.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp128))) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(90.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp33))) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp31))) Float(60.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp127)), Float(60.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp134)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp25)), Float(80.0f)) Float(90.0f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("-", Float(90.0f), LoadVarInst(stack, fTemp133)) Float(80.0f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(80.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp21))) Float(60.0f))))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec14[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp137))))
			DeclareVarInst(stack, "float", fTemp138, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec14[Int32(0)])))))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp137)))))
			DeclareVarInst(stack, "float", fTemp139, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec15[Int32(0)])))))
			DeclareVarInst(stack, "float", fTemp140, Select2Inst(LoadVarInst(stack, iTemp76) Select2Inst(LoadVarInst(stack, iTemp79) Select2Inst(LoadVarInst(stack, iTemp81) Select2Inst(LoadVarInst(stack, iTemp83) Select2Inst(LoadVarInst(stack, iTemp85) Select2Inst(LoadVarInst(stack, iTemp87) Select2Inst(LoadVarInst(stack, iTemp89) Select2Inst(LoadVarInst(stack, iTemp91) Select2Inst(LoadVarInst(stack, iTemp93) Select2Inst(LoadVarInst(stack, iTemp95) Select2Inst(LoadVarInst(stack, iTemp97) Select2Inst(LoadVarInst(stack, iTemp99) Select2Inst(LoadVarInst(stack, iTemp101) Select2Inst(LoadVarInst(stack, iTemp103) Select2Inst(LoadVarInst(stack, iTemp105) Select2Inst(LoadVarInst(stack, iTemp107) Select2Inst(LoadVarInst(stack, iTemp110) Select2Inst(LoadVarInst(stack, iTemp112) Select2Inst(LoadVarInst(stack, iTemp114) Select2Inst(LoadVarInst(stack, iTemp116) Select2Inst(LoadVarInst(stack, iTemp118) Select2Inst(LoadVarInst(stack, iTemp120) Select2Inst(LoadVarInst(stack, iTemp122) Select2Inst(LoadVarInst(stack, iTemp124) Float(1150.0f) Select2Inst(LoadVarInst(stack, iTemp122) BinopInst("+", BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp75)), Float(1150.0f)) Float(1600.0f))) Select2Inst(LoadVarInst(stack, iTemp120) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp123)), Float(1600.0f)) Float(1700.0f))) Select2Inst(LoadVarInst(stack, iTemp118) BinopInst("-", Float(1700.0f), BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp121))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp116) BinopInst("-", Float(800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp119))) Float(700.0f))) Select2Inst(LoadVarInst(stack, iTemp114) BinopInst("+", BinopInst("*", Float(340.0f), LoadVarInst(stack, fTemp117)), Float(700.0f)) Float(1040.0f))) Select2Inst(LoadVarInst(stack, iTemp112) BinopInst("+", BinopInst("*", Float(580.0f), LoadVarInst(stack, fTemp115)), Float(1040.0f)) Float(1620.0f))) Select2Inst(LoadVarInst(stack, iTemp110) BinopInst("+", BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp113)), Float(1620.0f)) Float(1750.0f))) Select2Inst(LoadVarInst(stack, iTemp107) BinopInst("-", Float(1750.0f), BinopInst("*", Float(1000.0f), LoadVarInst(stack, fTemp111))) Float(750.0f))) Select2Inst(LoadVarInst(stack, iTemp105) BinopInst("-", Float(750.0f), BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp108))) Float(600.0f))) Select2Inst(LoadVarInst(stack, iTemp103) BinopInst("+", BinopInst("*", Float(520.0f), LoadVarInst(stack, fTemp106)), Float(600.0f)) Float(1120.0f))) Select2Inst(LoadVarInst(stack, iTemp101) BinopInst("+", BinopInst("*", Float(680.0f), LoadVarInst(stack, fTemp104)), Float(1120.0f)) Float(1800.0f))) Select2Inst(LoadVarInst(stack, iTemp99) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp102)), Float(1800.0f)) Float(1850.0f))) Select2Inst(LoadVarInst(stack, iTemp97) BinopInst("-", Float(1850.0f), BinopInst("*", Float(1030.0f), LoadVarInst(stack, fTemp100))) Float(820.0f))) Select2Inst(LoadVarInst(stack, iTemp95) BinopInst("-", Float(820.0f), BinopInst("*", Float(190.0f), LoadVarInst(stack, fTemp98))) Float(630.0f))) Select2Inst(LoadVarInst(stack, iTemp93) BinopInst("+", BinopInst("*", Float(520.0f), LoadVarInst(stack, fTemp96)), Float(630.0f)) Float(1150.0f))) Select2Inst(LoadVarInst(stack, iTemp91) BinopInst("+", BinopInst("*", Float(850.0f), LoadVarInst(stack, fTemp94)), Float(1150.0f)) Float(2000.0f))) Select2Inst(LoadVarInst(stack, iTemp89) BinopInst("+", BinopInst("*", Float(140.0f), LoadVarInst(stack, fTemp92)), Float(2000.0f)) Float(2140.0f))) Select2Inst(LoadVarInst(stack, iTemp87) BinopInst("-", Float(2140.0f), BinopInst("*", Float(1340.0f), LoadVarInst(stack, fTemp90))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp85) BinopInst("-", Float(800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp88))) Float(700.0f))) Select2Inst(LoadVarInst(stack, iTemp83) BinopInst("+", BinopInst("*", Float(380.0f), LoadVarInst(stack, fTemp86)), Float(700.0f)) Float(1080.0f))) Select2Inst(LoadVarInst(stack, iTemp81) BinopInst("+", BinopInst("*", Float(620.0f), LoadVarInst(stack, fTemp84)), Float(1080.0f)) Float(1700.0f))) Select2Inst(LoadVarInst(stack, iTemp79) BinopInst("+", BinopInst("*", Float(170.0f), LoadVarInst(stack, fTemp82)), Float(1700.0f)) Float(1870.0f))) Select2Inst(LoadVarInst(stack, iTemp76) BinopInst("-", Float(1870.0f), BinopInst("*", Float(1070.0f), LoadVarInst(stack, fTemp80))) Float(800.0f))) Select2Inst(LoadVarInst(stack, iTemp77) BinopInst("-", Float(800.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp78))) Float(600.0f))))
			DeclareVarInst(stack, "float", fTemp141, BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(stack, fTemp2)), Float(30.0f)))
			DeclareVarInst(stack, "float", fTemp142, BinopInst("+", BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp74)), LoadVarInst(struct, fRec16[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), Select2Inst(LoadVarInst(stack, iSlow23) Select2Inst(BinopInst("&", BinopInst(">=", LoadVarInst(stack, fTemp140), Float(1300.0f)), BinopInst(">=", LoadVarInst(stack, fTemp3), Float(200.0f))) BinopInst("-", LoadVarInst(stack, fTemp140), BinopInst("*", Float(0.000952380942f), BinopInst("*", BinopInst("+", LoadVarInst(stack, fTemp3), Float(-200.0f)), BinopInst("+", LoadVarInst(stack, fTemp140), Float(-1300.0f))))) Select2Inst(BinopInst("<=", LoadVarInst(stack, fTemp140), LoadVarInst(stack, fTemp141)) LoadVarInst(stack, fTemp141) LoadVarInst(stack, fTemp140))) LoadVarInst(stack, fTemp140)))))
			StoreVarInst(struct, fRec16[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp142), FunCallInst("floorf", LoadVarInst(stack, fTemp142))))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(struct, iVec3[Int32(1)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec17[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("+", LoadVarInst(stack, fTemp139), LoadVarInst(stack, fTemp138)))), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp139), LoadVarInst(stack, fTemp138)), LoadVarInst(struct, fRec17[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp143, Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("+", BinopInst("*", Float(0.0293140002f), LoadVarInst(stack, fTemp33)), Float(0.0501190014f)) Float(0.0794330016f)))
			DeclareVarInst(stack, "float", fTemp144, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(0.100000001f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp18))) Float(0.0316229984f))) Float(0.0316229984f)) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("+", BinopInst("*", Float(0.126865998f), LoadVarInst(stack, fTemp63)), Float(0.0316229984f)) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(0.158489004f), BinopInst("*", Float(0.126865998f), LoadVarInst(stack, fTemp60))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", BinopInst("*", Float(0.323190004f), LoadVarInst(stack, fTemp57)), Float(0.0316229984f)) Float(0.35481301f))) Float(0.35481301f)) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.196324006f), LoadVarInst(stack, fTemp53))) Float(0.158489004f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.158489004f), BinopInst("*", Float(0.0693639964f), LoadVarInst(stack, fTemp51))) Float(0.0891249999f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(0.0891249999f), BinopInst("*", Float(0.0640060008f), LoadVarInst(stack, fTemp131))) Float(0.0251189992f))) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", BinopInst("*", Float(0.0456760004f), LoadVarInst(stack, fTemp48)), Float(0.0251189992f)) Float(0.0707949996f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("+", BinopInst("*", Float(0.0550980009f), LoadVarInst(stack, fTemp45)), Float(0.0707949996f)) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp41) BinopInst("-", Float(0.125892997f), BinopInst("*", Float(0.0627970025f), LoadVarInst(stack, fTemp43))) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("-", Float(0.0630960017f), BinopInst("*", Float(0.0129770003f), LoadVarInst(stack, fTemp130))) Float(0.0501190014f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("+", BinopInst("*", Float(0.020676f), LoadVarInst(stack, fTemp129)), Float(0.0501190014f)) Float(0.0707949996f))) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("-", Float(0.0707949996f), BinopInst("*", Float(0.0456760004f), LoadVarInst(stack, fTemp39))) Float(0.0251189992f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(0.152709007f), LoadVarInst(stack, fTemp36)), Float(0.0251189992f)) Float(0.177827999f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(0.177827999f), BinopInst("*", Float(0.127709001f), LoadVarInst(stack, fTemp128))) Float(0.0501190014f))) LoadVarInst(stack, fTemp143)) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0616500005f), LoadVarInst(stack, fTemp31))) Float(0.0177829992f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.428900987f), LoadVarInst(stack, fTemp127)), Float(0.0177829992f)) Float(0.446684003f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(0.446684003f), BinopInst("*", Float(0.195494995f), LoadVarInst(stack, fTemp27))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.125295997f), LoadVarInst(stack, fTemp25))) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.125295997f), LoadVarInst(stack, fTemp23)), Float(0.125892997f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.109935001f), LoadVarInst(stack, fTemp21))) Float(0.141253993f))))
			DeclareVarInst(stack, "float", fTemp145, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp127)))
			DeclareVarInst(stack, "float", fTemp146, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp39)))
			DeclareVarInst(stack, "float", fTemp147, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp45)))
			DeclareVarInst(stack, "float", fTemp148, BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp48)))
			DeclareVarInst(stack, "float", fTemp149, BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp57)))
			DeclareVarInst(stack, "float", fTemp150, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Float(120.0f) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp64)) Float(100.0f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("+", BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp60)), Float(100.0f)) Float(170.0f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("-", Float(170.0f), LoadVarInst(stack, fTemp149)) Float(110.0f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("-", Float(110.0f), LoadVarInst(stack, fTemp136)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", LoadVarInst(stack, fTemp148), Float(100.0f)) Float(120.0f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp147)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", LoadVarInst(stack, fTemp146), Float(100.0f)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(120.0f), BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp128))) Float(100.0f))) Float(100.0f)) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("+", BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp31)), Float(100.0f)) Float(170.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("-", Float(170.0f), LoadVarInst(stack, fTemp145)) Float(120.0f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(120.0f), LoadVarInst(stack, fTemp28)) Float(100.0f))) Float(100.0f)) Float(100.0f)) Float(100.0f)))
			StoreVarInst(struct, fRec18[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp150))))
			DeclareVarInst(stack, "float", fTemp151, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec18[Int32(0)])))))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec19[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp150)))))
			DeclareVarInst(stack, "float", fTemp152, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec19[Int32(0)])))))
			DeclareVarInst(stack, "float", fTemp153, BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp78)))
			DeclareVarInst(stack, "float", fTemp154, BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp104)))
			DeclareVarInst(stack, "float", fTemp155, BinopInst("+", BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp74)), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), Select2Inst(LoadVarInst(stack, iTemp76) Select2Inst(LoadVarInst(stack, iTemp79) Select2Inst(LoadVarInst(stack, iTemp81) Select2Inst(LoadVarInst(stack, iTemp83) Select2Inst(LoadVarInst(stack, iTemp85) Select2Inst(LoadVarInst(stack, iTemp87) Select2Inst(LoadVarInst(stack, iTemp89) Select2Inst(LoadVarInst(stack, iTemp91) Select2Inst(LoadVarInst(stack, iTemp93) Select2Inst(LoadVarInst(stack, iTemp95) Select2Inst(LoadVarInst(stack, iTemp97) Select2Inst(LoadVarInst(stack, iTemp99) Select2Inst(LoadVarInst(stack, iTemp101) Select2Inst(LoadVarInst(stack, iTemp103) Select2Inst(LoadVarInst(stack, iTemp105) Select2Inst(LoadVarInst(stack, iTemp107) Select2Inst(LoadVarInst(stack, iTemp110) Select2Inst(LoadVarInst(stack, iTemp112) Select2Inst(LoadVarInst(stack, iTemp114) Select2Inst(LoadVarInst(stack, iTemp116) Select2Inst(LoadVarInst(stack, iTemp118) Select2Inst(LoadVarInst(stack, iTemp120) Select2Inst(LoadVarInst(stack, iTemp122) Select2Inst(LoadVarInst(stack, iTemp124) Float(2800.0f) Select2Inst(LoadVarInst(stack, iTemp122) BinopInst("-", Float(2800.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp75))) Float(2700.0f))) Float(2700.0f)) Select2Inst(LoadVarInst(stack, iTemp118) BinopInst("+", BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp121)), Float(2700.0f)) Float(2830.0f))) Select2Inst(LoadVarInst(stack, iTemp116) BinopInst("-", Float(2830.0f), BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp119))) Float(2530.0f))) Select2Inst(LoadVarInst(stack, iTemp114) BinopInst("-", Float(2530.0f), BinopInst("*", Float(280.0f), LoadVarInst(stack, fTemp117))) Float(2250.0f))) Select2Inst(LoadVarInst(stack, iTemp112) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp115)), Float(2250.0f)) Float(2400.0f))) Select2Inst(LoadVarInst(stack, iTemp110) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp113)), Float(2400.0f)) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp107) BinopInst("-", Float(2600.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp111))) Float(2400.0f))) Float(2400.0f)) Select2Inst(LoadVarInst(stack, iTemp103) BinopInst("+", BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp106)), Float(2400.0f)) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp101) BinopInst("-", Float(2750.0f), LoadVarInst(stack, fTemp154)) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp99) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp102)), Float(2700.0f)) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp97) BinopInst("-", Float(2900.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp100))) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp95) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp98)), Float(2700.0f)) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp93) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp96)), Float(2750.0f)) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp91) BinopInst("-", Float(2900.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp94))) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp89) BinopInst("+", BinopInst("*", Float(150.0f), LoadVarInst(stack, fTemp92)), Float(2800.0f)) Float(2950.0f))) Select2Inst(LoadVarInst(stack, iTemp87) BinopInst("-", Float(2950.0f), BinopInst("*", Float(120.0f), LoadVarInst(stack, fTemp90))) Float(2830.0f))) Select2Inst(LoadVarInst(stack, iTemp85) BinopInst("-", Float(2830.0f), BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp88))) Float(2700.0f))) Select2Inst(LoadVarInst(stack, iTemp83) BinopInst("-", Float(2700.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp86))) Float(2650.0f))) Select2Inst(LoadVarInst(stack, iTemp81) BinopInst("-", Float(2650.0f), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp84))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp79) BinopInst("+", BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp82)), Float(2600.0f)) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp76) BinopInst("-", Float(2800.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp80))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp77) BinopInst("+", LoadVarInst(stack, fTemp153), Float(2600.0f)) Float(2700.0f))))))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp155), FunCallInst("floorf", LoadVarInst(stack, fTemp155))))
			StoreVarInst(struct, fRec21[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(struct, iVec3[Int32(1)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec21[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("+", LoadVarInst(stack, fTemp152), LoadVarInst(stack, fTemp151)))), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp152), LoadVarInst(stack, fTemp151)), LoadVarInst(struct, fRec21[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp156, Select2Inst(LoadVarInst(stack, iTemp41) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0841509998f), LoadVarInst(stack, fTemp43))) Float(0.0158489998f)))
			DeclareVarInst(stack, "float", fTemp157, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(0.0158489998f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("+", BinopInst("*", Float(0.00193400006f), LoadVarInst(stack, fTemp18)), Float(0.0158489998f)) Float(0.0177829992f))) Select2Inst(LoadVarInst(stack, iTemp62) BinopInst("-", Float(0.0177829992f), BinopInst("*", Float(0.00193400006f), LoadVarInst(stack, fTemp66))) Float(0.0158489998f))) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("+", BinopInst("*", Float(0.0239620004f), LoadVarInst(stack, fTemp63)), Float(0.0158489998f)) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(0.0398110002f), BinopInst("*", Float(0.0298110005f), LoadVarInst(stack, fTemp60))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", BinopInst("*", Float(0.344812989f), LoadVarInst(stack, fTemp57)), Float(0.00999999978f)) Float(0.35481301f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("-", Float(0.35481301f), BinopInst("*", Float(0.103624001f), LoadVarInst(stack, fTemp55))) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.171755999f), LoadVarInst(stack, fTemp53))) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("+", BinopInst("*", Float(0.0205669999f), LoadVarInst(stack, fTemp51)), Float(0.0794330016f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0601890013f), LoadVarInst(stack, fTemp131))) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", BinopInst("*", Float(0.0232849997f), LoadVarInst(stack, fTemp48)), Float(0.0398110002f)) Float(0.0630960017f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("+", BinopInst("*", Float(0.0369039997f), LoadVarInst(stack, fTemp45)), Float(0.0630960017f)) Float(0.100000001f))) LoadVarInst(stack, fTemp156)) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(0.0635839999f), LoadVarInst(stack, fTemp130)), Float(0.0158489998f)) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp38) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0478099994f), LoadVarInst(stack, fTemp129))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp39)), Float(0.0316229984f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0900000036f), LoadVarInst(stack, fTemp36))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(0.0401189998f), LoadVarInst(stack, fTemp128)), Float(0.00999999978f)) Float(0.0501190014f))) LoadVarInst(stack, fTemp143)) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("-", Float(0.0794330016f), BinopInst("*", Float(0.0694330037f), LoadVarInst(stack, fTemp31))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.388107002f), LoadVarInst(stack, fTemp127)), Float(0.00999999978f)) Float(0.398106992f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(0.398106992f), BinopInst("*", Float(0.198580995f), LoadVarInst(stack, fTemp27))) Float(0.199525997f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("-", Float(0.199525997f), BinopInst("*", Float(0.099526003f), LoadVarInst(stack, fTemp25))) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.151188999f), LoadVarInst(stack, fTemp23)), Float(0.100000001f)) Float(0.251188993f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(0.251188993f), BinopInst("*", Float(0.0516630001f), LoadVarInst(stack, fTemp21))) Float(0.199525997f))))
			DeclareVarInst(stack, "float", fTemp158, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(130.0f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("+", LoadVarInst(stack, fTemp68), Float(130.0f)) Float(150.0f))) Float(150.0f)) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("-", Float(150.0f), LoadVarInst(stack, fTemp64)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp60)), Float(130.0f)) Float(180.0f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("-", Float(180.0f), LoadVarInst(stack, fTemp149)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", LoadVarInst(stack, fTemp135), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp46)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp39)), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", LoadVarInst(stack, fTemp37), Float(130.0f)) Float(150.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(150.0f), BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp128))) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp31)), Float(120.0f)) Float(180.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("-", Float(180.0f), LoadVarInst(stack, fTemp145)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp134)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", LoadVarInst(stack, fTemp133), Float(120.0f)) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(130.0f), BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp21))) Float(120.0f))))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec22[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp158))))
			DeclareVarInst(stack, "float", fTemp159, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec22[Int32(0)])))))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec23[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp158)))))
			DeclareVarInst(stack, "float", fTemp160, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec23[Int32(0)])))))
			DeclareVarInst(stack, "float", fTemp161, BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp115)))
			DeclareVarInst(stack, "float", fTemp162, BinopInst("+", BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp74)), LoadVarInst(struct, fRec24[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), Select2Inst(LoadVarInst(stack, iTemp76) Select2Inst(LoadVarInst(stack, iTemp79) Select2Inst(LoadVarInst(stack, iTemp81) Select2Inst(LoadVarInst(stack, iTemp83) Select2Inst(LoadVarInst(stack, iTemp85) Select2Inst(LoadVarInst(stack, iTemp87) Select2Inst(LoadVarInst(stack, iTemp89) Select2Inst(LoadVarInst(stack, iTemp91) Select2Inst(LoadVarInst(stack, iTemp93) Select2Inst(LoadVarInst(stack, iTemp95) Select2Inst(LoadVarInst(stack, iTemp97) Select2Inst(LoadVarInst(stack, iTemp99) Select2Inst(LoadVarInst(stack, iTemp101) Select2Inst(LoadVarInst(stack, iTemp103) Select2Inst(LoadVarInst(stack, iTemp105) Select2Inst(LoadVarInst(stack, iTemp107) Select2Inst(LoadVarInst(stack, iTemp110) Select2Inst(LoadVarInst(stack, iTemp112) Select2Inst(LoadVarInst(stack, iTemp114) Select2Inst(LoadVarInst(stack, iTemp116) Select2Inst(LoadVarInst(stack, iTemp118) Select2Inst(LoadVarInst(stack, iTemp120) Select2Inst(LoadVarInst(stack, iTemp122) Select2Inst(LoadVarInst(stack, iTemp124) Float(3500.0f) Select2Inst(LoadVarInst(stack, iTemp122) BinopInst("-", Float(3500.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp75))) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp120) BinopInst("+", BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp123)), Float(3300.0f)) Float(3700.0f))) Select2Inst(LoadVarInst(stack, iTemp118) BinopInst("-", Float(3700.0f), BinopInst("*", Float(200.0f), LoadVarInst(stack, fTemp121))) Float(3500.0f))) Float(3500.0f)) Select2Inst(LoadVarInst(stack, iTemp114) BinopInst("-", Float(3500.0f), BinopInst("*", Float(1050.0f), LoadVarInst(stack, fTemp117))) Float(2450.0f))) Select2Inst(LoadVarInst(stack, iTemp112) BinopInst("+", LoadVarInst(stack, fTemp161), Float(2450.0f)) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp110) BinopInst("+", BinopInst("*", Float(250.0f), LoadVarInst(stack, fTemp113)), Float(2800.0f)) Float(3050.0f))) Select2Inst(LoadVarInst(stack, iTemp107) BinopInst("-", Float(3050.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp111))) Float(2600.0f))) Select2Inst(LoadVarInst(stack, iTemp105) BinopInst("+", BinopInst("*", Float(75.0f), LoadVarInst(stack, fTemp108)), Float(2600.0f)) Float(2675.0f))) Select2Inst(LoadVarInst(stack, iTemp103) BinopInst("+", BinopInst("*", Float(325.0f), LoadVarInst(stack, fTemp106)), Float(2675.0f)) Float(3000.0f))) Float(3000.0f)) Select2Inst(LoadVarInst(stack, iTemp99) BinopInst("+", BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp102)), Float(3000.0f)) Float(3350.0f))) Select2Inst(LoadVarInst(stack, iTemp97) BinopInst("-", Float(3350.0f), BinopInst("*", Float(350.0f), LoadVarInst(stack, fTemp100))) Float(3000.0f))) Float(3000.0f)) Select2Inst(LoadVarInst(stack, iTemp93) BinopInst("+", BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp96)), Float(3000.0f)) Float(3900.0f))) Select2Inst(LoadVarInst(stack, iTemp91) BinopInst("-", Float(3900.0f), BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp94))) Float(3600.0f))) Select2Inst(LoadVarInst(stack, iTemp89) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp92)), Float(3600.0f)) Float(3900.0f))) Select2Inst(LoadVarInst(stack, iTemp87) BinopInst("-", Float(3900.0f), BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp90))) Float(3800.0f))) Float(3800.0f)) Select2Inst(LoadVarInst(stack, iTemp83) BinopInst("-", Float(3800.0f), BinopInst("*", Float(900.0f), LoadVarInst(stack, fTemp86))) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp81) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp84)), Float(2900.0f)) Float(3200.0f))) Select2Inst(LoadVarInst(stack, iTemp79) BinopInst("+", BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp82)), Float(3200.0f)) Float(3250.0f))) Select2Inst(LoadVarInst(stack, iTemp76) BinopInst("-", Float(3250.0f), BinopInst("*", Float(450.0f), LoadVarInst(stack, fTemp80))) Float(2800.0f))) Select2Inst(LoadVarInst(stack, iTemp77) BinopInst("+", LoadVarInst(stack, fTemp153), Float(2800.0f)) Float(2900.0f))))))
			StoreVarInst(struct, fRec24[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp162), FunCallInst("floorf", LoadVarInst(stack, fTemp162))))
			StoreVarInst(struct, fRec25[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(struct, iVec3[Int32(1)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec25[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("+", LoadVarInst(stack, fTemp160), LoadVarInst(stack, fTemp159)))), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp160), LoadVarInst(stack, fTemp159)), LoadVarInst(struct, fRec25[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp163, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Float(0.00100000005f) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("+", BinopInst("*", Float(0.000777999987f), LoadVarInst(stack, fTemp63)), Float(0.00100000005f)) Float(0.00177800003f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("-", Float(0.00177800003f), BinopInst("*", Float(0.001147f), LoadVarInst(stack, fTemp60))) Float(0.000630999974f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("+", BinopInst("*", Float(0.0993689969f), LoadVarInst(stack, fTemp57)), Float(0.000630999974f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("+", BinopInst("*", Float(0.0258930009f), LoadVarInst(stack, fTemp55)), Float(0.100000001f)) Float(0.125892997f))) Select2Inst(LoadVarInst(stack, iTemp50) BinopInst("-", Float(0.125892997f), BinopInst("*", Float(0.0860819966f), LoadVarInst(stack, fTemp53))) Float(0.0398110002f))) Select2Inst(LoadVarInst(stack, iTemp49) BinopInst("-", Float(0.0398110002f), BinopInst("*", Float(0.0298110005f), LoadVarInst(stack, fTemp51))) Float(0.00999999978f))) Select2Inst(LoadVarInst(stack, iTemp47) BinopInst("+", BinopInst("*", Float(0.00584900007f), LoadVarInst(stack, fTemp131)), Float(0.00999999978f)) Float(0.0158489998f))) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("-", Float(0.0158489998f), BinopInst("*", Float(0.00325999991f), LoadVarInst(stack, fTemp48))) Float(0.0125890002f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("+", BinopInst("*", Float(0.0874110013f), LoadVarInst(stack, fTemp45)), Float(0.0125890002f)) Float(0.100000001f))) LoadVarInst(stack, fTemp156)) Select2Inst(LoadVarInst(stack, iTemp40) BinopInst("+", BinopInst("*", Float(0.00410400005f), LoadVarInst(stack, fTemp130)), Float(0.0158489998f)) Float(0.0199529994f))) Float(0.0199529994f)) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("-", Float(0.0199529994f), BinopInst("*", Float(0.0167909991f), LoadVarInst(stack, fTemp39))) Float(0.0031620001f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("-", Float(0.0031620001f), BinopInst("*", Float(0.00157700002f), LoadVarInst(stack, fTemp36))) Float(0.00158499996f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("+", BinopInst("*", Float(0.00472499989f), LoadVarInst(stack, fTemp128)), Float(0.00158499996f)) Float(0.00631000008f))) Select2Inst(LoadVarInst(stack, iTemp30) BinopInst("-", Float(0.00631000008f), BinopInst("*", Float(0.00314799999f), LoadVarInst(stack, fTemp33))) Float(0.0031620001f))) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("-", Float(0.0031620001f), BinopInst("*", Float(0.00216199993f), LoadVarInst(stack, fTemp31))) Float(0.00100000005f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("+", BinopInst("*", Float(0.0784329996f), LoadVarInst(stack, fTemp127)), Float(0.00100000005f)) Float(0.0794330016f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("+", BinopInst("*", Float(0.0205669999f), LoadVarInst(stack, fTemp27)), Float(0.0794330016f)) Float(0.100000001f))) Select2Inst(LoadVarInst(stack, iTemp22) BinopInst("-", Float(0.100000001f), BinopInst("*", Float(0.0683770031f), LoadVarInst(stack, fTemp25))) Float(0.0316229984f))) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(0.0184959993f), LoadVarInst(stack, fTemp23)), Float(0.0316229984f)) Float(0.0501190014f))) Float(0.0501190014f)))
			DeclareVarInst(stack, "float", fTemp164, Select2Inst(LoadVarInst(stack, iTemp19) Select2Inst(LoadVarInst(stack, iTemp22) Select2Inst(LoadVarInst(stack, iTemp24) Select2Inst(LoadVarInst(stack, iTemp26) Select2Inst(LoadVarInst(stack, iTemp29) Select2Inst(LoadVarInst(stack, iTemp30) Select2Inst(LoadVarInst(stack, iTemp32) Select2Inst(LoadVarInst(stack, iTemp34) Select2Inst(LoadVarInst(stack, iTemp35) Select2Inst(LoadVarInst(stack, iTemp38) Select2Inst(LoadVarInst(stack, iTemp40) Select2Inst(LoadVarInst(stack, iTemp41) Select2Inst(LoadVarInst(stack, iTemp42) Select2Inst(LoadVarInst(stack, iTemp44) Select2Inst(LoadVarInst(stack, iTemp47) Select2Inst(LoadVarInst(stack, iTemp49) Select2Inst(LoadVarInst(stack, iTemp50) Select2Inst(LoadVarInst(stack, iTemp52) Select2Inst(LoadVarInst(stack, iTemp54) Select2Inst(LoadVarInst(stack, iTemp56) Select2Inst(LoadVarInst(stack, iTemp59) Select2Inst(LoadVarInst(stack, iTemp62) Select2Inst(LoadVarInst(stack, iTemp65) Select2Inst(LoadVarInst(stack, iTemp67) Float(140.0f) Select2Inst(LoadVarInst(stack, iTemp65) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp18)), Float(140.0f)) Float(200.0f))) Float(200.0f)) Select2Inst(LoadVarInst(stack, iTemp59) BinopInst("-", Float(200.0f), BinopInst("*", Float(65.0f), LoadVarInst(stack, fTemp63))) Float(135.0f))) Select2Inst(LoadVarInst(stack, iTemp56) BinopInst("+", BinopInst("*", Float(65.0f), LoadVarInst(stack, fTemp60)), Float(135.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp54) BinopInst("-", Float(200.0f), BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp57))) Float(130.0f))) Select2Inst(LoadVarInst(stack, iTemp52) BinopInst("-", Float(130.0f), LoadVarInst(stack, fTemp136)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp44) BinopInst("+", LoadVarInst(stack, fTemp148), Float(120.0f)) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp42) BinopInst("-", Float(140.0f), LoadVarInst(stack, fTemp147)) Float(120.0f))) Float(120.0f)) Float(120.0f)) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp35) BinopInst("+", LoadVarInst(stack, fTemp146), Float(120.0f)) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp34) BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp36)), Float(140.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp32) BinopInst("-", Float(200.0f), BinopInst("*", Float(80.0f), LoadVarInst(stack, fTemp128))) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp29) BinopInst("+", BinopInst("*", Float(80.0f), LoadVarInst(stack, fTemp31)), Float(120.0f)) Float(200.0f))) Select2Inst(LoadVarInst(stack, iTemp26) BinopInst("-", Float(200.0f), BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp127))) Float(140.0f))) Select2Inst(LoadVarInst(stack, iTemp24) BinopInst("-", Float(140.0f), LoadVarInst(stack, fTemp28)) Float(120.0f))) Float(120.0f)) Select2Inst(LoadVarInst(stack, iTemp19) BinopInst("+", BinopInst("*", Float(15.0f), LoadVarInst(stack, fTemp23)), Float(120.0f)) Float(135.0f))) Select2Inst(LoadVarInst(stack, iTemp20) BinopInst("-", Float(135.0f), BinopInst("*", Float(15.0f), LoadVarInst(stack, fTemp21))) Float(120.0f))))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec26[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp164))))
			DeclareVarInst(stack, "float", fTemp165, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec26[Int32(0)])))))
			StoreVarInst(struct, fRec27[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(struct, fRec27[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst6), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp164)))))
			DeclareVarInst(stack, "float", fTemp166, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec27[Int32(0)])))))
			DeclareVarInst(stack, "float", fTemp167, BinopInst("+", BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp74)), LoadVarInst(struct, fRec28[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst7), Select2Inst(LoadVarInst(stack, iTemp76) Select2Inst(LoadVarInst(stack, iTemp79) Select2Inst(LoadVarInst(stack, iTemp81) Select2Inst(LoadVarInst(stack, iTemp83) Select2Inst(LoadVarInst(stack, iTemp85) Select2Inst(LoadVarInst(stack, iTemp87) Select2Inst(LoadVarInst(stack, iTemp89) Select2Inst(LoadVarInst(stack, iTemp91) Select2Inst(LoadVarInst(stack, iTemp93) Select2Inst(LoadVarInst(stack, iTemp95) Select2Inst(LoadVarInst(stack, iTemp97) Select2Inst(LoadVarInst(stack, iTemp99) Select2Inst(LoadVarInst(stack, iTemp101) Select2Inst(LoadVarInst(stack, iTemp103) Select2Inst(LoadVarInst(stack, iTemp105) Select2Inst(LoadVarInst(stack, iTemp107) Select2Inst(LoadVarInst(stack, iTemp110) Select2Inst(LoadVarInst(stack, iTemp112) Select2Inst(LoadVarInst(stack, iTemp114) Select2Inst(LoadVarInst(stack, iTemp116) Float(4950.0f) Select2Inst(LoadVarInst(stack, iTemp114) BinopInst("-", Float(4950.0f), BinopInst("*", Float(2200.0f), LoadVarInst(stack, fTemp117))) Float(2750.0f))) Select2Inst(LoadVarInst(stack, iTemp112) BinopInst("+", LoadVarInst(stack, fTemp161), Float(2750.0f)) Float(3100.0f))) Select2Inst(LoadVarInst(stack, iTemp110) BinopInst("+", BinopInst("*", Float(240.0f), LoadVarInst(stack, fTemp113)), Float(3100.0f)) Float(3340.0f))) Select2Inst(LoadVarInst(stack, iTemp107) BinopInst("-", Float(3340.0f), BinopInst("*", Float(440.0f), LoadVarInst(stack, fTemp111))) Float(2900.0f))) Select2Inst(LoadVarInst(stack, iTemp105) BinopInst("+", LoadVarInst(stack, fTemp109), Float(2900.0f)) Float(2950.0f))) Select2Inst(LoadVarInst(stack, iTemp103) BinopInst("+", BinopInst("*", Float(400.0f), LoadVarInst(stack, fTemp106)), Float(2950.0f)) Float(3350.0f))) Select2Inst(LoadVarInst(stack, iTemp101) BinopInst("-", Float(3350.0f), LoadVarInst(stack, fTemp154)) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp99) BinopInst("+", BinopInst("*", Float(290.0f), LoadVarInst(stack, fTemp102)), Float(3300.0f)) Float(3590.0f))) Select2Inst(LoadVarInst(stack, iTemp97) BinopInst("-", Float(3590.0f), BinopInst("*", Float(290.0f), LoadVarInst(stack, fTemp100))) Float(3300.0f))) Select2Inst(LoadVarInst(stack, iTemp95) BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp98)), Float(3300.0f)) Float(3400.0f))) Select2Inst(LoadVarInst(stack, iTemp93) BinopInst("+", BinopInst("*", Float(1550.0f), LoadVarInst(stack, fTemp96)), Float(3400.0f)) Float(4950.0f))) Float(4950.0f)) Float(4950.0f)) Float(4950.0f)) Float(4950.0f)) Select2Inst(LoadVarInst(stack, iTemp83) BinopInst("-", Float(4950.0f), BinopInst("*", Float(1700.0f), LoadVarInst(stack, fTemp86))) Float(3250.0f))) Select2Inst(LoadVarInst(stack, iTemp81) BinopInst("+", BinopInst("*", Float(330.0f), LoadVarInst(stack, fTemp84)), Float(3250.0f)) Float(3580.0f))) Select2Inst(LoadVarInst(stack, iTemp79) BinopInst("-", Float(3580.0f), BinopInst("*", Float(40.0f), LoadVarInst(stack, fTemp82))) Float(3540.0f))) Select2Inst(LoadVarInst(stack, iTemp76) BinopInst("-", Float(3540.0f), BinopInst("*", Float(540.0f), LoadVarInst(stack, fTemp80))) Float(3000.0f))) Select2Inst(LoadVarInst(stack, iTemp77) BinopInst("+", BinopInst("*", Float(300.0f), LoadVarInst(stack, fTemp78)), Float(3000.0f)) Float(3300.0f))))))
			StoreVarInst(struct, fRec28[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp167), FunCallInst("floorf", LoadVarInst(stack, fTemp167))))
			StoreVarInst(struct, fRec29[Int32(0)], BinopInst("-", CastInst("float", LoadVarInst(struct, iVec3[Int32(1)])), BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec29[Int32(1)]), BinopInst("-", Float(0.0f), BinopInst("+", LoadVarInst(stack, fTemp166), LoadVarInst(stack, fTemp165)))), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp166), LoadVarInst(stack, fTemp165)), LoadVarInst(struct, fRec29[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp168, BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), Select2Inst(LoadVarInst(stack, iSlow22) LoadVarInst(stack, fTemp73) LoadVarInst(stack, fTemp72))), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp71), BinopInst("*", LoadVarInst(stack, fTemp70), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp71)))))), LoadVarInst(static, ftbl0mydspSIG0[CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec12[Int32(0)])))])), BinopInst("*", BinopInst("*", BinopInst("*", Select2Inst(LoadVarInst(stack, iSlow22) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp132)) BinopInst("*", LoadVarInst(stack, fTemp72), LoadVarInst(stack, fTemp132))), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp138), BinopInst("*", LoadVarInst(stack, fTemp139), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp138)))))), LoadVarInst(static, ftbl0mydspSIG0[CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec16[Int32(0)])))])), LoadVarInst(struct, fRec17[Int32(0)]))), BinopInst("*", BinopInst("*", BinopInst("*", Select2Inst(LoadVarInst(stack, iSlow22) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp144)) BinopInst("*", LoadVarInst(stack, fTemp72), LoadVarInst(stack, fTemp144))), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp151), BinopInst("*", LoadVarInst(stack, fTemp152), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp151)))))), LoadVarInst(static, ftbl0mydspSIG0[CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec20[Int32(0)])))])), LoadVarInst(struct, fRec21[Int32(0)]))), BinopInst("*", BinopInst("*", BinopInst("*", Select2Inst(LoadVarInst(stack, iSlow22) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp157)) BinopInst("*", LoadVarInst(stack, fTemp72), LoadVarInst(stack, fTemp157))), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp159), BinopInst("*", LoadVarInst(stack, fTemp160), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp159)))))), LoadVarInst(static, ftbl0mydspSIG0[CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec24[Int32(0)])))])), LoadVarInst(struct, fRec25[Int32(0)]))), BinopInst("*", BinopInst("*", BinopInst("*", Select2Inst(LoadVarInst(stack, iSlow22) BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(stack, fTemp163)) BinopInst("*", LoadVarInst(stack, fTemp72), LoadVarInst(stack, fTemp163))), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp165), BinopInst("*", LoadVarInst(stack, fTemp166), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp165)))))), LoadVarInst(static, ftbl0mydspSIG0[CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec28[Int32(0)])))])), LoadVarInst(struct, fRec29[Int32(0)]))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp168)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp168)))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, iVec3[Int32(1)], LoadVarInst(struct, iVec3[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(2)], LoadVarInst(struct, fRec17[Int32(1)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec21[Int32(2)], LoadVarInst(struct, fRec21[Int32(1)]))
			StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(2)], LoadVarInst(struct, fRec25[Int32(1)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec29[Int32(2)], LoadVarInst(struct, fRec29[Int32(1)]))
			StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 16 bytes
Heap size real = 344 bytes
Heap size = 372 bytes
Stack size in compute = 116 bytes

