======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("oneSourceToStereo")
	AddHorizontalSlider("Angle", fHslider1, 0.0f, -6.28318548f, 6.28318548f, 0.00100000005f)
	AddHorizontalSlider("Radius", fHslider0, 1.0f, 0.0f, 5.0f, 0.00100000005f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
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
	StoreVarInst(struct, fConst0, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(50.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))))
	StoreVarInst(struct, fConst1, BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst0)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
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
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 7
Store = 0
Binop = 2
Numbers = 0
Declare = 5
Cast = 2
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 299
Store = 7
Binop = 431
Numbers = 217
Declare = 71
Cast = 28
Select = 0
Loop = 1
Funcall = 15

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec0[Int32(1)]))))
		DeclareVarInst(stack, "int", iTemp0, BinopInst(">", LoadVarInst(struct, fRec0[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "int", iTemp1, BinopInst("<", LoadVarInst(struct, fRec0[Int32(0)]), Float(1.0f)))
		DeclareVarInst(stack, "float", fTemp2, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp0)), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), CastInst("float", LoadVarInst(stack, iTemp1)))))
		DeclareVarInst(stack, "float", fTemp3, BinopInst("*", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("+", BinopInst("*", Float(2.07944155f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp2))), Float(1.0f))))
		DeclareVarInst(stack, "float", fTemp4, BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp2)))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", BinopInst("*", Float(3.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp2), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp4), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp4), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp4), Float(1.0f)))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec1[Int32(1)]))))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(stack, fTemp5), FunCallInst("cosf", LoadVarInst(struct, fRec1[Int32(0)]))))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec1[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("*", Float(2.07944155f), LoadVarInst(stack, fTemp2)))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-0.693147182f)))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("*", Float(2.46630335f), LoadVarInst(stack, fTemp9)))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", BinopInst("*", Float(2.46630335f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp10), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp10), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp10), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("*", Float(0.0777777806f), LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("*", Float(3.0f), LoadVarInst(struct, fRec1[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp15, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-1.09861231f)))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("*", Float(3.47605944f), LoadVarInst(stack, fTemp15)))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("+", BinopInst("*", Float(3.47605944f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp15), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp16), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp16), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp16), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp17)))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("*", Float(4.0f), LoadVarInst(struct, fRec1[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-1.38629436f)))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("*", Float(4.48142004f), LoadVarInst(stack, fTemp20)))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("+", BinopInst("*", Float(4.48142004f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp20), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp21), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp21), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp21), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("*", Float(0.0141414143f), BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp22))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("*", Float(5.0f), LoadVarInst(struct, fRec1[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-1.60943794f)))
		DeclareVarInst(stack, "float", fTemp26, BinopInst("*", Float(5.48481512f), LoadVarInst(stack, fTemp25)))
		DeclareVarInst(stack, "float", fTemp27, BinopInst("+", BinopInst("*", Float(5.48481512f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp25), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp26), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp26), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp26), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp28, BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp24)), LoadVarInst(stack, fTemp27)))
		DeclareVarInst(stack, "float", fTemp29, BinopInst("*", Float(6.0f), LoadVarInst(struct, fRec1[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp30, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-1.79175949f)))
		DeclareVarInst(stack, "float", fTemp31, BinopInst("*", Float(6.48715925f), LoadVarInst(stack, fTemp30)))
		DeclareVarInst(stack, "float", fTemp32, BinopInst("+", BinopInst("*", Float(6.48715925f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp30), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp31), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp31), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp31), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp33, BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp29)), LoadVarInst(stack, fTemp32)))
		DeclareVarInst(stack, "float", fTemp34, BinopInst("*", Float(0.00175299495f), LoadVarInst(stack, fTemp33)))
		DeclareVarInst(stack, "float", fTemp35, BinopInst("*", Float(7.0f), LoadVarInst(struct, fRec1[Int32(0)])))
		DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-1.9459101f)))
		DeclareVarInst(stack, "float", fTemp37, BinopInst("*", Float(7.48887587f), LoadVarInst(stack, fTemp36)))
		DeclareVarInst(stack, "float", fTemp38, BinopInst("+", BinopInst("*", Float(7.48887587f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp36), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp37), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp37), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp37), Float(1.0f)))))
		DeclareVarInst(stack, "float", fTemp39, BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp38)))
		DeclareVarInst(stack, "float", fTemp40, BinopInst("*", Float(0.707106769f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.116666667f), LoadVarInst(stack, fTemp6)), Float(0.0666666701f)), LoadVarInst(stack, fTemp13)), BinopInst("*", Float(0.0388888903f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp23)), BinopInst("*", Float(0.00353535358f), LoadVarInst(stack, fTemp28))), LoadVarInst(stack, fTemp34)), BinopInst("*", Float(0.00264818221f), LoadVarInst(stack, fTemp39)))))
		DeclareVarInst(stack, "float", fTemp41, BinopInst("*", Float(0.0141414143f), BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp22))))
		DeclareVarInst(stack, "float", fTemp42, BinopInst("*", FunCallInst("sinf", LoadVarInst(struct, fRec1[Int32(0)])), LoadVarInst(stack, fTemp5)))
		DeclareVarInst(stack, "float", fTemp43, BinopInst("*", Float(0.107785948f), LoadVarInst(stack, fTemp6)))
		DeclareVarInst(stack, "float", fTemp44, BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp11)))
		DeclareVarInst(stack, "float", fTemp45, BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44)))
		DeclareVarInst(stack, "float", fTemp46, BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "float", fTemp47, BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp17)))
		DeclareVarInst(stack, "float", fTemp48, BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp24)), LoadVarInst(stack, fTemp27)))
		DeclareVarInst(stack, "float", fTemp49, BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp29)), LoadVarInst(stack, fTemp32)))
		DeclareVarInst(stack, "float", fTemp50, BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49)))
		DeclareVarInst(stack, "float", fTemp51, BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33)))
		DeclareVarInst(stack, "float", fTemp52, BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp38)))
		DeclareVarInst(stack, "float", fTemp53, BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp42)), Float(0.0666666701f)), LoadVarInst(stack, fTemp43)), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46)), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp18)))), BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp28))), LoadVarInst(stack, fTemp50)), LoadVarInst(stack, fTemp51)), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp39))))
		DeclareVarInst(stack, "float", fTemp54, BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp42)))
		DeclareVarInst(stack, "float", fTemp55, BinopInst("*", Float(0.0777777806f), LoadVarInst(stack, fTemp44)))
		DeclareVarInst(stack, "float", fTemp56, BinopInst("*", Float(0.00175299495f), LoadVarInst(stack, fTemp49)))
		DeclareVarInst(stack, "float", fTemp57, BinopInst("+", BinopInst("*", Float(0.107785948f), LoadVarInst(stack, fTemp42)), Float(0.0666666701f)))
		DeclareVarInst(stack, "float", fTemp58, BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "float", fTemp59, BinopInst("*", Float(0.116666667f), LoadVarInst(stack, fTemp42)))
		DeclareVarInst(stack, "float", fTemp60, BinopInst("*", Float(0.0388888903f), LoadVarInst(stack, fTemp47)))
		DeclareVarInst(stack, "float", fTemp61, BinopInst("*", Float(0.00353535358f), LoadVarInst(stack, fTemp48)))
		DeclareVarInst(stack, "float", fTemp62, BinopInst("*", Float(0.00264818221f), LoadVarInst(stack, fTemp52)))
		DeclareVarInst(stack, "float", fTemp63, BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp6)))
		DeclareVarInst(stack, "float", fTemp64, BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp47)))
		DeclareVarInst(stack, "float", fTemp65, BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp48)))
		DeclareVarInst(stack, "float", fTemp66, BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp18)), BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("-", Float(0.0666666701f), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp42))), BinopInst("*", Float(0.107785948f), LoadVarInst(stack, fTemp6))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12))), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp47)))), LoadVarInst(stack, fTemp41)), LoadVarInst(stack, fTemp65)), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp28))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp39))))
		DeclareVarInst(stack, "float", fTemp67, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp1)), BinopInst("*", FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fRec0[Int32(0)])), CastInst("float", LoadVarInst(stack, iTemp0)))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp3), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp40), BinopInst("*", Float(0.980785251f), LoadVarInst(stack, fTemp53))), BinopInst("*", Float(0.987688363f), BinopInst("+", BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp39)), BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp54), Float(0.0666666701f)), BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp6))), LoadVarInst(stack, fTemp55)), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp23)), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp28))), LoadVarInst(stack, fTemp56)), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp52)))))), BinopInst("*", Float(0.923879504f), BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp51), BinopInst("+", LoadVarInst(stack, fTemp50), BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp57), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp6))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44))), LoadVarInst(stack, fTemp58)), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp41)), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp28))))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.809017003f), BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp23), BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp59), Float(0.0666666701f)), LoadVarInst(stack, fTemp13)), LoadVarInst(stack, fTemp60))), LoadVarInst(stack, fTemp61)), LoadVarInst(stack, fTemp34)), LoadVarInst(stack, fTemp62)))), BinopInst("*", Float(0.649448037f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp57), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp6))), LoadVarInst(stack, fTemp45)), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12))), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp18)))), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp28))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.453990489f), BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp56), BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp47)), BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp42)), Float(0.0666666701f)), LoadVarInst(stack, fTemp63)), LoadVarInst(stack, fTemp55))), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp23)), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp28)))), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.233445361f), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp42)), Float(0.0666666701f)), LoadVarInst(stack, fTemp43)), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44)))), LoadVarInst(stack, fTemp64)), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp41)), LoadVarInst(stack, fTemp65)), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp28))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.195090324f), LoadVarInst(stack, fTemp66)))), LoadVarInst(stack, fTemp67))))
		DeclareVarInst(stack, "float", fTemp68, BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp48)))
		DeclareVarInst(stack, "float", fTemp69, BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp28)))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp3), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp40), BinopInst("*", Float(0.195090324f), LoadVarInst(stack, fTemp53))), BinopInst("*", Float(0.233445361f), BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp46), BinopInst("+", LoadVarInst(stack, fTemp45), BinopInst("-", BinopInst("-", Float(0.0666666701f), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp42))), LoadVarInst(stack, fTemp43)))), LoadVarInst(stack, fTemp64)), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp18)))), BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp28))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.453990489f), BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp55), BinopInst("-", BinopInst("-", Float(0.0666666701f), LoadVarInst(stack, fTemp54)), BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp6)))), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp68)), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp28))), LoadVarInst(stack, fTemp56)), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.649448037f), BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44)), BinopInst("-", BinopInst("-", Float(0.0666666701f), BinopInst("*", Float(0.107785948f), LoadVarInst(stack, fTemp42))), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp6)))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12))), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp41)), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp48))), LoadVarInst(stack, fTemp69)), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.809017003f), BinopInst("+", LoadVarInst(stack, fTemp62), BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp23), BinopInst("+", LoadVarInst(stack, fTemp60), BinopInst("-", BinopInst("-", Float(0.0666666701f), LoadVarInst(stack, fTemp59)), LoadVarInst(stack, fTemp13)))), LoadVarInst(stack, fTemp61)), LoadVarInst(stack, fTemp34))))), BinopInst("*", Float(0.923879504f), BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp69), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("-", Float(0.0666666701f), BinopInst("*", Float(0.107785948f), LoadVarInst(stack, fTemp42))), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp6))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12))), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp18)))), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp48)))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.987688363f), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp56), BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp68), BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp63), BinopInst("-", Float(0.0666666701f), BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp42)))), LoadVarInst(stack, fTemp55)), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp23))), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp28)))), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.980785251f), LoadVarInst(stack, fTemp66)))), LoadVarInst(stack, fTemp67))))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "float", fConst1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, float, fRec1[2])
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("expf", BinopInst("-", Float(0.0f), BinopInst("/", Float(50.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))))
	StoreVarInst(struct, fConst1, BinopInst("-", Float(1.0f), LoadVarInst(struct, fConst0)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
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
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider0))))
	DeclareVarInst(stack, "float", fSlow1, BinopInst("*", LoadVarInst(struct, fConst1), CastInst("float", LoadVarInst(struct, fHslider1))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec0[Int32(1)]))))
			DeclareVarInst(stack, "int", iTemp0, BinopInst(">", LoadVarInst(struct, fRec0[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "int", iTemp1, BinopInst("<", LoadVarInst(struct, fRec0[Int32(0)]), Float(1.0f)))
			DeclareVarInst(stack, "float", fTemp2, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp0)), BinopInst("*", LoadVarInst(struct, fRec0[Int32(0)]), CastInst("float", LoadVarInst(stack, iTemp1)))))
			DeclareVarInst(stack, "float", fTemp3, BinopInst("*", CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])), BinopInst("+", BinopInst("*", Float(2.07944155f), BinopInst("-", Float(1.0f), LoadVarInst(stack, fTemp2))), Float(1.0f))))
			DeclareVarInst(stack, "float", fTemp4, BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp2)))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", BinopInst("*", Float(3.0f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp2), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp4), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp4), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp4), Float(1.0f)))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("+", LoadVarInst(stack, fSlow1), BinopInst("*", LoadVarInst(struct, fConst0), LoadVarInst(struct, fRec1[Int32(1)]))))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(stack, fTemp5), FunCallInst("cosf", LoadVarInst(struct, fRec1[Int32(0)]))))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("*", Float(2.0f), LoadVarInst(struct, fRec1[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("*", Float(2.07944155f), LoadVarInst(stack, fTemp2)))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-0.693147182f)))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("*", Float(2.46630335f), LoadVarInst(stack, fTemp9)))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", BinopInst("*", Float(2.46630335f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp9), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp10), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp10), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp10), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("*", Float(0.0777777806f), LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("*", Float(3.0f), LoadVarInst(struct, fRec1[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp15, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-1.09861231f)))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("*", Float(3.47605944f), LoadVarInst(stack, fTemp15)))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("+", BinopInst("*", Float(3.47605944f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp15), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp16), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp16), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp16), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp17)))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("*", Float(4.0f), LoadVarInst(struct, fRec1[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-1.38629436f)))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("*", Float(4.48142004f), LoadVarInst(stack, fTemp20)))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("+", BinopInst("*", Float(4.48142004f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp20), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp21), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp21), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp21), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("*", Float(0.0141414143f), BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp22))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("*", Float(5.0f), LoadVarInst(struct, fRec1[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-1.60943794f)))
			DeclareVarInst(stack, "float", fTemp26, BinopInst("*", Float(5.48481512f), LoadVarInst(stack, fTemp25)))
			DeclareVarInst(stack, "float", fTemp27, BinopInst("+", BinopInst("*", Float(5.48481512f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp25), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp26), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp26), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp26), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp28, BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp24)), LoadVarInst(stack, fTemp27)))
			DeclareVarInst(stack, "float", fTemp29, BinopInst("*", Float(6.0f), LoadVarInst(struct, fRec1[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp30, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-1.79175949f)))
			DeclareVarInst(stack, "float", fTemp31, BinopInst("*", Float(6.48715925f), LoadVarInst(stack, fTemp30)))
			DeclareVarInst(stack, "float", fTemp32, BinopInst("+", BinopInst("*", Float(6.48715925f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp30), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp31), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp31), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp31), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp33, BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp29)), LoadVarInst(stack, fTemp32)))
			DeclareVarInst(stack, "float", fTemp34, BinopInst("*", Float(0.00175299495f), LoadVarInst(stack, fTemp33)))
			DeclareVarInst(stack, "float", fTemp35, BinopInst("*", Float(7.0f), LoadVarInst(struct, fRec1[Int32(0)])))
			DeclareVarInst(stack, "float", fTemp36, BinopInst("+", LoadVarInst(stack, fTemp8), Float(-1.9459101f)))
			DeclareVarInst(stack, "float", fTemp37, BinopInst("*", Float(7.48887587f), LoadVarInst(stack, fTemp36)))
			DeclareVarInst(stack, "float", fTemp38, BinopInst("+", BinopInst("*", Float(7.48887587f), BinopInst("*", BinopInst("*", LoadVarInst(stack, fTemp36), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp37), Float(0.0f)))), CastInst("float", BinopInst("<=", LoadVarInst(stack, fTemp37), Float(1.0f))))), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp37), Float(1.0f)))))
			DeclareVarInst(stack, "float", fTemp39, BinopInst("*", FunCallInst("cosf", LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp38)))
			DeclareVarInst(stack, "float", fTemp40, BinopInst("*", Float(0.707106769f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.116666667f), LoadVarInst(stack, fTemp6)), Float(0.0666666701f)), LoadVarInst(stack, fTemp13)), BinopInst("*", Float(0.0388888903f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp23)), BinopInst("*", Float(0.00353535358f), LoadVarInst(stack, fTemp28))), LoadVarInst(stack, fTemp34)), BinopInst("*", Float(0.00264818221f), LoadVarInst(stack, fTemp39)))))
			DeclareVarInst(stack, "float", fTemp41, BinopInst("*", Float(0.0141414143f), BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp19)), LoadVarInst(stack, fTemp22))))
			DeclareVarInst(stack, "float", fTemp42, BinopInst("*", FunCallInst("sinf", LoadVarInst(struct, fRec1[Int32(0)])), LoadVarInst(stack, fTemp5)))
			DeclareVarInst(stack, "float", fTemp43, BinopInst("*", Float(0.107785948f), LoadVarInst(stack, fTemp6)))
			DeclareVarInst(stack, "float", fTemp44, BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp7)), LoadVarInst(stack, fTemp11)))
			DeclareVarInst(stack, "float", fTemp45, BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44)))
			DeclareVarInst(stack, "float", fTemp46, BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "float", fTemp47, BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp14)), LoadVarInst(stack, fTemp17)))
			DeclareVarInst(stack, "float", fTemp48, BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp24)), LoadVarInst(stack, fTemp27)))
			DeclareVarInst(stack, "float", fTemp49, BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp29)), LoadVarInst(stack, fTemp32)))
			DeclareVarInst(stack, "float", fTemp50, BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49)))
			DeclareVarInst(stack, "float", fTemp51, BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33)))
			DeclareVarInst(stack, "float", fTemp52, BinopInst("*", FunCallInst("sinf", LoadVarInst(stack, fTemp35)), LoadVarInst(stack, fTemp38)))
			DeclareVarInst(stack, "float", fTemp53, BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp42)), Float(0.0666666701f)), LoadVarInst(stack, fTemp43)), LoadVarInst(stack, fTemp45)), LoadVarInst(stack, fTemp46)), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp18)))), BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp28))), LoadVarInst(stack, fTemp50)), LoadVarInst(stack, fTemp51)), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp39))))
			DeclareVarInst(stack, "float", fTemp54, BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp42)))
			DeclareVarInst(stack, "float", fTemp55, BinopInst("*", Float(0.0777777806f), LoadVarInst(stack, fTemp44)))
			DeclareVarInst(stack, "float", fTemp56, BinopInst("*", Float(0.00175299495f), LoadVarInst(stack, fTemp49)))
			DeclareVarInst(stack, "float", fTemp57, BinopInst("+", BinopInst("*", Float(0.107785948f), LoadVarInst(stack, fTemp42)), Float(0.0666666701f)))
			DeclareVarInst(stack, "float", fTemp58, BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "float", fTemp59, BinopInst("*", Float(0.116666667f), LoadVarInst(stack, fTemp42)))
			DeclareVarInst(stack, "float", fTemp60, BinopInst("*", Float(0.0388888903f), LoadVarInst(stack, fTemp47)))
			DeclareVarInst(stack, "float", fTemp61, BinopInst("*", Float(0.00353535358f), LoadVarInst(stack, fTemp48)))
			DeclareVarInst(stack, "float", fTemp62, BinopInst("*", Float(0.00264818221f), LoadVarInst(stack, fTemp52)))
			DeclareVarInst(stack, "float", fTemp63, BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp6)))
			DeclareVarInst(stack, "float", fTemp64, BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp47)))
			DeclareVarInst(stack, "float", fTemp65, BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp48)))
			DeclareVarInst(stack, "float", fTemp66, BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp18)), BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("-", Float(0.0666666701f), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp42))), BinopInst("*", Float(0.107785948f), LoadVarInst(stack, fTemp6))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12))), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp47)))), LoadVarInst(stack, fTemp41)), LoadVarInst(stack, fTemp65)), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp28))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp39))))
			DeclareVarInst(stack, "float", fTemp67, BinopInst("+", CastInst("float", LoadVarInst(stack, iTemp1)), BinopInst("*", FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fRec0[Int32(0)])), CastInst("float", LoadVarInst(stack, iTemp0)))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp3), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp40), BinopInst("*", Float(0.980785251f), LoadVarInst(stack, fTemp53))), BinopInst("*", Float(0.987688363f), BinopInst("+", BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp39)), BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp54), Float(0.0666666701f)), BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp6))), LoadVarInst(stack, fTemp55)), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp23)), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp28))), LoadVarInst(stack, fTemp56)), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp52)))))), BinopInst("*", Float(0.923879504f), BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp51), BinopInst("+", LoadVarInst(stack, fTemp50), BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp57), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp6))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44))), LoadVarInst(stack, fTemp58)), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp41)), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp28))))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.809017003f), BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp23), BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp59), Float(0.0666666701f)), LoadVarInst(stack, fTemp13)), LoadVarInst(stack, fTemp60))), LoadVarInst(stack, fTemp61)), LoadVarInst(stack, fTemp34)), LoadVarInst(stack, fTemp62)))), BinopInst("*", Float(0.649448037f), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", LoadVarInst(stack, fTemp57), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp6))), LoadVarInst(stack, fTemp45)), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12))), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp18)))), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp28))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.453990489f), BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp56), BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp47)), BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp42)), Float(0.0666666701f)), LoadVarInst(stack, fTemp63)), LoadVarInst(stack, fTemp55))), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp23)), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp28)))), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.233445361f), BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp58), BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp42)), Float(0.0666666701f)), LoadVarInst(stack, fTemp43)), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44)))), LoadVarInst(stack, fTemp64)), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp41)), LoadVarInst(stack, fTemp65)), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp28))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.195090324f), LoadVarInst(stack, fTemp66)))), LoadVarInst(stack, fTemp67))))
			DeclareVarInst(stack, "float", fTemp68, BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp48)))
			DeclareVarInst(stack, "float", fTemp69, BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp28)))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("/", BinopInst("*", LoadVarInst(stack, fTemp3), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp40), BinopInst("*", Float(0.195090324f), LoadVarInst(stack, fTemp53))), BinopInst("*", Float(0.233445361f), BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp46), BinopInst("+", LoadVarInst(stack, fTemp45), BinopInst("-", BinopInst("-", Float(0.0666666701f), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp42))), LoadVarInst(stack, fTemp43)))), LoadVarInst(stack, fTemp64)), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp18)))), BinopInst("*", Float(0.0032662407f), LoadVarInst(stack, fTemp48))), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp28))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.453990489f), BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp55), BinopInst("-", BinopInst("-", Float(0.0666666701f), LoadVarInst(stack, fTemp54)), BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp6)))), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp23)), LoadVarInst(stack, fTemp68)), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp28))), LoadVarInst(stack, fTemp56)), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.649448037f), BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("+", BinopInst("-", BinopInst("+", BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44)), BinopInst("-", BinopInst("-", Float(0.0666666701f), BinopInst("*", Float(0.107785948f), LoadVarInst(stack, fTemp42))), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp6)))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12))), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp41)), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp48))), LoadVarInst(stack, fTemp69)), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.809017003f), BinopInst("+", LoadVarInst(stack, fTemp62), BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp23), BinopInst("+", LoadVarInst(stack, fTemp60), BinopInst("-", BinopInst("-", Float(0.0666666701f), LoadVarInst(stack, fTemp59)), LoadVarInst(stack, fTemp13)))), LoadVarInst(stack, fTemp61)), LoadVarInst(stack, fTemp34))))), BinopInst("*", Float(0.923879504f), BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp69), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp41), BinopInst("-", BinopInst("+", BinopInst("-", BinopInst("-", BinopInst("+", BinopInst("-", Float(0.0666666701f), BinopInst("*", Float(0.107785948f), LoadVarInst(stack, fTemp42))), BinopInst("*", Float(0.044646401f), LoadVarInst(stack, fTemp6))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp44))), BinopInst("*", Float(0.0549971946f), LoadVarInst(stack, fTemp12))), BinopInst("*", Float(0.0148821333f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.035928648f), LoadVarInst(stack, fTemp18)))), BinopInst("*", Float(0.00135292124f), LoadVarInst(stack, fTemp48)))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp49))), BinopInst("*", Float(0.00123955461f), LoadVarInst(stack, fTemp33))), BinopInst("*", Float(0.00244660117f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.0010134154f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.987688363f), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp56), BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp68), BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("-", BinopInst("+", LoadVarInst(stack, fTemp63), BinopInst("-", Float(0.0666666701f), BinopInst("*", Float(0.0824957937f), LoadVarInst(stack, fTemp42)))), LoadVarInst(stack, fTemp55)), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp47))), BinopInst("*", Float(0.0274985973f), LoadVarInst(stack, fTemp18))), LoadVarInst(stack, fTemp23))), BinopInst("*", Float(0.00249987235f), LoadVarInst(stack, fTemp28)))), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp52))), BinopInst("*", Float(0.00187254755f), LoadVarInst(stack, fTemp39))))), BinopInst("*", Float(0.980785251f), LoadVarInst(stack, fTemp66)))), LoadVarInst(stack, fTemp67))))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 32 bytes
Heap size = 36 bytes
Stack size in compute = 32 bytes

