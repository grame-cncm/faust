======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "tooltip", "See Faust's   vaeffects.lib for info and references")
	OpenHorizontalBox("MOOG VCF (Voltage Controlled Filter)")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("0x00")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When this is checked, the Moog VCF   has no effect")
	AddCheckButtonInst("Bypass"fCheckbox0)
	AddMetaDeclareInst(fCheckbox1, "1", "")
	AddMetaDeclareInst(fCheckbox1, "tooltip", "Select moog_vcf_2b (two-biquad)   implementation, instead of the default moog_vcf (analog style) implementation")
	AddCheckButtonInst("Use Biquads"fCheckbox1)
	AddMetaDeclareInst(fCheckbox2, "2", "")
	AddMetaDeclareInst(fCheckbox2, "tooltip", "If using biquads, make   them normalized ladders (moog_vcf_2bn)")
	AddCheckButtonInst("Normalized Ladders"fCheckbox2)
	CloseboxInst
	AddMetaDeclareInst(fHslider2, "1", "")
	AddMetaDeclareInst(fHslider2, "tooltip", "The VCF resonates   at the corner frequency (specified in PianoKey (PK) units, with A440 = 49 PK).   The VCF response is flat below the corner frequency, and rolls off -24 dB per   octave above.")
	AddMetaDeclareInst(fHslider2, "unit", "PK")
	AddHorizontalSlider("Corner Frequency", fHslider2, 25.0f, 1.0f, 88.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider1, "2", "")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "tooltip", "Amount of   resonance near VCF corner frequency (specified between 0 and 1)")
	AddHorizontalSlider("Corner Resonance", fHslider1, 0.899999976f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider0, "3", "")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddMetaDeclareInst(fHslider0, "tooltip", "output level in decibels")
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("VCF Output Level", fHslider0, 5.0f, -60.0f, 20.0f, 0.100000001f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower4_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, float, fRec7[3])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec13[2])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
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
			Case 0
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
	StoreVarInst(struct, fConst2, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.90000000000000002f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(25.0f)))
	StoreVarInst(struct, fCheckbox2, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
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
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
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
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 23
Store = 0
Binop = 20
Numbers = 22
Declare = 20
Cast = 9
Select = 0
Loop = 0
Funcall = 7

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))))
	DeclareVarInst(stack, "int", iSlow2, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox1))))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("-", Float(0.0f), BinopInst("*", Float(4.0f), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", FunCallInst("mydsp_faustpower4_f", LoadVarInst(stack, fSlow3)), Float(0.999998987f))))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.439999998f), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", CastInst("float", LoadVarInst(struct, fHslider2)), Float(-49.0f))))))
	DeclareVarInst(stack, "int", iSlow6, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox2))))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("min_f", Float(1.41419947f), BinopInst("*", Float(1.41421354f), LoadVarInst(stack, fSlow3))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("+", LoadVarInst(stack, fSlow7), Float(1.41421354f))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(1.41421354f), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("+", LoadVarInst(stack, fSlow9), Float(2.0f)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("+", LoadVarInst(stack, fSlow7), Float(-1.41421354f))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("-", Float(2.0f), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", Float(1.99997997f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow14, FunCallInst("mydsp_faustpower2_f", BinopInst("*", Float(1.41419947f), LoadVarInst(stack, fSlow3))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("+", LoadVarInst(stack, fSlow13), LoadVarInst(stack, fSlow14)))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("+", LoadVarInst(stack, fSlow13), Float(2.0f)))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("-", Float(2.0f), LoadVarInst(stack, fSlow13)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 199
Store = 32
Binop = 162
Numbers = 91
Declare = 40
Cast = 2
Select = 0
Loop = 1
Funcall = 32

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp1, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec6[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec6[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp2)))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(struct, fRec5[Int32(1)])))))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", LoadVarInst(struct, fRec5[Int32(0)]), BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(struct, fRec4[Int32(1)]))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(struct, fRec4[Int32(0)]), BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(struct, fRec3[Int32(1)]))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(struct, fRec3[Int32(0)]), BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp3))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), FunCallInst("powf", LoadVarInst(stack, fTemp2), Float(4.0f))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec9[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp4, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst2), FunCallInst("max_f", Float(20.0f), FunCallInst("min_f", Float(10000.0f), LoadVarInst(struct, fRec9[Int32(0)]))))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp4)))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp4)))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fTemp5)), LoadVarInst(stack, fTemp4)), Float(1.0f))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec8[Int32(2)]), BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fSlow10)), LoadVarInst(stack, fTemp4)), Float(1.0f)))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(stack, fSlow8), LoadVarInst(stack, fTemp6))))), LoadVarInst(stack, fTemp7))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(stack, fSlow11), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow12), LoadVarInst(stack, fTemp5)), LoadVarInst(stack, fTemp4)), Float(1.0f))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", BinopInst("/", BinopInst("+", LoadVarInst(struct, fRec8[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec8[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec8[Int32(1)])))), LoadVarInst(stack, fTemp7)), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec7[Int32(2)]), BinopInst("+", LoadVarInst(stack, fSlow11), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fSlow12)), LoadVarInst(stack, fTemp4)), Float(1.0f)))), BinopInst("*", Float(2.0f), BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow11), LoadVarInst(stack, fTemp6)), LoadVarInst(struct, fRec7[Int32(1)])))), LoadVarInst(stack, fTemp8))))
		DeclareVarInst(stack, "float", fTemp9, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst2), FunCallInst("max_f", LoadVarInst(struct, fRec9[Int32(0)]), Float(20.0f)))))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp9)))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(stack, fSlow15), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow16), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp9)), Float(1.0f))))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow15), BinopInst("-", Float(1.0f), BinopInst("/", BinopInst("-", LoadVarInst(stack, fSlow16), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp9)))), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "float", fTemp13, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "float", fTemp15, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp14))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec10[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13))), BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp15))))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp9)))))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("+", LoadVarInst(stack, fSlow15), LoadVarInst(stack, fTemp17)))
		DeclareVarInst(stack, "float", fTemp19, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(stack, fTemp18), BinopInst("*", LoadVarInst(stack, fTemp11), BinopInst("+", LoadVarInst(stack, fTemp12), Float(1.0f))))))))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp19))))
		DeclareVarInst(stack, "float", fTemp21, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp20))))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp19))), BinopInst("*", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fTemp21))))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fTemp19)), BinopInst("*", LoadVarInst(struct, fRec12[Int32(1)]), LoadVarInst(stack, fTemp21))))
		DeclareVarInst(stack, "float", fRec11, LoadVarInst(struct, fRec12[Int32(0)]))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(stack, fTemp18), LoadVarInst(stack, fTemp11))))
		DeclareVarInst(stack, "float", fTemp23, FunCallInst("sqrtf", LoadVarInst(stack, fTemp14)))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp13)), BinopInst("*", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(stack, fTemp15))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec10[Int32(0)]), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec11), BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp12)), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp22))))), BinopInst("*", LoadVarInst(stack, fTemp23), FunCallInst("sqrtf", LoadVarInst(stack, fTemp20))))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow17), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp9)), Float(1.0f)), LoadVarInst(stack, fSlow13))))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fSlow17)), LoadVarInst(stack, fTemp9)), Float(1.0f)), LoadVarInst(stack, fSlow13))), LoadVarInst(stack, fTemp25)))
		DeclareVarInst(stack, "float", fTemp27, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), LoadVarInst(stack, fTemp26))))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp27))))
		DeclareVarInst(stack, "float", fTemp29, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp28))))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec13[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp27))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp29)), LoadVarInst(stack, fTemp11))))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("-", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fSlow13))))
		DeclareVarInst(stack, "float", fTemp32, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(stack, fTemp31), BinopInst("*", LoadVarInst(stack, fTemp25), BinopInst("+", LoadVarInst(stack, fTemp26), Float(1.0f))))))))
		DeclareVarInst(stack, "float", fTemp33, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp32))))
		DeclareVarInst(stack, "float", fTemp34, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp33))))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec15[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp32))), BinopInst("*", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp34))))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp32)), BinopInst("*", LoadVarInst(struct, fRec15[Int32(1)]), LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fRec14, LoadVarInst(struct, fRec15[Int32(0)]))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(stack, fTemp31), LoadVarInst(stack, fTemp25))))
		DeclareVarInst(stack, "float", fTemp36, FunCallInst("sqrtf", LoadVarInst(stack, fTemp28)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), Select2Inst(LoadVarInst(stack, iSlow2) Select2Inst(LoadVarInst(stack, iSlow6) BinopInst("/", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp27)), LoadVarInst(stack, fTemp11)), BinopInst("*", LoadVarInst(struct, fRec13[Int32(1)]), LoadVarInst(stack, fTemp29))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp36)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec14), BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp26)), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(stack, fTemp32), LoadVarInst(stack, fTemp35))))), BinopInst("*", LoadVarInst(stack, fTemp36), FunCallInst("sqrtf", LoadVarInst(stack, fTemp33))))), LoadVarInst(stack, fTemp25)) BinopInst("/", BinopInst("+", LoadVarInst(struct, fRec7[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec7[Int32(1)])))), LoadVarInst(stack, fTemp8))) LoadVarInst(struct, fRec1[Int32(0)]))))))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(2)], LoadVarInst(struct, fRec7[Int32(1)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower4_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec8[3])
	DeclareVarInst(struct, float, fRec7[3])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec13[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(6.28318548f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.90000000000000002f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(25.0f)))
	StoreVarInst(struct, fCheckbox2, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
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
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(3))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
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
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "int", iSlow0, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))))
	DeclareVarInst(stack, "int", iSlow2, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox1))))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("-", Float(0.0f), BinopInst("*", Float(4.0f), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", FunCallInst("mydsp_faustpower4_f", LoadVarInst(stack, fSlow3)), Float(0.999998987f))))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(0.439999998f), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", CastInst("float", LoadVarInst(struct, fHslider2)), Float(-49.0f))))))
	DeclareVarInst(stack, "int", iSlow6, CastInst("int", CastInst("float", LoadVarInst(struct, fCheckbox2))))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("min_f", Float(1.41419947f), BinopInst("*", Float(1.41421354f), LoadVarInst(stack, fSlow3))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("+", LoadVarInst(stack, fSlow7), Float(1.41421354f))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("*", Float(1.41421354f), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("+", LoadVarInst(stack, fSlow9), Float(2.0f)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", LoadVarInst(stack, fSlow7), BinopInst("+", LoadVarInst(stack, fSlow7), Float(-1.41421354f))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("-", Float(2.0f), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", Float(1.99997997f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow14, FunCallInst("mydsp_faustpower2_f", BinopInst("*", Float(1.41419947f), LoadVarInst(stack, fSlow3))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("+", LoadVarInst(stack, fSlow13), LoadVarInst(stack, fSlow14)))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("+", LoadVarInst(stack, fSlow13), Float(2.0f)))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("-", Float(2.0f), LoadVarInst(stack, fSlow13)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp1, Select2Inst(LoadVarInst(stack, iSlow0) Float(0.0f) LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec6[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec6[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp2)))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(struct, fRec5[Int32(1)])))))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", LoadVarInst(struct, fRec5[Int32(0)]), BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(struct, fRec4[Int32(1)]))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(struct, fRec4[Int32(0)]), BinopInst("*", LoadVarInst(stack, fTemp3), LoadVarInst(struct, fRec3[Int32(1)]))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(struct, fRec3[Int32(0)]), BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(stack, fTemp3))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), FunCallInst("powf", LoadVarInst(stack, fTemp2), Float(4.0f))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec9[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp4, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst2), FunCallInst("max_f", Float(20.0f), FunCallInst("min_f", Float(10000.0f), LoadVarInst(struct, fRec9[Int32(0)]))))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp4)))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp4)))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow10), LoadVarInst(stack, fTemp5)), LoadVarInst(stack, fTemp4)), Float(1.0f))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec8[Int32(2)]), BinopInst("+", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fSlow10)), LoadVarInst(stack, fTemp4)), Float(1.0f)))), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec8[Int32(1)]), BinopInst("+", LoadVarInst(stack, fSlow8), LoadVarInst(stack, fTemp6))))), LoadVarInst(stack, fTemp7))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(stack, fSlow11), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow12), LoadVarInst(stack, fTemp5)), LoadVarInst(stack, fTemp4)), Float(1.0f))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", BinopInst("/", BinopInst("+", LoadVarInst(struct, fRec8[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec8[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec8[Int32(1)])))), LoadVarInst(stack, fTemp7)), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec7[Int32(2)]), BinopInst("+", LoadVarInst(stack, fSlow11), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fSlow12)), LoadVarInst(stack, fTemp4)), Float(1.0f)))), BinopInst("*", Float(2.0f), BinopInst("*", BinopInst("+", LoadVarInst(stack, fSlow11), LoadVarInst(stack, fTemp6)), LoadVarInst(struct, fRec7[Int32(1)])))), LoadVarInst(stack, fTemp8))))
			DeclareVarInst(stack, "float", fTemp9, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst2), FunCallInst("max_f", LoadVarInst(struct, fRec9[Int32(0)]), Float(20.0f)))))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp9)))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(stack, fSlow15), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow16), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp9)), Float(1.0f))))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow15), BinopInst("-", Float(1.0f), BinopInst("/", BinopInst("-", LoadVarInst(stack, fSlow16), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp9)))), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "float", fTemp13, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "float", fTemp15, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp14))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec10[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13))), BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp15))))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp9)))))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("+", LoadVarInst(stack, fSlow15), LoadVarInst(stack, fTemp17)))
			DeclareVarInst(stack, "float", fTemp19, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(stack, fTemp18), BinopInst("*", LoadVarInst(stack, fTemp11), BinopInst("+", LoadVarInst(stack, fTemp12), Float(1.0f))))))))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp19))))
			DeclareVarInst(stack, "float", fTemp21, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp20))))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec12[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp19))), BinopInst("*", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fTemp21))))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fTemp19)), BinopInst("*", LoadVarInst(struct, fRec12[Int32(1)]), LoadVarInst(stack, fTemp21))))
			DeclareVarInst(stack, "float", fRec11, LoadVarInst(struct, fRec12[Int32(0)]))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(stack, fTemp18), LoadVarInst(stack, fTemp11))))
			DeclareVarInst(stack, "float", fTemp23, FunCallInst("sqrtf", LoadVarInst(stack, fTemp14)))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp13)), BinopInst("*", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(stack, fTemp15))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec10[Int32(0)]), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec11), BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp12)), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp22))))), BinopInst("*", LoadVarInst(stack, fTemp23), FunCallInst("sqrtf", LoadVarInst(stack, fTemp20))))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow17), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp9)), Float(1.0f)), LoadVarInst(stack, fSlow13))))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("-", BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fSlow17)), LoadVarInst(stack, fTemp9)), Float(1.0f)), LoadVarInst(stack, fSlow13))), LoadVarInst(stack, fTemp25)))
			DeclareVarInst(stack, "float", fTemp27, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), LoadVarInst(stack, fTemp26))))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp27))))
			DeclareVarInst(stack, "float", fTemp29, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp28))))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec13[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp27))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp29)), LoadVarInst(stack, fTemp11))))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("-", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fSlow13))))
			DeclareVarInst(stack, "float", fTemp32, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(stack, fTemp31), BinopInst("*", LoadVarInst(stack, fTemp25), BinopInst("+", LoadVarInst(stack, fTemp26), Float(1.0f))))))))
			DeclareVarInst(stack, "float", fTemp33, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp32))))
			DeclareVarInst(stack, "float", fTemp34, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp33))))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec15[Int32(1)]), BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp32))), BinopInst("*", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp34))))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp32)), BinopInst("*", LoadVarInst(struct, fRec15[Int32(1)]), LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fRec14, LoadVarInst(struct, fRec15[Int32(0)]))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(stack, fTemp31), LoadVarInst(stack, fTemp25))))
			DeclareVarInst(stack, "float", fTemp36, FunCallInst("sqrtf", LoadVarInst(stack, fTemp28)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", Select2Inst(LoadVarInst(stack, iSlow0) LoadVarInst(stack, fTemp0) BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), Select2Inst(LoadVarInst(stack, iSlow2) Select2Inst(LoadVarInst(stack, iSlow6) BinopInst("/", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp27)), LoadVarInst(stack, fTemp11)), BinopInst("*", LoadVarInst(struct, fRec13[Int32(1)]), LoadVarInst(stack, fTemp29))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp36)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec14), BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp26)), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(stack, fTemp32), LoadVarInst(stack, fTemp35))))), BinopInst("*", LoadVarInst(stack, fTemp36), FunCallInst("sqrtf", LoadVarInst(stack, fTemp33))))), LoadVarInst(stack, fTemp25)) BinopInst("/", BinopInst("+", LoadVarInst(struct, fRec7[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec7[Int32(1)])))), LoadVarInst(stack, fTemp8))) LoadVarInst(struct, fRec1[Int32(0)]))))))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(2)], LoadVarInst(struct, fRec7[Int32(1)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 156 bytes
Heap size = 160 bytes
Stack size in compute = 88 bytes

