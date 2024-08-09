======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("comb_bug")
	AddHorizontalSlider("comb_res", fHslider0, 0.999f, -0.999f, 0.999f, 0.01f)
	AddHorizontalSlider("env_a", fHslider2, 0.95f, 0.001f, 1.0f, 0.01f)
	AddHorizontalSlider("env_r", fHslider3, 0.95f, 0.001f, 1.0f, 0.01f)
	AddHorizontalSlider("freq", fHslider4, 2e+02f, 2e+02f, 8e+02f, 1.0f)
	AddHorizontalSlider("gain", fHslider5, 0.8f, 0.0f, 1.0f, 0.01f)
	AddButtonInst("gate"fButton0)
	AddHorizontalSlider("vitesse", fHslider1, 127.0f, 0.0f, 127.0f, 1.0f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("int[2]", iRec2)("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fHslider2)("FAUSTFLOAT", fButton0)("float[2]", fVec0)("int[2]", iRec3)("FAUSTFLOAT", fHslider3)("float", fConst1)("float[2]", fRec4)("float", fConst2)("int[2]", iRec5)("int", IOTA0)("float[2048]", fVec1)("float", fConst3)("float", fConst4)("FAUSTFLOAT", fHslider4)("float[2]", fRec6)("float", fConst5)("float", fConst6)("float[2]", fRec0)("FAUSTFLOAT", fHslider5)("float[2]", fRec7)("float[2]", fVec2)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.1f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.01f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst3, kStruct), FunCallInst("expf", MinusInst(BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst3, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(0.9993265f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("*", Float(1.0006735f), LoadVarInst(Address(fConst0, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.999f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(127.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.95f)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.95f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(2e+02f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.8f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec2, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec3, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec5, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2048))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 14 Store = 0 Binop = 8 [ { Real(*) = 5 } { Real(/) = 2 } { Real(==) = 1 } ] Mathop = 2 [ { max_f = 2 } ] Numbers = 9 Declare = 11 Cast = 7 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(3.6666243e-12f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))))
	DeclareVarInst("int", iSlow6, kStack, BinopInst("==", LoadVarInst(Address(fSlow4, kStack)), Float(0.0f)))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider5, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 80 Store = 23 Binop = 54 [ { Int(&) = 3 } { Int(*) = 3 } { Int(+) = 7 } { Int(-) = 2 } { Int(<) = 1 } { Int(>) = 1 } { Real(*) = 15 } { Real(+) = 9 } { Real(-) = 5 } { Real(/) = 3 } { Real(<=) = 2 } { Real(>) = 1 } { Real(>=) = 2 } ] Mathop = 10 [ { floorf = 2 } { max_f = 2 } { max_i = 2 } { min_f = 2 } { min_i = 2 } ] Numbers = 73 Declare = 11 Cast = 7 Select = 2 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iRec2, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec2, kStruct)[Int32(1)])), Int32(12345)))
		StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fSlow4, kStack)))
		StoreVarInst(Address(iRec3, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("+", LoadVarInst(Address(iRec3, kStruct)[Int32(1)]), BinopInst(">", LoadVarInst(Address(iRec3, kStruct)[Int32(1)]), Int32(0))), BinopInst("<=", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)]))), BinopInst(">", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(iRec3, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), CastInst("float", BinopInst(">=", LoadVarInst(Address(fVec0, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow4, kStack)))))))
		StoreVarInst(Address(iRec5, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(iSlow6, kStack)), BinopInst("+", LoadVarInst(Address(iRec5, kStruct)[Int32(1)]), Int32(1))))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", BinopInst("*", CastInst("float", LoadVarInst(Address(iRec2, kStruct)[Int32(0)])), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("-", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fTemp0, kStack)))), Float(1.0f))))), FunCallInst("max_f", Float(0.0f), BinopInst("-", FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)])), Float(1.0f)), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), CastInst("float", LoadVarInst(Address(iRec5, kStruct)[Int32(0)])))))))))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp1, kStack)))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("/", LoadVarInst(Address(fConst0, kStruct)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp2, kStack)))))
		DeclareVarInst("float", fTemp4, kStack, Select2Inst(BinopInst("<=", LoadVarInst(Address(fTemp3, kStack)), Float(0.06f)) BinopInst("/", LoadVarInst(Address(fConst6, kStruct)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])) Select2Inst(BinopInst(">=", LoadVarInst(Address(fTemp3, kStack)), Float(0.95f)) BinopInst("/", LoadVarInst(Address(fConst5, kStruct)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])) LoadVarInst(Address(fTemp2, kStack)))))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), Float(-1.0f)))
		DeclareVarInst("int", iTemp6, kStack, CastInst("int", LoadVarInst(Address(fTemp5, kStack))))
		DeclareVarInst("float", fTemp7, kStack, FunCallInst("floorf", LoadVarInst(Address(fTemp5, kStack))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp6, kStack))))), Int32(2047))]), BinopInst("+", LoadVarInst(Address(fTemp7, kStack)), BinopInst("-", Float(2.0f), LoadVarInst(Address(fTemp4, kStack))))), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), BinopInst("-", Float(-1.0f), LoadVarInst(Address(fTemp7, kStack)))), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(Address(iTemp6, kStack)), Int32(1))))), Int32(2047))]))))
		DeclareVarInst("float", fRec1, kStack, LoadVarInst(Address(fTemp1, kStack)))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec2, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fRec1, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp8, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp8, kStack))))
		StoreVarInst(Address(iRec2, kStruct)[Int32(1)], LoadVarInst(Address(iRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(iRec3, kStruct)[Int32(1)], LoadVarInst(Address(iRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(iRec5, kStruct)[Int32(1)], LoadVarInst(Address(iRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", iRec2[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fButton0, kStruct)
	DeclareVarInst("float", fVec0[2], kStruct)
	DeclareVarInst("int", iRec3[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("int", iRec5[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec1[2048], kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("float", fConst5, kStruct)
	DeclareVarInst("float", fConst6, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("float", fRec7[2], kStruct)
	DeclareVarInst("float", fVec2[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.1f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.01f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst3, kStruct), FunCallInst("expf", MinusInst(BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst3, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(0.9993265f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("*", Float(1.0006735f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.999f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(127.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.95f)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.95f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(2e+02f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.8f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec2, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec3, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec5, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2048))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(3.6666243e-12f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))))
	DeclareVarInst("int", iSlow6, kStack, BinopInst("==", LoadVarInst(Address(fSlow4, kStack)), Float(0.0f)))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider5, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec2, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec2, kStruct)[Int32(1)])), Int32(12345)))
			StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fSlow4, kStack)))
			StoreVarInst(Address(iRec3, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("+", LoadVarInst(Address(iRec3, kStruct)[Int32(1)]), BinopInst(">", LoadVarInst(Address(iRec3, kStruct)[Int32(1)]), Int32(0))), BinopInst("<=", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)]))), BinopInst(">", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(iRec3, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), CastInst("float", BinopInst(">=", LoadVarInst(Address(fVec0, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow4, kStack)))))))
			StoreVarInst(Address(iRec5, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(iSlow6, kStack)), BinopInst("+", LoadVarInst(Address(iRec5, kStruct)[Int32(1)]), Int32(1))))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", BinopInst("*", CastInst("float", LoadVarInst(Address(iRec2, kStruct)[Int32(0)])), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), BinopInst("-", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fTemp0, kStack)))), Float(1.0f))))), FunCallInst("max_f", Float(0.0f), BinopInst("-", FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)])), Float(1.0f)), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), CastInst("float", LoadVarInst(Address(iRec5, kStruct)[Int32(0)])))))))))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp1, kStack)))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("/", LoadVarInst(Address(fConst0, kStruct)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp2, kStack)))))
			DeclareVarInst("float", fTemp4, kStack, Select2Inst(BinopInst("<=", LoadVarInst(Address(fTemp3, kStack)), Float(0.06f)) BinopInst("/", LoadVarInst(Address(fConst6, kStruct)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])) Select2Inst(BinopInst(">=", LoadVarInst(Address(fTemp3, kStack)), Float(0.95f)) BinopInst("/", LoadVarInst(Address(fConst5, kStruct)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])) LoadVarInst(Address(fTemp2, kStack)))))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), Float(-1.0f)))
			DeclareVarInst("int", iTemp6, kStack, CastInst("int", LoadVarInst(Address(fTemp5, kStack))))
			DeclareVarInst("float", fTemp7, kStack, FunCallInst("floorf", LoadVarInst(Address(fTemp5, kStack))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp6, kStack))))), Int32(2047))]), BinopInst("+", LoadVarInst(Address(fTemp7, kStack)), BinopInst("-", Float(2.0f), LoadVarInst(Address(fTemp4, kStack))))), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), BinopInst("-", Float(-1.0f), LoadVarInst(Address(fTemp7, kStack)))), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(Address(iTemp6, kStack)), Int32(1))))), Int32(2047))]))))
			DeclareVarInst("float", fRec1, kStack, LoadVarInst(Address(fTemp1, kStack)))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec2, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fRec1, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp8, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp8, kStack))))
			StoreVarInst(Address(iRec2, kStruct)[Int32(1)], LoadVarInst(Address(iRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(iRec3, kStruct)[Int32(1)], LoadVarInst(Address(iRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(iRec5, kStruct)[Int32(1)], LoadVarInst(Address(iRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 24 bytes
Heap size real = 8296 bytes
Total heap size = 8328 bytes
Stack size in compute = 52 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = iRec3 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = IOTA0 size = 1 size_bytes = 4 read = 4 write = 1 ratio = 5
Field = fVec1 size = 2048 size_bytes = 8192 read = 2 write = 1 ratio = 0.00146484
Field = fConst3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fConst5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
