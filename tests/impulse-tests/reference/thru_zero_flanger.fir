======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG0",("int", IOTA1)("int[2]", iVec9SI)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec9SI, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 18 Store = 4 Binop = 23 [ { Int(&) = 5 } { Int(+) = 4 } { Int(-) = 1 } { Int(<) = 1 } { Real(*) = 5 } { Real(+) = 2 } { Real(-) = 1 } { Real(<) = 1 } { Real(<=) = 3 } ] Mathop = 0 Numbers = 18 Declare = 4 Cast = 3 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec9SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec9SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
		DeclareVarInst("float", fTemp14SI, kStack, CastInst("float", BinopInst("+", LoadVarInst(Address(iVec9SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))]), Int32(-1))))
		DeclareVarInst("float", fTemp15SI, kStack, BinopInst("*", Float(0.001953125f), LoadVarInst(Address(fTemp14SI, kStack))))
		DeclareVarInst("float", fTemp16SI, kStack, BinopInst("*", Float(0.00390625f), LoadVarInst(Address(fTemp14SI, kStack))))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", CastInst("float", BinopInst("&", BinopInst("<=", Float(0.0f), LoadVarInst(Address(fTemp15SI, kStack))), BinopInst("<=", LoadVarInst(Address(fTemp15SI, kStack)), Float(0.5f)))), BinopInst("+", LoadVarInst(Address(fTemp16SI, kStack)), Float(-0.5f))), BinopInst("*", CastInst("float", BinopInst("&", BinopInst("<", Float(0.5f), LoadVarInst(Address(fTemp15SI, kStack))), BinopInst("<=", LoadVarInst(Address(fTemp15SI, kStack)), Float(1.0f)))), BinopInst("-", Float(1.5f), LoadVarInst(Address(fTemp16SI, kStack)))))))
		StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Thru Zero Flanger")
	AddMetaDeclareInst(fHslider0, "OWL", "PARAMETER_B")
	AddMetaDeclareInst(fHslider0, "unit", "ms")
	AddHorizontalSlider("Delay", fHslider0, 1e+01f, 0.5f, 2e+01f, 0.01f)
	AddMetaDeclareInst(fHslider1, "OWL", "PARAMETER_D")
	AddMetaDeclareInst(fHslider1, "unit", "%")
	AddHorizontalSlider("Depth", fHslider1, 2e+01f, 3.0f, 1e+02f, 1.0f)
	AddMetaDeclareInst(fHslider3, "OWL", "PARAMETER_C")
	AddHorizontalSlider("L-R Offset", fHslider3, 0.0f, 0.0f, 1.0f, 0.001f)
	AddMetaDeclareInst(fHslider2, "OWL", "PARAMETER_A")
	AddMetaDeclareInst(fHslider2, "unit", "hz")
	AddHorizontalSlider("Rate", fHslider2, 0.1f, 0.0f, 1.0f, 0.001f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0SImydspSIG0[513], kStaticStruct)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("float[4096]", fVec0SE)("int", fSampleRate)("float", fConst0KI)("float", fConst1KI)("FAUSTFLOAT", fHslider0)("float", fConst2KI)("float", fConst3KI)("float[2]", fVec1SE)("FAUSTFLOAT", fHslider1)("float", fConst4KI)("float[2]", fVec5SE)("FAUSTFLOAT", fHslider2)("float", fConst5KI)("float[2]", fVec7SE)("float[4096]", fVec13SE)("FAUSTFLOAT", fHslider3)("float", fConst6KI)("float[2]", fVec16SE)>)

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

======= Static Init begin ==========

BlockInst 
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(513), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst2KI, kStruct), FunCallInst("expf", MinusInst(BinopInst("/", Float(2e+02f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst3KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst2KI, kStruct)))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("*", Float(0.01f), LoadVarInst(Address(fConst3KI, kStruct))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst6KI, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst3KI, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+01f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(2e+01f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.1f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(4096))
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
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
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
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4096))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 12 Store = 0 Binop = 4 [ { Real(*) = 4 } ] Mathop = 0 Numbers = 4 Declare = 8 Cast = 4 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", LoadVarInst(Address(fConst6KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 120 Store = 10 Binop = 100 [ { Int(&) = 28 } { Int(+) = 7 } { Int(-) = 12 } { Int(<) = 1 } { Real(*) = 22 } { Real(+) = 30 } ] Mathop = 13 [ { floorf = 3 } { fmodf = 2 } { max_i = 4 } { min_i = 4 } ] Numbers = 57 Declare = 26 Cast = 12 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp0SE, kStack)))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp2SE, kStack, BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), LoadVarInst(Address(fTemp1SE, kStack))))
		DeclareVarInst("int", iTemp3SE, kStack, CastInst("int", LoadVarInst(Address(fTemp2SE, kStack))))
		DeclareVarInst("int", iTemp4SE, kStack, BinopInst("&", LoadVarInst(Address(iTemp3SE, kStack)), Int32(4095)))
		DeclareVarInst("float", fTemp5SE, kStack, CastInst("float", LoadVarInst(Address(iTemp3SE, kStack))))
		DeclareVarInst("float", fTemp6SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp5SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))))
		DeclareVarInst("float", fTemp7SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), MinusInst(LoadVarInst(Address(fTemp5SE, kStack)))))
		DeclareVarInst("int", iTemp8SE, kStack, BinopInst("&", BinopInst("+", LoadVarInst(Address(iTemp3SE, kStack)), Int32(1)), Int32(4095)))
		StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack)))))))
		DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp12SE, kStack, BinopInst("*", Float(512.0f), FunCallInst("fmodf", LoadVarInst(Address(fTemp11SE, kStack)), Float(1.0f))))
		DeclareVarInst("int", iTemp13SE, kStack, CastInst("int", LoadVarInst(Address(fTemp12SE, kStack))))
		DeclareVarInst("float", fTemp17SE, kStack, LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp13SE, kStack)), Int32(512)))]))
		DeclareVarInst("float", fTemp18SE, kStack, BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp9SE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp17SE, kStack)), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp12SE, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp12SE, kStack))))), BinopInst("+", LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp13SE, kStack)), Int32(1)), Int32(512)))]), MinusInst(LoadVarInst(Address(fTemp17SE, kStack))))))), Float(1.0f)))))
		DeclareVarInst("int", iTemp19SE, kStack, CastInst("int", LoadVarInst(Address(fTemp18SE, kStack))))
		DeclareVarInst("float", fTemp20SE, kStack, CastInst("float", LoadVarInst(Address(iTemp19SE, kStack))))
		DeclareVarInst("float", fTemp21SE, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp21SE, kStack)))
		StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp22SE, kStack, BinopInst("*", Float(512.0f), FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fTemp11SE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1.0f))))
		DeclareVarInst("int", iTemp23SE, kStack, CastInst("int", LoadVarInst(Address(fTemp22SE, kStack))))
		DeclareVarInst("float", fTemp24SE, kStack, LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp23SE, kStack)), Int32(512)))]))
		DeclareVarInst("float", fTemp25SE, kStack, BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp9SE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp22SE, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp22SE, kStack))))), BinopInst("+", LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp23SE, kStack)), Int32(1)), Int32(512)))]), MinusInst(LoadVarInst(Address(fTemp24SE, kStack))))))), Float(1.0f)))))
		DeclareVarInst("int", iTemp26SE, kStack, CastInst("int", LoadVarInst(Address(fTemp25SE, kStack))))
		DeclareVarInst("float", fTemp27SE, kStack, CastInst("float", LoadVarInst(Address(iTemp26SE, kStack))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp4SE, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp6SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp7SE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp8SE, kStack))), Int32(4095))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp19SE, kStack)), Int32(4095))), Int32(4095))]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp20SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp18SE, kStack))))))), MinusInst(BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp18SE, kStack)), MinusInst(LoadVarInst(Address(fTemp20SE, kStack)))), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", LoadVarInst(Address(iTemp19SE, kStack)), Int32(1)), Int32(4095))), Int32(4095))]))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp6SE, kStack)), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp4SE, kStack))), Int32(4095))])), BinopInst("*", LoadVarInst(Address(fTemp7SE, kStack)), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp8SE, kStack))), Int32(4095))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp26SE, kStack)), Int32(4095))), Int32(4095))]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp27SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp25SE, kStack))))))), MinusInst(BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp25SE, kStack)), MinusInst(LoadVarInst(Address(fTemp27SE, kStack)))), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", LoadVarInst(Address(iTemp26SE, kStack)), Int32(1)), Int32(4095))), Int32(4095))]))))))
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
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0SImydspSIG0[513], kStaticStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0SE[4096], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	DeclareVarInst("float", fConst1KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("float", fConst2KI, kStruct)
	DeclareVarInst("float", fConst3KI, kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fConst4KI, kStruct)
	// Recursion delay fVec5SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec5SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fConst5KI, kStruct)
	// Recursion delay fVec7SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec7SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec13SE[4096], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fConst6KI, kStruct)
	// Recursion delay fVec16SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec16SE[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst2KI, kStruct), FunCallInst("expf", MinusInst(BinopInst("/", Float(2e+02f), LoadVarInst(Address(fConst0KI, kStruct))))))
	StoreVarInst(Address(fConst3KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst2KI, kStruct)))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("*", Float(0.01f), LoadVarInst(Address(fConst3KI, kStruct))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst6KI, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst3KI, kStruct))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+01f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(2e+01f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.1f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(4096))
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
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
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
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4096))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(513), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst("int", IOTA1, kStruct)
	// Recursion delay iVec9SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec9SI[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec9SI, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec9SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec9SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
			DeclareVarInst("float", fTemp14SI, kStack, CastInst("float", BinopInst("+", LoadVarInst(Address(iVec9SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))]), Int32(-1))))
			DeclareVarInst("float", fTemp15SI, kStack, BinopInst("*", Float(0.001953125f), LoadVarInst(Address(fTemp14SI, kStack))))
			DeclareVarInst("float", fTemp16SI, kStack, BinopInst("*", Float(0.00390625f), LoadVarInst(Address(fTemp14SI, kStack))))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", CastInst("float", BinopInst("&", BinopInst("<=", Float(0.0f), LoadVarInst(Address(fTemp15SI, kStack))), BinopInst("<=", LoadVarInst(Address(fTemp15SI, kStack)), Float(0.5f)))), BinopInst("+", LoadVarInst(Address(fTemp16SI, kStack)), Float(-0.5f))), BinopInst("*", CastInst("float", BinopInst("&", BinopInst("<", Float(0.5f), LoadVarInst(Address(fTemp15SI, kStack))), BinopInst("<=", LoadVarInst(Address(fTemp15SI, kStack)), Float(1.0f)))), BinopInst("-", Float(1.5f), LoadVarInst(Address(fTemp16SI, kStack)))))))
			StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", LoadVarInst(Address(fConst6KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp0SE, kStack)))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp2SE, kStack, BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), LoadVarInst(Address(fTemp1SE, kStack))))
			DeclareVarInst("int", iTemp3SE, kStack, CastInst("int", LoadVarInst(Address(fTemp2SE, kStack))))
			DeclareVarInst("int", iTemp4SE, kStack, BinopInst("&", LoadVarInst(Address(iTemp3SE, kStack)), Int32(4095)))
			DeclareVarInst("float", fTemp5SE, kStack, CastInst("float", LoadVarInst(Address(iTemp3SE, kStack))))
			DeclareVarInst("float", fTemp6SE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp5SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp2SE, kStack)))))
			DeclareVarInst("float", fTemp7SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), MinusInst(LoadVarInst(Address(fTemp5SE, kStack)))))
			DeclareVarInst("int", iTemp8SE, kStack, BinopInst("&", BinopInst("+", LoadVarInst(Address(iTemp3SE, kStack)), Int32(1)), Int32(4095)))
			StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack)))))))
			DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp12SE, kStack, BinopInst("*", Float(512.0f), FunCallInst("fmodf", LoadVarInst(Address(fTemp11SE, kStack)), Float(1.0f))))
			DeclareVarInst("int", iTemp13SE, kStack, CastInst("int", LoadVarInst(Address(fTemp12SE, kStack))))
			DeclareVarInst("float", fTemp17SE, kStack, LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp13SE, kStack)), Int32(512)))]))
			DeclareVarInst("float", fTemp18SE, kStack, BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp9SE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp17SE, kStack)), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp12SE, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp12SE, kStack))))), BinopInst("+", LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp13SE, kStack)), Int32(1)), Int32(512)))]), MinusInst(LoadVarInst(Address(fTemp17SE, kStack))))))), Float(1.0f)))))
			DeclareVarInst("int", iTemp19SE, kStack, CastInst("int", LoadVarInst(Address(fTemp18SE, kStack))))
			DeclareVarInst("float", fTemp20SE, kStack, CastInst("float", LoadVarInst(Address(iTemp19SE, kStack))))
			DeclareVarInst("float", fTemp21SE, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp21SE, kStack)))
			StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp22SE, kStack, BinopInst("*", Float(512.0f), FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fTemp11SE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(1.0f))))
			DeclareVarInst("int", iTemp23SE, kStack, CastInst("int", LoadVarInst(Address(fTemp22SE, kStack))))
			DeclareVarInst("float", fTemp24SE, kStack, LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp23SE, kStack)), Int32(512)))]))
			DeclareVarInst("float", fTemp25SE, kStack, BinopInst("*", LoadVarInst(Address(fConst1KI, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp9SE, kStack)), BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp22SE, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp22SE, kStack))))), BinopInst("+", LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp23SE, kStack)), Int32(1)), Int32(512)))]), MinusInst(LoadVarInst(Address(fTemp24SE, kStack))))))), Float(1.0f)))))
			DeclareVarInst("int", iTemp26SE, kStack, CastInst("int", LoadVarInst(Address(fTemp25SE, kStack))))
			DeclareVarInst("float", fTemp27SE, kStack, CastInst("float", LoadVarInst(Address(iTemp26SE, kStack))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp4SE, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp6SE, kStack))), BinopInst("*", LoadVarInst(Address(fTemp7SE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp8SE, kStack))), Int32(4095))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp19SE, kStack)), Int32(4095))), Int32(4095))]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp20SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp18SE, kStack))))))), MinusInst(BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp18SE, kStack)), MinusInst(LoadVarInst(Address(fTemp20SE, kStack)))), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", LoadVarInst(Address(iTemp19SE, kStack)), Int32(1)), Int32(4095))), Int32(4095))]))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fTemp6SE, kStack)), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp4SE, kStack))), Int32(4095))])), BinopInst("*", LoadVarInst(Address(fTemp7SE, kStack)), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp8SE, kStack))), Int32(4095))]))), MinusInst(BinopInst("*", LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp26SE, kStack)), Int32(4095))), Int32(4095))]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp27SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp25SE, kStack))))))), MinusInst(BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp25SE, kStack)), MinusInst(LoadVarInst(Address(fTemp27SE, kStack)))), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", LoadVarInst(Address(iTemp26SE, kStack)), Int32(1)), Int32(4095))), Int32(4095))]))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 32844 bytes
Total heap size = 32864 bytes
Stack size in compute = 48 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec7SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst4KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst5KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec7SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst6KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 23 write = 1 ratio = 24
Field = fVec0SE size = 4096 size_bytes = 16384 read = 4 write = 1 ratio = 0.0012207
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec7SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec13SE size = 4096 size_bytes = 16384 read = 4 write = 1 ratio = 0.0012207
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
