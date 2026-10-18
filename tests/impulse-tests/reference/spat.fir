======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Spatializer 1x8")
	AddHorizontalSlider("angle", fHslider1, 0.0f, 0.0f, 1.0f, 0.01f)
	AddHorizontalSlider("distance", fHslider0, 0.5f, 0.0f, 1.0f, 0.01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("float[2]", fIIR0)("float[2]", fIIR1)("float[2]", fIIR2)("float[2]", fIIR3)("float[2]", fIIR4)("float[2]", fIIR5)("float[2]", fIIR6)("float[2]", fIIR7)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(8))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.5f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 44 Store = 0 Binop = 49 [ { Real(*) = 24 } { Real(+) = 17 } { Real(-) = 8 } ] Mathop = 36 [ { fabsf = 8 } { fmodf = 8 } { max_f = 10 } { min_f = 2 } { sqrtf = 8 } ] Numbers = 62 Declare = 28 Cast = 2 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(1.5f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(1.375f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow5, kStack)))))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(1.25f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow7, kStack)))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(1.125f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow9, kStack)))))))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow11, kStack)))))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(0.875f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow13, kStack)))))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(0.75f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow15, kStack)))))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(0.625f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow17, kStack)))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 61 Store = 25 Binop = 34 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 24 } { Real(+) = 8 } ] Mathop = 0 Numbers = 50 Declare = 10 Cast = 9 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp1, kStack))))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp2, kStack))))))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp3, kStack))))))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("+", LoadVarInst(Address(fSlow10, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp4, kStack))))))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fSlow12, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp5, kStack)))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp5, kStack))))))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("+", LoadVarInst(Address(fSlow14, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp6, kStack))))))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("+", LoadVarInst(Address(fSlow16, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp7, kStack)))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp7, kStack))))))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("+", LoadVarInst(Address(fSlow18, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp8, kStack)))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp8, kStack))))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Post compute DSP begin ==========

BlockInst 
EndBlockInst

======= Post compute DSP end ==========

======= Flatten FIR begin ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fIIR0[2], kStruct)
	DeclareVarInst("float", fIIR1[2], kStruct)
	DeclareVarInst("float", fIIR2[2], kStruct)
	DeclareVarInst("float", fIIR3[2], kStruct)
	DeclareVarInst("float", fIIR4[2], kStruct)
	DeclareVarInst("float", fIIR5[2], kStruct)
	DeclareVarInst("float", fIIR6[2], kStruct)
	DeclareVarInst("float", fIIR7[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.5f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(1.5f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(1.375f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow5, kStack)))))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(1.25f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow7, kStack)))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(1.125f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow9, kStack)))))))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow11, kStack)))))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(0.875f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow13, kStack)))))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(0.75f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow15, kStack)))))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", Float(-0.5f), FunCallInst("fmodf", BinopInst("+", Float(0.625f), LoadVarInst(Address(fSlow1, kStack))), Float(1.0f)))))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow17, kStack)))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp1, kStack))))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp2, kStack))))))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp3, kStack))))))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("+", LoadVarInst(Address(fSlow10, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp4, kStack))))))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fSlow12, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp5, kStack)))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp5, kStack))))))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("+", LoadVarInst(Address(fSlow14, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp6, kStack))))))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("+", LoadVarInst(Address(fSlow16, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp7, kStack)))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp7, kStack))))))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("+", LoadVarInst(Address(fSlow18, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp8, kStack)))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", Float(5e-05f), LoadVarInst(Address(fTemp8, kStack))))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 72 bytes
Total heap size = 76 bytes
Stack size in compute = 148 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR4 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR5 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR6 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR7 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            814
  eval() cache hits:       193 (23.7101%)
  eval() cache misses:     621
  Loop detector calls:     621
  Stack detector calls:    621

--- Phase 3: Propagation ---
  propagate() calls:       570
  propagate() cache hits:  182 (31.9298%)
  propagate() cache misses:388

--- Box Type Computation ---
  getBoxType() calls:      1118
  getBoxType() cache hits: 873 (78.0859%)
  getBoxType() computed:   245

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       45

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           2931
  Trees reused (hash):     6988 (70.4507% reuse rate)
  Property set ops:        1368
  Property get ops:        5111

--- Iteration Constructs ---
  par() iterations:        8
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
