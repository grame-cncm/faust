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
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("float[2]", fRec0)("float[2]", fRec1)("float[2]", fRec2)("float[2]", fRec3)("float[2]", fRec4)("float[2]", fRec5)("float[2]", fRec6)("float[2]", fRec7)("int", fSampleRate)>)

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
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 36 Store = 0 Binop = 57 [ { Real(*) = 32 } { Real(+) = 17 } { Real(-) = 8 } ] Mathop = 32 [ { fabsf = 8 } { fmodf = 8 } { max_f = 8 } { sqrtf = 8 } ] Numbers = 66 Declare = 20 Cast = 2 Select = 0 Loop = 0

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
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), Float(1.0f)))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.5f)), Float(1.0f)), Float(-0.5f)))))))), LoadVarInst(Address(fSlow2, kStack)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.375f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.25f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.125f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(0.875f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(0.75f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(0.625f)), Float(1.0f)), Float(-0.5f)))))))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 53 Store = 25 Binop = 26 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 16 } { Real(+) = 8 } ] Mathop = 0 Numbers = 50 Declare = 2 Cast = 9 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow3, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow10, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "sqrtf", "float", dummy0)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("float", fRec7[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), Float(1.0f)))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.5f)), Float(1.0f)), Float(-0.5f)))))))), LoadVarInst(Address(fSlow2, kStack)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.375f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.25f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.125f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(0.875f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(0.75f)), Float(1.0f)), Float(-0.5f)))))))))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("*", Float(5e-05f), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), FunCallInst("sqrtf", FunCallInst("max_f", Float(0.0f), BinopInst("-", Float(1.0f), BinopInst("*", Float(8.0f), BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), FunCallInst("fabsf", BinopInst("+", FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(0.625f)), Float(1.0f)), Float(-0.5f)))))))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow3, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow10, kStack)), BinopInst("*", Float(0.9999f), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
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
Stack size in compute = 116 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec3 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec7 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
