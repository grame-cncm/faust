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

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fButton0)("int", IOTA0)("float[2]", fVec0BE)("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("int[2]", iVec2SI)("FAUSTFLOAT", fHslider2)("int", fSampleRate)("float", fConst0KI)("int[2]", iVec5SE)("FAUSTFLOAT", fHslider3)("float", fConst1KI)("float[2]", fVec7SE)("float", fConst2KI)("int[2]", iVec9SE)("float[2048]", fVec11SE)("FAUSTFLOAT", fHslider4)("float", fConst3KI)("float", fConst4KI)("float[2]", fVec12SE)("float", fConst5KI)("float", fConst6KI)("float[2]", fVec1SE)("FAUSTFLOAT", fHslider5)("float[2]", fVec17SE)("float[2]", fVec19SE)>)

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
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.1f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.01f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst3KI, kStruct), FunCallInst("expf", MinusInst(BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst3KI, kStruct)))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("*", Float(0.9993265f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst6KI, kStruct), BinopInst("*", Float(1.0006735f), LoadVarInst(Address(fConst0KI, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.999f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(127.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.95f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.95f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(2e+02f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.8f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0BE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2SI, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec5SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec9SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2048))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 15 Store = 0 Binop = 8 [ { Real(*) = 5 } { Real(/) = 2 } { Real(==) = 1 } ] Mathop = 2 [ { max_f = 2 } ] Numbers = 9 Declare = 12 Cast = 7 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, LoadVarInst(Address(fSlow0BE, kStack)))
	DeclareVarInst("float", fSlow2BE, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", Float(3.6666243e-12f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow4BE, kStack, FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow4BE, kStack))))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))))
	DeclareVarInst("int", iSlow7BE, kStack, BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(0.0f)))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider5, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 99 Store = 14 Binop = 87 [ { Int(&) = 27 } { Int(*) = 3 } { Int(+) = 7 } { Int(-) = 11 } { Int(<) = 1 } { Int(>) = 1 } { Real(*) = 15 } { Real(+) = 14 } { Real(/) = 3 } { Real(<=) = 2 } { Real(>) = 1 } { Real(>=) = 2 } ] Mathop = 10 [ { floorf = 2 } { max_f = 2 } { max_i = 2 } { min_f = 2 } { min_i = 2 } ] Numbers = 59 Declare = 15 Cast = 7 Select = 2 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fSlow1BE, kStack)))
		StoreVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("int", iTemp1SE, kStack, LoadVarInst(Address(iVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(iVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", BinopInst("<=", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), BinopInst("+", LoadVarInst(Address(iTemp1SE, kStack)), BinopInst(">", LoadVarInst(Address(iTemp1SE, kStack)), Int32(0)))), BinopInst(">", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))))
		DeclareVarInst("float", fTemp2SE, kStack, CastInst("float", LoadVarInst(Address(iVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("*", LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), CastInst("float", BinopInst(">=", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fSlow0BE, kStack)))))))
		StoreVarInst(Address(iVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(iSlow7BE, kStack)), BinopInst("+", LoadVarInst(Address(iVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Int32(1))))
		DeclareVarInst("float", fTemp3SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("*", BinopInst("*", CastInst("float", LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow4BE, kStack)), MinusInst(LoadVarInst(Address(fTemp2SE, kStack))))), Float(1.0f))))), FunCallInst("max_f", Float(0.0f), BinopInst("+", FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1.0f)), MinusInst(BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), CastInst("float", LoadVarInst(Address(iVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))))))
		DeclareVarInst("float", fTemp4SE, kStack, LoadVarInst(Address(fTemp3SE, kStack)))
		StoreVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp4SE, kStack)))
		StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp6SE, kStack, BinopInst("/", LoadVarInst(Address(fConst0KI, kStruct)), LoadVarInst(Address(fTemp5SE, kStack))))
		DeclareVarInst("float", fTemp7SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp6SE, kStack))))))
		DeclareVarInst("float", fTemp8SE, kStack, Select2Inst(BinopInst("<=", LoadVarInst(Address(fTemp7SE, kStack)), Float(0.06f)) BinopInst("/", LoadVarInst(Address(fConst6KI, kStruct)), LoadVarInst(Address(fTemp5SE, kStack))) Select2Inst(BinopInst(">=", LoadVarInst(Address(fTemp7SE, kStack)), Float(0.95f)) BinopInst("/", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fTemp5SE, kStack))) LoadVarInst(Address(fTemp6SE, kStack)))))
		DeclareVarInst("float", fTemp9SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp8SE, kStack)), Float(-1.0f)))
		DeclareVarInst("int", iTemp10SE, kStack, CastInst("int", LoadVarInst(Address(fTemp9SE, kStack))))
		DeclareVarInst("float", fTemp11SE, kStack, FunCallInst("floorf", LoadVarInst(Address(fTemp9SE, kStack))))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp10SE, kStack))))), Int32(2047))]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp11SE, kStack)), Float(2.0f)), MinusInst(LoadVarInst(Address(fTemp8SE, kStack))))), BinopInst("*", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp8SE, kStack)), Float(-1.0f)), MinusInst(LoadVarInst(Address(fTemp11SE, kStack)))), LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(Address(iTemp10SE, kStack)), Int32(1))))), Int32(2047))]))))
		DeclareVarInst("float", fRec6SE, kStack, LoadVarInst(Address(fTemp3SE, kStack)))
		StoreVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec19SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fRec6SE, kStack)), LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		DeclareVarInst("float", fTemp12SE, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec19SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp12SE, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp12SE, kStack))))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
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
	DeclareVarInst("FAUSTFLOAT", fButton0, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0BE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	// Recursion delay iVec2SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec2SI[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	// Recursion delay iVec5SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec5SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fConst1KI, kStruct)
	// Recursion delay fVec7SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec7SE[2], kStruct)
	DeclareVarInst("float", fConst2KI, kStruct)
	// Recursion delay iVec9SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec9SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec11SE[2048], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("float", fConst3KI, kStruct)
	DeclareVarInst("float", fConst4KI, kStruct)
	// Recursion delay fVec12SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec12SE[2], kStruct)
	DeclareVarInst("float", fConst5KI, kStruct)
	DeclareVarInst("float", fConst6KI, kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	// Recursion delay fRec6SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	// Recursion delay fVec17SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec17SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec19SE[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.1f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.01f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst3KI, kStruct), FunCallInst("expf", MinusInst(BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst3KI, kStruct)))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("*", Float(0.9993265f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst6KI, kStruct), BinopInst("*", Float(1.0006735f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.999f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(127.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.95f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.95f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(2e+02f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.8f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0BE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2SI, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec5SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec9SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2048))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, LoadVarInst(Address(fSlow0BE, kStack)))
	DeclareVarInst("float", fSlow2BE, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", Float(3.6666243e-12f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow4BE, kStack, FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow4BE, kStack))))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))))
	DeclareVarInst("int", iSlow7BE, kStack, BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(0.0f)))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("*", Float(0.001f), CastInst("float", LoadVarInst(Address(fHslider5, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fSlow1BE, kStack)))
			StoreVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("int", iTemp1SE, kStack, LoadVarInst(Address(iVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(iVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", BinopInst("<=", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), BinopInst("+", LoadVarInst(Address(iTemp1SE, kStack)), BinopInst(">", LoadVarInst(Address(iTemp1SE, kStack)), Int32(0)))), BinopInst(">", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))))
			DeclareVarInst("float", fTemp2SE, kStack, CastInst("float", LoadVarInst(Address(iVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("*", LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), CastInst("float", BinopInst(">=", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fSlow0BE, kStack)))))))
			StoreVarInst(Address(iVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(iSlow7BE, kStack)), BinopInst("+", LoadVarInst(Address(iVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Int32(1))))
			DeclareVarInst("float", fTemp3SE, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("*", BinopInst("*", CastInst("float", LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), BinopInst("+", LoadVarInst(Address(fSlow4BE, kStack)), MinusInst(LoadVarInst(Address(fTemp2SE, kStack))))), Float(1.0f))))), FunCallInst("max_f", Float(0.0f), BinopInst("+", FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1.0f)), MinusInst(BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), CastInst("float", LoadVarInst(Address(iVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))))))
			DeclareVarInst("float", fTemp4SE, kStack, LoadVarInst(Address(fTemp3SE, kStack)))
			StoreVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp4SE, kStack)))
			StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp6SE, kStack, BinopInst("/", LoadVarInst(Address(fConst0KI, kStruct)), LoadVarInst(Address(fTemp5SE, kStack))))
			DeclareVarInst("float", fTemp7SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp6SE, kStack))))))
			DeclareVarInst("float", fTemp8SE, kStack, Select2Inst(BinopInst("<=", LoadVarInst(Address(fTemp7SE, kStack)), Float(0.06f)) BinopInst("/", LoadVarInst(Address(fConst6KI, kStruct)), LoadVarInst(Address(fTemp5SE, kStack))) Select2Inst(BinopInst(">=", LoadVarInst(Address(fTemp7SE, kStack)), Float(0.95f)) BinopInst("/", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fTemp5SE, kStack))) LoadVarInst(Address(fTemp6SE, kStack)))))
			DeclareVarInst("float", fTemp9SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp8SE, kStack)), Float(-1.0f)))
			DeclareVarInst("int", iTemp10SE, kStack, CastInst("int", LoadVarInst(Address(fTemp9SE, kStack))))
			DeclareVarInst("float", fTemp11SE, kStack, FunCallInst("floorf", LoadVarInst(Address(fTemp9SE, kStack))))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp10SE, kStack))))), Int32(2047))]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp11SE, kStack)), Float(2.0f)), MinusInst(LoadVarInst(Address(fTemp8SE, kStack))))), BinopInst("*", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp8SE, kStack)), Float(-1.0f)), MinusInst(LoadVarInst(Address(fTemp11SE, kStack)))), LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(Address(iTemp10SE, kStack)), Int32(1))))), Int32(2047))]))))
			DeclareVarInst("float", fRec6SE, kStack, LoadVarInst(Address(fTemp3SE, kStack)))
			StoreVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec19SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fRec6SE, kStack)), LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			DeclareVarInst("float", fTemp12SE, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec19SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp12SE, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp12SE, kStack))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
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
Stack size in compute = 56 bytes

======= Variable access in Control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec2SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec7SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec2SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = iVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec7SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 28 write = 1 ratio = 29
Field = fVec0BE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec2SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec5SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec7SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst2KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec9SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec11SE size = 2048 size_bytes = 8192 read = 2 write = 1 ratio = 0.00146484
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst5KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst6KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec17SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec19SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
