======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenHorizontalBox("mixer")
	OpenVerticalBox("Ch 0")
	AddMetaDeclareInst(fEntry0, "1", "")
	AddMetaDeclareInst(fEntry0, "style", "knob")
	AddNumEntry"pan", fEntry0, 0.0f, -90.0f, 90.0f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider1, "1", "")
	AddVerticalSlider("0x00", fVslider1, 0.0f, -70.0f, 4.0f, 0.100000001f)
	AddMetaDeclareInst(fVbargraph0, "2", "")
	AddMetaDeclareInst(fVbargraph0, "unit", "dB")
	AddVerticalBargraph("0x7f9ac6ee2040", fVbargraph0, -70.0f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox0)
	CloseboxInst
	OpenVerticalBox("Ch 1")
	AddMetaDeclareInst(fEntry1, "1", "")
	AddMetaDeclareInst(fEntry1, "style", "knob")
	AddNumEntry"pan", fEntry1, 0.0f, -90.0f, 90.0f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider2, "1", "")
	AddVerticalSlider("0x00", fVslider2, 0.0f, -70.0f, 4.0f, 0.100000001f)
	AddMetaDeclareInst(fVbargraph1, "2", "")
	AddMetaDeclareInst(fVbargraph1, "unit", "dB")
	AddVerticalBargraph("0x7f9ac6eec140", fVbargraph1, -70.0f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox1)
	CloseboxInst
	OpenVerticalBox("Ch 2")
	AddMetaDeclareInst(fEntry2, "1", "")
	AddMetaDeclareInst(fEntry2, "style", "knob")
	AddNumEntry"pan", fEntry2, 0.0f, -90.0f, 90.0f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider3, "1", "")
	AddVerticalSlider("0x00", fVslider3, 0.0f, -70.0f, 4.0f, 0.100000001f)
	AddMetaDeclareInst(fVbargraph2, "2", "")
	AddMetaDeclareInst(fVbargraph2, "unit", "dB")
	AddVerticalBargraph("0x7f9ac6ef6680", fVbargraph2, -70.0f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox2)
	CloseboxInst
	OpenVerticalBox("Ch 3")
	AddMetaDeclareInst(fEntry3, "1", "")
	AddMetaDeclareInst(fEntry3, "style", "knob")
	AddNumEntry"pan", fEntry3, 0.0f, -90.0f, 90.0f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider4, "1", "")
	AddVerticalSlider("0x00", fVslider4, 0.0f, -70.0f, 4.0f, 0.100000001f)
	AddMetaDeclareInst(fVbargraph3, "2", "")
	AddMetaDeclareInst(fVbargraph3, "unit", "dB")
	AddVerticalBargraph("0x7f9ac8004e00", fVbargraph3, -70.0f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox3)
	CloseboxInst
	OpenVerticalBox("Ch 4")
	AddMetaDeclareInst(fEntry4, "1", "")
	AddMetaDeclareInst(fEntry4, "style", "knob")
	AddNumEntry"pan", fEntry4, 0.0f, -90.0f, 90.0f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider5, "1", "")
	AddVerticalSlider("0x00", fVslider5, 0.0f, -70.0f, 4.0f, 0.100000001f)
	AddMetaDeclareInst(fVbargraph4, "2", "")
	AddMetaDeclareInst(fVbargraph4, "unit", "dB")
	AddVerticalBargraph("0x7f9ac800f8c0", fVbargraph4, -70.0f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox4)
	CloseboxInst
	OpenVerticalBox("Ch 5")
	AddMetaDeclareInst(fEntry5, "1", "")
	AddMetaDeclareInst(fEntry5, "style", "knob")
	AddNumEntry"pan", fEntry5, 0.0f, -90.0f, 90.0f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider6, "1", "")
	AddVerticalSlider("0x00", fVslider6, 0.0f, -70.0f, 4.0f, 0.100000001f)
	AddMetaDeclareInst(fVbargraph5, "2", "")
	AddMetaDeclareInst(fVbargraph5, "unit", "dB")
	AddVerticalBargraph("0x7f9ac801a640", fVbargraph5, -70.0f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox5)
	CloseboxInst
	OpenVerticalBox("Ch 6")
	AddMetaDeclareInst(fEntry6, "1", "")
	AddMetaDeclareInst(fEntry6, "style", "knob")
	AddNumEntry"pan", fEntry6, 0.0f, -90.0f, 90.0f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider7, "1", "")
	AddVerticalSlider("0x00", fVslider7, 0.0f, -70.0f, 4.0f, 0.100000001f)
	AddMetaDeclareInst(fVbargraph6, "2", "")
	AddMetaDeclareInst(fVbargraph6, "unit", "dB")
	AddVerticalBargraph("0x7f9ac8025680", fVbargraph6, -70.0f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox6)
	CloseboxInst
	OpenVerticalBox("Ch 7")
	AddMetaDeclareInst(fEntry7, "1", "")
	AddMetaDeclareInst(fEntry7, "style", "knob")
	AddNumEntry"pan", fEntry7, 0.0f, -90.0f, 90.0f, 1.0f)
	AddMetaDeclareInst(0, "2", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fVslider8, "1", "")
	AddVerticalSlider("0x00", fVslider8, 0.0f, -70.0f, 4.0f, 0.100000001f)
	AddMetaDeclareInst(fVbargraph7, "2", "")
	AddMetaDeclareInst(fVbargraph7, "unit", "dB")
	AddVerticalBargraph("0x7f9ac8030980", fVbargraph7, -70.0f, 5.0f)
	CloseboxInst
	AddCheckButtonInst("mute"fCheckbox7)
	CloseboxInst
	OpenHorizontalBox("stereo out")
	OpenVerticalBox("L")
	AddMetaDeclareInst(fVbargraph8, "2", "")
	AddMetaDeclareInst(fVbargraph8, "unit", "dB")
	AddVerticalBargraph("0x7f9ac8034870", fVbargraph8, -70.0f, 5.0f)
	CloseboxInst
	OpenVerticalBox("R")
	AddMetaDeclareInst(fVbargraph9, "2", "")
	AddMetaDeclareInst(fVbargraph9, "unit", "dB")
	AddVerticalBargraph("0x7f9ac803de10", fVbargraph9, -70.0f, 5.0f)
	CloseboxInst
	AddMetaDeclareInst(fVslider0, "1", "")
	AddVerticalSlider("0x00", fVslider0, 0.0f, -70.0f, 4.0f, 0.100000001f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph0)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry1)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry2)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph2)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry3)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph3)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry4)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph4)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry5)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox5)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph5)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry6)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox6)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph6)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry7)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox7)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph7)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph8)
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph9)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(8))
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
			Case 2
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 3
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 4
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 5
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 6
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 7
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
	StoreVarInst(struct, fConst0, BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l3)], Float(0.0f))
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
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l9)], Float(0.0f))
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
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 51
Store = 0
Binop = 58
Numbers = 67
Declare = 51
Cast = 25
Select = 0
Loop = 0
Funcall = 25

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input6, LoadVarInst(kFunArgs, inputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input7, LoadVarInst(kFunArgs, inputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider0))))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry0)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow1))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider1))))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry1)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow5))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox1))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider2))))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry2)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox2))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider3))))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry3)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow14, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow13))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox3))))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider4))))))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry4)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow18, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow17))))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox4))))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider5))))))
	DeclareVarInst(stack, "float", fSlow21, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry5)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow22, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow21))))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox5))))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider6))))))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry6)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow26, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow25))))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox6))))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider7))))))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry7)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow30, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow29))))
	DeclareVarInst(stack, "float", fSlow31, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox7))))
	DeclareVarInst(stack, "float", fSlow32, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider8))))))
	DeclareVarInst(stack, "float", fSlow33, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow1), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow34, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow5), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow35, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow9), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow36, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow13), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow37, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow17), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow38, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow21), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow39, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow25), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow40, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow29), Float(1.0f))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 142
Store = 51
Binop = 88
Numbers = 69
Declare = 11
Cast = 20
Select = 0
Loop = 1
Funcall = 40

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec1[Int32(1)]))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec3[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("*", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec3[Int32(0)]))))
		StoreVarInst(struct, fRec2[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp0))))
		StoreVarInst(struct, fVbargraph0, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec2[Int32(0)]))))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec5[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("*", CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec5[Int32(0)]))))
		StoreVarInst(struct, fRec4[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp1))))
		StoreVarInst(struct, fVbargraph1, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec4[Int32(0)]))))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow12), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec7[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(stack, fSlow11), BinopInst("*", CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec7[Int32(0)]))))
		StoreVarInst(struct, fRec6[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp2))))
		StoreVarInst(struct, fVbargraph2, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec6[Int32(0)]))))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow16), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec9[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("*", CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec9[Int32(0)]))))
		StoreVarInst(struct, fRec8[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp3))))
		StoreVarInst(struct, fVbargraph3, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec8[Int32(0)]))))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec11[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("*", CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec11[Int32(0)]))))
		StoreVarInst(struct, fRec10[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp4))))
		StoreVarInst(struct, fVbargraph4, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec10[Int32(0)]))))))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow24), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec13[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fSlow23), BinopInst("*", CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec13[Int32(0)]))))
		StoreVarInst(struct, fRec12[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec12[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp5))))
		StoreVarInst(struct, fVbargraph5, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec12[Int32(0)]))))))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow28), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec15[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(stack, fSlow27), BinopInst("*", CastInst("float", LoadVarInst(stack, input6[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec15[Int32(0)]))))
		StoreVarInst(struct, fRec14[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp6))))
		StoreVarInst(struct, fVbargraph6, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec14[Int32(0)]))))))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow32), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec17[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fSlow31), BinopInst("*", CastInst("float", LoadVarInst(stack, input7[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec17[Int32(0)]))))
		StoreVarInst(struct, fRec16[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp7))))
		StoreVarInst(struct, fVbargraph7, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec16[Int32(0)]))))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fTemp0)), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(stack, fTemp1))), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fTemp2))), BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(stack, fTemp3))), BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fTemp4))), BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(stack, fTemp5))), BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(stack, fTemp6))), BinopInst("*", LoadVarInst(stack, fSlow30), LoadVarInst(stack, fTemp7)))))
		StoreVarInst(struct, fRec0[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp8))))
		StoreVarInst(struct, fVbargraph8, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec0[Int32(0)]))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp8)))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow33), LoadVarInst(stack, fTemp0)), BinopInst("*", LoadVarInst(stack, fSlow34), LoadVarInst(stack, fTemp1))), BinopInst("*", LoadVarInst(stack, fSlow35), LoadVarInst(stack, fTemp2))), BinopInst("*", LoadVarInst(stack, fSlow36), LoadVarInst(stack, fTemp3))), BinopInst("*", LoadVarInst(stack, fSlow37), LoadVarInst(stack, fTemp4))), BinopInst("*", LoadVarInst(stack, fSlow38), LoadVarInst(stack, fTemp5))), BinopInst("*", LoadVarInst(stack, fSlow39), LoadVarInst(stack, fTemp6))), BinopInst("*", LoadVarInst(stack, fSlow40), LoadVarInst(stack, fTemp7)))))
		StoreVarInst(struct, fRec18[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec18[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp9))))
		StoreVarInst(struct, fVbargraph9, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec18[Int32(0)]))))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp9)))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "log10f", "float", dummy0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph0)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry1)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry2)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph2)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry3)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox3)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph3)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry4)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox4)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph4)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry5)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox5)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph5)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry6)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox6)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph6)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry7)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox7)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph7)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph8)
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph9)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fEntry7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l3)], Float(0.0f))
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
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l9)], Float(0.0f))
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
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input6, LoadVarInst(kFunArgs, inputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input7, LoadVarInst(kFunArgs, inputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider0))))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry0)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow2, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow1))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider1))))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry1)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow5))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox1))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider2))))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry2)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow10, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox2))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider3))))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry3)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow14, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow13))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox3))))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider4))))))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry4)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow18, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow17))))
	DeclareVarInst(stack, "float", fSlow19, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox4))))
	DeclareVarInst(stack, "float", fSlow20, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider5))))))
	DeclareVarInst(stack, "float", fSlow21, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry5)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow22, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow21))))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox5))))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider6))))))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry6)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow26, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow25))))
	DeclareVarInst(stack, "float", fSlow27, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox6))))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider7))))))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("*", Float(0.00555555569f), BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry7)), Float(-90.0f))))
	DeclareVarInst(stack, "float", fSlow30, FunCallInst("sqrtf", BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow29))))
	DeclareVarInst(stack, "float", fSlow31, BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(struct, fCheckbox7))))
	DeclareVarInst(stack, "float", fSlow32, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fVslider8))))))
	DeclareVarInst(stack, "float", fSlow33, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow1), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow34, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow5), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow35, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow9), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow36, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow13), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow37, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow17), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow38, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow21), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow39, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow25), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow40, FunCallInst("sqrtf", BinopInst("+", LoadVarInst(stack, fSlow29), Float(1.0f))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec1[Int32(1)]))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec3[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("*", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec3[Int32(0)]))))
			StoreVarInst(struct, fRec2[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp0))))
			StoreVarInst(struct, fVbargraph0, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec2[Int32(0)]))))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec5[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("*", CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec5[Int32(0)]))))
			StoreVarInst(struct, fRec4[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp1))))
			StoreVarInst(struct, fVbargraph1, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec4[Int32(0)]))))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow12), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec7[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(stack, fSlow11), BinopInst("*", CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec7[Int32(0)]))))
			StoreVarInst(struct, fRec6[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp2))))
			StoreVarInst(struct, fVbargraph2, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec6[Int32(0)]))))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow16), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec9[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("*", CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec9[Int32(0)]))))
			StoreVarInst(struct, fRec8[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp3))))
			StoreVarInst(struct, fVbargraph3, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec8[Int32(0)]))))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow20), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec11[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("*", LoadVarInst(stack, fSlow19), BinopInst("*", CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec11[Int32(0)]))))
			StoreVarInst(struct, fRec10[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp4))))
			StoreVarInst(struct, fVbargraph4, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec10[Int32(0)]))))))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow24), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec13[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fSlow23), BinopInst("*", CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec13[Int32(0)]))))
			StoreVarInst(struct, fRec12[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec12[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp5))))
			StoreVarInst(struct, fVbargraph5, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec12[Int32(0)]))))))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow28), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec15[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(stack, fSlow27), BinopInst("*", CastInst("float", LoadVarInst(stack, input6[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec15[Int32(0)]))))
			StoreVarInst(struct, fRec14[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp6))))
			StoreVarInst(struct, fVbargraph6, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec14[Int32(0)]))))))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow32), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec17[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fSlow31), BinopInst("*", CastInst("float", LoadVarInst(stack, input7[LoadVarInst(loop, i)])), LoadVarInst(struct, fRec17[Int32(0)]))))
			StoreVarInst(struct, fRec16[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp7))))
			StoreVarInst(struct, fVbargraph7, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec16[Int32(0)]))))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fTemp0)), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(stack, fTemp1))), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fTemp2))), BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(stack, fTemp3))), BinopInst("*", LoadVarInst(stack, fSlow18), LoadVarInst(stack, fTemp4))), BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(stack, fTemp5))), BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(stack, fTemp6))), BinopInst("*", LoadVarInst(stack, fSlow30), LoadVarInst(stack, fTemp7)))))
			StoreVarInst(struct, fRec0[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp8))))
			StoreVarInst(struct, fVbargraph8, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec0[Int32(0)]))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp8)))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow33), LoadVarInst(stack, fTemp0)), BinopInst("*", LoadVarInst(stack, fSlow34), LoadVarInst(stack, fTemp1))), BinopInst("*", LoadVarInst(stack, fSlow35), LoadVarInst(stack, fTemp2))), BinopInst("*", LoadVarInst(stack, fSlow36), LoadVarInst(stack, fTemp3))), BinopInst("*", LoadVarInst(stack, fSlow37), LoadVarInst(stack, fTemp4))), BinopInst("*", LoadVarInst(stack, fSlow38), LoadVarInst(stack, fTemp5))), BinopInst("*", LoadVarInst(stack, fSlow39), LoadVarInst(stack, fTemp6))), BinopInst("*", LoadVarInst(stack, fSlow40), LoadVarInst(stack, fTemp7)))))
			StoreVarInst(struct, fRec18[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec18[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", LoadVarInst(stack, fTemp9))))
			StoreVarInst(struct, fVbargraph9, CastInst("FAUSTFLOAT", BinopInst("*", Float(20.0f), FunCallInst("log10f", FunCallInst("max_f", Float(0.000316227757f), LoadVarInst(struct, fRec18[Int32(0)]))))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp9)))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 296 bytes
Heap size = 300 bytes
Stack size in compute = 244 bytes

