======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("clarinet")
	AddHorizontalSlider("kb0k0status", fHslider1, 0.0f, 0.0f, 1.0f, 1.0f)
	AddHorizontalSlider("kb0k1status", fHslider2, 0.0f, 0.0f, 1.0f, 1.0f)
	AddHorizontalSlider("kb0k2status", fHslider3, 0.0f, 0.0f, 1.0f, 1.0f)
	AddHorizontalSlider("kb0k3status", fHslider8, 0.0f, 0.0f, 1.0f, 1.0f)
	AddHorizontalSlider("kb1k0status", fHslider4, 0.0f, 0.0f, 1.0f, 1.0f)
	AddHorizontalSlider("kb1k1status", fHslider5, 0.0f, 0.0f, 1.0f, 1.0f)
	AddHorizontalSlider("kb1k2status", fHslider6, 0.0f, 0.0f, 1.0f, 1.0f)
	AddHorizontalSlider("kb1k3status", fHslider7, 0.0f, 0.0f, 1.0f, 1.0f)
	AddHorizontalSlider("kb1k4status", fHslider9, 0.0f, 0.0f, 1.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "acc", "1 1 -10 0 10")
	AddHorizontalSlider("reedStiffness", fHslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, int, iRec6[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec15[2048])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, int, iRec21[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, int, iVec1[2])
	DeclareVarInst(struct, int, iRec22[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec2[2048])
	DeclareVarInst(struct, float, fRec0[2])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
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
	StoreVarInst(struct, fConst1, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(50.0f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst2, BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst1)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, iRec6[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2048))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l7)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec21[LoadVarInst(loop, l8)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec1[LoadVarInst(loop, l9)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec22[LoadVarInst(loop, l10)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2048))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 100
Store = 0
Binop = 89
Numbers = 36
Declare = 38
Cast = 20
Select = 0
Loop = 0
Funcall = 9

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "int", iSlow1, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "int", iSlow2, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(1)))
	DeclareVarInst(stack, "int", iSlow3, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(1)))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("&", LoadVarInst(stack, iSlow2), LoadVarInst(stack, iSlow4)))
	DeclareVarInst(stack, "int", iSlow6, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider3)))))
	DeclareVarInst(stack, "int", iSlow7, BinopInst("==", LoadVarInst(stack, iSlow6), Int32(0)))
	DeclareVarInst(stack, "int", iSlow8, BinopInst("&", LoadVarInst(stack, iSlow5), LoadVarInst(stack, iSlow7)))
	DeclareVarInst(stack, "int", iSlow9, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider4)))))
	DeclareVarInst(stack, "int", iSlow10, BinopInst("==", LoadVarInst(stack, iSlow9), Int32(0)))
	DeclareVarInst(stack, "int", iSlow11, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider5)))))
	DeclareVarInst(stack, "int", iSlow12, BinopInst("==", LoadVarInst(stack, iSlow11), Int32(0)))
	DeclareVarInst(stack, "int", iSlow13, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider6)))))
	DeclareVarInst(stack, "int", iSlow14, BinopInst("==", LoadVarInst(stack, iSlow13), Int32(0)))
	DeclareVarInst(stack, "int", iSlow15, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider7)))))
	DeclareVarInst(stack, "int", iSlow16, BinopInst("==", LoadVarInst(stack, iSlow15), Int32(0)))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("*", Float(4.0f), BinopInst("-", Float(1.0f), CastInst("float", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow8), LoadVarInst(stack, iSlow10)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16))))))
	DeclareVarInst(stack, "int", iSlow18, BinopInst("==", LoadVarInst(stack, iSlow6), Int32(1)))
	DeclareVarInst(stack, "int", iSlow19, BinopInst("&", LoadVarInst(stack, iSlow5), LoadVarInst(stack, iSlow18)))
	DeclareVarInst(stack, "int", iSlow20, BinopInst("==", LoadVarInst(stack, iSlow9), Int32(1)))
	DeclareVarInst(stack, "int", iSlow21, BinopInst("&", LoadVarInst(stack, iSlow19), LoadVarInst(stack, iSlow20)))
	DeclareVarInst(stack, "int", iSlow22, BinopInst("==", LoadVarInst(stack, iSlow11), Int32(1)))
	DeclareVarInst(stack, "int", iSlow23, BinopInst("&", LoadVarInst(stack, iSlow21), LoadVarInst(stack, iSlow22)))
	DeclareVarInst(stack, "int", iSlow24, BinopInst("&", LoadVarInst(stack, iSlow23), BinopInst("==", LoadVarInst(stack, iSlow13), Int32(1))))
	DeclareVarInst(stack, "int", iSlow25, BinopInst("==", LoadVarInst(stack, iSlow15), Int32(1)))
	DeclareVarInst(stack, "int", iSlow26, BinopInst("&", LoadVarInst(stack, iSlow23), LoadVarInst(stack, iSlow14)))
	DeclareVarInst(stack, "int", iSlow27, BinopInst("&", LoadVarInst(stack, iSlow19), LoadVarInst(stack, iSlow10)))
	DeclareVarInst(stack, "int", iSlow28, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(0)))
	DeclareVarInst(stack, "int", iSlow29, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(0)))
	DeclareVarInst(stack, "int", iSlow30, BinopInst("&", LoadVarInst(stack, iSlow2), LoadVarInst(stack, iSlow29)))
	DeclareVarInst(stack, "int", iSlow31, BinopInst("+", BinopInst("*", Int32(13), BinopInst("&", LoadVarInst(stack, iSlow24), LoadVarInst(stack, iSlow25))), BinopInst("+", BinopInst("*", Int32(11), BinopInst("&", LoadVarInst(stack, iSlow24), LoadVarInst(stack, iSlow16))), BinopInst("+", BinopInst("*", Int32(10), BinopInst("&", LoadVarInst(stack, iSlow26), LoadVarInst(stack, iSlow25))), BinopInst("+", BinopInst("*", Int32(9), BinopInst("&", LoadVarInst(stack, iSlow26), LoadVarInst(stack, iSlow16))), BinopInst("+", BinopInst("*", Int32(8), BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow21), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16))), BinopInst("+", BinopInst("*", Int32(7), BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow27), LoadVarInst(stack, iSlow22)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16))), BinopInst("+", BinopInst("*", Int32(6), BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow27), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow28), LoadVarInst(stack, iSlow4)), LoadVarInst(stack, iSlow7)), LoadVarInst(stack, iSlow10)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16)), BinopInst("*", Int32(2), BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow30), LoadVarInst(stack, iSlow7)), LoadVarInst(stack, iSlow10)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16)))), BinopInst("*", Int32(3), BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow30), LoadVarInst(stack, iSlow18)), LoadVarInst(stack, iSlow10)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16)))), BinopInst("*", Int32(5), BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow8), LoadVarInst(stack, iSlow20)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16))))))))))))
	DeclareVarInst(stack, "int", iSlow32, BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow28), LoadVarInst(stack, iSlow29)), LoadVarInst(stack, iSlow7)), LoadVarInst(stack, iSlow10)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow25)))
	DeclareVarInst(stack, "int", iSlow33, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider8)))))
	DeclareVarInst(stack, "int", iSlow34, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider9)))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 150
Store = 34
Binop = 123
Numbers = 94
Declare = 40
Cast = 22
Select = 0
Loop = 1
Funcall = 16

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, iRec6[Int32(0)], Int32(0))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec13[Int32(1)]), LoadVarInst(struct, fRec11[Int32(1)]))))
		DeclareVarInst(stack, "float", fRec10, BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), CastInst("float", LoadVarInst(struct, iRec6[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp0, FunCallInst("fabsf", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)]))))
		StoreVarInst(struct, fRec18[Int32(0)], FunCallInst("max_f", LoadVarInst(stack, fTemp0), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp0)))))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec18[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", Float(0.699999988f), LoadVarInst(struct, fRec17[Int32(0)])))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(stack, fTemp1)))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec14[Int32(1)])))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec19[Int32(1)]))))
		StoreVarInst(struct, fRec15[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("*", LoadVarInst(stack, fTemp2), FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", Float(0.25999999f), LoadVarInst(struct, fRec19[Int32(0)])), Float(-0.439999998f))), Float(0.699999988f)))))))
		DeclareVarInst(stack, "int", iRec16, Int32(0))
		StoreVarInst(struct, iVec0[Int32(0)], LoadVarInst(stack, iSlow33))
		StoreVarInst(struct, iRec21[Int32(0)], BinopInst("+", BinopInst(">", BinopInst("-", LoadVarInst(stack, iSlow33), LoadVarInst(struct, iVec0[Int32(1)])), Int32(0)), LoadVarInst(struct, iRec21[Int32(1)])))
		StoreVarInst(struct, iVec1[Int32(0)], LoadVarInst(stack, iSlow34))
		StoreVarInst(struct, iRec22[Int32(0)], BinopInst("+", BinopInst(">", BinopInst("-", LoadVarInst(stack, iSlow34), LoadVarInst(struct, iVec1[Int32(1)])), Int32(0)), LoadVarInst(struct, iRec22[Int32(1)])))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("/", Float(0.000772727246f), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("-", LoadVarInst(stack, fSlow17), CastInst("float", BinopInst("+", LoadVarInst(stack, iSlow31), BinopInst("*", Int32(12), BinopInst("-", LoadVarInst(stack, iSlow32), BinopInst("-", LoadVarInst(struct, iRec21[Int32(0)]), LoadVarInst(struct, iRec22[Int32(0)]))))))))))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec20[Int32(0)])), Float(-0.0500000007f))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(stack, fTemp3), Float(-1.49999499f)))
		DeclareVarInst(stack, "int", iTemp5, CastInst("int", LoadVarInst(stack, fTemp4)))
		DeclareVarInst(stack, "int", iTemp6, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp5)))))), Int32(1)))
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
		DeclareVarInst(stack, "int", iTemp17, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(2))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp14))))
		DeclareVarInst(stack, "int", iTemp20, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(1))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp14))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "int", iTemp25, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(3))))))), Int32(1)))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp14)))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "int", iTemp28, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(4))))))), Int32(1)))
		StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp6)), Int32(2047))]), LoadVarInst(stack, fTemp9)), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(stack, fTemp15)), BinopInst("*", LoadVarInst(stack, fTemp16), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp17)), Int32(2047))])), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp19))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp20)), Int32(2047))]), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp25)), Int32(2047))])), LoadVarInst(stack, fTemp26)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp27), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp28)), Int32(2047))])))))))
		StoreVarInst(struct, fRec11[Int32(0)], LoadVarInst(struct, fVec2[Int32(1)]))
		DeclareVarInst(stack, "int", iRec12, LoadVarInst(stack, iRec16))
		DeclareVarInst(stack, "float", fRec7, LoadVarInst(stack, fRec10))
		DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec11[Int32(0)]))
		DeclareVarInst(stack, "float", fRec9, BinopInst("+", LoadVarInst(struct, fRec11[Int32(0)]), CastInst("float", LoadVarInst(stack, iRec12))))
		StoreVarInst(struct, fRec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec7))
		DeclareVarInst(stack, "float", fRec3, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(stack, fTemp15)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp6)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp16), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp26)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp25)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp20)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp19)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp17)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp27), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp28)), Int32(2047))])))))))
		DeclareVarInst(stack, "float", fRec4, LoadVarInst(stack, fRec8))
		DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
		StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec3))
		DeclareVarInst(stack, "float", fRec1, LoadVarInst(stack, fRec5))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec1)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec1)))
		StoreVarInst(struct, iRec6[Int32(1)], LoadVarInst(struct, iRec6[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, iRec21[Int32(1)], LoadVarInst(struct, iRec21[Int32(0)]))
		StoreVarInst(struct, iVec1[Int32(1)], LoadVarInst(struct, iVec1[Int32(0)]))
		StoreVarInst(struct, iRec22[Int32(1)], LoadVarInst(struct, iRec22[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst(struct, int, iRec6[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fRec15[2048])
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, "float", fConst4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider8)
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, int, iRec21[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider9)
	DeclareVarInst(struct, int, iVec1[2])
	DeclareVarInst(struct, int, iRec22[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fVec2[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec2[2048])
	DeclareVarInst(struct, float, fRec0[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, fConst1, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(50.0f), LoadVarInst(struct, fConst0)))))
	StoreVarInst(struct, fConst2, BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst1)))
	StoreVarInst(struct, fConst3, BinopInst("*", Float(0.00882352982f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fConst4, BinopInst("*", Float(0.00147058826f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider8, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider9, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2048))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l7)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec21[LoadVarInst(loop, l8)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec1[LoadVarInst(loop, l9)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec22[LoadVarInst(loop, l10)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2048))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "int", iSlow1, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider1)))))
	DeclareVarInst(stack, "int", iSlow2, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(1)))
	DeclareVarInst(stack, "int", iSlow3, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider2)))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(1)))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("&", LoadVarInst(stack, iSlow2), LoadVarInst(stack, iSlow4)))
	DeclareVarInst(stack, "int", iSlow6, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider3)))))
	DeclareVarInst(stack, "int", iSlow7, BinopInst("==", LoadVarInst(stack, iSlow6), Int32(0)))
	DeclareVarInst(stack, "int", iSlow8, BinopInst("&", LoadVarInst(stack, iSlow5), LoadVarInst(stack, iSlow7)))
	DeclareVarInst(stack, "int", iSlow9, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider4)))))
	DeclareVarInst(stack, "int", iSlow10, BinopInst("==", LoadVarInst(stack, iSlow9), Int32(0)))
	DeclareVarInst(stack, "int", iSlow11, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider5)))))
	DeclareVarInst(stack, "int", iSlow12, BinopInst("==", LoadVarInst(stack, iSlow11), Int32(0)))
	DeclareVarInst(stack, "int", iSlow13, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider6)))))
	DeclareVarInst(stack, "int", iSlow14, BinopInst("==", LoadVarInst(stack, iSlow13), Int32(0)))
	DeclareVarInst(stack, "int", iSlow15, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider7)))))
	DeclareVarInst(stack, "int", iSlow16, BinopInst("==", LoadVarInst(stack, iSlow15), Int32(0)))
	DeclareVarInst(stack, "float", fSlow17, BinopInst("*", Float(4.0f), BinopInst("-", Float(1.0f), CastInst("float", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow8), LoadVarInst(stack, iSlow10)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16))))))
	DeclareVarInst(stack, "int", iSlow18, BinopInst("==", LoadVarInst(stack, iSlow6), Int32(1)))
	DeclareVarInst(stack, "int", iSlow19, BinopInst("&", LoadVarInst(stack, iSlow5), LoadVarInst(stack, iSlow18)))
	DeclareVarInst(stack, "int", iSlow20, BinopInst("==", LoadVarInst(stack, iSlow9), Int32(1)))
	DeclareVarInst(stack, "int", iSlow21, BinopInst("&", LoadVarInst(stack, iSlow19), LoadVarInst(stack, iSlow20)))
	DeclareVarInst(stack, "int", iSlow22, BinopInst("==", LoadVarInst(stack, iSlow11), Int32(1)))
	DeclareVarInst(stack, "int", iSlow23, BinopInst("&", LoadVarInst(stack, iSlow21), LoadVarInst(stack, iSlow22)))
	DeclareVarInst(stack, "int", iSlow24, BinopInst("&", LoadVarInst(stack, iSlow23), BinopInst("==", LoadVarInst(stack, iSlow13), Int32(1))))
	DeclareVarInst(stack, "int", iSlow25, BinopInst("==", LoadVarInst(stack, iSlow15), Int32(1)))
	DeclareVarInst(stack, "int", iSlow26, BinopInst("&", LoadVarInst(stack, iSlow23), LoadVarInst(stack, iSlow14)))
	DeclareVarInst(stack, "int", iSlow27, BinopInst("&", LoadVarInst(stack, iSlow19), LoadVarInst(stack, iSlow10)))
	DeclareVarInst(stack, "int", iSlow28, BinopInst("==", LoadVarInst(stack, iSlow1), Int32(0)))
	DeclareVarInst(stack, "int", iSlow29, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(0)))
	DeclareVarInst(stack, "int", iSlow30, BinopInst("&", LoadVarInst(stack, iSlow2), LoadVarInst(stack, iSlow29)))
	DeclareVarInst(stack, "int", iSlow31, BinopInst("+", BinopInst("*", Int32(13), BinopInst("&", LoadVarInst(stack, iSlow24), LoadVarInst(stack, iSlow25))), BinopInst("+", BinopInst("*", Int32(11), BinopInst("&", LoadVarInst(stack, iSlow24), LoadVarInst(stack, iSlow16))), BinopInst("+", BinopInst("*", Int32(10), BinopInst("&", LoadVarInst(stack, iSlow26), LoadVarInst(stack, iSlow25))), BinopInst("+", BinopInst("*", Int32(9), BinopInst("&", LoadVarInst(stack, iSlow26), LoadVarInst(stack, iSlow16))), BinopInst("+", BinopInst("*", Int32(8), BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow21), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16))), BinopInst("+", BinopInst("*", Int32(7), BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow27), LoadVarInst(stack, iSlow22)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16))), BinopInst("+", BinopInst("*", Int32(6), BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow27), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow28), LoadVarInst(stack, iSlow4)), LoadVarInst(stack, iSlow7)), LoadVarInst(stack, iSlow10)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16)), BinopInst("*", Int32(2), BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow30), LoadVarInst(stack, iSlow7)), LoadVarInst(stack, iSlow10)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16)))), BinopInst("*", Int32(3), BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow30), LoadVarInst(stack, iSlow18)), LoadVarInst(stack, iSlow10)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16)))), BinopInst("*", Int32(5), BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow8), LoadVarInst(stack, iSlow20)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow16))))))))))))
	DeclareVarInst(stack, "int", iSlow32, BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", BinopInst("&", LoadVarInst(stack, iSlow28), LoadVarInst(stack, iSlow29)), LoadVarInst(stack, iSlow7)), LoadVarInst(stack, iSlow10)), LoadVarInst(stack, iSlow12)), LoadVarInst(stack, iSlow14)), LoadVarInst(stack, iSlow25)))
	DeclareVarInst(stack, "int", iSlow33, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider8)))))
	DeclareVarInst(stack, "int", iSlow34, CastInst("int", FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fHslider9)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec6[Int32(0)], Int32(0))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(struct, fRec13[Int32(1)]), LoadVarInst(struct, fRec11[Int32(1)]))))
			DeclareVarInst(stack, "float", fRec10, BinopInst("+", LoadVarInst(struct, fRec13[Int32(0)]), CastInst("float", LoadVarInst(struct, iRec6[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp0, FunCallInst("fabsf", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)]))))
			StoreVarInst(struct, fRec18[Int32(0)], FunCallInst("max_f", LoadVarInst(stack, fTemp0), BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec18[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(stack, fTemp0)))))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fConst1), LoadVarInst(struct, fRec17[Int32(1)])), BinopInst("*", LoadVarInst(struct, fConst2), LoadVarInst(struct, fRec18[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", Float(0.699999988f), LoadVarInst(struct, fRec17[Int32(0)])))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("+", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(stack, fTemp1)))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("-", Float(0.0f), LoadVarInst(struct, fRec14[Int32(1)])))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec19[Int32(1)]))))
			StoreVarInst(struct, fRec15[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], BinopInst("+", LoadVarInst(stack, fTemp1), BinopInst("*", LoadVarInst(stack, fTemp2), FunCallInst("max_f", Float(-1.0f), FunCallInst("min_f", Float(1.0f), BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp2), BinopInst("+", BinopInst("*", Float(0.25999999f), LoadVarInst(struct, fRec19[Int32(0)])), Float(-0.439999998f))), Float(0.699999988f)))))))
			DeclareVarInst(stack, "int", iRec16, Int32(0))
			StoreVarInst(struct, iVec0[Int32(0)], LoadVarInst(stack, iSlow33))
			StoreVarInst(struct, iRec21[Int32(0)], BinopInst("+", BinopInst(">", BinopInst("-", LoadVarInst(stack, iSlow33), LoadVarInst(struct, iVec0[Int32(1)])), Int32(0)), LoadVarInst(struct, iRec21[Int32(1)])))
			StoreVarInst(struct, iVec1[Int32(0)], LoadVarInst(stack, iSlow34))
			StoreVarInst(struct, iRec22[Int32(0)], BinopInst("+", BinopInst(">", BinopInst("-", LoadVarInst(stack, iSlow34), LoadVarInst(struct, iVec1[Int32(1)])), Int32(0)), LoadVarInst(struct, iRec22[Int32(1)])))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("+", BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec20[Int32(1)])), BinopInst("/", Float(0.000772727246f), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("-", LoadVarInst(stack, fSlow17), CastInst("float", BinopInst("+", LoadVarInst(stack, iSlow31), BinopInst("*", Int32(12), BinopInst("-", LoadVarInst(stack, iSlow32), BinopInst("-", LoadVarInst(struct, iRec21[Int32(0)]), LoadVarInst(struct, iRec22[Int32(0)]))))))))))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", LoadVarInst(struct, fConst4), BinopInst("+", BinopInst("*", Float(0.5f), LoadVarInst(struct, fRec20[Int32(0)])), Float(-0.0500000007f))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(stack, fTemp3), Float(-1.49999499f)))
			DeclareVarInst(stack, "int", iTemp5, CastInst("int", LoadVarInst(stack, fTemp4)))
			DeclareVarInst(stack, "int", iTemp6, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", LoadVarInst(stack, iTemp5)))))), Int32(1)))
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
			DeclareVarInst(stack, "int", iTemp17, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(2))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp14))))
			DeclareVarInst(stack, "int", iTemp20, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(1))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.5f), LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("-", Float(0.0f), BinopInst("*", Float(0.333333343f), LoadVarInst(stack, fTemp14))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "int", iTemp25, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(3))))))), Int32(1)))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp14)))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "int", iTemp28, BinopInst("+", CastInst("int", FunCallInst("min_f", LoadVarInst(struct, fConst3), CastInst("float", FunCallInst("max_i", Int32(0), CastInst("int", BinopInst("+", LoadVarInst(stack, iTemp5), Int32(4))))))), Int32(1)))
			StoreVarInst(struct, fVec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp6)), Int32(2047))]), LoadVarInst(stack, fTemp9)), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(stack, fTemp15)), BinopInst("*", LoadVarInst(stack, fTemp16), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp17)), Int32(2047))])), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp19))), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp20)), Int32(2047))]), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23))), BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp25)), Int32(2047))])), LoadVarInst(stack, fTemp26)))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp27), LoadVarInst(struct, fRec15[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp28)), Int32(2047))])))))))
			StoreVarInst(struct, fRec11[Int32(0)], LoadVarInst(struct, fVec2[Int32(1)]))
			DeclareVarInst(stack, "int", iRec12, LoadVarInst(stack, iRec16))
			DeclareVarInst(stack, "float", fRec7, LoadVarInst(stack, fRec10))
			DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec11[Int32(0)]))
			DeclareVarInst(stack, "float", fRec9, BinopInst("+", LoadVarInst(struct, fRec11[Int32(0)]), CastInst("float", LoadVarInst(stack, iRec12))))
			StoreVarInst(struct, fRec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(2047))], LoadVarInst(stack, fRec7))
			DeclareVarInst(stack, "float", fRec3, BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp13)), LoadVarInst(stack, fTemp15)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp6)), Int32(2047))])), BinopInst("*", LoadVarInst(stack, fTemp16), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.166666672f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp24), LoadVarInst(stack, fTemp26)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp25)), Int32(2047))]))), BinopInst("+", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), LoadVarInst(stack, fTemp22)), LoadVarInst(stack, fTemp23)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp20)), Int32(2047))])), BinopInst("*", Float(0.5f), BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp8), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp19)), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp17)), Int32(2047))]))))), BinopInst("*", Float(0.0416666679f), BinopInst("*", LoadVarInst(stack, fTemp27), LoadVarInst(struct, fRec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(stack, iTemp28)), Int32(2047))])))))))
			DeclareVarInst(stack, "float", fRec4, LoadVarInst(stack, fRec8))
			DeclareVarInst(stack, "float", fRec5, LoadVarInst(stack, fRec9))
			StoreVarInst(struct, fRec0[Int32(0)], LoadVarInst(stack, fRec3))
			DeclareVarInst(stack, "float", fRec1, LoadVarInst(stack, fRec5))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec1)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(stack, fRec1)))
			StoreVarInst(struct, iRec6[Int32(1)], LoadVarInst(struct, iRec6[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, iRec21[Int32(1)], LoadVarInst(struct, iRec21[Int32(0)]))
			StoreVarInst(struct, iVec1[Int32(1)], LoadVarInst(struct, iVec1[Int32(0)]))
			StoreVarInst(struct, iRec22[Int32(1)], LoadVarInst(struct, iRec22[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fVec2[Int32(1)], LoadVarInst(struct, fVec2[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 40 bytes
Heap size real = 16516 bytes
Heap size = 16564 bytes
Stack size in compute = 164 bytes

