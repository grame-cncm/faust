======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("wind")
	AddHorizontalSlider("force", fHslider0, 0.660000026f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, int, iRec1[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec13[2])
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
	StoreVarInst(struct, fConst0, BinopInst("/", Float(3.14159274f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.66000000000000003f)))
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
			StoreVarInst(struct, iRec1[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
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
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 3
Store = 0
Binop = 1
Numbers = 1
Declare = 3
Cast = 1
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00300000003f), CastInst("float", LoadVarInst(struct, fHslider0))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 197
Store = 25
Binop = 162
Numbers = 83
Declare = 54
Cast = 4
Select = 0
Loop = 1
Funcall = 29

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.996999979f), LoadVarInst(struct, fRec0[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp0, BinopInst("*", Int32(1103515245), BinopInst("+", LoadVarInst(struct, iRec1[Int32(1)]), Int32(12345))))
		StoreVarInst(struct, iRec1[Int32(0)], BinopInst("*", Int32(1103515245), BinopInst("+", LoadVarInst(stack, iTemp0), Int32(12345))))
		DeclareVarInst(stack, "int", iRec2, LoadVarInst(stack, iTemp0))
		DeclareVarInst(stack, "float", fTemp1, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec1[Int32(0)]))))
		StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.996999979f), LoadVarInst(struct, fRec3[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp2, FunCallInst("mydsp_faustpower2_f", BinopInst("*", Float(1.41419947f), LoadVarInst(struct, fRec3[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", Float(1.99997997f), LoadVarInst(struct, fRec3[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(stack, fTemp2), LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(stack, fTemp3), Float(2.0f)))
		DeclareVarInst(stack, "float", fTemp6, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), FunCallInst("max_f", BinopInst("*", Float(440.0f), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", BinopInst("*", Float(87.0f), LoadVarInst(struct, fRec3[Int32(0)])), Float(-48.0f))))), Float(20.0f)))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp6)))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp6))), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(1.0f), BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp6)))), LoadVarInst(stack, fTemp8)))
		DeclareVarInst(stack, "float", fTemp10, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), LoadVarInst(stack, fTemp9))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp10))))
		DeclareVarInst(stack, "float", fTemp13, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp12))))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp11)), BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp13))))
		DeclareVarInst(stack, "float", fTemp15, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp6))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp15))))
		DeclareVarInst(stack, "float", fTemp17, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(stack, fTemp16), BinopInst("*", LoadVarInst(stack, fTemp8), BinopInst("+", LoadVarInst(stack, fTemp9), Float(1.0f))))))))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp17)))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp17))))
		DeclareVarInst(stack, "float", fTemp20, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp19))))
		StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(stack, fTemp18)), BinopInst("*", LoadVarInst(stack, fTemp14), LoadVarInst(stack, fTemp20))))
		StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp14), LoadVarInst(stack, fTemp17)), BinopInst("*", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(stack, fTemp20))))
		DeclareVarInst(stack, "float", fRec5, LoadVarInst(struct, fRec6[Int32(0)]))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fTemp8))))
		DeclareVarInst(stack, "float", fTemp22, FunCallInst("sqrtf", LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp9)), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp21)))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("*", LoadVarInst(stack, fTemp22), FunCallInst("sqrtf", LoadVarInst(stack, fTemp19))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp10)), BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp13))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec5), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24))))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("-", Float(2.0f), LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp3)))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp26)), LoadVarInst(stack, fTemp6))), LoadVarInst(stack, fTemp27)))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("/", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp26)), LoadVarInst(stack, fTemp6))), LoadVarInst(stack, fTemp27)), LoadVarInst(stack, fTemp28)))
		DeclareVarInst(stack, "float", fTemp30, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), LoadVarInst(stack, fTemp29))))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp30)))
		DeclareVarInst(stack, "float", fTemp32, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp30))))
		DeclareVarInst(stack, "float", fTemp33, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp32))))
		DeclareVarInst(stack, "float", fTemp34, BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(stack, fTemp31)), BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp33)), LoadVarInst(stack, fTemp8))))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp15)))))
		DeclareVarInst(stack, "float", fTemp36, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(stack, fTemp35), BinopInst("*", LoadVarInst(stack, fTemp28), BinopInst("+", LoadVarInst(stack, fTemp29), Float(1.0f))))))))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp36)))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp36))))
		DeclareVarInst(stack, "float", fTemp39, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp38))))
		StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fTemp37)), BinopInst("*", LoadVarInst(stack, fTemp34), LoadVarInst(stack, fTemp39))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp34), LoadVarInst(stack, fTemp36)), BinopInst("*", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fTemp39))))
		DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec9[Int32(0)]))
		DeclareVarInst(stack, "float", fTemp40, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(stack, fTemp35), LoadVarInst(stack, fTemp28))))
		DeclareVarInst(stack, "float", fTemp41, FunCallInst("sqrtf", LoadVarInst(stack, fTemp32)))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp29)), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp40)))))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("*", LoadVarInst(stack, fTemp41), FunCallInst("sqrtf", LoadVarInst(stack, fTemp38))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp30)), LoadVarInst(stack, fTemp8)), BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp41)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec8), LoadVarInst(stack, fTemp42)), LoadVarInst(stack, fTemp43)))), LoadVarInst(stack, fTemp28))))
		DeclareVarInst(stack, "float", fTemp44, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(stack, iRec2))))
		DeclareVarInst(stack, "float", fTemp45, BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp11), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(stack, fTemp13), LoadVarInst(stack, fTemp44))))
		StoreVarInst(struct, fRec12[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp18), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", LoadVarInst(stack, fTemp20), LoadVarInst(stack, fTemp45))))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp45)), BinopInst("*", LoadVarInst(stack, fTemp20), LoadVarInst(struct, fRec12[Int32(1)]))))
		DeclareVarInst(stack, "float", fRec11, LoadVarInst(struct, fRec12[Int32(0)]))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fTemp44)), BinopInst("*", LoadVarInst(stack, fTemp13), LoadVarInst(struct, fRec10[Int32(1)]))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec10[Int32(0)]), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec11), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24))))
		DeclareVarInst(stack, "float", fTemp47, BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp31), LoadVarInst(struct, fRec13[Int32(1)])), BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp8))))
		StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp37), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(stack, fTemp39), LoadVarInst(stack, fTemp47))))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp47)), BinopInst("*", LoadVarInst(stack, fTemp39), LoadVarInst(struct, fRec15[Int32(1)]))))
		DeclareVarInst(stack, "float", fRec14, LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp8)), BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(struct, fRec13[Int32(1)]))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp41)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec14), LoadVarInst(stack, fTemp42)), LoadVarInst(stack, fTemp43)))), LoadVarInst(stack, fTemp28))))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, iRec1[Int32(1)], LoadVarInst(struct, iRec1[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, int, iRec1[2])
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, float, fRec13[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(3.14159274f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.66000000000000003f)))
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
			StoreVarInst(struct, iRec1[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
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
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", Float(0.00300000003f), CastInst("float", LoadVarInst(struct, fHslider0))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.996999979f), LoadVarInst(struct, fRec0[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp0, BinopInst("*", Int32(1103515245), BinopInst("+", LoadVarInst(struct, iRec1[Int32(1)]), Int32(12345))))
			StoreVarInst(struct, iRec1[Int32(0)], BinopInst("*", Int32(1103515245), BinopInst("+", LoadVarInst(stack, iTemp0), Int32(12345))))
			DeclareVarInst(stack, "int", iRec2, LoadVarInst(stack, iTemp0))
			DeclareVarInst(stack, "float", fTemp1, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(struct, iRec1[Int32(0)]))))
			StoreVarInst(struct, fRec3[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", Float(0.996999979f), LoadVarInst(struct, fRec3[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp2, FunCallInst("mydsp_faustpower2_f", BinopInst("*", Float(1.41419947f), LoadVarInst(struct, fRec3[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", Float(1.99997997f), LoadVarInst(struct, fRec3[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("+", LoadVarInst(stack, fTemp2), LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(stack, fTemp3), Float(2.0f)))
			DeclareVarInst(stack, "float", fTemp6, FunCallInst("tanf", BinopInst("*", LoadVarInst(struct, fConst0), FunCallInst("max_f", BinopInst("*", Float(440.0f), FunCallInst("powf", Float(2.0f), BinopInst("*", Float(0.0833333358f), BinopInst("+", BinopInst("*", Float(87.0f), LoadVarInst(struct, fRec3[Int32(0)])), Float(-48.0f))))), Float(20.0f)))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("/", Float(1.0f), LoadVarInst(stack, fTemp6)))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp6))), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(1.0f), BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp5), LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp6)))), LoadVarInst(stack, fTemp8)))
			DeclareVarInst(stack, "float", fTemp10, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), LoadVarInst(stack, fTemp9))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp10))))
			DeclareVarInst(stack, "float", fTemp13, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp12))))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp11)), BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp13))))
			DeclareVarInst(stack, "float", fTemp15, BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp6))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("+", LoadVarInst(stack, fTemp4), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp15))))
			DeclareVarInst(stack, "float", fTemp17, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(stack, fTemp16), BinopInst("*", LoadVarInst(stack, fTemp8), BinopInst("+", LoadVarInst(stack, fTemp9), Float(1.0f))))))))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp17)))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp17))))
			DeclareVarInst(stack, "float", fTemp20, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp19))))
			StoreVarInst(struct, fRec6[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(stack, fTemp18)), BinopInst("*", LoadVarInst(stack, fTemp14), LoadVarInst(stack, fTemp20))))
			StoreVarInst(struct, fRec4[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp14), LoadVarInst(stack, fTemp17)), BinopInst("*", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(stack, fTemp20))))
			DeclareVarInst(stack, "float", fRec5, LoadVarInst(struct, fRec6[Int32(0)]))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(stack, fTemp16), LoadVarInst(stack, fTemp8))))
			DeclareVarInst(stack, "float", fTemp22, FunCallInst("sqrtf", LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp9)), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp21)))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("*", LoadVarInst(stack, fTemp22), FunCallInst("sqrtf", LoadVarInst(stack, fTemp19))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp1), LoadVarInst(stack, fTemp10)), BinopInst("*", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(stack, fTemp13))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec4[Int32(0)]), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec5), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24))))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("-", Float(2.0f), LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp3)))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("/", BinopInst("+", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp26)), LoadVarInst(stack, fTemp6))), LoadVarInst(stack, fTemp27)))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("/", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("/", BinopInst("-", LoadVarInst(stack, fTemp7), LoadVarInst(stack, fTemp26)), LoadVarInst(stack, fTemp6))), LoadVarInst(stack, fTemp27)), LoadVarInst(stack, fTemp28)))
			DeclareVarInst(stack, "float", fTemp30, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), LoadVarInst(stack, fTemp29))))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp30)))
			DeclareVarInst(stack, "float", fTemp32, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp30))))
			DeclareVarInst(stack, "float", fTemp33, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp32))))
			DeclareVarInst(stack, "float", fTemp34, BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(stack, fTemp31)), BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp33)), LoadVarInst(stack, fTemp8))))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("+", LoadVarInst(stack, fTemp2), BinopInst("-", Float(1.0f), BinopInst("+", LoadVarInst(stack, fTemp3), LoadVarInst(stack, fTemp15)))))
			DeclareVarInst(stack, "float", fTemp36, FunCallInst("max_f", Float(-0.999899983f), FunCallInst("min_f", Float(0.999899983f), BinopInst("*", Float(2.0f), BinopInst("/", LoadVarInst(stack, fTemp35), BinopInst("*", LoadVarInst(stack, fTemp28), BinopInst("+", LoadVarInst(stack, fTemp29), Float(1.0f))))))))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("-", Float(0.0f), LoadVarInst(stack, fTemp36)))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("-", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(stack, fTemp36))))
			DeclareVarInst(stack, "float", fTemp39, FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), LoadVarInst(stack, fTemp38))))
			StoreVarInst(struct, fRec9[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fTemp37)), BinopInst("*", LoadVarInst(stack, fTemp34), LoadVarInst(stack, fTemp39))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp34), LoadVarInst(stack, fTemp36)), BinopInst("*", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(stack, fTemp39))))
			DeclareVarInst(stack, "float", fRec8, LoadVarInst(struct, fRec9[Int32(0)]))
			DeclareVarInst(stack, "float", fTemp40, BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(stack, fTemp35), LoadVarInst(stack, fTemp28))))
			DeclareVarInst(stack, "float", fTemp41, FunCallInst("sqrtf", LoadVarInst(stack, fTemp32)))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("-", BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp29)), BinopInst("*", Float(2.0f), BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp40)))))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("*", LoadVarInst(stack, fTemp41), FunCallInst("sqrtf", LoadVarInst(stack, fTemp38))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp25), LoadVarInst(stack, fTemp30)), LoadVarInst(stack, fTemp8)), BinopInst("*", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec7[Int32(0)]), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp41)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec8), LoadVarInst(stack, fTemp42)), LoadVarInst(stack, fTemp43)))), LoadVarInst(stack, fTemp28))))
			DeclareVarInst(stack, "float", fTemp44, BinopInst("*", Float(4.65661287e-10f), CastInst("float", LoadVarInst(stack, iRec2))))
			DeclareVarInst(stack, "float", fTemp45, BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp11), LoadVarInst(struct, fRec10[Int32(1)])), BinopInst("*", LoadVarInst(stack, fTemp13), LoadVarInst(stack, fTemp44))))
			StoreVarInst(struct, fRec12[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp18), LoadVarInst(struct, fRec12[Int32(1)])), BinopInst("*", LoadVarInst(stack, fTemp20), LoadVarInst(stack, fTemp45))))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp17), LoadVarInst(stack, fTemp45)), BinopInst("*", LoadVarInst(stack, fTemp20), LoadVarInst(struct, fRec12[Int32(1)]))))
			DeclareVarInst(stack, "float", fRec11, LoadVarInst(struct, fRec12[Int32(0)]))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp10), LoadVarInst(stack, fTemp44)), BinopInst("*", LoadVarInst(stack, fTemp13), LoadVarInst(struct, fRec10[Int32(1)]))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec10[Int32(0)]), LoadVarInst(stack, fTemp21)), LoadVarInst(stack, fTemp22)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec11), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp24))))
			DeclareVarInst(stack, "float", fTemp47, BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp31), LoadVarInst(struct, fRec13[Int32(1)])), BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp8))))
			StoreVarInst(struct, fRec15[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp37), LoadVarInst(struct, fRec15[Int32(1)])), BinopInst("*", LoadVarInst(stack, fTemp39), LoadVarInst(stack, fTemp47))))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(stack, fTemp36), LoadVarInst(stack, fTemp47)), BinopInst("*", LoadVarInst(stack, fTemp39), LoadVarInst(struct, fRec15[Int32(1)]))))
			DeclareVarInst(stack, "float", fRec14, LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp30), LoadVarInst(stack, fTemp46)), LoadVarInst(stack, fTemp8)), BinopInst("*", LoadVarInst(stack, fTemp33), LoadVarInst(struct, fRec13[Int32(1)]))), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("*", LoadVarInst(struct, fRec13[Int32(0)]), LoadVarInst(stack, fTemp40)), LoadVarInst(stack, fTemp41)))), BinopInst("/", BinopInst("*", LoadVarInst(stack, fRec14), LoadVarInst(stack, fTemp42)), LoadVarInst(stack, fTemp43)))), LoadVarInst(stack, fTemp28))))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, iRec1[Int32(1)], LoadVarInst(struct, iRec1[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
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
Heap size int* = 8 bytes
Heap size real = 88 bytes
Heap size = 100 bytes
Stack size in compute = 20 bytes

