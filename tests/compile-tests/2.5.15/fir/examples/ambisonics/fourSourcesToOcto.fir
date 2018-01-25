======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("fourSourcesToOcto")
	AddHorizontalSlider("Angle1", fHslider4, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f)
	AddHorizontalSlider("Angle2", fHslider5, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f)
	AddHorizontalSlider("Angle3", fHslider6, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f)
	AddHorizontalSlider("Angle4", fHslider7, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f)
	AddHorizontalSlider("Radius1", fHslider0, 1.0f, 0.0f, 5.0f, 0.00100000005f)
	AddHorizontalSlider("Radius2", fHslider1, 1.0f, 0.0f, 5.0f, 0.00100000005f)
	AddHorizontalSlider("Radius3", fHslider2, 1.0f, 0.0f, 5.0f, 0.00100000005f)
	AddHorizontalSlider("Radius4", fHslider3, 1.0f, 0.0f, 5.0f, 0.00100000005f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec7[2])
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(4))
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

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(50.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))))
	StoreVarInst(struct, fConst1, BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 28
Store = 0
Binop = 8
Numbers = 0
Declare = 20
Cast = 8
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider4))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider5))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider6))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider7))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 337
Store = 25
Binop = 340
Numbers = 139
Declare = 86
Cast = 64
Select = 0
Loop = 1
Funcall = 28

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec0[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp1, BinopInst(">", LoadVarInst(struct, fRec0[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "int", iTemp2, BinopInst("<", LoadVarInst(struct, fRec0[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp1)), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), CastInst("float", LoadVarInst(stack, iTemp2)))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("+", BinopInst("*", Float(1.38629436f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp3))), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fTemp0), LoadVarInst(stack, fTemp4)))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp2)), BinopInst("*", FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fRec0[Int32(0)])), CastInst("float", LoadVarInst(stack, iTemp1)))))
		DeclareVarInst(stack, "float", fTemp7, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec1[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp8, BinopInst(">", LoadVarInst(struct, fRec1[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "int", iTemp9, BinopInst("<", LoadVarInst(struct, fRec1[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp8)), BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), CastInst("float", LoadVarInst(stack, iTemp9)))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", BinopInst("*", Float(1.38629436f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp10))), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp9)), BinopInst("*", FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fRec1[Int32(0)])), CastInst("float", LoadVarInst(stack, iTemp8)))))
		DeclareVarInst(stack, "float", fTemp14, CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec2[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp15, BinopInst(">", LoadVarInst(struct, fRec2[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "int", iTemp16, BinopInst("<", LoadVarInst(struct, fRec2[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp15)), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), CastInst("float", LoadVarInst(stack, iTemp16)))))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("+", BinopInst("*", Float(1.38629436f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp17))), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("*", LoadVarInst(stack, fTemp14), LoadVarInst(stack, fTemp18)))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp16)), BinopInst("*", FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fRec2[Int32(0)])), CastInst("float", LoadVarInst(stack, iTemp15)))))
		DeclareVarInst(stack, "float", fTemp21, CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec3[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp22, BinopInst(">", LoadVarInst(struct, fRec3[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "int", iTemp23, BinopInst("<", LoadVarInst(struct, fRec3[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp22)), BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), CastInst("float", LoadVarInst(stack, iTemp23)))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("+", BinopInst("*", Float(1.38629436f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp24))), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("*", LoadVarInst(stack, fTemp21), LoadVarInst(stack, fTemp25)))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp23)), BinopInst("*", FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fRec3[Int32(0)])), CastInst("float", LoadVarInst(stack, iTemp22)))))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("*", Float(0.142857149f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fTemp6)), BinopInst("/", LoadVarInst(stack, fTemp12), LoadVarInst(stack, fTemp13))), BinopInst("/", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp20))), BinopInst("/", LoadVarInst(stack, fTemp26), LoadVarInst(stack, fTemp27)))))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("*", Float(2.0f), LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp3), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp29), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp29), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp29), Float(1.0f)))))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec4[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("*", Float(2.0f), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp32, BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp10), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp31), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp31), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp31), Float(1.0f)))))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec5[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp33, BinopInst("*", Float(2.0f), LoadVarInst(stack, fTemp17)))
		DeclareVarInst(stack, "float", fTemp34, BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp17), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp33), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp33), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp33), Float(1.0f)))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec6[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("*", Float(2.0f), LoadVarInst(stack, fTemp24)))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp24), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp35), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp35), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp35), Float(1.0f)))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec7[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fTemp30)), FunCallInst("cosf", LoadVarInst(struct, fRec4[Int32(0)]))), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp12), LoadVarInst(stack, fTemp32)), FunCallInst("cosf", LoadVarInst(struct, fRec5[Int32(0)]))), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp34)), FunCallInst("cosf", LoadVarInst(struct, fRec6[Int32(0)]))), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(stack, fTemp36)), FunCallInst("cosf", LoadVarInst(struct, fRec7[Int32(0)]))), LoadVarInst(stack, fTemp27))))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("*", Float(0.214285716f), LoadVarInst(stack, fTemp37)))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec4[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp40, BinopInst("*", Float(1.38629436f), LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fTemp41, BinopInst("+", LoadVarInst(stack, fTemp40), Float(-0.693147182f)))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("*", Float(2.46630335f), LoadVarInst(stack, fTemp41)))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("+", BinopInst("*", Float(2.46630335f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp41), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp42), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp42), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp42), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp44, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec5[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp45, BinopInst("*", Float(1.38629436f), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("+", LoadVarInst(stack, fTemp45), Float(-0.693147182f)))
		DeclareVarInst(stack, "float", fTemp47, BinopInst("*", Float(2.46630335f), LoadVarInst(stack, fTemp46)))
		DeclareVarInst(stack, "float", fTemp48, BinopInst("+", BinopInst("*", Float(2.46630335f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp46), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp47), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp47), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp47), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp49, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec6[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp50, BinopInst("*", Float(1.38629436f), LoadVarInst(stack, fTemp17)))
		DeclareVarInst(stack, "float", fTemp51, BinopInst("+", LoadVarInst(stack, fTemp50), Float(-0.693147182f)))
		DeclareVarInst(stack, "float", fTemp52, BinopInst("*", Float(2.46630335f), LoadVarInst(stack, fTemp51)))
		DeclareVarInst(stack, "float", fTemp53, BinopInst("+", BinopInst("*", Float(2.46630335f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp51), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp52), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp52), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp52), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec7[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp55, BinopInst("*", Float(1.38629436f), LoadVarInst(stack, fTemp24)))
		DeclareVarInst(stack, "float", fTemp56, BinopInst("+", LoadVarInst(stack, fTemp55), Float(-0.693147182f)))
		DeclareVarInst(stack, "float", fTemp57, BinopInst("*", Float(2.46630335f), LoadVarInst(stack, fTemp56)))
		DeclareVarInst(stack, "float", fTemp58, BinopInst("+", BinopInst("*", Float(2.46630335f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp56), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp57), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp57), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp57), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp59, BinopInst("*", Float(0.0857142881f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp0), FunCallInst("cosf", LoadVarInst(stack, fTemp39))), LoadVarInst(stack, fTemp4)), LoadVarInst(stack, fTemp43)), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), FunCallInst("cosf", LoadVarInst(stack, fTemp44))), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp48)), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp14), FunCallInst("cosf", LoadVarInst(stack, fTemp49))), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp53)), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), FunCallInst("cosf", LoadVarInst(stack, fTemp54))), LoadVarInst(stack, fTemp25)), LoadVarInst(stack, fTemp58)), LoadVarInst(stack, fTemp27)))))
		DeclareVarInst(stack, "float", fTemp60, BinopInst("*", Float(3.0f), LoadVarInst(struct, fRec4[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp61, BinopInst("+", LoadVarInst(stack, fTemp40), Float(-1.09861231f)))
		DeclareVarInst(stack, "float", fTemp62, BinopInst("*", Float(3.47605944f), LoadVarInst(stack, fTemp61)))
		DeclareVarInst(stack, "float", fTemp63, BinopInst("+", BinopInst("*", Float(3.47605944f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp61), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp62), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp62), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp62), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp64, BinopInst("*", Float(3.0f), LoadVarInst(struct, fRec5[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp65, BinopInst("+", LoadVarInst(stack, fTemp45), Float(-1.09861231f)))
		DeclareVarInst(stack, "float", fTemp66, BinopInst("*", Float(3.47605944f), LoadVarInst(stack, fTemp65)))
		DeclareVarInst(stack, "float", fTemp67, BinopInst("+", BinopInst("*", Float(3.47605944f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp65), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp66), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp66), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp66), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp68, BinopInst("*", Float(3.0f), LoadVarInst(struct, fRec6[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp69, BinopInst("+", LoadVarInst(stack, fTemp50), Float(-1.09861231f)))
		DeclareVarInst(stack, "float", fTemp70, BinopInst("*", Float(3.47605944f), LoadVarInst(stack, fTemp69)))
		DeclareVarInst(stack, "float", fTemp71, BinopInst("+", BinopInst("*", Float(3.47605944f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp69), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp70), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp70), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp70), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp72, BinopInst("*", Float(3.0f), LoadVarInst(struct, fRec7[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp73, BinopInst("+", LoadVarInst(stack, fTemp55), Float(-1.09861231f)))
		DeclareVarInst(stack, "float", fTemp74, BinopInst("*", Float(3.47605944f), LoadVarInst(stack, fTemp73)))
		DeclareVarInst(stack, "float", fTemp75, BinopInst("+", BinopInst("*", Float(3.47605944f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp73), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp74), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp74), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp74), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp76, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp0), FunCallInst("cosf", LoadVarInst(stack, fTemp60))), LoadVarInst(stack, fTemp4)), LoadVarInst(stack, fTemp63)), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), FunCallInst("cosf", LoadVarInst(stack, fTemp64))), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp67)), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp14), FunCallInst("cosf", LoadVarInst(stack, fTemp68))), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp71)), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), FunCallInst("cosf", LoadVarInst(stack, fTemp72))), LoadVarInst(stack, fTemp25)), LoadVarInst(stack, fTemp75)), LoadVarInst(stack, fTemp27))))
		DeclareVarInst(stack, "float", fTemp77, BinopInst("*", Float(0.0142857144f), LoadVarInst(stack, fTemp76)))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp59)), LoadVarInst(stack, fTemp77))))
		DeclareVarInst(stack, "float", fTemp78, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp5), FunCallInst("sinf", LoadVarInst(struct, fRec4[Int32(0)]))), LoadVarInst(stack, fTemp30)), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp12), FunCallInst("sinf", LoadVarInst(struct, fRec5[Int32(0)]))), LoadVarInst(stack, fTemp32)), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp19), FunCallInst("sinf", LoadVarInst(struct, fRec6[Int32(0)]))), LoadVarInst(stack, fTemp34)), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp26), FunCallInst("sinf", LoadVarInst(struct, fRec7[Int32(0)]))), LoadVarInst(stack, fTemp36)), LoadVarInst(stack, fTemp27))))
		DeclareVarInst(stack, "float", fTemp79, BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp78)))
		DeclareVarInst(stack, "float", fTemp80, BinopInst("*", Float(0.0857142881f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp0), FunCallInst("sinf", LoadVarInst(stack, fTemp39))), LoadVarInst(stack, fTemp4)), LoadVarInst(stack, fTemp43)), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), FunCallInst("sinf", LoadVarInst(stack, fTemp44))), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp48)), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp14), FunCallInst("sinf", LoadVarInst(stack, fTemp49))), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp53)), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), FunCallInst("sinf", LoadVarInst(stack, fTemp54))), LoadVarInst(stack, fTemp25)), LoadVarInst(stack, fTemp58)), LoadVarInst(stack, fTemp27)))))
		DeclareVarInst(stack, "float", fTemp81, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp0), FunCallInst("sinf", LoadVarInst(stack, fTemp60))), LoadVarInst(stack, fTemp4)), LoadVarInst(stack, fTemp63)), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), FunCallInst("sinf", LoadVarInst(stack, fTemp64))), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp67)), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp14), FunCallInst("sinf", LoadVarInst(stack, fTemp68))), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp71)), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), FunCallInst("sinf", LoadVarInst(stack, fTemp72))), LoadVarInst(stack, fTemp25)), LoadVarInst(stack, fTemp75)), LoadVarInst(stack, fTemp27))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp79)), BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp37))), LoadVarInst(stack, fTemp80)), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp81))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp76)))))
		DeclareVarInst(stack, "float", fTemp82, BinopInst("*", Float(0.214285716f), LoadVarInst(stack, fTemp78)))
		DeclareVarInst(stack, "float", fTemp83, BinopInst("*", Float(0.0142857144f), LoadVarInst(stack, fTemp81)))
		StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp82)), BinopInst("+", LoadVarInst(stack, fTemp59), LoadVarInst(stack, fTemp83)))))
		DeclareVarInst(stack, "float", fTemp84, BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp37)))
		StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp78))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp81))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp76))), BinopInst("+", LoadVarInst(stack, fTemp80), LoadVarInst(stack, fTemp84)))))
		StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp59)), BinopInst("+", LoadVarInst(stack, fTemp38), LoadVarInst(stack, fTemp77)))))
		StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp80)), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp76))), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp79), BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp37))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp81))))))
		StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp83)), BinopInst("+", LoadVarInst(stack, fTemp59), LoadVarInst(stack, fTemp82)))))
		StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp84)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp80), BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp78))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp81))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp76))))))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider3)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider4)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider5)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider6)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider7)
	DeclareVarInst(struct, float, fRec7[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(50.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))))
	StoreVarInst(struct, fConst1, BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider3, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider4, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider5, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider6, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider7, CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1))))
	DeclareVarInst(stack, "float", fSlow2, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider2))))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider3))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider4))))
	DeclareVarInst(stack, "float", fSlow5, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider5))))
	DeclareVarInst(stack, "float", fSlow6, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider6))))
	DeclareVarInst(stack, "float", fSlow7, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider7))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec0[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp1, BinopInst(">", LoadVarInst(struct, fRec0[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "int", iTemp2, BinopInst("<", LoadVarInst(struct, fRec0[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp1)), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), CastInst("float", LoadVarInst(stack, iTemp2)))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("+", BinopInst("*", Float(1.38629436f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp3))), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("*", LoadVarInst(stack, fTemp0), LoadVarInst(stack, fTemp4)))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp2)), BinopInst("*", FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fRec0[Int32(0)])), CastInst("float", LoadVarInst(stack, iTemp1)))))
			DeclareVarInst(stack, "float", fTemp7, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec1[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp8, BinopInst(">", LoadVarInst(struct, fRec1[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "int", iTemp9, BinopInst("<", LoadVarInst(struct, fRec1[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp8)), BinopInst("*", LoadVarInst(struct, fRec1[Int32(0)]), CastInst("float", LoadVarInst(stack, iTemp9)))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", BinopInst("*", Float(1.38629436f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp10))), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("*", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp9)), BinopInst("*", FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fRec1[Int32(0)])), CastInst("float", LoadVarInst(stack, iTemp8)))))
			DeclareVarInst(stack, "float", fTemp14, CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec2[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow2), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec2[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp15, BinopInst(">", LoadVarInst(struct, fRec2[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "int", iTemp16, BinopInst("<", LoadVarInst(struct, fRec2[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp15)), BinopInst("*", LoadVarInst(struct, fRec2[Int32(0)]), CastInst("float", LoadVarInst(stack, iTemp16)))))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("+", BinopInst("*", Float(1.38629436f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp17))), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("*", LoadVarInst(stack, fTemp14), LoadVarInst(stack, fTemp18)))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp16)), BinopInst("*", FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fRec2[Int32(0)])), CastInst("float", LoadVarInst(stack, iTemp15)))))
			DeclareVarInst(stack, "float", fTemp21, CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec3[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp22, BinopInst(">", LoadVarInst(struct, fRec3[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "int", iTemp23, BinopInst("<", LoadVarInst(struct, fRec3[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp22)), BinopInst("*", LoadVarInst(struct, fRec3[Int32(0)]), CastInst("float", LoadVarInst(stack, iTemp23)))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("+", BinopInst("*", Float(1.38629436f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp24))), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("*", LoadVarInst(stack, fTemp21), LoadVarInst(stack, fTemp25)))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp23)), BinopInst("*", FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fRec3[Int32(0)])), CastInst("float", LoadVarInst(stack, iTemp22)))))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("*", Float(0.142857149f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fTemp6)), BinopInst("/", LoadVarInst(stack, fTemp12), LoadVarInst(stack, fTemp13))), BinopInst("/", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp20))), BinopInst("/", LoadVarInst(stack, fTemp26), LoadVarInst(stack, fTemp27)))))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("*", Float(2.0f), LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp3), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp29), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp29), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp29), Float(1.0f)))))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow4), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec4[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("*", Float(2.0f), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp32, BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp10), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp31), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp31), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp31), Float(1.0f)))))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow5), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec5[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp33, BinopInst("*", Float(2.0f), LoadVarInst(stack, fTemp17)))
			DeclareVarInst(stack, "float", fTemp34, BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp17), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp33), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp33), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp33), Float(1.0f)))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow6), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec6[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("*", Float(2.0f), LoadVarInst(stack, fTemp24)))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("+", BinopInst("*", Float(2.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp24), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp35), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp35), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp35), Float(1.0f)))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow7), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec7[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fTemp30)), FunCallInst("cosf", LoadVarInst(struct, fRec4[Int32(0)]))), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp12), LoadVarInst(stack, fTemp32)), FunCallInst("cosf", LoadVarInst(struct, fRec5[Int32(0)]))), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp19), LoadVarInst(stack, fTemp34)), FunCallInst("cosf", LoadVarInst(struct, fRec6[Int32(0)]))), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp26), LoadVarInst(stack, fTemp36)), FunCallInst("cosf", LoadVarInst(struct, fRec7[Int32(0)]))), LoadVarInst(stack, fTemp27))))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("*", Float(0.214285716f), LoadVarInst(stack, fTemp37)))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec4[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp40, BinopInst("*", Float(1.38629436f), LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fTemp41, BinopInst("+", LoadVarInst(stack, fTemp40), Float(-0.693147182f)))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("*", Float(2.46630335f), LoadVarInst(stack, fTemp41)))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("+", BinopInst("*", Float(2.46630335f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp41), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp42), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp42), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp42), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp44, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec5[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp45, BinopInst("*", Float(1.38629436f), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("+", LoadVarInst(stack, fTemp45), Float(-0.693147182f)))
			DeclareVarInst(stack, "float", fTemp47, BinopInst("*", Float(2.46630335f), LoadVarInst(stack, fTemp46)))
			DeclareVarInst(stack, "float", fTemp48, BinopInst("+", BinopInst("*", Float(2.46630335f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp46), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp47), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp47), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp47), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp49, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec6[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp50, BinopInst("*", Float(1.38629436f), LoadVarInst(stack, fTemp17)))
			DeclareVarInst(stack, "float", fTemp51, BinopInst("+", LoadVarInst(stack, fTemp50), Float(-0.693147182f)))
			DeclareVarInst(stack, "float", fTemp52, BinopInst("*", Float(2.46630335f), LoadVarInst(stack, fTemp51)))
			DeclareVarInst(stack, "float", fTemp53, BinopInst("+", BinopInst("*", Float(2.46630335f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp51), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp52), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp52), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp52), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec7[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp55, BinopInst("*", Float(1.38629436f), LoadVarInst(stack, fTemp24)))
			DeclareVarInst(stack, "float", fTemp56, BinopInst("+", LoadVarInst(stack, fTemp55), Float(-0.693147182f)))
			DeclareVarInst(stack, "float", fTemp57, BinopInst("*", Float(2.46630335f), LoadVarInst(stack, fTemp56)))
			DeclareVarInst(stack, "float", fTemp58, BinopInst("+", BinopInst("*", Float(2.46630335f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp56), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp57), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp57), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp57), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp59, BinopInst("*", Float(0.0857142881f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp0), FunCallInst("cosf", LoadVarInst(stack, fTemp39))), LoadVarInst(stack, fTemp4)), LoadVarInst(stack, fTemp43)), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), FunCallInst("cosf", LoadVarInst(stack, fTemp44))), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp48)), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp14), FunCallInst("cosf", LoadVarInst(stack, fTemp49))), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp53)), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), FunCallInst("cosf", LoadVarInst(stack, fTemp54))), LoadVarInst(stack, fTemp25)), LoadVarInst(stack, fTemp58)), LoadVarInst(stack, fTemp27)))))
			DeclareVarInst(stack, "float", fTemp60, BinopInst("*", Float(3.0f), LoadVarInst(struct, fRec4[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp61, BinopInst("+", LoadVarInst(stack, fTemp40), Float(-1.09861231f)))
			DeclareVarInst(stack, "float", fTemp62, BinopInst("*", Float(3.47605944f), LoadVarInst(stack, fTemp61)))
			DeclareVarInst(stack, "float", fTemp63, BinopInst("+", BinopInst("*", Float(3.47605944f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp61), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp62), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp62), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp62), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp64, BinopInst("*", Float(3.0f), LoadVarInst(struct, fRec5[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp65, BinopInst("+", LoadVarInst(stack, fTemp45), Float(-1.09861231f)))
			DeclareVarInst(stack, "float", fTemp66, BinopInst("*", Float(3.47605944f), LoadVarInst(stack, fTemp65)))
			DeclareVarInst(stack, "float", fTemp67, BinopInst("+", BinopInst("*", Float(3.47605944f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp65), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp66), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp66), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp66), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp68, BinopInst("*", Float(3.0f), LoadVarInst(struct, fRec6[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp69, BinopInst("+", LoadVarInst(stack, fTemp50), Float(-1.09861231f)))
			DeclareVarInst(stack, "float", fTemp70, BinopInst("*", Float(3.47605944f), LoadVarInst(stack, fTemp69)))
			DeclareVarInst(stack, "float", fTemp71, BinopInst("+", BinopInst("*", Float(3.47605944f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp69), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp70), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp70), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp70), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp72, BinopInst("*", Float(3.0f), LoadVarInst(struct, fRec7[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp73, BinopInst("+", LoadVarInst(stack, fTemp55), Float(-1.09861231f)))
			DeclareVarInst(stack, "float", fTemp74, BinopInst("*", Float(3.47605944f), LoadVarInst(stack, fTemp73)))
			DeclareVarInst(stack, "float", fTemp75, BinopInst("+", BinopInst("*", Float(3.47605944f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp73), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp74), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp74), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp74), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp76, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp0), FunCallInst("cosf", LoadVarInst(stack, fTemp60))), LoadVarInst(stack, fTemp4)), LoadVarInst(stack, fTemp63)), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), FunCallInst("cosf", LoadVarInst(stack, fTemp64))), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp67)), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp14), FunCallInst("cosf", LoadVarInst(stack, fTemp68))), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp71)), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), FunCallInst("cosf", LoadVarInst(stack, fTemp72))), LoadVarInst(stack, fTemp25)), LoadVarInst(stack, fTemp75)), LoadVarInst(stack, fTemp27))))
			DeclareVarInst(stack, "float", fTemp77, BinopInst("*", Float(0.0142857144f), LoadVarInst(stack, fTemp76)))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp38)), LoadVarInst(stack, fTemp59)), LoadVarInst(stack, fTemp77))))
			DeclareVarInst(stack, "float", fTemp78, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp5), FunCallInst("sinf", LoadVarInst(struct, fRec4[Int32(0)]))), LoadVarInst(stack, fTemp30)), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp12), FunCallInst("sinf", LoadVarInst(struct, fRec5[Int32(0)]))), LoadVarInst(stack, fTemp32)), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp19), FunCallInst("sinf", LoadVarInst(struct, fRec6[Int32(0)]))), LoadVarInst(stack, fTemp34)), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp26), FunCallInst("sinf", LoadVarInst(struct, fRec7[Int32(0)]))), LoadVarInst(stack, fTemp36)), LoadVarInst(stack, fTemp27))))
			DeclareVarInst(stack, "float", fTemp79, BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp78)))
			DeclareVarInst(stack, "float", fTemp80, BinopInst("*", Float(0.0857142881f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp0), FunCallInst("sinf", LoadVarInst(stack, fTemp39))), LoadVarInst(stack, fTemp4)), LoadVarInst(stack, fTemp43)), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), FunCallInst("sinf", LoadVarInst(stack, fTemp44))), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp48)), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp14), FunCallInst("sinf", LoadVarInst(stack, fTemp49))), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp53)), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), FunCallInst("sinf", LoadVarInst(stack, fTemp54))), LoadVarInst(stack, fTemp25)), LoadVarInst(stack, fTemp58)), LoadVarInst(stack, fTemp27)))))
			DeclareVarInst(stack, "float", fTemp81, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp0), FunCallInst("sinf", LoadVarInst(stack, fTemp60))), LoadVarInst(stack, fTemp4)), LoadVarInst(stack, fTemp63)), LoadVarInst(stack, fTemp6)), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp7), FunCallInst("sinf", LoadVarInst(stack, fTemp64))), LoadVarInst(stack, fTemp11)), LoadVarInst(stack, fTemp67)), LoadVarInst(stack, fTemp13))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp14), FunCallInst("sinf", LoadVarInst(stack, fTemp68))), LoadVarInst(stack, fTemp18)), LoadVarInst(stack, fTemp71)), LoadVarInst(stack, fTemp20))), BinopInst("/", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp21), FunCallInst("sinf", LoadVarInst(stack, fTemp72))), LoadVarInst(stack, fTemp25)), LoadVarInst(stack, fTemp75)), LoadVarInst(stack, fTemp27))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp79)), BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp37))), LoadVarInst(stack, fTemp80)), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp81))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp76)))))
			DeclareVarInst(stack, "float", fTemp82, BinopInst("*", Float(0.214285716f), LoadVarInst(stack, fTemp78)))
			DeclareVarInst(stack, "float", fTemp83, BinopInst("*", Float(0.0142857144f), LoadVarInst(stack, fTemp81)))
			StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp82)), BinopInst("+", LoadVarInst(stack, fTemp59), LoadVarInst(stack, fTemp83)))))
			DeclareVarInst(stack, "float", fTemp84, BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp37)))
			StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp28), BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp78))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp81))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp76))), BinopInst("+", LoadVarInst(stack, fTemp80), LoadVarInst(stack, fTemp84)))))
			StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp59)), BinopInst("+", LoadVarInst(stack, fTemp38), LoadVarInst(stack, fTemp77)))))
			StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp80)), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp76))), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp79), BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp37))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp81))))))
			StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp83)), BinopInst("+", LoadVarInst(stack, fTemp59), LoadVarInst(stack, fTemp82)))))
			StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp28), LoadVarInst(stack, fTemp84)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp80), BinopInst("*", Float(0.151522875f), LoadVarInst(stack, fTemp78))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp81))), BinopInst("*", Float(0.0101015251f), LoadVarInst(stack, fTemp76))))))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 104 bytes
Heap size = 108 bytes
Stack size in compute = 128 bytes

