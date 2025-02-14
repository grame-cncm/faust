======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("SmoothDelay")
	AddMetaDeclareInst(fHslider1, "style", "knob")
	AddMetaDeclareInst(fHslider1, "unit", "ms")
	AddHorizontalSlider("delay", fHslider1, 114.5f, 0.0f, 5e+03f, 0.1f)
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddHorizontalSlider("feedback", fHslider2, 87.11f, 0.0f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddMetaDeclareInst(fHslider0, "unit", "ms")
	AddHorizontalSlider("interpolation", fHslider0, 68.0329f, 1.0f, 1e+02f, 0.1f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("FAUSTFLOAT", fHslider0)("int", fSampleRate)("float", fConst0KI)("float", fConst1KI)("FAUSTFLOAT", fHslider1)("float", fConst2KI)("float[2]", fVec0SE)("float[2]", fVec1SE)("FAUSTFLOAT", fHslider2)("float[524288]", fVec6SE)("float[2]", fVec2SE)("float[2]", fVec3SE)("float[2]", fVec5SE)("float[524288]", fVec13SE)("float[2]", fVec12SE)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(2))
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
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0KI, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(68.0329f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(114.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(87.11f)))
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
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(524288))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(524288))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 9 Store = 0 Binop = 3 [ { Real(*) = 2 } { Real(/) = 1 } ] Mathop = 0 Numbers = 5 Declare = 7 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("/", LoadVarInst(Address(fConst1KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", Float(0.01f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 86 Store = 12 Binop = 66 [ { Int(&) = 30 } { Int(+) = 2 } { Int(-) = 10 } { Int(<) = 1 } { Real(!=) = 5 } { Real(*) = 6 } { Real(+) = 6 } { Real(<) = 1 } { Real(<=) = 1 } { Real(==) = 2 } { Real(>) = 1 } { Real(>=) = 1 } ] Mathop = 2 [ { max_f = 1 } { min_f = 1 } ] Numbers = 46 Declare = 12 Cast = 6 Select = 6 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp4SE, kStack, Select2Inst(BinopInst("!=", LoadVarInst(Address(fTemp0SE, kStack)), Float(0.0f)) Select2Inst(BinopInst("&", BinopInst(">", LoadVarInst(Address(fTemp1SE, kStack)), Float(0.0f)), BinopInst("<", LoadVarInst(Address(fTemp1SE, kStack)), Float(1.0f))) LoadVarInst(Address(fTemp0SE, kStack)) Float(0.0f)) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(Address(fTemp1SE, kStack)), Float(0.0f)), BinopInst("!=", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack)))) LoadVarInst(Address(fSlow0BE, kStack)) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(Address(fTemp1SE, kStack)), Float(1.0f)), BinopInst("!=", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))) MinusInst(LoadVarInst(Address(fSlow0BE, kStack))) Float(0.0f)))))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp4SE, kStack)))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), LoadVarInst(Address(fTemp4SE, kStack))))))
		DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp6SE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fTemp5SE, kStack)))))
		DeclareVarInst("float", fTemp7SE, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], LoadVarInst(Address(fTemp7SE, kStack)))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(BinopInst("&", BinopInst(">=", LoadVarInst(Address(fTemp1SE, kStack)), Float(1.0f)), BinopInst("!=", LoadVarInst(Address(fTemp3SE, kStack)), LoadVarInst(Address(fSlow1BE, kStack)))) LoadVarInst(Address(fSlow1BE, kStack)) LoadVarInst(Address(fTemp2SE, kStack))))
		DeclareVarInst("int", iTemp8SE, kStack, BinopInst("&", CastInst("int", LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Int32(524287)))
		StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(BinopInst("&", BinopInst("<=", LoadVarInst(Address(fTemp1SE, kStack)), Float(0.0f)), BinopInst("!=", LoadVarInst(Address(fTemp2SE, kStack)), LoadVarInst(Address(fSlow1BE, kStack)))) LoadVarInst(Address(fSlow1BE, kStack)) LoadVarInst(Address(fTemp3SE, kStack))))
		DeclareVarInst("int", iTemp9SE, kStack, BinopInst("&", CastInst("int", LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Int32(524287)))
		StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp6SE, kStack)), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp8SE, kStack))), Int32(524287))])), BinopInst("*", LoadVarInst(Address(fTemp5SE, kStack)), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp9SE, kStack))), Int32(524287))]))))
		DeclareVarInst("float", fTemp10SE, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], LoadVarInst(Address(fTemp10SE, kStack)))
		StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp6SE, kStack)), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp8SE, kStack))), Int32(524287))])), BinopInst("*", LoadVarInst(Address(fTemp5SE, kStack)), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp9SE, kStack))), Int32(524287))]))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
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
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	DeclareVarInst("float", fConst1KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fConst2KI, kStruct)
	// Recursion delay fVec0SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec0SE[2], kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec6SE[524288], kStruct)
	// Recursion delay fVec2SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec2SE[2], kStruct)
	// Recursion delay fVec3SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec3SE[2], kStruct)
	// Recursion delay fVec5SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec5SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec13SE[524288], kStruct)
	// Recursion delay fVec12SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec12SE[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(68.0329f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(114.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(87.11f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(524288))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(524288))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("/", LoadVarInst(Address(fConst1KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", Float(0.01f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp4SE, kStack, Select2Inst(BinopInst("!=", LoadVarInst(Address(fTemp0SE, kStack)), Float(0.0f)) Select2Inst(BinopInst("&", BinopInst(">", LoadVarInst(Address(fTemp1SE, kStack)), Float(0.0f)), BinopInst("<", LoadVarInst(Address(fTemp1SE, kStack)), Float(1.0f))) LoadVarInst(Address(fTemp0SE, kStack)) Float(0.0f)) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(Address(fTemp1SE, kStack)), Float(0.0f)), BinopInst("!=", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack)))) LoadVarInst(Address(fSlow0BE, kStack)) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(Address(fTemp1SE, kStack)), Float(1.0f)), BinopInst("!=", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))) MinusInst(LoadVarInst(Address(fSlow0BE, kStack))) Float(0.0f)))))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp4SE, kStack)))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), LoadVarInst(Address(fTemp4SE, kStack))))))
			DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp6SE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fTemp5SE, kStack)))))
			DeclareVarInst("float", fTemp7SE, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], LoadVarInst(Address(fTemp7SE, kStack)))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(BinopInst("&", BinopInst(">=", LoadVarInst(Address(fTemp1SE, kStack)), Float(1.0f)), BinopInst("!=", LoadVarInst(Address(fTemp3SE, kStack)), LoadVarInst(Address(fSlow1BE, kStack)))) LoadVarInst(Address(fSlow1BE, kStack)) LoadVarInst(Address(fTemp2SE, kStack))))
			DeclareVarInst("int", iTemp8SE, kStack, BinopInst("&", CastInst("int", LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Int32(524287)))
			StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(BinopInst("&", BinopInst("<=", LoadVarInst(Address(fTemp1SE, kStack)), Float(0.0f)), BinopInst("!=", LoadVarInst(Address(fTemp2SE, kStack)), LoadVarInst(Address(fSlow1BE, kStack)))) LoadVarInst(Address(fSlow1BE, kStack)) LoadVarInst(Address(fTemp3SE, kStack))))
			DeclareVarInst("int", iTemp9SE, kStack, BinopInst("&", CastInst("int", LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Int32(524287)))
			StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp6SE, kStack)), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp8SE, kStack))), Int32(524287))])), BinopInst("*", LoadVarInst(Address(fTemp5SE, kStack)), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp9SE, kStack))), Int32(524287))]))))
			DeclareVarInst("float", fTemp10SE, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], LoadVarInst(Address(fTemp10SE, kStack)))
			StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp6SE, kStack)), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp8SE, kStack))), Int32(524287))])), BinopInst("*", LoadVarInst(Address(fTemp5SE, kStack)), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp9SE, kStack))), Int32(524287))]))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 4194376 bytes
Total heap size = 4194384 bytes
Stack size in compute = 44 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec6SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 24 write = 1 ratio = 25
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec1SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 524288 size_bytes = 2097152 read = 2 write = 1 ratio = 5.72205e-06
Field = fVec2SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec3SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec5SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec13SE size = 524288 size_bytes = 2097152 read = 2 write = 1 ratio = 5.72205e-06
Field = fVec12SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
