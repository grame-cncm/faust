======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenHorizontalBox("flute")
	OpenVerticalBox("blower")
	AddMetaDeclareInst(fHslider3, "0", "")
	AddHorizontalSlider("pressure", fHslider3, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider4, "1", "")
	AddHorizontalSlider("breathGain", fHslider4, 0.100000001f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider5, "2", "")
	AddHorizontalSlider("breathCutoff", fHslider5, 2000.0f, 20.0f, 20000.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider2, "3", "")
	AddHorizontalSlider("vibratoFreq", fHslider2, 5.0f, 0.100000001f, 10.0f, 0.100000001f)
	AddMetaDeclareInst(fHslider1, "4", "")
	AddHorizontalSlider("vibratoGain", fHslider1, 0.25f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	OpenVerticalBox("fluteModel")
	AddMetaDeclareInst(fHslider6, "0", "")
	AddHorizontalSlider("tubeLength", fHslider6, 0.800000012f, 0.00999999978f, 3.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider7, "1", "")
	AddHorizontalSlider("mouthPosition", fHslider7, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	AddMetaDeclareInst(fHslider0, "2", "")
	AddHorizontalSlider("outGain", fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
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
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, int, iRec27[2])
	DeclareVarInst(struct, float, fRec26[3])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec29[2048])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fVec2[2048])
	DeclareVarInst(struct, float, fVec3[2])
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
	StoreVarInst(struct, fConst2, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.25f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(2000.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.80000000000000004f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.5f)))
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
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec27[LoadVarInst(loop, l6)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2048))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2048))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
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
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2048))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2048))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 23
Store = 0
Binop = 20
Numbers = 15
Declare = 18
Cast = 8
Select = 0
Loop = 0
Funcall = 4

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.0299999993f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("sinf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("cosf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider5)))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow8), Float(1.41421354f)), LoadVarInst(stack, fSlow7)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", Float(0.0500000007f), BinopInst("/", CastInst("float", LoadVarInst(struct, fHslider4)), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow8), Float(-1.41421354f)), LoadVarInst(stack, fSlow7)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow7))))))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider6))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider7))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 252
Store = 45
Binop = 220
Numbers = 152
Declare = 73
Cast = 28
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
		StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec25[Int32(1)]))))
		StoreVarInst(struct, iRec27[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec27[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec27[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow11), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec26[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fRec26[Int32(1)]))))))
		StoreVarInst(struct, fRec28[Int32(0)], LoadVarInst(struct, fRec1[Int32(1)]))
		StoreVarInst(struct, fRec29[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fRec28[Int32(1)])))
		DeclareVarInst(stack, "int", iRec30, Int32(0))
		StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec31[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("+", LoadVarInst(struct, fRec31[Int32(0)]), Float(0.270000011f)))
		StoreVarInst(struct, fRec32[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow15), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec32[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", Float(0.400000006f), BinopInst("+", LoadVarInst(struct, fRec32[Int32(0)]), Float(-0.5f))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("*", LoadVarInst(stack, fTemp0), BinopInst("+", LoadVarInst(stack, fTemp1), Float(0.270000011f)))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp4, CastInst("int", LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "int", iTemp5, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp4))))), Int32(1)))
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
		DeclareVarInst(stack, "int", iTemp16, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(2)))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "int", iTemp19, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(1)))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp9)))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp11))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp9)))
		DeclareVarInst(stack, "int", iTemp24, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(3)))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13)))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "int", iTemp27, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(4)))))), Int32(1)))
		StoreVarInst(struct, fVec1[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp5)), Int32(2047))]), LoadVarInst(stack, fTemp8)), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp16)), Int32(2047))])), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp19)), Int32(2047))]), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp24)), Int32(2047))])), LoadVarInst(stack, fTemp25)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp27)), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec23[Int32(0)])), BinopInst("*", LoadVarInst(struct, fRec25[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", LoadVarInst(struct, fRec26[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec26[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec26[Int32(1)]))))), Float(1.0f)))), BinopInst("*", Float(0.5f), LoadVarInst(struct, fVec1[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("+", BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec7[Int32(1)])), FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), BinopInst("*", LoadVarInst(stack, fTemp28), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp28)), Float(-1.0f)))))))
		StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp29))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("*", LoadVarInst(stack, fTemp0), BinopInst("-", Float(0.730000019f), LoadVarInst(stack, fTemp1)))))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(stack, fTemp30), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp32, CastInst("int", LoadVarInst(stack, fTemp31)))
		DeclareVarInst(stack, "int", iTemp33, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp32))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp34, FunCallInst("floorf", LoadVarInst(stack, fTemp31)))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp35)))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp37))))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fTemp40, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp39))))
		DeclareVarInst(stack, "float", fTemp41, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp34))))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp41))))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("-", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp34)))
		DeclareVarInst(stack, "int", iTemp44, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp32), Int32(2)))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp45, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp39)))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp41))))
		DeclareVarInst(stack, "int", iTemp47, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp32), Int32(1)))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp48, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp37)))
		DeclareVarInst(stack, "float", fTemp49, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp39))))
		DeclareVarInst(stack, "float", fTemp50, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp41))))
		DeclareVarInst(stack, "float", fTemp51, BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(stack, fTemp37)))
		DeclareVarInst(stack, "int", iTemp52, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp32), Int32(3)))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp53, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp41)))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(stack, fTemp39)))
		DeclareVarInst(stack, "int", iTemp55, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp32), Int32(4)))))), Int32(1)))
		StoreVarInst(struct, fVec3[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp33)), Int32(2047))]), LoadVarInst(stack, fTemp36)), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp42)), BinopInst("*", LoadVarInst(stack, fTemp43), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp44)), Int32(2047))])), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp47)), Int32(2047))]), LoadVarInst(stack, fTemp48)), LoadVarInst(stack, fTemp49)), LoadVarInst(stack, fTemp50))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp52)), Int32(2047))])), LoadVarInst(stack, fTemp53)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp55)), Int32(2047))])))))))
		StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(struct, fVec3[Int32(1)]))
		DeclareVarInst(stack, "int", iRec21, LoadVarInst(stack, iRec30))
		DeclareVarInst(stack, "float", fRec16, LoadVarInst(stack, fRec19))
		DeclareVarInst(stack, "float", fRec17, LoadVarInst(struct, fRec20[Int32(0)]))
		DeclareVarInst(stack, "float", fRec18, BinopInst("+", LoadVarInst(struct, fRec20[Int32(0)]), CastInst("float", LoadVarInst(stack, iRec21))))
		StoreVarInst(struct, fRec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec16))
		DeclareVarInst(stack, "float", fRec12, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp42)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp33)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp43), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(stack, fTemp53)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp52)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(stack, fTemp49)), LoadVarInst(stack, fTemp50)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp47)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp44)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp55)), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fRec13, LoadVarInst(stack, fRec17))
		DeclareVarInst(stack, "float", fRec14, LoadVarInst(stack, fRec18))
		StoreVarInst(struct, fRec7[Int32(0)], LoadVarInst(stack, fRec12))
		DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec7[Int32(1)]))
		DeclareVarInst(stack, "float", fRec9, LoadVarInst(stack, fRec13))
		DeclareVarInst(stack, "float", fRec10, LoadVarInst(stack, fRec14))
		StoreVarInst(struct, fRec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec8))
		DeclareVarInst(stack, "float", fRec4, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp5)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp25)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp24)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp20), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp19)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp16)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp27)), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
		DeclareVarInst(stack, "float", fRec6, LoadVarInst(stack, fRec10))
		StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(stack, fRec4))
		StoreVarInst(struct, fRec2[Int32(0)], LoadVarInst(stack, fRec6))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("*", Float(0.995000005f), LoadVarInst(struct, fRec0[Int32(1)]))), LoadVarInst(struct, fRec2[Int32(1)])))
		DeclareVarInst(stack, "float", fTemp56, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec0[Int32(0)])))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp56)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp56)))
		StoreVarInst(struct, iRec15[Int32(1)], LoadVarInst(struct, iRec15[Int32(0)]))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, iRec27[Int32(1)], LoadVarInst(struct, iRec27[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(2)], LoadVarInst(struct, fRec26[Int32(1)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
		StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
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
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, int, iRec27[2])
	DeclareVarInst(struct, float, fRec26[3])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec29[2048])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fVec1[2])
	DeclareVarInst(struct, float, fVec2[2048])
	DeclareVarInst(struct, float, fVec3[2])
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
	StoreVarInst(struct, fConst2, BinopInst("/", Float(3.14159274f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.25f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(5.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.10000000000000001f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(2000.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.80000000000000004f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.5f)))
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
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec27[LoadVarInst(loop, l6)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(3))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2048))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2048))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
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
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2048))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2048))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", Float(0.0299999993f), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow3, FunCallInst("sinf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow4, FunCallInst("cosf", LoadVarInst(stack, fSlow2)))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("-", Float(0.0f), LoadVarInst(stack, fSlow3)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow7, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst2), CastInst("float", LoadVarInst(struct, fHslider5)))))
	DeclareVarInst(stack, "float", fSlow8, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow7)))
	DeclareVarInst(stack, "float", fSlow9, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow8), Float(1.41421354f)), LoadVarInst(stack, fSlow7)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow10, BinopInst("*", Float(0.0500000007f), BinopInst("/", CastInst("float", LoadVarInst(struct, fHslider4)), LoadVarInst(stack, fSlow9))))
	DeclareVarInst(stack, "float", fSlow11, BinopInst("/", Float(1.0f), LoadVarInst(stack, fSlow9)))
	DeclareVarInst(stack, "float", fSlow12, BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(stack, fSlow8), Float(-1.41421354f)), LoadVarInst(stack, fSlow7)), Float(1.0f)))
	DeclareVarInst(stack, "float", fSlow13, BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fSlow7))))))
	DeclareVarInst(stack, "float", fSlow14, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider6))))
	DeclareVarInst(stack, "float", fSlow15, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider7))))
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
			StoreVarInst(struct, fRec25[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec25[Int32(1)]))))
			StoreVarInst(struct, iRec27[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec27[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("-", BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec27[Int32(0)]))), BinopInst("*", LoadVarInst(stack, fSlow11), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow12), LoadVarInst(struct, fRec26[Int32(2)])), BinopInst("*", LoadVarInst(stack, fSlow13), LoadVarInst(struct, fRec26[Int32(1)]))))))
			StoreVarInst(struct, fRec28[Int32(0)], LoadVarInst(struct, fRec1[Int32(1)]))
			StoreVarInst(struct, fRec29[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("*", Float(0.949999988f), LoadVarInst(struct, fRec28[Int32(1)])))
			DeclareVarInst(stack, "int", iRec30, Int32(0))
			StoreVarInst(struct, fRec31[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow14), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec31[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("+", LoadVarInst(struct, fRec31[Int32(0)]), Float(0.270000011f)))
			StoreVarInst(struct, fRec32[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow15), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec32[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", Float(0.400000006f), BinopInst("+", LoadVarInst(struct, fRec32[Int32(0)]), Float(-0.5f))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("*", LoadVarInst(stack, fTemp0), BinopInst("+", LoadVarInst(stack, fTemp1), Float(0.270000011f)))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", LoadVarInst(stack, fTemp2), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp4, CastInst("int", LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "int", iTemp5, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp4))))), Int32(1)))
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
			DeclareVarInst(stack, "int", iTemp16, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(2)))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "int", iTemp19, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(1)))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp9)))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp11))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp9)))
			DeclareVarInst(stack, "int", iTemp24, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(3)))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp13)))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "int", iTemp27, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp4), Int32(4)))))), Int32(1)))
			StoreVarInst(struct, fVec1[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp5)), Int32(2047))]), LoadVarInst(stack, fTemp8)), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp16)), Int32(2047))])), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp19)), Int32(2047))]), LoadVarInst(stack, fTemp20)), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp24)), Int32(2047))])), LoadVarInst(stack, fTemp25)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fRec29[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp27)), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow1), LoadVarInst(struct, fRec23[Int32(0)])), BinopInst("*", LoadVarInst(struct, fRec25[Int32(0)]), BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow10), BinopInst("+", LoadVarInst(struct, fRec26[Int32(2)]), BinopInst("+", LoadVarInst(struct, fRec26[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec26[Int32(1)]))))), Float(1.0f)))), BinopInst("*", Float(0.5f), LoadVarInst(struct, fVec1[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("+", BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec7[Int32(1)])), FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), BinopInst("*", LoadVarInst(stack, fTemp28), BinopInst("+", FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp28)), Float(-1.0f)))))))
			StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fTemp29))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("*", LoadVarInst(stack, fTemp0), BinopInst("-", Float(0.730000019f), LoadVarInst(stack, fTemp1)))))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("+", LoadVarInst(stack, fTemp30), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp32, CastInst("int", LoadVarInst(stack, fTemp31)))
			DeclareVarInst(stack, "int", iTemp33, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), LoadVarInst(stack, iTemp32))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp34, FunCallInst("floorf", LoadVarInst(stack, fTemp31)))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-1.0f), LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp35)))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-2.0f), LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp37))))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-3.0f), LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fTemp40, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp39))))
			DeclareVarInst(stack, "float", fTemp41, BinopInst("+", LoadVarInst(stack, fTemp30), BinopInst("-", Float(-4.0f), LoadVarInst(stack, fTemp34))))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.25f), LoadVarInst(stack, fTemp41))))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("-", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp34)))
			DeclareVarInst(stack, "int", iTemp44, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp32), Int32(2)))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp45, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp39)))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp41))))
			DeclareVarInst(stack, "int", iTemp47, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp32), Int32(1)))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp48, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp37)))
			DeclareVarInst(stack, "float", fTemp49, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp39))))
			DeclareVarInst(stack, "float", fTemp50, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp41))))
			DeclareVarInst(stack, "float", fTemp51, BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(stack, fTemp37)))
			DeclareVarInst(stack, "int", iTemp52, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp32), Int32(3)))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp53, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp41)))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(stack, fTemp39)))
			DeclareVarInst(stack, "int", iTemp55, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(stack, iTemp32), Int32(4)))))), Int32(1)))
			StoreVarInst(struct, fVec3[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp33)), Int32(2047))]), LoadVarInst(stack, fTemp36)), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp42)), BinopInst("*", LoadVarInst(stack, fTemp43), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp44)), Int32(2047))])), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp47)), Int32(2047))]), LoadVarInst(stack, fTemp48)), LoadVarInst(stack, fTemp49)), LoadVarInst(stack, fTemp50))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp52)), Int32(2047))])), LoadVarInst(stack, fTemp53)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp55)), Int32(2047))])))))))
			StoreVarInst(struct, fRec20[Int32(0)], LoadVarInst(struct, fVec3[Int32(1)]))
			DeclareVarInst(stack, "int", iRec21, LoadVarInst(stack, iRec30))
			DeclareVarInst(stack, "float", fRec16, LoadVarInst(stack, fRec19))
			DeclareVarInst(stack, "float", fRec17, LoadVarInst(struct, fRec20[Int32(0)]))
			DeclareVarInst(stack, "float", fRec18, BinopInst("+", LoadVarInst(struct, fRec20[Int32(0)]), CastInst("float", LoadVarInst(stack, iRec21))))
			StoreVarInst(struct, fRec11[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec16))
			DeclareVarInst(stack, "float", fRec12, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp42)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp33)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp43), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp51), LoadVarInst(stack, fTemp53)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp52)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp48), LoadVarInst(stack, fTemp49)), LoadVarInst(stack, fTemp50)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp47)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp35), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46)), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp44)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp54), LoadVarInst(struct, fRec11[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp55)), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fRec13, LoadVarInst(stack, fRec17))
			DeclareVarInst(stack, "float", fRec14, LoadVarInst(stack, fRec18))
			StoreVarInst(struct, fRec7[Int32(0)], LoadVarInst(stack, fRec12))
			DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec7[Int32(1)]))
			DeclareVarInst(stack, "float", fRec9, LoadVarInst(stack, fRec13))
			DeclareVarInst(stack, "float", fRec10, LoadVarInst(stack, fRec14))
			StoreVarInst(struct, fRec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec8))
			DeclareVarInst(stack, "float", fRec4, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp10)), LoadVarInst(stack, fTemp12)), LoadVarInst(stack, fTemp14)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp5)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp15), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp23), LoadVarInst(stack, fTemp25)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp24)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp20), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp19)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp17)), LoadVarInst(stack, fTemp18)), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp16)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(struct, fRec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp27)), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
			DeclareVarInst(stack, "float", fRec6, LoadVarInst(stack, fRec10))
			StoreVarInst(struct, fRec1[Int32(0)], LoadVarInst(stack, fRec4))
			StoreVarInst(struct, fRec2[Int32(0)], LoadVarInst(stack, fRec6))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(struct, fRec2[Int32(0)]), BinopInst("*", Float(0.995000005f), LoadVarInst(struct, fRec0[Int32(1)]))), LoadVarInst(struct, fRec2[Int32(1)])))
			DeclareVarInst(stack, "float", fTemp56, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(struct, fRec0[Int32(0)])))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp56)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fTemp56)))
			StoreVarInst(struct, iRec15[Int32(1)], LoadVarInst(struct, iRec15[Int32(0)]))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, iRec27[Int32(1)], LoadVarInst(struct, iRec27[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(2)], LoadVarInst(struct, fRec26[Int32(1)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, fVec1[Int32(1)], LoadVarInst(struct, fVec1[Int32(0)]))
			StoreVarInst(struct, fVec3[Int32(1)], LoadVarInst(struct, fVec3[Int32(0)]))
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
Heap size real = 32944 bytes
Heap size = 32976 bytes
Stack size in compute = 80 bytes

