======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	AddMetaDeclareInst(0, "0", "")
	AddMetaDeclareInst(0, "tooltip", "See Faust's filters.lib   for info and pointers")
	OpenHorizontalBox("PARAMETRIC EQ SECTIONS")
	AddMetaDeclareInst(0, "1", "")
	OpenVerticalBox("Low Shelf")
	AddMetaDeclareInst(fHslider2, "0", "")
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddMetaDeclareInst(fHslider2, "tooltip", "Amount of low-frequency boost or cut in decibels")
	AddMetaDeclareInst(fHslider2, "unit", "dB")
	AddHorizontalSlider("Low Boost|Cut", fHslider2, 0.0f, -40.0f, 40.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider1, "1", "")
	AddMetaDeclareInst(fHslider1, "scale", "log")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "tooltip", "Transition-frequency from boost (cut) to unity gain")
	AddMetaDeclareInst(fHslider1, "unit", "Hz")
	AddHorizontalSlider("Transition Frequency", fHslider1, 200.0f, 1.0f, 5000.0f, 1.0f)
	CloseboxInst
	AddMetaDeclareInst(0, "2", "")
	AddMetaDeclareInst(0, "tooltip", "Parametric Equalizer   sections from filters.lib")
	OpenVerticalBox("Peaking Equalizer")
	AddMetaDeclareInst(fHslider4, "0", "")
	AddMetaDeclareInst(fHslider4, "style", "knob")
	AddMetaDeclareInst(fHslider4, "tooltip", "Amount of   local boost or cut in decibels")
	AddMetaDeclareInst(fHslider4, "unit", "dB")
	AddHorizontalSlider("Peak Boost|Cut", fHslider4, 0.0f, -40.0f, 40.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider3, "1", "")
	AddMetaDeclareInst(fHslider3, "style", "knob")
	AddMetaDeclareInst(fHslider3, "tooltip", "Peak   Frequency in Piano Key (PK) units (A440 = 49PK)")
	AddMetaDeclareInst(fHslider3, "unit", "PK")
	AddHorizontalSlider("Peak Frequency", fHslider3, 49.0f, 1.0f, 100.0f, 1.0f)
	AddMetaDeclareInst(fHslider5, "2", "")
	AddMetaDeclareInst(fHslider5, "scale", "log")
	AddMetaDeclareInst(fHslider5, "style", "knob")
	AddMetaDeclareInst(fHslider5, "tooltip", "Quality factor   (Q) of the peak = center-frequency/bandwidth")
	AddHorizontalSlider("Peak Q", fHslider5, 40.0f, 1.0f, 1000.0f, 0.100000001f)
	CloseboxInst
	AddMetaDeclareInst(0, "3", "")
	AddMetaDeclareInst(0, "tooltip", "A high shelf provides a boost   or cut above some frequency")
	OpenVerticalBox("High Shelf")
	AddMetaDeclareInst(fHslider6, "0", "")
	AddMetaDeclareInst(fHslider6, "style", "knob")
	AddMetaDeclareInst(fHslider6, "tooltip", "Amount of   high-frequency boost or cut in decibels")
	AddMetaDeclareInst(fHslider6, "unit", "dB")
	AddHorizontalSlider("High Boost|Cut", fHslider6, 0.0f, -40.0f, 40.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider0, "1", "")
	AddMetaDeclareInst(fHslider0, "scale", "log")
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddMetaDeclareInst(fHslider0, "tooltip", "Transition-frequency from boost (cut) to unity gain")
	AddMetaDeclareInst(fHslider0, "unit", "Hz")
	AddHorizontalSlider("Transition Frequency", fHslider0, 8000.0f, 20.0f, 10000.0f, 1.0f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec8[3])
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
	StoreVarInst(struct, fConst1, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1382.30078f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(1382.30078f), LoadVarInst(struct, fConst3)))
	StoreVarInst(struct, fConst5, BinopInst("*", Float(2764.60156f), LoadVarInst(struct, fConst3)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(8000.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(200.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(49.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(40.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(3))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
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
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
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
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 43
Store = 0
Binop = 48
Numbers = 40
Declare = 32
Cast = 7
Select = 0
Loop = 0
Funcall = 8

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow0)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow1), Float(1.0f)), LoadVarInst(stack, fSlow0)), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("+", LoadVarInst(stack, fSlow1), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)), LoadVarInst(stack, fSlow3))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow7), Float(1.0f)), LoadVarInst(stack, fSlow6)), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("+", LoadVarInst(stack, fSlow7), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow7)), LoadVarInst(stack, fSlow10))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow10)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow7), Float(-1.0f)), LoadVarInst(stack, fSlow6)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow17, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow19, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "int", iSlow20, BinopInst(">", LoadVarInst(stack, fSlow19), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow21, CastInst("float", LoadVarInst(struct, fHslider5)))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), FunCallInst("fabsf", LoadVarInst(stack, fSlow19)))), LoadVarInst(stack, fSlow21))))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("/", LoadVarInst(struct, fConst4), LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow24))))
	DeclareVarInst(stack, "float", fSlow26, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow1), Float(-1.0f)), LoadVarInst(stack, fSlow0)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow27, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider6)))))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow24))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 134
Store = 31
Binop = 99
Numbers = 45
Declare = 13
Cast = 2
Select = 0
Loop = 1
Funcall = 4

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fTemp0))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec4[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow12), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fTemp0)), BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fVec0[Int32(1)]))))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec4[Int32(0)]), BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec3[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec3[Int32(2)]))))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow12), BinopInst("+", LoadVarInst(stack, fTemp0), LoadVarInst(struct, fVec0[Int32(1)])))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec6[Int32(0)]), BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec5[Int32(2)]))))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow18), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec7[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp1, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-49.0f)))))
		DeclareVarInst(stack, "float", fTemp2, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp1))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp2)))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("/", LoadVarInst(stack, fTemp1), FunCallInst("sinf", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp1)))))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(stack, fTemp4)))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(stack, fSlow23), LoadVarInst(stack, fTemp4)))
		DeclareVarInst(stack, "float", fTemp7, Select2Inst(LoadVarInst(stack, iSlow20) LoadVarInst(stack, fTemp6) LoadVarInst(stack, fTemp5)))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp2)))))))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp2)), Float(1.0f)))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec3[Int32(0)])), BinopInst("*", LoadVarInst(stack, fSlow16), LoadVarInst(struct, fRec3[Int32(1)]))), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec3[Int32(2)]))), BinopInst("*", LoadVarInst(stack, fSlow17), BinopInst("+", LoadVarInst(struct, fRec5[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec5[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec5[Int32(1)]))))))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp2)), Float(1.0f))), LoadVarInst(stack, fTemp8)), LoadVarInst(stack, fTemp9))))
		DeclareVarInst(stack, "float", fTemp10, Select2Inst(LoadVarInst(stack, iSlow20) LoadVarInst(stack, fTemp5) LoadVarInst(stack, fTemp6)))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("/", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp2)), Float(1.0f)))), BinopInst("*", LoadVarInst(struct, fRec2[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp2)), Float(1.0f)))), LoadVarInst(stack, fTemp9)))
		StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp11))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", LoadVarInst(struct, fVec1[Int32(1)]), LoadVarInst(stack, fTemp11)))))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(struct, fRec0[Int32(2)]))))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow28), LoadVarInst(struct, fVec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fTemp11))))))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec9[Int32(0)]), BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(struct, fRec8[Int32(2)]))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec0[Int32(1)])))), BinopInst("*", LoadVarInst(stack, fSlow27), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(struct, fRec8[Int32(0)])), BinopInst("*", LoadVarInst(stack, fSlow29), LoadVarInst(struct, fRec8[Int32(1)]))), BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(struct, fRec8[Int32(2)]))))))))
		StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fVec0[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec3[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec5[3])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "float", fConst5)
	DeclareVarInst(struct, float, fRec2[3])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec8[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst2, BinopInst("/", Float(1382.30078f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(1382.30078f), LoadVarInst(struct, fConst3)))
	StoreVarInst(struct, fConst5, BinopInst("*", Float(2764.60156f), LoadVarInst(struct, fConst3)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(8000.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(200.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(49.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(40.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(3))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
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
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(3))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(3))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
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
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, "float", fSlow0, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider0)))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow0)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow1), Float(1.0f)), LoadVarInst(stack, fSlow0)), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("+", LoadVarInst(stack, fSlow1), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow1)), LoadVarInst(stack, fSlow3))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow6, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow6)))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow7), Float(1.0f)), LoadVarInst(stack, fSlow6)), Float(1.0f))))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow6))))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("+", LoadVarInst(stack, fSlow7), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("-", Float(0.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow7)), LoadVarInst(stack, fSlow10))))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow10)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow7), Float(-1.0f)), LoadVarInst(stack, fSlow6)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow16, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow17, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "float", fSlow18, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow19, CastInst("float", LoadVarInst(struct, fHslider4)))
	DeclareVarInst(stack, "int", iSlow20, BinopInst(">", LoadVarInst(stack, fSlow19), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow21, CastInst("float", LoadVarInst(struct, fHslider5)))
	DeclareVarInst(stack, "float", fSlow22, BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("/", FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), FunCallInst("fabsf", LoadVarInst(stack, fSlow19)))), LoadVarInst(stack, fSlow21))))
	DeclareVarInst(stack, "float", fSlow23, BinopInst("/", LoadVarInst(struct, fConst4), LoadVarInst(stack, fSlow21)))
	DeclareVarInst(stack, "float", fSlow24, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow0))))
	DeclareVarInst(stack, "float", fSlow25, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fSlow24))))
	DeclareVarInst(stack, "float", fSlow26, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow1), Float(-1.0f)), LoadVarInst(stack, fSlow0)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow27, FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider6)))))
	DeclareVarInst(stack, "float", fSlow28, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow1)))
	DeclareVarInst(stack, "float", fSlow29, BinopInst("*", Float(2.0f), BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow24))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fVec0[Int32(0)], LoadVarInst(stack, fTemp0))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec4[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow12), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow7), LoadVarInst(stack, fTemp0)), BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fVec0[Int32(1)]))))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec4[Int32(0)]), BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec3[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec3[Int32(2)]))))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow11), LoadVarInst(struct, fRec6[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow12), BinopInst("+", LoadVarInst(stack, fTemp0), LoadVarInst(struct, fVec0[Int32(1)])))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec6[Int32(0)]), BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow14), LoadVarInst(struct, fRec5[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow15), LoadVarInst(struct, fRec5[Int32(2)]))))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow18), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec7[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp1, FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", LoadVarInst(struct, fRec7[Int32(0)]), Float(-49.0f)))))
			DeclareVarInst(stack, "float", fTemp2, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp1))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp2)))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("/", LoadVarInst(stack, fTemp1), FunCallInst("sinf", BinopInst("*", LoadVarInst(struct, fConst5), LoadVarInst(stack, fTemp1)))))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fSlow22), LoadVarInst(stack, fTemp4)))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(stack, fSlow23), LoadVarInst(stack, fTemp4)))
			DeclareVarInst(stack, "float", fTemp7, Select2Inst(LoadVarInst(stack, iSlow20) LoadVarInst(stack, fTemp6) LoadVarInst(stack, fTemp5)))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(struct, fRec2[Int32(1)]), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp2)))))))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp2)), Float(1.0f)))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(stack, fSlow8), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec3[Int32(0)])), BinopInst("*", LoadVarInst(stack, fSlow16), LoadVarInst(struct, fRec3[Int32(1)]))), BinopInst("*", LoadVarInst(stack, fSlow9), LoadVarInst(struct, fRec3[Int32(2)]))), BinopInst("*", LoadVarInst(stack, fSlow17), BinopInst("+", LoadVarInst(struct, fRec5[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec5[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec5[Int32(1)]))))))), BinopInst("/", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec2[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp2)), Float(1.0f))), LoadVarInst(stack, fTemp8)), LoadVarInst(stack, fTemp9))))
			DeclareVarInst(stack, "float", fTemp10, Select2Inst(LoadVarInst(stack, iSlow20) LoadVarInst(stack, fTemp5) LoadVarInst(stack, fTemp6)))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("/", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp2)), Float(1.0f)))), BinopInst("*", LoadVarInst(struct, fRec2[Int32(2)]), BinopInst("+", BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp2)), Float(1.0f)))), LoadVarInst(stack, fTemp9)))
			StoreVarInst(struct, fVec1[Int32(0)], LoadVarInst(stack, fTemp11))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", LoadVarInst(struct, fVec1[Int32(1)]), LoadVarInst(stack, fTemp11)))))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec1[Int32(0)]), BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), LoadVarInst(struct, fRec0[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(struct, fRec0[Int32(2)]))))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec9[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow5), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow28), LoadVarInst(struct, fVec1[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fTemp11))))))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("-", LoadVarInst(struct, fRec9[Int32(0)]), BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow25), LoadVarInst(struct, fRec8[Int32(1)])), BinopInst("*", LoadVarInst(stack, fSlow26), LoadVarInst(struct, fRec8[Int32(2)]))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fSlow2), BinopInst("+", BinopInst("+", LoadVarInst(struct, fRec0[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec0[Int32(1)])))), BinopInst("*", LoadVarInst(stack, fSlow27), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(struct, fRec8[Int32(0)])), BinopInst("*", LoadVarInst(stack, fSlow29), LoadVarInst(struct, fRec8[Int32(1)]))), BinopInst("*", LoadVarInst(stack, fSlow24), LoadVarInst(struct, fRec8[Int32(2)]))))))))
			StoreVarInst(struct, fVec0[Int32(1)], LoadVarInst(struct, fVec0[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(2)], LoadVarInst(struct, fRec3[Int32(1)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(2)], LoadVarInst(struct, fRec5[Int32(1)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(2)], LoadVarInst(struct, fRec2[Int32(1)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(2)], LoadVarInst(struct, fRec0[Int32(1)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(2)], LoadVarInst(struct, fRec8[Int32(1)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 168 bytes
Heap size = 172 bytes
Stack size in compute = 136 bytes

