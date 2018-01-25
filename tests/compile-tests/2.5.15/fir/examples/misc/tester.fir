======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "sinf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, int, iRec1[2])
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
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec1[LoadVarInst(loop, l1)], Int32(0))
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
		StoreVarInst(struct, iRec1[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec1[Int32(1)]), Int32(1)))
		StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], FunCallInst("sinf", BinopInst("*", Float(9.58738019e-05f), CastInst("float", BinopInst("+", LoadVarInst(struct, iRec1[Int32(0)]), Int32(-1))))))
		StoreVarInst(struct, iRec1[Int32(1)], LoadVarInst(struct, iRec1[Int32(0)]))
		EndBlock
	EndForLoop

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("Audio Tester")
	AddMetaDeclareInst(fHslider2, "1", "")
	AddMetaDeclareInst(fHslider2, "unit", "Hz")
	AddHorizontalSlider("freq", fHslider2, 1000.0f, 10.0f, 20000.0f, 1.0f)
	AddMetaDeclareInst(fHslider1, "2", "")
	AddMetaDeclareInst(fHslider1, "unit", "dB")
	AddHorizontalSlider("volume", fHslider1, -96.0f, -96.0f, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "3", "")
	AddHorizontalSlider("destination", fHslider0, 0.0f, 0.0f, 8.0f, 1.0f)
	AddCheckButtonInst("pink noise"fCheckbox2)
	AddCheckButtonInst("sine wave"fCheckbox0)
	AddCheckButtonInst("white noise"fCheckbox1)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareVarInst(static, float, ftbl0mydspSIG0[65537])
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, int, iRec3[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, float, fRec4[3])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(8))
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
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(-96.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
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
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(3))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec3[LoadVarInst(loop, l3)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 23
Store = 0
Binop = 13
Numbers = 13
Declare = 22
Cast = 6
Select = 0
Loop = 0
Funcall = 1

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "int", iSlow1, BinopInst("==", LoadVarInst(stack, fSlow0), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider1))))))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fCheckbox0)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, fCheckbox1))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(10.0f), CastInst("float", LoadVarInst(struct, fCheckbox2))))
	DeclareVarInst(stack, "int", iSlow7, BinopInst("==", LoadVarInst(stack, fSlow0), Float(1.0f)))
	DeclareVarInst(stack, "int", iSlow8, BinopInst("==", LoadVarInst(stack, fSlow0), Float(2.0f)))
	DeclareVarInst(stack, "int", iSlow9, BinopInst("==", LoadVarInst(stack, fSlow0), Float(3.0f)))
	DeclareVarInst(stack, "int", iSlow10, BinopInst("==", LoadVarInst(stack, fSlow0), Float(4.0f)))
	DeclareVarInst(stack, "int", iSlow11, BinopInst("==", LoadVarInst(stack, fSlow0), Float(5.0f)))
	DeclareVarInst(stack, "int", iSlow12, BinopInst("==", LoadVarInst(stack, fSlow0), Float(6.0f)))
	DeclareVarInst(stack, "int", iSlow13, BinopInst("==", LoadVarInst(stack, fSlow0), Float(7.0f)))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 58
Store = 19
Binop = 37
Numbers = 21
Declare = 4
Cast = 21
Select = 0
Loop = 1
Funcall = 2

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("-", LoadVarInst(struct, fRec2[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec2[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp0, BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec2[Int32(0)])))
		DeclareVarInst(stack, "int", iTemp1, CastInst("int", LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, iRec3[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec3[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(6.90678287e-12f), CastInst("float", LoadVarInst(struct, iRec3[Int32(2)]))), BinopInst("+", BinopInst("*", Float(1.80116081f), LoadVarInst(struct, fRec4[Int32(1)])), BinopInst("*", Float(2.30852802e-11f), CastInst("float", LoadVarInst(struct, iRec3[Int32(0)]))))), BinopInst("+", BinopInst("*", Float(0.802577376f), LoadVarInst(struct, fRec4[Int32(2)])), BinopInst("*", Float(2.93626512e-11f), CastInst("float", LoadVarInst(struct, iRec3[Int32(1)]))))))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("+", LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)]), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp0), FunCallInst("floorf", LoadVarInst(stack, fTemp0))), BinopInst("-", LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iTemp1), Int32(1))]), LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)]))))), BinopInst("*", LoadVarInst(stack, fSlow5), CastInst("float", LoadVarInst(struct, iRec3[Int32(0)])))), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec4[Int32(0)])))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow1)), LoadVarInst(stack, fTemp2))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow7)), LoadVarInst(stack, fTemp2))))
		StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow8)), LoadVarInst(stack, fTemp2))))
		StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow9)), LoadVarInst(stack, fTemp2))))
		StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow10)), LoadVarInst(stack, fTemp2))))
		StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow11)), LoadVarInst(stack, fTemp2))))
		StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow12)), LoadVarInst(stack, fTemp2))))
		StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow13)), LoadVarInst(stack, fTemp2))))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, iRec3[Int32(2)], LoadVarInst(struct, iRec3[Int32(1)]))
		StoreVarInst(struct, iRec3[Int32(1)], LoadVarInst(struct, iRec3[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareVarInst(static, float, ftbl0mydspSIG0[65537])
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox1)
	DeclareVarInst(struct, int, iRec3[3])
	DeclareVarInst(struct, "FAUSTFLOAT", fCheckbox2)
	DeclareVarInst(struct, float, fRec4[3])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(-96.0f)))
	StoreVarInst(struct, fCheckbox0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1000.0f)))
	StoreVarInst(struct, fCheckbox1, CastInst("FAUSTFLOAT", Double(0.0f)))
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
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(3))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec3[LoadVarInst(loop, l3)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(3))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l4)], Float(0.0f))
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
	DeclareVarInst(struct, int, iRec1[2])
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec1[LoadVarInst(loop, l1)], Int32(0))
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
			StoreVarInst(struct, iRec1[Int32(0)], BinopInst("+", LoadVarInst(struct, iRec1[Int32(1)]), Int32(1)))
			StoreVarInst(kFunArgs, output[LoadVarInst(loop, i)], FunCallInst("sinf", BinopInst("*", Float(9.58738019e-05f), CastInst("float", BinopInst("+", LoadVarInst(struct, iRec1[Int32(0)]), Int32(-1))))))
			StoreVarInst(struct, iRec1[Int32(1)], LoadVarInst(struct, iRec1[Int32(0)]))
			EndBlock
		EndForLoop
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "int", iSlow1, BinopInst("==", LoadVarInst(stack, fSlow0), Float(0.0f)))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", Float(0.00100000005f), FunCallInst("powf", Float(10.0f), BinopInst("*", Float(0.0500000007f), CastInst("float", LoadVarInst(struct, fHslider1))))))
	DeclareVarInst(stack, "float", fSlow3, CastInst("float", LoadVarInst(struct, fCheckbox0)))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", LoadVarInst(struct, fConst0), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, fCheckbox1))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", Float(10.0f), CastInst("float", LoadVarInst(struct, fCheckbox2))))
	DeclareVarInst(stack, "int", iSlow7, BinopInst("==", LoadVarInst(stack, fSlow0), Float(1.0f)))
	DeclareVarInst(stack, "int", iSlow8, BinopInst("==", LoadVarInst(stack, fSlow0), Float(2.0f)))
	DeclareVarInst(stack, "int", iSlow9, BinopInst("==", LoadVarInst(stack, fSlow0), Float(3.0f)))
	DeclareVarInst(stack, "int", iSlow10, BinopInst("==", LoadVarInst(stack, fSlow0), Float(4.0f)))
	DeclareVarInst(stack, "int", iSlow11, BinopInst("==", LoadVarInst(stack, fSlow0), Float(5.0f)))
	DeclareVarInst(stack, "int", iSlow12, BinopInst("==", LoadVarInst(stack, fSlow0), Float(6.0f)))
	DeclareVarInst(stack, "int", iSlow13, BinopInst("==", LoadVarInst(stack, fSlow0), Float(7.0f)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", Float(0.999000013f), LoadVarInst(struct, fRec0[Int32(1)]))))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("-", LoadVarInst(struct, fRec2[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(stack, fSlow4), LoadVarInst(struct, fRec2[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp0, BinopInst("*", Float(65536.0f), LoadVarInst(struct, fRec2[Int32(0)])))
			DeclareVarInst(stack, "int", iTemp1, CastInst("int", LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, iRec3[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec3[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(6.90678287e-12f), CastInst("float", LoadVarInst(struct, iRec3[Int32(2)]))), BinopInst("+", BinopInst("*", Float(1.80116081f), LoadVarInst(struct, fRec4[Int32(1)])), BinopInst("*", Float(2.30852802e-11f), CastInst("float", LoadVarInst(struct, iRec3[Int32(0)]))))), BinopInst("+", BinopInst("*", Float(0.802577376f), LoadVarInst(struct, fRec4[Int32(2)])), BinopInst("*", Float(2.93626512e-11f), CastInst("float", LoadVarInst(struct, iRec3[Int32(1)]))))))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow3), BinopInst("+", LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)]), BinopInst("*", BinopInst("-", LoadVarInst(stack, fTemp0), FunCallInst("floorf", LoadVarInst(stack, fTemp0))), BinopInst("-", LoadVarInst(static, ftbl0mydspSIG0[BinopInst("+", LoadVarInst(stack, iTemp1), Int32(1))]), LoadVarInst(static, ftbl0mydspSIG0[LoadVarInst(stack, iTemp1)]))))), BinopInst("*", LoadVarInst(stack, fSlow5), CastInst("float", LoadVarInst(struct, iRec3[Int32(0)])))), BinopInst("*", LoadVarInst(stack, fSlow6), LoadVarInst(struct, fRec4[Int32(0)])))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow1)), LoadVarInst(stack, fTemp2))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow7)), LoadVarInst(stack, fTemp2))))
			StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow8)), LoadVarInst(stack, fTemp2))))
			StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow9)), LoadVarInst(stack, fTemp2))))
			StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow10)), LoadVarInst(stack, fTemp2))))
			StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow11)), LoadVarInst(stack, fTemp2))))
			StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow12)), LoadVarInst(stack, fTemp2))))
			StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", LoadVarInst(stack, iSlow13)), LoadVarInst(stack, fTemp2))))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, iRec3[Int32(2)], LoadVarInst(struct, iRec3[Int32(1)]))
			StoreVarInst(struct, iRec3[Int32(1)], LoadVarInst(struct, iRec3[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(2)], LoadVarInst(struct, fRec4[Int32(1)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 12 bytes
Heap size real = 56 bytes
Heap size = 80 bytes
Stack size in compute = 120 bytes

