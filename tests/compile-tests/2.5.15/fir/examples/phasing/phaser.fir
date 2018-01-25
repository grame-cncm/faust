======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "tooltip", "Reference:   https://ccrma.stanford.edu/~jos/pasp/Flanging.html")
	OpenVerticalBox("PHASER2")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked, the phaser   has no effect")
	AddCheckButtonInst("Bypass"fCheckbox0)
	AddMetaDeclareInst(fCheckbox2, "1", "")
	AddCheckButtonInst("Invert Internal Phaser Sum"fCheckbox2)
	AddMetaDeclareInst(fCheckbox1, "2", "")
	AddCheckButtonInst("Vibrato Mode"fCheckbox1)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fHslider7, "1", "")
	AddMetaDeclareInst(fHslider7, "style", "knob")
	AddMetaDeclareInst(fHslider7, "unit", "Hz")
	AddHorizontalSlider("Speed", fHslider7, 0.5f, 0.0f, 10.0f, 0.00100000005f)
	AddMetaDeclareInst(fHslider1, "2", "")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddHorizontalSlider("Notch Depth (Intensity)", fHslider1, 1.0f, 0.0f, 1.0f, 0.00100000005f)
	AddMetaDeclareInst(fHslider3, "3", "")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddHorizontalSlider("Feedback Gain", fHslider3, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f)
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fHslider2, "1", "")
	AddMetaDeclareInst(fHslider2, "scale", "log")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddMetaDeclareInst(fHslider2, "unit", "Hz")
	AddHorizontalSlider("Notch width", fHslider2, 1000.0f, 10.0f, 5000.0f, 1.0f)
	AddMetaDeclareInst(fHslider5, "2", "")
	AddMetaDeclareInst(fHslider5, "scale", "log")
	AddMetaDeclareInst(fHslider5, "style", "knob")
	AddMetaDeclareInst(fHslider5, "unit", "Hz")
	AddHorizontalSlider("Min Notch1 Freq", fHslider5, 100.0f, 20.0f, 5000.0f, 1.0f)
	AddMetaDeclareInst(fHslider6, "3", "")
	AddMetaDeclareInst(fHslider6, "scale", "log")
	AddMetaDeclareInst(fHslider6, "style", "knob")
	AddMetaDeclareInst(fHslider6, "unit", "Hz")
	AddHorizontalSlider("Max Notch1 Freq", fHslider6, 800.0f, 20.0f, 10000.0f, 1.0f)
	AddMetaDeclareInst(fHslider4, "4", "")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddHorizontalSlider("Notch Freq Ratio: NotchFreq(n+1)/NotchFreq(n)", fHslider4, 1.5f, 1.10000002f, 4.0f, 0.00100000005f)
	CloseboxInst
	AddMetaDeclareInst(0, "3", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("Phaser Output Level", fHslider0, 0.0f, -60.0f, 10.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "mydsp_faustpower4_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, float, fRec11[3])
	DeclareVarInst(struct, float, fRec10[3])
	DeclareVarInst(struct, float, fRec9[3])
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, float, fRec7[2])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(2))
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(1.5f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(100.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(800.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fCheckbox2, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(3))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(3))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(3))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(3))
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
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 33
Store = 0
Binop = 16
Numbers = 13
Declare = 24
Cast = 14
Select = 0
Loop = 0
Funcall = 9

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.5f), Select2Inst(CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox1))) Float(2.0f) CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("-", Float(0.0f), BinopInst("*", Float(3.14159274f), CastInst("float", LoadVarInst(struct, fHslider2)))))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fHslider3)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow8, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "float", fSlow9, CastInst("float", LoadVarInst(struct, fHslider5)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", Float(0.5f), BinopInst("-", Float(0.0f), BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("-", LoadVarInst(stack, fSlow9), FunCallInst("max_f", LoadVarInst(stack, fSlow9), CastInst("float", LoadVarInst(struct, fHslider6))))))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider7))))
	DeclareVarInst(stack, "float", fSlow13, FunCallInst("sinf", LoadVarInst(stack, fSlow12)))
	DeclareVarInst(stack, "float", fSlow14, FunCallInst("cosf", LoadVarInst(stack, fSlow12)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow16, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow17, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow18, FunCallInst("mydsp_faustpower4_f", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow19, Select2Inst(CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox2))) BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow2)) LoadVarInst(stack, fSlow2)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 153
Store = 37
Binop = 98
Numbers = 42
Declare = 15
Cast = 5
Select = 0
Loop = 1
Funcall = 8

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp1, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec5[Int32(1)]))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec5[Int32(1)]))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(stack, fSlow10), BinopInst("*", LoadVarInst(stack, fSlow11), BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec5[Int32(0)])))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(stack, fTemp2)))))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec0[Int32(1)]))), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fTemp3)), BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec4[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow16), LoadVarInst(stack, fTemp2)))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec4[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp4)))), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(struct, fRec3[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow17), LoadVarInst(stack, fTemp2)))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fRec2[Int32(2)]))), BinopInst("+", LoadVarInst(struct, fRec3[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp4), LoadVarInst(stack, fTemp5))))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fTemp2)))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec2[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fTemp6)))), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec1[Int32(2)])))))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec1[Int32(0)])), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fTemp6)), LoadVarInst(struct, fRec1[Int32(2)]))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fSlow3))), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(stack, fSlow19))))))
		DeclareVarInst(stack, "float", fTemp7, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp8, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp7)))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("+", LoadVarInst(stack, fSlow10), BinopInst("*", LoadVarInst(stack, fSlow11), BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec6[Int32(0)])))))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("*", LoadVarInst(struct, fRec11[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(stack, fTemp9)))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fTemp8)), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec7[Int32(1)]))), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fTemp10)), BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec11[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("*", LoadVarInst(struct, fRec10[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow16), LoadVarInst(stack, fTemp9)))))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec11[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fTemp11)))), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(struct, fRec10[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("*", LoadVarInst(struct, fRec9[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow17), LoadVarInst(stack, fTemp9)))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec10[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp11), LoadVarInst(stack, fTemp12)))), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec10[Int32(0)]), LoadVarInst(struct, fRec9[Int32(2)])))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fTemp9)))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec9[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp12), LoadVarInst(stack, fTemp13)))), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(struct, fRec8[Int32(2)])))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec8[Int32(0)])), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fTemp13)), LoadVarInst(struct, fRec8[Int32(2)]))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp7) BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fSlow3))), BinopInst("*", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(stack, fSlow19))))))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(2)], LoadVarInst(struct, fRec11[Int32(1)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(2)], LoadVarInst(struct, fRec10[Int32(1)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(2)], LoadVarInst(struct, fRec9[Int32(1)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "mydsp_faustpower4_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fRec1[3])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, float, fRec11[3])
	DeclareVarInst(struct, float, fRec10[3])
	DeclareVarInst(struct, float, fRec9[3])
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, float, fRec7[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(1.5f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(100.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(800.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fCheckbox2, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(3))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(3))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(3))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(3))
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
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.5f), Select2Inst(CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox1))) Float(2.0f) CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("expf", BinopInst("*", LoadVarInst(struct, fConst1), BinopInst("-", Float(0.0f), BinopInst("*", Float(3.14159274f), CastInst("float", LoadVarInst(struct, fHslider2)))))))
	DeclareVarInst(stack, "float", fSlow5, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow4)))
	DeclareVarInst(stack, "float", fSlow6, CastInst("float", LoadVarInst(struct, fHslider3)))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("-", Float(0.0f), BinopInst("*", Float(2.0f), LoadVarInst(stack, fSlow4))))
	DeclareVarInst(stack, "float", fSlow8, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "float", fSlow9, CastInst("float", LoadVarInst(struct, fHslider5)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", Float(0.5f), BinopInst("-", Float(0.0f), BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("-", LoadVarInst(stack, fSlow9), FunCallInst("max_f", LoadVarInst(stack, fSlow9), CastInst("float", LoadVarInst(struct, fHslider6))))))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider7))))
	DeclareVarInst(stack, "float", fSlow13, FunCallInst("sinf", LoadVarInst(stack, fSlow12)))
	DeclareVarInst(stack, "float", fSlow14, FunCallInst("cosf", LoadVarInst(stack, fSlow12)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow13)))
	DeclareVarInst(stack, "float", fSlow16, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow17, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow18, FunCallInst("mydsp_faustpower4_f", LoadVarInst(stack, fSlow8)))
	DeclareVarInst(stack, "float", fSlow19, Select2Inst(CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox2))) BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow2)) LoadVarInst(stack, fSlow2)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp1, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec5[Int32(1)]))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec5[Int32(1)]))), CastInst("float", BinopInst("-", Int32(1), LoadVarInst(struct, iVec0[Int32(1)])))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("+", LoadVarInst(stack, fSlow10), BinopInst("*", LoadVarInst(stack, fSlow11), BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec5[Int32(0)])))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(stack, fTemp2)))))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fTemp1)), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec0[Int32(1)]))), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fTemp3)), BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec4[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(struct, fRec3[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow16), LoadVarInst(stack, fTemp2)))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec4[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp4)))), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(struct, fRec3[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow17), LoadVarInst(stack, fTemp2)))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec3[Int32(0)]), LoadVarInst(struct, fRec2[Int32(2)]))), BinopInst("+", LoadVarInst(struct, fRec3[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp4), LoadVarInst(stack, fTemp5))))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(struct, fRec1[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fTemp2)))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec2[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fTemp6)))), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec2[Int32(0)]), LoadVarInst(struct, fRec1[Int32(2)])))))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec1[Int32(0)])), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fTemp6)), LoadVarInst(struct, fRec1[Int32(2)]))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fSlow3))), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(stack, fSlow19))))))
			DeclareVarInst(stack, "float", fTemp7, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp8, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp7)))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("+", LoadVarInst(stack, fSlow10), BinopInst("*", LoadVarInst(stack, fSlow11), BinopInst("-", Float(1.0f), LoadVarInst(struct, fRec6[Int32(0)])))))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("*", LoadVarInst(struct, fRec11[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow8), LoadVarInst(stack, fTemp9)))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fTemp8)), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec7[Int32(1)]))), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fTemp10)), BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec11[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("*", LoadVarInst(struct, fRec10[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow16), LoadVarInst(stack, fTemp9)))))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec11[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fTemp11)))), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(struct, fRec10[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("*", LoadVarInst(struct, fRec9[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow17), LoadVarInst(stack, fTemp9)))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec10[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp11), LoadVarInst(stack, fTemp12)))), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec10[Int32(0)]), LoadVarInst(struct, fRec9[Int32(2)])))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), FunCallInst("cosf", BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fTemp9)))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec9[Int32(2)]), BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("-", LoadVarInst(stack, fTemp12), LoadVarInst(stack, fTemp13)))), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("-", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(struct, fRec8[Int32(2)])))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow5), LoadVarInst(struct, fRec8[Int32(0)])), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fTemp13)), LoadVarInst(struct, fRec8[Int32(2)]))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp7) BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fSlow3))), BinopInst("*", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(stack, fSlow19))))))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(2)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(2)], LoadVarInst(struct, fRec11[Int32(1)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(2)], LoadVarInst(struct, fRec10[Int32(1)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(2)], LoadVarInst(struct, fRec9[Int32(1)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 184 bytes
Heap size = 196 bytes
Stack size in compute = 112 bytes

