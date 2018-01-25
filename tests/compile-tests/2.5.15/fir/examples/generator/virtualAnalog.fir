======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "0", "")
	AddMetaDeclareInst(0, "tooltip", "See Faust's oscillators.lib for documentation and references")
	OpenVerticalBox("VIRTUAL ANALOG OSCILLATORS")
	AddMetaDeclareInst(0, "0", "")
	OpenHorizontalBox("Signal Levels")
	AddMetaDeclareInst(fVslider1, "0", "")
	AddMetaDeclareInst(fVslider1, "style", "vslider")
	AddVerticalSlider("Sawtooth", fVslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(0, "1", "")
	OpenVerticalBox("Pulse Train")
	AddMetaDeclareInst(fCheckbox0, "0", "")
	AddMetaDeclareInst(fCheckbox0, "tooltip", "When checked, use 3rd-order aliasing suppression (up from 2)  See if you can hear a difference with the freq high and swept")
	AddCheckButtonInst("Order 3"fCheckbox0)
	AddMetaDeclareInst(fVslider7, "1", "")
	AddMetaDeclareInst(fVslider7, "style", "vslider")
	AddVerticalSlider("0x00", fVslider7, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fVslider8, "2", "")
	AddMetaDeclareInst(fVslider8, "style", "knob")
	AddVerticalSlider("Duty Cycle", fVslider8, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(fVslider5, "2", "")
	AddMetaDeclareInst(fVslider5, "style", "vslider")
	AddVerticalSlider("Square", fVslider5, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fVslider6, "3", "")
	AddMetaDeclareInst(fVslider6, "style", "vslider")
	AddVerticalSlider("Triangle", fVslider6, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fVslider9, "4", "")
	AddMetaDeclareInst(fVslider9, "style", "vslider")
	AddMetaDeclareInst(fVslider9, "tooltip", "Pink Noise (or 1/f noise) is   Constant-Q Noise, meaning that it has the same total power in every octave   (uses only amplitude controls)")
	AddVerticalSlider("Pink Noise", fVslider9, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fVslider0, "5", "")
	AddMetaDeclareInst(fVslider0, "style", "vslider")
	AddVerticalSlider("Ext Input", fVslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(0, "1", "")
	OpenHorizontalBox("Signal Parameters")
	AddMetaDeclareInst(0, "0", "")
	OpenVerticalBox("0x00")
	AddMetaDeclareInst(fHslider0, "1", "")
	AddMetaDeclareInst(fHslider0, "style", "hslider")
	AddMetaDeclareInst(fHslider0, "tooltip", "Sawtooth waveform amplitude")
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("Mix Amplitude", fHslider0, -20.0f, -120.0f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider1, "2", "")
	AddMetaDeclareInst(fHslider1, "style", "hslider")
	AddMetaDeclareInst(fHslider1, "tooltip", "Sawtooth   frequency as a Piano Key (PK) number (A440 = key 49)")
	AddMetaDeclareInst(fHslider1, "unit", "PK")
	AddHorizontalSlider("Frequency", fHslider1, 49.0f, 1.0f, 88.0f, 0.00999999978f)
	CloseboxInst
	AddMetaDeclareInst(fVslider3, "3", "")
	AddMetaDeclareInst(fVslider3, "style", "knob")
	AddMetaDeclareInst(fVslider3, "tooltip", "Percentange frequency-shift up or down for second oscillator")
	AddMetaDeclareInst(fVslider3, "unit", "%%")
	AddVerticalSlider("Detuning 1", fVslider3, -0.100000001f, -10.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fVslider4, "4", "")
	AddMetaDeclareInst(fVslider4, "style", "knob")
	AddMetaDeclareInst(fVslider4, "tooltip", "Percentange frequency-shift up or down for third detuned oscillator")
	AddMetaDeclareInst(fVslider4, "unit", "%%")
	AddVerticalSlider("Detuning 2", fVslider4, 0.100000001f, -10.0f, 10.0f, 0.00999999978f)
	AddMetaDeclareInst(fVslider2, "5", "")
	AddMetaDeclareInst(fVslider2, "scale", "log")
	AddMetaDeclareInst(fVslider2, "style", "knob")
	AddMetaDeclareInst(fVslider2, "tooltip", "Portamento (frequency-glide) time-constant in seconds")
	AddMetaDeclareInst(fVslider2, "unit", "sec")
	AddVerticalSlider("Portamento", fVslider2, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f)
	AddMetaDeclareInst(fEntry0, "6", "")
	AddMetaDeclareInst(fEntry0, "tooltip", "Order of sawtooth aliasing  suppression")
	AddNumEntry"Saw Order", fEntry0, 2.0f, 1.0f, 4.0f, 1.0f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iVec0[4])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, float, fVec5[2])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, float, fVec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fVec8[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fVec9[2])
	DeclareVarInst(struct, float, fVec10[2])
	DeclareVarInst(struct, float, fVec11[2])
	DeclareVarInst(struct, float, fVec12[2])
	DeclareVarInst(struct, float, fVec13[2])
	DeclareVarInst(struct, float, fVec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, float, fVec15[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fVec16[2])
	DeclareVarInst(struct, float, fVec17[2])
	DeclareVarInst(struct, float, fVec18[2])
	DeclareVarInst(struct, float, fVec19[2])
	DeclareVarInst(struct, float, fVec20[2])
	DeclareVarInst(struct, float, fVec21[2])
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, float, fVec22[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fVec23[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec24[4096])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, float, fVec25[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fVec26[2])
	DeclareVarInst(struct, float, fVec27[4096])
	DeclareVarInst(struct, float, fVec28[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fVec29[2])
	DeclareVarInst(struct, float, fVec30[4096])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, float, fVec31[2])
	DeclareVarInst(struct, float, fVec32[2])
	DeclareVarInst(struct, float, fVec33[4096])
	DeclareVarInst(struct, float, fVec34[2])
	DeclareVarInst(struct, float, fVec35[2])
	DeclareVarInst(struct, float, fVec36[4096])
	DeclareVarInst(struct, float, fVec37[2])
	DeclareVarInst(struct, float, fVec38[2])
	DeclareVarInst(struct, float, fVec39[4096])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, int, iRec13[2])
	DeclareVarInst(struct, float, fRec12[4])
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.25f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.0416666679f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.00520833349f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst5, BinopInst("*", Float(0.0833333358f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, BinopInst("*", Float(0.5f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.33333337f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst8, BinopInst("*", Float(0.013888889f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(-20.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(49.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(-0.10000000000000001f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(4))
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
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l1)], Float(0.0f))
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
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec14[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec15[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec16[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec17[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec18[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec19[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec20[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec21[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec22[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec23[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(4096))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec24[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec25[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec26[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(4096))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec27[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec28[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec29[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(4096))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec30[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(2))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(2))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(2))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec31[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(2))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec32[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(4096))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec33[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec34[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(2))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec35[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(4096))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec36[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec37[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec38[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(4096))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec39[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec13[LoadVarInst(loop, l52)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(4))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 27
Store = 0
Binop = 25
Numbers = 21
Declare = 21
Cast = 15
Select = 0
Loop = 0
Funcall = 3

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fVslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.333333343f), CastInst("float", LoadVarInst(struct, fVslider1))))
	DeclareVarInst(stack, "int", iSlow3, CastInst("int", BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry0)), Float(-1.0f))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst(">=", LoadVarInst(stack, iSlow3), Int32(2)))
	DeclareVarInst(stack, "int", iSlow5, BinopInst(">=", LoadVarInst(stack, iSlow3), Int32(1)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fVslider2))))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(440.0f), BinopInst("*", FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", CastInst("float", LoadVarInst(struct, fHslider1)), Float(-49.0f)))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow6)))))
	DeclareVarInst(stack, "int", iSlow8, BinopInst(">=", LoadVarInst(stack, iSlow3), Int32(3)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("-", Float(1.0f), BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fVslider3)))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("+", BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fVslider4))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", LoadVarInst(struct, fConst5), CastInst("float", LoadVarInst(struct, fVslider5))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", LoadVarInst(struct, fConst7), CastInst("float", LoadVarInst(struct, fVslider6))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fVslider7))))
	DeclareVarInst(stack, "float", fSlow14, CastInst("float", LoadVarInst(struct, fCheckbox0)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("*", Float(0.0833333358f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow14))))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fVslider8))))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(stack, fSlow14)))
	DeclareVarInst(stack, "float", fSlow18, CastInst("float", LoadVarInst(struct, fVslider9)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 443
Store = 107
Binop = 278
Numbers = 182
Declare = 95
Cast = 24
Select = 0
Loop = 3
Funcall = 51

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec2[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(struct, fRec2[Int32(0)]))))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp0))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec1[Int32(1)]))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), FunCallInst("floorf", LoadVarInst(stack, fTemp1))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec1[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.0f)))
		DeclareVarInst(stack, "float", fTemp4, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp3)))
		StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp4))
		DeclareVarInst(stack, "float", fTemp5, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp3)))
		StoreVarInst(struct, fVec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp2))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp2), LoadVarInst(struct, fVec3[Int32(1)])))), LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fVec4[Int32(0)], LoadVarInst(stack, fTemp6))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fTemp4), BinopInst("+", LoadVarInst(stack, fTemp4), Float(-2.0f))))
		StoreVarInst(struct, fVec5[Int32(0)], LoadVarInst(stack, fTemp7))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fVec5[Int32(1)])), LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fVec6[Int32(0)], LoadVarInst(stack, fTemp8))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec6[Int32(1)])), LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fVec7[Int32(0)], LoadVarInst(stack, fTemp9))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec2[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp11, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp10))))
		StoreVarInst(struct, fVec8[Int32(0)], LoadVarInst(stack, fTemp11))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec8[Int32(1)]))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp12), FunCallInst("floorf", LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec3[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(stack, fTemp13), Float(-1.0f)))
		DeclareVarInst(stack, "float", fTemp15, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp14)))
		StoreVarInst(struct, fVec9[Int32(0)], LoadVarInst(stack, fTemp15))
		DeclareVarInst(stack, "float", fTemp16, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp14)))
		StoreVarInst(struct, fVec10[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp16), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp16), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp13), LoadVarInst(struct, fVec10[Int32(1)])))), LoadVarInst(stack, fTemp11)))
		StoreVarInst(struct, fVec11[Int32(0)], LoadVarInst(stack, fTemp17))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", LoadVarInst(stack, fTemp15), Float(-2.0f))))
		StoreVarInst(struct, fVec12[Int32(0)], LoadVarInst(stack, fTemp18))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp18), LoadVarInst(struct, fVec12[Int32(1)])), LoadVarInst(stack, fTemp11)))
		StoreVarInst(struct, fVec13[Int32(0)], LoadVarInst(stack, fTemp19))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp19), LoadVarInst(struct, fVec13[Int32(1)])), LoadVarInst(stack, fTemp11)))
		StoreVarInst(struct, fVec14[Int32(0)], LoadVarInst(stack, fTemp20))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec2[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp22, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp21))))
		StoreVarInst(struct, fVec15[Int32(0)], LoadVarInst(stack, fTemp22))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec15[Int32(1)]))))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp23), FunCallInst("floorf", LoadVarInst(stack, fTemp23))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec4[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("+", LoadVarInst(stack, fTemp24), Float(-1.0f)))
		DeclareVarInst(stack, "float", fTemp26, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp25)))
		StoreVarInst(struct, fVec16[Int32(0)], LoadVarInst(stack, fTemp26))
		DeclareVarInst(stack, "float", fTemp27, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp25)))
		StoreVarInst(struct, fVec17[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp24))))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp24), LoadVarInst(struct, fVec17[Int32(1)])))), LoadVarInst(stack, fTemp22)))
		StoreVarInst(struct, fVec18[Int32(0)], LoadVarInst(stack, fTemp28))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("*", LoadVarInst(stack, fTemp26), BinopInst("+", LoadVarInst(stack, fTemp26), Float(-2.0f))))
		StoreVarInst(struct, fVec19[Int32(0)], LoadVarInst(stack, fTemp29))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp29), LoadVarInst(struct, fVec19[Int32(1)])), LoadVarInst(stack, fTemp22)))
		StoreVarInst(struct, fVec20[Int32(0)], LoadVarInst(stack, fTemp30))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp30), LoadVarInst(struct, fVec20[Int32(1)])), LoadVarInst(stack, fTemp22)))
		StoreVarInst(struct, fVec21[Int32(0)], LoadVarInst(stack, fTemp31))
		DeclareVarInst(stack, "float", fTemp32, FunCallInst("max_f", LoadVarInst(struct, fRec2[Int32(0)]), Float(23.4489498f)))
		DeclareVarInst(stack, "float", fTemp33, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp32))))
		StoreVarInst(struct, fVec22[Int32(0)], LoadVarInst(stack, fTemp33))
		DeclareVarInst(stack, "float", fTemp34, BinopInst("+", LoadVarInst(struct, fRec5[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec22[Int32(1)]))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp34), FunCallInst("floorf", LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec5[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(stack, fTemp35), Float(-1.0f)))
		DeclareVarInst(stack, "float", fTemp37, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp36)))
		StoreVarInst(struct, fVec23[Int32(0)], LoadVarInst(stack, fTemp37))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp37), LoadVarInst(struct, fVec23[Int32(1)]))), LoadVarInst(stack, fTemp33)))
		StoreVarInst(struct, fVec24[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp38))
		DeclareVarInst(stack, "float", fTemp39, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp32)))))
		DeclareVarInst(stack, "int", iTemp40, CastInst("int", LoadVarInst(stack, fTemp39)))
		DeclareVarInst(stack, "float", fTemp41, FunCallInst("floorf", LoadVarInst(stack, fTemp39)))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp38), BinopInst("*", LoadVarInst(struct, fVec24[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp40)), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp39))))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp39), LoadVarInst(stack, fTemp41)), LoadVarInst(struct, fVec24[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp40), Int32(1))), Int32(4095))]))))
		DeclareVarInst(stack, "float", fTemp43, FunCallInst("max_f", LoadVarInst(stack, fTemp10), Float(23.4489498f)))
		DeclareVarInst(stack, "float", fTemp44, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp43))))
		StoreVarInst(struct, fVec25[Int32(0)], LoadVarInst(stack, fTemp44))
		DeclareVarInst(stack, "float", fTemp45, BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec25[Int32(1)]))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp45), FunCallInst("floorf", LoadVarInst(stack, fTemp45))))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec6[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp47, BinopInst("+", LoadVarInst(stack, fTemp46), Float(-1.0f)))
		DeclareVarInst(stack, "float", fTemp48, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp47)))
		StoreVarInst(struct, fVec26[Int32(0)], LoadVarInst(stack, fTemp48))
		DeclareVarInst(stack, "float", fTemp49, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp48), LoadVarInst(struct, fVec26[Int32(1)]))), LoadVarInst(stack, fTemp44)))
		StoreVarInst(struct, fVec27[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp49))
		DeclareVarInst(stack, "float", fTemp50, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp43)))))
		DeclareVarInst(stack, "int", iTemp51, CastInst("int", LoadVarInst(stack, fTemp50)))
		DeclareVarInst(stack, "float", fTemp52, FunCallInst("floorf", LoadVarInst(stack, fTemp50)))
		DeclareVarInst(stack, "float", fTemp53, BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp49), BinopInst("*", LoadVarInst(struct, fVec27[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp51)), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp52), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp50))))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp50), LoadVarInst(stack, fTemp52)), LoadVarInst(struct, fVec27[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp51), Int32(1))), Int32(4095))]))))
		DeclareVarInst(stack, "float", fTemp54, FunCallInst("max_f", LoadVarInst(stack, fTemp21), Float(23.4489498f)))
		DeclareVarInst(stack, "float", fTemp55, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp54))))
		StoreVarInst(struct, fVec28[Int32(0)], LoadVarInst(stack, fTemp55))
		DeclareVarInst(stack, "float", fTemp56, BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec28[Int32(1)]))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp56), FunCallInst("floorf", LoadVarInst(stack, fTemp56))))
		DeclareVarInst(stack, "float", fTemp57, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec7[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp58, BinopInst("+", LoadVarInst(stack, fTemp57), Float(-1.0f)))
		DeclareVarInst(stack, "float", fTemp59, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp58)))
		StoreVarInst(struct, fVec29[Int32(0)], LoadVarInst(stack, fTemp59))
		DeclareVarInst(stack, "float", fTemp60, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp59), LoadVarInst(struct, fVec29[Int32(1)]))), LoadVarInst(stack, fTemp55)))
		StoreVarInst(struct, fVec30[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp60))
		DeclareVarInst(stack, "float", fTemp61, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp54)))))
		DeclareVarInst(stack, "int", iTemp62, CastInst("int", LoadVarInst(stack, fTemp61)))
		DeclareVarInst(stack, "float", fTemp63, FunCallInst("floorf", LoadVarInst(stack, fTemp61)))
		DeclareVarInst(stack, "float", fTemp64, BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp60), BinopInst("*", LoadVarInst(struct, fVec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp62)), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp63), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp61))))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp61), LoadVarInst(stack, fTemp63)), LoadVarInst(struct, fVec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp62), Int32(1))), Int32(4095))]))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp42)), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec8[Int32(1)]))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp53)), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec9[Int32(1)]))))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp64)), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec10[Int32(1)]))))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow16), BinopInst("*", Float(0.99000001f), LoadVarInst(struct, fRec11[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp65, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("/", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(stack, fTemp32))))))
		DeclareVarInst(stack, "float", fTemp66, FunCallInst("floorf", LoadVarInst(stack, fTemp65)))
		DeclareVarInst(stack, "float", fTemp67, BinopInst("+", LoadVarInst(stack, fTemp66), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp65))))
		DeclareVarInst(stack, "int", iTemp68, CastInst("int", LoadVarInst(stack, fTemp65)))
		DeclareVarInst(stack, "float", fTemp69, BinopInst("-", LoadVarInst(stack, fTemp65), LoadVarInst(stack, fTemp66)))
		DeclareVarInst(stack, "int", iTemp70, BinopInst("+", LoadVarInst(stack, iTemp68), Int32(1)))
		DeclareVarInst(stack, "float", fTemp71, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("/", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(stack, fTemp43))))))
		DeclareVarInst(stack, "float", fTemp72, FunCallInst("floorf", LoadVarInst(stack, fTemp71)))
		DeclareVarInst(stack, "float", fTemp73, BinopInst("+", LoadVarInst(stack, fTemp72), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp71))))
		DeclareVarInst(stack, "int", iTemp74, CastInst("int", LoadVarInst(stack, fTemp71)))
		DeclareVarInst(stack, "float", fTemp75, BinopInst("-", LoadVarInst(stack, fTemp71), LoadVarInst(stack, fTemp72)))
		DeclareVarInst(stack, "int", iTemp76, BinopInst("+", LoadVarInst(stack, iTemp74), Int32(1)))
		DeclareVarInst(stack, "float", fTemp77, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("/", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(stack, fTemp54))))))
		DeclareVarInst(stack, "float", fTemp78, FunCallInst("floorf", LoadVarInst(stack, fTemp77)))
		DeclareVarInst(stack, "float", fTemp79, BinopInst("+", LoadVarInst(stack, fTemp78), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp77))))
		DeclareVarInst(stack, "int", iTemp80, CastInst("int", LoadVarInst(stack, fTemp77)))
		DeclareVarInst(stack, "float", fTemp81, BinopInst("-", LoadVarInst(stack, fTemp77), LoadVarInst(stack, fTemp78)))
		DeclareVarInst(stack, "int", iTemp82, BinopInst("+", LoadVarInst(stack, iTemp80), Int32(1)))
		DeclareVarInst(stack, "float", fTemp83, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp36)))
		StoreVarInst(struct, fVec31[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp83), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp35))))
		DeclareVarInst(stack, "float", fTemp84, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp83), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp35), LoadVarInst(struct, fVec31[Int32(1)])))), LoadVarInst(stack, fTemp33)))
		StoreVarInst(struct, fVec32[Int32(0)], LoadVarInst(stack, fTemp84))
		DeclareVarInst(stack, "float", fTemp85, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp84), LoadVarInst(struct, fVec32[Int32(1)]))), LoadVarInst(stack, fTemp33)))
		StoreVarInst(struct, fVec33[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp85))
		DeclareVarInst(stack, "float", fTemp86, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp47)))
		StoreVarInst(struct, fVec34[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp86), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp46))))
		DeclareVarInst(stack, "float", fTemp87, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp86), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp46), LoadVarInst(struct, fVec34[Int32(1)])))), LoadVarInst(stack, fTemp44)))
		StoreVarInst(struct, fVec35[Int32(0)], LoadVarInst(stack, fTemp87))
		DeclareVarInst(stack, "float", fTemp88, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp87), LoadVarInst(struct, fVec35[Int32(1)]))), LoadVarInst(stack, fTemp44)))
		StoreVarInst(struct, fVec36[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp88))
		DeclareVarInst(stack, "float", fTemp89, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp58)))
		StoreVarInst(struct, fVec37[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp89), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp57))))
		DeclareVarInst(stack, "float", fTemp90, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp89), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp57), LoadVarInst(struct, fVec37[Int32(1)])))), LoadVarInst(stack, fTemp55)))
		StoreVarInst(struct, fVec38[Int32(0)], LoadVarInst(stack, fTemp90))
		DeclareVarInst(stack, "float", fTemp91, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp90), LoadVarInst(struct, fVec38[Int32(1)]))), LoadVarInst(stack, fTemp55)))
		StoreVarInst(struct, fVec39[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp91))
		StoreVarInst(struct, iRec13[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec13[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(0.522189379f), LoadVarInst(struct, fRec12[Int32(3)])), BinopInst("+", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec13[Int32(0)]))), BinopInst("*", Float(2.49495602f), LoadVarInst(struct, fRec12[Int32(1)])))), BinopInst("*", Float(2.0172658f), LoadVarInst(struct, fRec12[Int32(2)]))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)]))), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("+", BinopInst("+", Select2Inst(LoadVarInst(stack, iSlow4) Select2Inst(LoadVarInst(stack, iSlow8) BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fVec7[Int32(1)]))), LoadVarInst(stack, fTemp0))) BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp6), LoadVarInst(struct, fVec4[Int32(1)]))), LoadVarInst(stack, fTemp0)))) Select2Inst(LoadVarInst(stack, iSlow5) BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp4), LoadVarInst(struct, fVec2[Int32(1)]))), LoadVarInst(stack, fTemp0))) LoadVarInst(stack, fTemp3))), Select2Inst(LoadVarInst(stack, iSlow4) Select2Inst(LoadVarInst(stack, iSlow8) BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp20), LoadVarInst(struct, fVec14[Int32(1)]))), LoadVarInst(stack, fTemp11))) BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp17), LoadVarInst(struct, fVec11[Int32(1)]))), LoadVarInst(stack, fTemp11)))) Select2Inst(LoadVarInst(stack, iSlow5) BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp15), LoadVarInst(struct, fVec9[Int32(1)]))), LoadVarInst(stack, fTemp11))) LoadVarInst(stack, fTemp14)))), Select2Inst(LoadVarInst(stack, iSlow4) Select2Inst(LoadVarInst(stack, iSlow8) BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp31), LoadVarInst(struct, fVec21[Int32(1)]))), LoadVarInst(stack, fTemp22))) BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fVec18[Int32(1)]))), LoadVarInst(stack, fTemp22)))) Select2Inst(LoadVarInst(stack, iSlow5) BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fVec16[Int32(1)]))), LoadVarInst(stack, fTemp22))) LoadVarInst(stack, fTemp25))))), BinopInst("*", LoadVarInst(stack, fSlow11), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp42), LoadVarInst(stack, fTemp53)), LoadVarInst(stack, fTemp64)))), BinopInst("*", LoadVarInst(stack, fSlow12), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec8[Int32(0)]), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec9[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec10[Int32(0)])))))), BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp38), BinopInst("*", LoadVarInst(stack, fTemp67), LoadVarInst(struct, fVec24[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp68)), Int32(4095))]))), BinopInst("*", LoadVarInst(stack, fTemp69), LoadVarInst(struct, fVec24[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp70)), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp49), BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(struct, fVec27[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp74)), Int32(4095))]))), BinopInst("*", LoadVarInst(stack, fTemp75), LoadVarInst(struct, fVec27[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp76)), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp60), BinopInst("*", LoadVarInst(stack, fTemp79), LoadVarInst(struct, fVec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp80)), Int32(4095))]))), BinopInst("*", LoadVarInst(stack, fTemp81), LoadVarInst(struct, fVec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp82)), Int32(4095))]))))), BinopInst("*", LoadVarInst(stack, fSlow17), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp85), BinopInst("*", LoadVarInst(struct, fVec33[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp68)), Int32(4095))]), LoadVarInst(stack, fTemp67))), BinopInst("*", LoadVarInst(stack, fTemp69), LoadVarInst(struct, fVec33[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp70)), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp88), BinopInst("*", LoadVarInst(struct, fVec36[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp74)), Int32(4095))]), LoadVarInst(stack, fTemp73))), BinopInst("*", LoadVarInst(stack, fTemp75), LoadVarInst(struct, fVec36[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp76)), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp91), BinopInst("*", LoadVarInst(struct, fVec39[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp80)), Int32(4095))]), LoadVarInst(stack, fTemp79))), BinopInst("*", LoadVarInst(stack, fTemp81), LoadVarInst(struct, fVec39[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp82)), Int32(4095))])))))))), BinopInst("*", LoadVarInst(stack, fSlow18), BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0499220341f), LoadVarInst(struct, fRec12[Int32(0)])), BinopInst("*", Float(0.0506126992f), LoadVarInst(struct, fRec12[Int32(2)]))), BinopInst("+", BinopInst("*", Float(0.0959935337f), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", Float(0.00440878607f), LoadVarInst(struct, fRec12[Int32(3)]))))))))))
		ForLoopInst 
			DeclareVarInst(loop, "int", j0, Int32(3))
			BinopInst(">", LoadVarInst(loop, j0), Int32(0))
			StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
			BlockInst 
				StoreVarInst(struct, iVec0[LoadVarInst(loop, j0)], LoadVarInst(struct, iVec0[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
				EndBlock
			EndForLoop
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
		StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
		StoreVarInst(struct, fVec5[Int32(1)], LoadVarInst(struct, fVec5[Int32(0)]))
		StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
		StoreVarInst(struct, fVec7[Int32(1)], LoadVarInst(struct, fVec7[Int32(0)]))
		StoreVarInst(struct, fVec8[Int32(1)], LoadVarInst(struct, fVec8[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fVec9[Int32(1)], LoadVarInst(struct, fVec9[Int32(0)]))
		StoreVarInst(struct, fVec10[Int32(1)], LoadVarInst(struct, fVec10[Int32(0)]))
		StoreVarInst(struct, fVec11[Int32(1)], LoadVarInst(struct, fVec11[Int32(0)]))
		StoreVarInst(struct, fVec12[Int32(1)], LoadVarInst(struct, fVec12[Int32(0)]))
		StoreVarInst(struct, fVec13[Int32(1)], LoadVarInst(struct, fVec13[Int32(0)]))
		StoreVarInst(struct, fVec14[Int32(1)], LoadVarInst(struct, fVec14[Int32(0)]))
		StoreVarInst(struct, fVec15[Int32(1)], LoadVarInst(struct, fVec15[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fVec16[Int32(1)], LoadVarInst(struct, fVec16[Int32(0)]))
		StoreVarInst(struct, fVec17[Int32(1)], LoadVarInst(struct, fVec17[Int32(0)]))
		StoreVarInst(struct, fVec18[Int32(1)], LoadVarInst(struct, fVec18[Int32(0)]))
		StoreVarInst(struct, fVec19[Int32(1)], LoadVarInst(struct, fVec19[Int32(0)]))
		StoreVarInst(struct, fVec20[Int32(1)], LoadVarInst(struct, fVec20[Int32(0)]))
		StoreVarInst(struct, fVec21[Int32(1)], LoadVarInst(struct, fVec21[Int32(0)]))
		StoreVarInst(struct, fVec22[Int32(1)], LoadVarInst(struct, fVec22[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fVec23[Int32(1)], LoadVarInst(struct, fVec23[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fVec25[Int32(1)], LoadVarInst(struct, fVec25[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fVec26[Int32(1)], LoadVarInst(struct, fVec26[Int32(0)]))
		StoreVarInst(struct, fVec28[Int32(1)], LoadVarInst(struct, fVec28[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fVec29[Int32(1)], LoadVarInst(struct, fVec29[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fVec31[Int32(1)], LoadVarInst(struct, fVec31[Int32(0)]))
		StoreVarInst(struct, fVec32[Int32(1)], LoadVarInst(struct, fVec32[Int32(0)]))
		StoreVarInst(struct, fVec34[Int32(1)], LoadVarInst(struct, fVec34[Int32(0)]))
		StoreVarInst(struct, fVec35[Int32(1)], LoadVarInst(struct, fVec35[Int32(0)]))
		StoreVarInst(struct, fVec37[Int32(1)], LoadVarInst(struct, fVec37[Int32(0)]))
		StoreVarInst(struct, fVec38[Int32(1)], LoadVarInst(struct, fVec38[Int32(0)]))
		StoreVarInst(struct, iRec13[Int32(1)], LoadVarInst(struct, iRec13[Int32(0)]))
		ForLoopInst 
			DeclareVarInst(loop, "int", j1, Int32(3))
			BinopInst(">", LoadVarInst(loop, j1), Int32(0))
			StoreVarInst(loop, j1, BinopInst("-", LoadVarInst(loop, j1), Int32(1)))
			BlockInst 
				StoreVarInst(struct, fRec12[LoadVarInst(loop, j1)], LoadVarInst(struct, fRec12[BinopInst("-", LoadVarInst(loop, j1), Int32(1))]))
				EndBlock
			EndForLoop
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, int, iVec0[4])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fEntry0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider2)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, float, fVec3[2])
	DeclareVarInst(struct, float, fVec4[2])
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, float, fVec5[2])
	DeclareVarInst(struct, float, fVec6[2])
	DeclareVarInst(struct, float, fVec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider3)
	DeclareVarInst(struct, float, fVec8[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, float, fVec9[2])
	DeclareVarInst(struct, float, fVec10[2])
	DeclareVarInst(struct, float, fVec11[2])
	DeclareVarInst(struct, float, fVec12[2])
	DeclareVarInst(struct, float, fVec13[2])
	DeclareVarInst(struct, float, fVec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider4)
	DeclareVarInst(struct, float, fVec15[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fVec16[2])
	DeclareVarInst(struct, float, fVec17[2])
	DeclareVarInst(struct, float, fVec18[2])
	DeclareVarInst(struct, float, fVec19[2])
	DeclareVarInst(struct, float, fVec20[2])
	DeclareVarInst(struct, float, fVec21[2])
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider5)
	DeclareVarInst(struct, float, fVec22[2])
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fVec23[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec24[4096])
	DeclareVarInst(struct, "float", fConst6)
	DeclareVarInst(struct, float, fVec25[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fVec26[2])
	DeclareVarInst(struct, float, fVec27[4096])
	DeclareVarInst(struct, float, fVec28[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fVec29[2])
	DeclareVarInst(struct, float, fVec30[4096])
	DeclareVarInst(struct, "float", fConst7)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider6)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider8)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "float", fConst8)
	DeclareVarInst(struct, float, fVec31[2])
	DeclareVarInst(struct, float, fVec32[2])
	DeclareVarInst(struct, float, fVec33[4096])
	DeclareVarInst(struct, float, fVec34[2])
	DeclareVarInst(struct, float, fVec35[2])
	DeclareVarInst(struct, float, fVec36[4096])
	DeclareVarInst(struct, float, fVec37[2])
	DeclareVarInst(struct, float, fVec38[2])
	DeclareVarInst(struct, float, fVec39[4096])
	DeclareVarInst(struct, "FAUSTFLOAT", fVslider9)
	DeclareVarInst(struct, int, iRec13[2])
	DeclareVarInst(struct, float, fRec12[4])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(0.25f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.0416666679f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.00520833349f), FunCallInst("mydsp_faustpower3_f", LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst5, BinopInst("*", Float(0.0833333358f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst6, BinopInst("*", Float(0.5f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst7, BinopInst("/", Float(1.33333337f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst8, BinopInst("*", Float(0.013888889f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fVslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(-20.0f)))
	StoreVarInst(struct, fVslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fEntry0, CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(49.0f)))
	StoreVarInst(struct, fVslider2, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	StoreVarInst(struct, fVslider3, CastInst("FAUSTFLOAT", Double(-0.10000000000000001f)))
	StoreVarInst(struct, fVslider4, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	StoreVarInst(struct, fVslider5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fVslider8, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fVslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(4))
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
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l1)], Float(0.0f))
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
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec6[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec7[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec8[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec9[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec10[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec11[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec12[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec13[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec14[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec15[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec16[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec17[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec18[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec19[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec20[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec21[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec22[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec23[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(4096))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec24[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec25[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec26[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(4096))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec27[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec28[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec29[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(4096))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec30[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(2))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(2))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(2))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec31[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(2))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec32[LoadVarInst(loop, l44)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(4096))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec33[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec34[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(2))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec35[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(4096))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec36[LoadVarInst(loop, l48)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec37[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec38[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(4096))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec39[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec13[LoadVarInst(loop, l52)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(4))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fVslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.333333343f), CastInst("float", LoadVarInst(struct, fVslider1))))
	DeclareVarInst(stack, "int", iSlow3, CastInst("int", BinopInst("+", CastInst("float", LoadVarInst(struct, fEntry0)), Float(-1.0f))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst(">=", LoadVarInst(stack, iSlow3), Int32(2)))
	DeclareVarInst(stack, "int", iSlow5, BinopInst(">=", LoadVarInst(stack, iSlow3), Int32(1)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fVslider2))))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", Float(440.0f), BinopInst("*", FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", CastInst("float", LoadVarInst(struct, fHslider1)), Float(-49.0f)))), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow6)))))
	DeclareVarInst(stack, "int", iSlow8, BinopInst(">=", LoadVarInst(stack, iSlow3), Int32(3)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("-", Float(1.0f), BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fVslider3)))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("+", BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fVslider4))), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("*", LoadVarInst(struct, fConst5), CastInst("float", LoadVarInst(struct, fVslider5))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("*", LoadVarInst(struct, fConst7), CastInst("float", LoadVarInst(struct, fVslider6))))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fVslider7))))
	DeclareVarInst(stack, "float", fSlow14, CastInst("float", LoadVarInst(struct, fCheckbox0)))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("*", Float(0.0833333358f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow14))))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", Float(0.00999999978f), CastInst("float", LoadVarInst(struct, fVslider8))))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("*", LoadVarInst(struct, fConst8), LoadVarInst(stack, fSlow14)))
	DeclareVarInst(stack, "float", fSlow18, CastInst("float", LoadVarInst(struct, fVslider9)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[Int32(0)], Int32(1))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec2[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(struct, fRec2[Int32(0)]))))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp0))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec1[Int32(1)]))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp1), FunCallInst("floorf", LoadVarInst(stack, fTemp1))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec1[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.0f)))
			DeclareVarInst(stack, "float", fTemp4, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp3)))
			StoreVarInst(struct, fVec2[Int32(0)], LoadVarInst(stack, fTemp4))
			DeclareVarInst(stack, "float", fTemp5, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp3)))
			StoreVarInst(struct, fVec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp2))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp2), LoadVarInst(struct, fVec3[Int32(1)])))), LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fVec4[Int32(0)], LoadVarInst(stack, fTemp6))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("*", LoadVarInst(stack, fTemp4), BinopInst("+", LoadVarInst(stack, fTemp4), Float(-2.0f))))
			StoreVarInst(struct, fVec5[Int32(0)], LoadVarInst(stack, fTemp7))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fVec5[Int32(1)])), LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fVec6[Int32(0)], LoadVarInst(stack, fTemp8))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec6[Int32(1)])), LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fVec7[Int32(0)], LoadVarInst(stack, fTemp9))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec2[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp11, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp10))))
			StoreVarInst(struct, fVec8[Int32(0)], LoadVarInst(stack, fTemp11))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(struct, fRec3[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec8[Int32(1)]))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp12), FunCallInst("floorf", LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec3[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(stack, fTemp13), Float(-1.0f)))
			DeclareVarInst(stack, "float", fTemp15, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp14)))
			StoreVarInst(struct, fVec9[Int32(0)], LoadVarInst(stack, fTemp15))
			DeclareVarInst(stack, "float", fTemp16, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp14)))
			StoreVarInst(struct, fVec10[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp16), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp16), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp13), LoadVarInst(struct, fVec10[Int32(1)])))), LoadVarInst(stack, fTemp11)))
			StoreVarInst(struct, fVec11[Int32(0)], LoadVarInst(stack, fTemp17))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", LoadVarInst(stack, fTemp15), Float(-2.0f))))
			StoreVarInst(struct, fVec12[Int32(0)], LoadVarInst(stack, fTemp18))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp18), LoadVarInst(struct, fVec12[Int32(1)])), LoadVarInst(stack, fTemp11)))
			StoreVarInst(struct, fVec13[Int32(0)], LoadVarInst(stack, fTemp19))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp19), LoadVarInst(struct, fVec13[Int32(1)])), LoadVarInst(stack, fTemp11)))
			StoreVarInst(struct, fVec14[Int32(0)], LoadVarInst(stack, fTemp20))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec2[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp22, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp21))))
			StoreVarInst(struct, fVec15[Int32(0)], LoadVarInst(stack, fTemp22))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("+", LoadVarInst(struct, fRec4[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec15[Int32(1)]))))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp23), FunCallInst("floorf", LoadVarInst(stack, fTemp23))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec4[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("+", LoadVarInst(stack, fTemp24), Float(-1.0f)))
			DeclareVarInst(stack, "float", fTemp26, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp25)))
			StoreVarInst(struct, fVec16[Int32(0)], LoadVarInst(stack, fTemp26))
			DeclareVarInst(stack, "float", fTemp27, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp25)))
			StoreVarInst(struct, fVec17[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp24))))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp27), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp24), LoadVarInst(struct, fVec17[Int32(1)])))), LoadVarInst(stack, fTemp22)))
			StoreVarInst(struct, fVec18[Int32(0)], LoadVarInst(stack, fTemp28))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("*", LoadVarInst(stack, fTemp26), BinopInst("+", LoadVarInst(stack, fTemp26), Float(-2.0f))))
			StoreVarInst(struct, fVec19[Int32(0)], LoadVarInst(stack, fTemp29))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp29), LoadVarInst(struct, fVec19[Int32(1)])), LoadVarInst(stack, fTemp22)))
			StoreVarInst(struct, fVec20[Int32(0)], LoadVarInst(stack, fTemp30))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp30), LoadVarInst(struct, fVec20[Int32(1)])), LoadVarInst(stack, fTemp22)))
			StoreVarInst(struct, fVec21[Int32(0)], LoadVarInst(stack, fTemp31))
			DeclareVarInst(stack, "float", fTemp32, FunCallInst("max_f", LoadVarInst(struct, fRec2[Int32(0)]), Float(23.4489498f)))
			DeclareVarInst(stack, "float", fTemp33, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp32))))
			StoreVarInst(struct, fVec22[Int32(0)], LoadVarInst(stack, fTemp33))
			DeclareVarInst(stack, "float", fTemp34, BinopInst("+", LoadVarInst(struct, fRec5[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec22[Int32(1)]))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp34), FunCallInst("floorf", LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec5[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(stack, fTemp35), Float(-1.0f)))
			DeclareVarInst(stack, "float", fTemp37, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp36)))
			StoreVarInst(struct, fVec23[Int32(0)], LoadVarInst(stack, fTemp37))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp37), LoadVarInst(struct, fVec23[Int32(1)]))), LoadVarInst(stack, fTemp33)))
			StoreVarInst(struct, fVec24[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp38))
			DeclareVarInst(stack, "float", fTemp39, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp32)))))
			DeclareVarInst(stack, "int", iTemp40, CastInst("int", LoadVarInst(stack, fTemp39)))
			DeclareVarInst(stack, "float", fTemp41, FunCallInst("floorf", LoadVarInst(stack, fTemp39)))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp38), BinopInst("*", LoadVarInst(struct, fVec24[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp40)), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp39))))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp39), LoadVarInst(stack, fTemp41)), LoadVarInst(struct, fVec24[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp40), Int32(1))), Int32(4095))]))))
			DeclareVarInst(stack, "float", fTemp43, FunCallInst("max_f", LoadVarInst(stack, fTemp10), Float(23.4489498f)))
			DeclareVarInst(stack, "float", fTemp44, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp43))))
			StoreVarInst(struct, fVec25[Int32(0)], LoadVarInst(stack, fTemp44))
			DeclareVarInst(stack, "float", fTemp45, BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec25[Int32(1)]))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp45), FunCallInst("floorf", LoadVarInst(stack, fTemp45))))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec6[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp47, BinopInst("+", LoadVarInst(stack, fTemp46), Float(-1.0f)))
			DeclareVarInst(stack, "float", fTemp48, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp47)))
			StoreVarInst(struct, fVec26[Int32(0)], LoadVarInst(stack, fTemp48))
			DeclareVarInst(stack, "float", fTemp49, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp48), LoadVarInst(struct, fVec26[Int32(1)]))), LoadVarInst(stack, fTemp44)))
			StoreVarInst(struct, fVec27[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp49))
			DeclareVarInst(stack, "float", fTemp50, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp43)))))
			DeclareVarInst(stack, "int", iTemp51, CastInst("int", LoadVarInst(stack, fTemp50)))
			DeclareVarInst(stack, "float", fTemp52, FunCallInst("floorf", LoadVarInst(stack, fTemp50)))
			DeclareVarInst(stack, "float", fTemp53, BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp49), BinopInst("*", LoadVarInst(struct, fVec27[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp51)), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp52), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp50))))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp50), LoadVarInst(stack, fTemp52)), LoadVarInst(struct, fVec27[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp51), Int32(1))), Int32(4095))]))))
			DeclareVarInst(stack, "float", fTemp54, FunCallInst("max_f", LoadVarInst(stack, fTemp21), Float(23.4489498f)))
			DeclareVarInst(stack, "float", fTemp55, FunCallInst("max_f", Float(20.0f), FunCallInst("fabsf", LoadVarInst(stack, fTemp54))))
			StoreVarInst(struct, fVec28[Int32(0)], LoadVarInst(stack, fTemp55))
			DeclareVarInst(stack, "float", fTemp56, BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fVec28[Int32(1)]))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("-", LoadVarInst(stack, fTemp56), FunCallInst("floorf", LoadVarInst(stack, fTemp56))))
			DeclareVarInst(stack, "float", fTemp57, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec7[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp58, BinopInst("+", LoadVarInst(stack, fTemp57), Float(-1.0f)))
			DeclareVarInst(stack, "float", fTemp59, FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp58)))
			StoreVarInst(struct, fVec29[Int32(0)], LoadVarInst(stack, fTemp59))
			DeclareVarInst(stack, "float", fTemp60, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp59), LoadVarInst(struct, fVec29[Int32(1)]))), LoadVarInst(stack, fTemp55)))
			StoreVarInst(struct, fVec30[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp60))
			DeclareVarInst(stack, "float", fTemp61, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(struct, fConst6), LoadVarInst(stack, fTemp54)))))
			DeclareVarInst(stack, "int", iTemp62, CastInst("int", LoadVarInst(stack, fTemp61)))
			DeclareVarInst(stack, "float", fTemp63, FunCallInst("floorf", LoadVarInst(stack, fTemp61)))
			DeclareVarInst(stack, "float", fTemp64, BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp60), BinopInst("*", LoadVarInst(struct, fVec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp62)), Int32(4095))]), BinopInst("+", LoadVarInst(stack, fTemp63), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp61))))), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp61), LoadVarInst(stack, fTemp63)), LoadVarInst(struct, fVec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), BinopInst("+", LoadVarInst(stack, iTemp62), Int32(1))), Int32(4095))]))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp42)), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec8[Int32(1)]))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp53)), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec9[Int32(1)]))))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp64)), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec10[Int32(1)]))))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow16), BinopInst("*", Float(0.99000001f), LoadVarInst(struct, fRec11[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp65, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("/", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(stack, fTemp32))))))
			DeclareVarInst(stack, "float", fTemp66, FunCallInst("floorf", LoadVarInst(stack, fTemp65)))
			DeclareVarInst(stack, "float", fTemp67, BinopInst("+", LoadVarInst(stack, fTemp66), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp65))))
			DeclareVarInst(stack, "int", iTemp68, CastInst("int", LoadVarInst(stack, fTemp65)))
			DeclareVarInst(stack, "float", fTemp69, BinopInst("-", LoadVarInst(stack, fTemp65), LoadVarInst(stack, fTemp66)))
			DeclareVarInst(stack, "int", iTemp70, BinopInst("+", LoadVarInst(stack, iTemp68), Int32(1)))
			DeclareVarInst(stack, "float", fTemp71, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("/", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(stack, fTemp43))))))
			DeclareVarInst(stack, "float", fTemp72, FunCallInst("floorf", LoadVarInst(stack, fTemp71)))
			DeclareVarInst(stack, "float", fTemp73, BinopInst("+", LoadVarInst(stack, fTemp72), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp71))))
			DeclareVarInst(stack, "int", iTemp74, CastInst("int", LoadVarInst(stack, fTemp71)))
			DeclareVarInst(stack, "float", fTemp75, BinopInst("-", LoadVarInst(stack, fTemp71), LoadVarInst(stack, fTemp72)))
			DeclareVarInst(stack, "int", iTemp76, BinopInst("+", LoadVarInst(stack, iTemp74), Int32(1)))
			DeclareVarInst(stack, "float", fTemp77, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("*", LoadVarInst(struct, fConst0), BinopInst("/", LoadVarInst(struct, fRec11[Int32(0)]), LoadVarInst(stack, fTemp54))))))
			DeclareVarInst(stack, "float", fTemp78, FunCallInst("floorf", LoadVarInst(stack, fTemp77)))
			DeclareVarInst(stack, "float", fTemp79, BinopInst("+", LoadVarInst(stack, fTemp78), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp77))))
			DeclareVarInst(stack, "int", iTemp80, CastInst("int", LoadVarInst(stack, fTemp77)))
			DeclareVarInst(stack, "float", fTemp81, BinopInst("-", LoadVarInst(stack, fTemp77), LoadVarInst(stack, fTemp78)))
			DeclareVarInst(stack, "int", iTemp82, BinopInst("+", LoadVarInst(stack, iTemp80), Int32(1)))
			DeclareVarInst(stack, "float", fTemp83, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp36)))
			StoreVarInst(struct, fVec31[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp83), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp35))))
			DeclareVarInst(stack, "float", fTemp84, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp83), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp35), LoadVarInst(struct, fVec31[Int32(1)])))), LoadVarInst(stack, fTemp33)))
			StoreVarInst(struct, fVec32[Int32(0)], LoadVarInst(stack, fTemp84))
			DeclareVarInst(stack, "float", fTemp85, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp84), LoadVarInst(struct, fVec32[Int32(1)]))), LoadVarInst(stack, fTemp33)))
			StoreVarInst(struct, fVec33[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp85))
			DeclareVarInst(stack, "float", fTemp86, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp47)))
			StoreVarInst(struct, fVec34[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp86), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp46))))
			DeclareVarInst(stack, "float", fTemp87, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp86), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp46), LoadVarInst(struct, fVec34[Int32(1)])))), LoadVarInst(stack, fTemp44)))
			StoreVarInst(struct, fVec35[Int32(0)], LoadVarInst(stack, fTemp87))
			DeclareVarInst(stack, "float", fTemp88, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp87), LoadVarInst(struct, fVec35[Int32(1)]))), LoadVarInst(stack, fTemp44)))
			StoreVarInst(struct, fVec36[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp88))
			DeclareVarInst(stack, "float", fTemp89, FunCallInst("mydsp_faustpower3_f", LoadVarInst(stack, fTemp58)))
			StoreVarInst(struct, fVec37[Int32(0)], BinopInst("+", LoadVarInst(stack, fTemp89), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp57))))
			DeclareVarInst(stack, "float", fTemp90, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp89), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp57), LoadVarInst(struct, fVec37[Int32(1)])))), LoadVarInst(stack, fTemp55)))
			StoreVarInst(struct, fVec38[Int32(0)], LoadVarInst(stack, fTemp90))
			DeclareVarInst(stack, "float", fTemp91, BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp90), LoadVarInst(struct, fVec38[Int32(1)]))), LoadVarInst(stack, fTemp55)))
			StoreVarInst(struct, fVec39[BinopInst("&", LoadVarInst(struct, IOTA), Int32(4095))], LoadVarInst(stack, fTemp91))
			StoreVarInst(struct, iRec13[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec13[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(0.522189379f), LoadVarInst(struct, fRec12[Int32(3)])), BinopInst("+", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec13[Int32(0)]))), BinopInst("*", Float(2.49495602f), LoadVarInst(struct, fRec12[Int32(1)])))), BinopInst("*", Float(2.0172658f), LoadVarInst(struct, fRec12[Int32(2)]))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)]))), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("+", BinopInst("+", Select2Inst(LoadVarInst(stack, iSlow4) Select2Inst(LoadVarInst(stack, iSlow8) BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fVec7[Int32(1)]))), LoadVarInst(stack, fTemp0))) BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp6), LoadVarInst(struct, fVec4[Int32(1)]))), LoadVarInst(stack, fTemp0)))) Select2Inst(LoadVarInst(stack, iSlow5) BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp4), LoadVarInst(struct, fVec2[Int32(1)]))), LoadVarInst(stack, fTemp0))) LoadVarInst(stack, fTemp3))), Select2Inst(LoadVarInst(stack, iSlow4) Select2Inst(LoadVarInst(stack, iSlow8) BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp20), LoadVarInst(struct, fVec14[Int32(1)]))), LoadVarInst(stack, fTemp11))) BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp17), LoadVarInst(struct, fVec11[Int32(1)]))), LoadVarInst(stack, fTemp11)))) Select2Inst(LoadVarInst(stack, iSlow5) BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp15), LoadVarInst(struct, fVec9[Int32(1)]))), LoadVarInst(stack, fTemp11))) LoadVarInst(stack, fTemp14)))), Select2Inst(LoadVarInst(stack, iSlow4) Select2Inst(LoadVarInst(stack, iSlow8) BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(3)])), BinopInst("-", LoadVarInst(stack, fTemp31), LoadVarInst(struct, fVec21[Int32(1)]))), LoadVarInst(stack, fTemp22))) BinopInst("*", LoadVarInst(struct, fConst3), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(2)])), BinopInst("-", LoadVarInst(stack, fTemp28), LoadVarInst(struct, fVec18[Int32(1)]))), LoadVarInst(stack, fTemp22)))) Select2Inst(LoadVarInst(stack, iSlow5) BinopInst("*", LoadVarInst(struct, fConst2), BinopInst("/", BinopInst("*", CastInst("float", LoadVarInst(struct, iVec0[Int32(1)])), BinopInst("-", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fVec16[Int32(1)]))), LoadVarInst(stack, fTemp22))) LoadVarInst(stack, fTemp25))))), BinopInst("*", LoadVarInst(stack, fSlow11), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp42), LoadVarInst(stack, fTemp53)), LoadVarInst(stack, fTemp64)))), BinopInst("*", LoadVarInst(stack, fSlow12), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec8[Int32(0)]), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec9[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow10), LoadVarInst(struct, fRec10[Int32(0)])))))), BinopInst("*", LoadVarInst(stack, fSlow13), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow15), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp38), BinopInst("*", LoadVarInst(stack, fTemp67), LoadVarInst(struct, fVec24[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp68)), Int32(4095))]))), BinopInst("*", LoadVarInst(stack, fTemp69), LoadVarInst(struct, fVec24[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp70)), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp49), BinopInst("*", LoadVarInst(stack, fTemp73), LoadVarInst(struct, fVec27[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp74)), Int32(4095))]))), BinopInst("*", LoadVarInst(stack, fTemp75), LoadVarInst(struct, fVec27[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp76)), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp60), BinopInst("*", LoadVarInst(stack, fTemp79), LoadVarInst(struct, fVec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp80)), Int32(4095))]))), BinopInst("*", LoadVarInst(stack, fTemp81), LoadVarInst(struct, fVec30[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp82)), Int32(4095))]))))), BinopInst("*", LoadVarInst(stack, fSlow17), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp85), BinopInst("*", LoadVarInst(struct, fVec33[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp68)), Int32(4095))]), LoadVarInst(stack, fTemp67))), BinopInst("*", LoadVarInst(stack, fTemp69), LoadVarInst(struct, fVec33[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp70)), Int32(4095))]))), BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp88), BinopInst("*", LoadVarInst(struct, fVec36[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp74)), Int32(4095))]), LoadVarInst(stack, fTemp73))), BinopInst("*", LoadVarInst(stack, fTemp75), LoadVarInst(struct, fVec36[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp76)), Int32(4095))])))), BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp91), BinopInst("*", LoadVarInst(struct, fVec39[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp80)), Int32(4095))]), LoadVarInst(stack, fTemp79))), BinopInst("*", LoadVarInst(stack, fTemp81), LoadVarInst(struct, fVec39[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp82)), Int32(4095))])))))))), BinopInst("*", LoadVarInst(stack, fSlow18), BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0499220341f), LoadVarInst(struct, fRec12[Int32(0)])), BinopInst("*", Float(0.0506126992f), LoadVarInst(struct, fRec12[Int32(2)]))), BinopInst("+", BinopInst("*", Float(0.0959935337f), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", Float(0.00440878607f), LoadVarInst(struct, fRec12[Int32(3)]))))))))))
			ForLoopInst 
				DeclareVarInst(loop, "int", j0, Int32(3))
				BinopInst(">", LoadVarInst(loop, j0), Int32(0))
				StoreVarInst(loop, j0, BinopInst("-", LoadVarInst(loop, j0), Int32(1)))
				BlockInst 
					StoreVarInst(struct, iVec0[LoadVarInst(loop, j0)], LoadVarInst(struct, iVec0[BinopInst("-", LoadVarInst(loop, j0), Int32(1))]))
					EndBlock
				EndForLoop
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
			StoreVarInst(struct, fVec4[Int32(1)], LoadVarInst(struct, fVec4[Int32(0)]))
			StoreVarInst(struct, fVec5[Int32(1)], LoadVarInst(struct, fVec5[Int32(0)]))
			StoreVarInst(struct, fVec6[Int32(1)], LoadVarInst(struct, fVec6[Int32(0)]))
			StoreVarInst(struct, fVec7[Int32(1)], LoadVarInst(struct, fVec7[Int32(0)]))
			StoreVarInst(struct, fVec8[Int32(1)], LoadVarInst(struct, fVec8[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fVec9[Int32(1)], LoadVarInst(struct, fVec9[Int32(0)]))
			StoreVarInst(struct, fVec10[Int32(1)], LoadVarInst(struct, fVec10[Int32(0)]))
			StoreVarInst(struct, fVec11[Int32(1)], LoadVarInst(struct, fVec11[Int32(0)]))
			StoreVarInst(struct, fVec12[Int32(1)], LoadVarInst(struct, fVec12[Int32(0)]))
			StoreVarInst(struct, fVec13[Int32(1)], LoadVarInst(struct, fVec13[Int32(0)]))
			StoreVarInst(struct, fVec14[Int32(1)], LoadVarInst(struct, fVec14[Int32(0)]))
			StoreVarInst(struct, fVec15[Int32(1)], LoadVarInst(struct, fVec15[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fVec16[Int32(1)], LoadVarInst(struct, fVec16[Int32(0)]))
			StoreVarInst(struct, fVec17[Int32(1)], LoadVarInst(struct, fVec17[Int32(0)]))
			StoreVarInst(struct, fVec18[Int32(1)], LoadVarInst(struct, fVec18[Int32(0)]))
			StoreVarInst(struct, fVec19[Int32(1)], LoadVarInst(struct, fVec19[Int32(0)]))
			StoreVarInst(struct, fVec20[Int32(1)], LoadVarInst(struct, fVec20[Int32(0)]))
			StoreVarInst(struct, fVec21[Int32(1)], LoadVarInst(struct, fVec21[Int32(0)]))
			StoreVarInst(struct, fVec22[Int32(1)], LoadVarInst(struct, fVec22[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fVec23[Int32(1)], LoadVarInst(struct, fVec23[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fVec25[Int32(1)], LoadVarInst(struct, fVec25[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fVec26[Int32(1)], LoadVarInst(struct, fVec26[Int32(0)]))
			StoreVarInst(struct, fVec28[Int32(1)], LoadVarInst(struct, fVec28[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fVec29[Int32(1)], LoadVarInst(struct, fVec29[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fVec31[Int32(1)], LoadVarInst(struct, fVec31[Int32(0)]))
			StoreVarInst(struct, fVec32[Int32(1)], LoadVarInst(struct, fVec32[Int32(0)]))
			StoreVarInst(struct, fVec34[Int32(1)], LoadVarInst(struct, fVec34[Int32(0)]))
			StoreVarInst(struct, fVec35[Int32(1)], LoadVarInst(struct, fVec35[Int32(0)]))
			StoreVarInst(struct, fVec37[Int32(1)], LoadVarInst(struct, fVec37[Int32(0)]))
			StoreVarInst(struct, fVec38[Int32(1)], LoadVarInst(struct, fVec38[Int32(0)]))
			StoreVarInst(struct, iRec13[Int32(1)], LoadVarInst(struct, iRec13[Int32(0)]))
			ForLoopInst 
				DeclareVarInst(loop, "int", j1, Int32(3))
				BinopInst(">", LoadVarInst(loop, j1), Int32(0))
				StoreVarInst(loop, j1, BinopInst("-", LoadVarInst(loop, j1), Int32(1)))
				BlockInst 
					StoreVarInst(struct, fRec12[LoadVarInst(loop, j1)], LoadVarInst(struct, fRec12[BinopInst("-", LoadVarInst(loop, j1), Int32(1))]))
					EndBlock
				EndForLoop
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 24 bytes
Heap size real = 98772 bytes
Heap size = 98804 bytes
Stack size in compute = 92 bytes

