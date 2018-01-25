======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "sinf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, int, iRec2[2])
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
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec2[LoadVarInst(loop, l2)], Int32(0))
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
		StoreVarInst(struct, iRec2[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec2[Int32(1)]), Int32(1)))
		StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], FunCallInst("sinf", BinopInst("*", Float(9.58738019e-05f), CastInst("float", BinopInst("+", LoadVarInst(struct, iRec2[Int32(0)]), Int32(-1))))))
		StoreVarInst(struct, iRec2[Int32(1)], LoadVarInst(struct, iRec2[Int32(0)]))
		EndBlock
	EndForLoop

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("Stereo Audio Tester")
	AddMetaDeclareInst(fHslider3, "1", "")
	AddMetaDeclareInst(fHslider3, "scale", "log")
	AddMetaDeclareInst(fHslider3, "unit", "Hz")
	AddHorizontalSlider("freq", fHslider3, 440.0f, 40.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "2", "")
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("volume", fHslider0, -96.0f, -96.0f, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider2, "3", "")
	AddMetaDeclareInst(fHslider2, "style", "menu{'white noise':0;'pink noise':1;'sine':2}")
	AddHorizontalSlider("signal", fHslider2, 0.0f, 0.0f, 2.0f, 1.0f)
	AddMetaDeclareInst(fHslider1, "4", "")
	AddMetaDeclareInst(fHslider1, "style", "radio{'none':0;'left':1;'right':2;'both':3}")
	AddHorizontalSlider("channel", fHslider1, 0.0f, 0.0f, 3.0f, 1.0f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareVarInst(static, float, ftbl0mydspSIG0[65537])
	DeclareFunInst("float", "floorf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, int, iRec5[3])
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, float, fRec6[2])
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
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(stack, sig0), Int32(65537), LoadVarInst(static, ftbl0mydspSIG0)))
	EndBlock
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(stack, sig0)))
	EndBlock

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(-96.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(440.0f)))
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
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l1)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec5[LoadVarInst(loop, l4)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(3))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l5)], Float(0.0f))
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
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 11
Store = 0
Binop = 9
Numbers = 9
Declare = 10
Cast = 6
Select = 0
Loop = 0
Funcall = 1

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))))
	DeclareVarInst(stack, "int", iSlow1, CastInst("int", CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "int", iSlow2, BinopInst("!=", BinopInst("&", LoadVarInst(stack, iSlow1), Int32(1)), Int32(0)))
	DeclareVarInst(stack, "int", iSlow3, CastInst("int", CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(0)))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(1)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "int", iSlow7, BinopInst("!=", BinopInst("&", LoadVarInst(stack, iSlow1), Int32(2)), Int32(0)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 54
Store = 17
Binop = 34
Numbers = 30
Declare = 4
Cast = 13
Select = 0
Loop = 1
Funcall = 6

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
		StoreVarInst(struct, fRec1[Int32(0)], Select2Inst(BinopInst("<", LoadVarInst(struct, fRec1[Int32(1)]), CastInst("float", LoadVarInst(stack, iSlow2))) FunCallInst("min_f", BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), Float(0.000226757373f)), CastInst("float", LoadVarInst(stack, iSlow2))) FunCallInst("max_f", BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), Float(-0.000226757373f)), CastInst("float", LoadVarInst(stack, iSlow2)))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("-", LoadVarInst(struct, fRec3[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec3[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec3[Int32(0)])))
		DeclareVarInst(stack, "int", iTemp1, CastInst("int", LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, iRec5[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec5[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(6.90678287e-12f), CastInst("float", LoadVarInst(struct, iRec5[Int32(2)]))), BinopInst("+", BinopInst("*", Float(1.80116081f), LoadVarInst(struct, fRec4[Int32(1)])), BinopInst("*", Float(2.30852802e-11f), CastInst("float", LoadVarInst(struct, iRec5[Int32(0)]))))), BinopInst("+", BinopInst("*", Float(0.802577376f), LoadVarInst(struct, fRec4[Int32(2)])), BinopInst("*", Float(2.93626512e-11f), CastInst("float", LoadVarInst(struct, iRec5[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp2, Select2Inst(LoadVarInst(stack, iSlow4) BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec5[Int32(0)]))) Select2Inst(LoadVarInst(stack, iSlow5) LoadVarInst(struct, fRec4[Int32(0)]) BinopInst("+", LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)]), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp0), FunCallInst("floorf", LoadVarInst(stack, fTemp0))), BinopInst("-", LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iTemp1), Int32(1))]), LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)])))))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(struct, fRec1[Int32(0)])), LoadVarInst(stack, fTemp2))))
		StoreVarInst(struct, fRec6[Int32(0)], Select2Inst(BinopInst("<", LoadVarInst(struct, fRec6[Int32(1)]), CastInst("float", LoadVarInst(stack, iSlow7))) FunCallInst("min_f", BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), Float(0.000226757373f)), CastInst("float", LoadVarInst(stack, iSlow7))) FunCallInst("max_f", BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), Float(-0.000226757373f)), CastInst("float", LoadVarInst(stack, iSlow7)))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(struct, fRec6[Int32(0)])), LoadVarInst(stack, fTemp2))))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, iRec5[Int32(2)], LoadVarInst(struct, iRec5[Int32(1)]))
		StoreVarInst(struct, iRec5[Int32(1)], LoadVarInst(struct, iRec5[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareVarInst(static, float, ftbl0mydspSIG0[65537])
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, int, iRec5[3])
	DeclareVarInst(struct, float, fRec4[3])
	DeclareVarInst(struct, float, fRec6[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(-96.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(440.0f)))
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
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l1)], Float(0.0f))
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
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec5[LoadVarInst(loop, l4)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(3))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l5)], Float(0.0f))
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
	========== Static init method ==========
	DeclareVarInst(stack, mydspSIG0, sig0, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(stack, sig0), LoadVarInst(kFunArgs, samplingFreq)))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(stack, sig0), Int32(65537), LoadVarInst(static, ftbl0mydspSIG0)))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(stack, sig0)))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst(struct, int, iRec2[2])
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec2[LoadVarInst(loop, l2)], Int32(0))
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
			StoreVarInst(struct, iRec2[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec2[Int32(1)]), Int32(1)))
			StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], FunCallInst("sinf", BinopInst("*", Float(9.58738019e-05f), CastInst("float", BinopInst("+", LoadVarInst(struct, iRec2[Int32(0)]), Int32(-1))))))
			StoreVarInst(struct, iRec2[Int32(1)], LoadVarInst(struct, iRec2[Int32(0)]))
			EndBlock
		EndForLoop
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider0))))))
	DeclareVarInst(stack, "int", iSlow1, CastInst("int", CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "int", iSlow2, BinopInst("!=", BinopInst("&", LoadVarInst(stack, iSlow1), Int32(1)), Int32(0)))
	DeclareVarInst(stack, "int", iSlow3, CastInst("int", CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "int", iSlow4, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(0)))
	DeclareVarInst(stack, "int", iSlow5, BinopInst("==", LoadVarInst(stack, iSlow3), Int32(1)))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "int", iSlow7, BinopInst("!=", BinopInst("&", LoadVarInst(stack, iSlow1), Int32(2)), Int32(0)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
			StoreVarInst(struct, fRec1[Int32(0)], Select2Inst(BinopInst("<", LoadVarInst(struct, fRec1[Int32(1)]), CastInst("float", LoadVarInst(stack, iSlow2))) FunCallInst("min_f", BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), Float(0.000226757373f)), CastInst("float", LoadVarInst(stack, iSlow2))) FunCallInst("max_f", BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), Float(-0.000226757373f)), CastInst("float", LoadVarInst(stack, iSlow2)))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("-", LoadVarInst(struct, fRec3[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec3[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec3[Int32(0)])))
			DeclareVarInst(stack, "int", iTemp1, CastInst("int", LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, iRec5[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec5[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(6.90678287e-12f), CastInst("float", LoadVarInst(struct, iRec5[Int32(2)]))), BinopInst("+", BinopInst("*", Float(1.80116081f), LoadVarInst(struct, fRec4[Int32(1)])), BinopInst("*", Float(2.30852802e-11f), CastInst("float", LoadVarInst(struct, iRec5[Int32(0)]))))), BinopInst("+", BinopInst("*", Float(0.802577376f), LoadVarInst(struct, fRec4[Int32(2)])), BinopInst("*", Float(2.93626512e-11f), CastInst("float", LoadVarInst(struct, iRec5[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp2, Select2Inst(LoadVarInst(stack, iSlow4) BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec5[Int32(0)]))) Select2Inst(LoadVarInst(stack, iSlow5) LoadVarInst(struct, fRec4[Int32(0)]) BinopInst("+", LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)]), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp0), FunCallInst("floorf", LoadVarInst(stack, fTemp0))), BinopInst("-", LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iTemp1), Int32(1))]), LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)])))))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(struct, fRec1[Int32(0)])), LoadVarInst(stack, fTemp2))))
			StoreVarInst(struct, fRec6[Int32(0)], Select2Inst(BinopInst("<", LoadVarInst(struct, fRec6[Int32(1)]), CastInst("float", LoadVarInst(stack, iSlow7))) FunCallInst("min_f", BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), Float(0.000226757373f)), CastInst("float", LoadVarInst(stack, iSlow7))) FunCallInst("max_f", BinopInst("+", LoadVarInst(struct, fRec6[Int32(1)]), Float(-0.000226757373f)), CastInst("float", LoadVarInst(stack, iSlow7)))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), LoadVarInst(struct, fRec6[Int32(0)])), LoadVarInst(stack, fTemp2))))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, iRec5[Int32(2)], LoadVarInst(struct, iRec5[Int32(1)]))
			StoreVarInst(struct, iRec5[Int32(1)], LoadVarInst(struct, iRec5[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 12 bytes
Heap size real = 64 bytes
Heap size = 88 bytes
Stack size in compute = 48 bytes

