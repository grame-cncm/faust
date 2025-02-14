======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "sinf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG0",("int", IOTA1)("int[2]", iVec13SI)>)

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
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec13SI, kStruct)[LoadVarInst(Address(l6, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 10 Store = 4 Binop = 10 [ { Int(&) = 3 } { Int(+) = 4 } { Int(-) = 1 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { sinf = 1 } ] Numbers = 10 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec13SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec13SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iVec13SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))]), Int32(-1))))))
		StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container "mydspSIG1" ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "cosf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG1",("int", IOTA2)("int[2]", iVec15SI)>)

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
	StoreVarInst(Address(IOTA2, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec15SI, kStruct)[LoadVarInst(Address(l7, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 10 Store = 4 Binop = 10 [ { Int(&) = 3 } { Int(+) = 4 } { Int(-) = 1 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { cosf = 1 } ] Numbers = 10 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i2, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i2, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i2, kLoop), BinopInst("+", LoadVarInst(Address(i2, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec15SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA2, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec15SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA2, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i2, kLoop))], FunCallInst("cosf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iVec15SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA2, kStruct)), Int32(1))]), Int32(-1))))))
		StoreVarInst(Address(IOTA2, kStruct), BinopInst("+", LoadVarInst(Address(IOTA2, kStruct)), Int32(1)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("grain3")
	AddHorizontalSlider("delaymax", fHslider2, 1e+03f, 1e+01f, 1e+04f, 1.0f)
	AddMetaDeclareInst(fHslider0, "unit", "msec")
	AddHorizontalSlider("grainsize", fHslider0, 1e+02f, 1.0f, 1e+03f, 1.0f)
	AddHorizontalSlider("rarefaction", fHslider1, 0.2f, 0.0f, 1.0f, 0.01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0SImydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst("float", ftbl1SImydspSIG1[65536], kStaticStruct)
	DeclareFunInst("float", "sinf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("int", fSampleRate)("float", fConst0KI)("float", fConst1KI)("int", IOTA0)("float[2]", fVec0SE)("float[2]", fVec1SE)("FAUSTFLOAT", fHslider1)("int[2]", iVec5SI)("int[2]", iVec4SE)("float[1048576]", fVec8SE)("FAUSTFLOAT", fHslider2)("float", fConst2KI)("float[2]", fVec9SE)("int", iConst3KC)("float", fConst4KI)("float", fConst5KI)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Static Init begin ==========

BlockInst 
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct|kReference|kMutable))))
	DeclareVarInst("mydspSIG1", sig1, kStack, FunCallInst("newmydspSIG1"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG1", LoadVarInst(Address(sig1, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG1", LoadVarInst(Address(sig1, kStack)), Int32(65536), LoadVarInst(Address(ftbl1SImydspSIG1, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	DropInst(FunCallInst("deletemydspSIG1", LoadVarInst(Address(sig1, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("*", Float(0.0005f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(iConst3KC, kStruct), Int32(0))
	StoreVarInst(Address(fConst4KI, kStruct), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[LoadVarInst(Address(iConst3KC, kStruct))]))
	StoreVarInst(Address(fConst5KI, kStruct), LoadVarInst(Address(ftbl1SImydspSIG1, kStaticStruct)[LoadVarInst(Address(iConst3KC, kStruct))]))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.2f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
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
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec5SI, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec4SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(1048576))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 7 Store = 0 Binop = 2 [ { Real(*) = 1 } { Real(/) = 1 } ] Mathop = 0 Numbers = 2 Declare = 5 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("/", LoadVarInst(Address(fConst1KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 62 Store = 9 Binop = 54 [ { Int(&) = 18 } { Int(*) = 2 } { Int(+) = 4 } { Int(-) = 7 } { Int(<) = 1 } { Real(*) = 10 } { Real(+) = 9 } { Real(<=) = 1 } { Real(>) = 2 } ] Mathop = 8 [ { cosf = 1 } { floorf = 2 } { max_i = 2 } { min_i = 2 } { sinf = 1 } ] Numbers = 40 Declare = 10 Cast = 5 Select = 2 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))))))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp2SE, kStack, BinopInst("*", BinopInst(">", LoadVarInst(Address(fTemp1SE, kStack)), Float(0.0001f)), BinopInst("<=", LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(0.0001f))))
		StoreVarInst(Address(iVec5SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec5SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
		DeclareVarInst("float", fTemp3SI, kStack, BinopInst("+", BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(iVec5SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), Float(1.0f)))
		StoreVarInst(Address(iVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iTemp2SE, kStack)) BinopInst(">", BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp3SI, kStack))), LoadVarInst(Address(fSlow1BE, kStack))) LoadVarInst(Address(iVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
		DeclareVarInst("float", fTemp4SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1048575))], LoadVarInst(Address(fTemp4SE, kStack)))
		StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iTemp2SE, kStack)) BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp3SI, kStack))) LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
		DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp6SE, kStack, CastInst("int", LoadVarInst(Address(fTemp5SE, kStack))))
		DeclareVarInst("float", fTemp7SE, kStack, FunCallInst("floorf", LoadVarInst(Address(fTemp5SE, kStack))))
		DeclareVarInst("float", fTemp8SE, kStack, BinopInst("*", Float(3.1415927f), LoadVarInst(Address(fTemp1SE, kStack))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", CastInst("float", LoadVarInst(Address(iVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(524289), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp6SE, kStack))))), Int32(1048575))]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp7SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp5SE, kStack))))), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp5SE, kStack)), MinusInst(LoadVarInst(Address(fTemp7SE, kStack)))), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(524289), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(Address(iTemp6SE, kStack)), Int32(1))))), Int32(1048575))])))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), FunCallInst("cosf", LoadVarInst(Address(fTemp8SE, kStack)))), BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), FunCallInst("sinf", LoadVarInst(Address(fTemp8SE, kStack))))))))
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
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0SImydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst("float", ftbl1SImydspSIG1[65536], kStaticStruct)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	DeclareVarInst("float", fConst1KI, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay fVec0SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec0SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	// Recursion delay iVec5SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec5SI[2], kStruct)
	// Recursion delay iVec4SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec4SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec8SE[1048576], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fConst2KI, kStruct)
	// Recursion delay fVec9SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec9SE[2], kStruct)
	DeclareVarInst("int", iConst3KC, kStruct)
	DeclareVarInst("float", fConst4KI, kStruct)
	DeclareVarInst("float", fConst5KI, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1KI, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("*", Float(0.0005f), LoadVarInst(Address(fConst0KI, kStruct))))
	StoreVarInst(Address(iConst3KC, kStruct), Int32(0))
	StoreVarInst(Address(fConst4KI, kStruct), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[LoadVarInst(Address(iConst3KC, kStruct))]))
	StoreVarInst(Address(fConst5KI, kStruct), LoadVarInst(Address(ftbl1SImydspSIG1, kStaticStruct)[LoadVarInst(Address(iConst3KC, kStruct))]))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.2f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
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
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec5SI, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec4SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(1048576))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct|kReference|kMutable))))
	DeclareVarInst("mydspSIG1", sig1, kStack, FunCallInst("newmydspSIG1"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG1", LoadVarInst(Address(sig1, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG1", LoadVarInst(Address(sig1, kStack)), Int32(65536), LoadVarInst(Address(ftbl1SImydspSIG1, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	DropInst(FunCallInst("deletemydspSIG1", LoadVarInst(Address(sig1, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst("int", IOTA1, kStruct)
	// Recursion delay iVec13SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec13SI[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec13SI, kStruct)[LoadVarInst(Address(l6, kLoop))], Int32(0))
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
			StoreVarInst(Address(iVec13SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec13SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iVec13SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))]), Int32(-1))))))
			StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Declaration part ==========
	DeclareVarInst("int", IOTA2, kStruct)
	// Recursion delay iVec15SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec15SI[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(IOTA2, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec15SI, kStruct)[LoadVarInst(Address(l7, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i2, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i2, kLoop), BinopInst("+", LoadVarInst(Address(i2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec15SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA2, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec15SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA2, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i2, kLoop))], FunCallInst("cosf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iVec15SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA2, kStruct)), Int32(1))]), Int32(-1))))))
			StoreVarInst(Address(IOTA2, kStruct), BinopInst("+", LoadVarInst(Address(IOTA2, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("/", LoadVarInst(Address(fConst1KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))))))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp2SE, kStack, BinopInst("*", BinopInst(">", LoadVarInst(Address(fTemp1SE, kStack)), Float(0.0001f)), BinopInst("<=", LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), Float(0.0001f))))
			StoreVarInst(Address(iVec5SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec5SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
			DeclareVarInst("float", fTemp3SI, kStack, BinopInst("+", BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(iVec5SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), Float(1.0f)))
			StoreVarInst(Address(iVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iTemp2SE, kStack)) BinopInst(">", BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp3SI, kStack))), LoadVarInst(Address(fSlow1BE, kStack))) LoadVarInst(Address(iVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
			DeclareVarInst("float", fTemp4SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1048575))], LoadVarInst(Address(fTemp4SE, kStack)))
			StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], Select2Inst(LoadVarInst(Address(iTemp2SE, kStack)) BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp3SI, kStack))) LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
			DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp6SE, kStack, CastInst("int", LoadVarInst(Address(fTemp5SE, kStack))))
			DeclareVarInst("float", fTemp7SE, kStack, FunCallInst("floorf", LoadVarInst(Address(fTemp5SE, kStack))))
			DeclareVarInst("float", fTemp8SE, kStack, BinopInst("*", Float(3.1415927f), LoadVarInst(Address(fTemp1SE, kStack))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", CastInst("float", LoadVarInst(Address(iVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(524289), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp6SE, kStack))))), Int32(1048575))]), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp7SE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fTemp5SE, kStack))))), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp5SE, kStack)), MinusInst(LoadVarInst(Address(fTemp7SE, kStack)))), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(524289), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(Address(iTemp6SE, kStack)), Int32(1))))), Int32(1048575))])))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), FunCallInst("cosf", LoadVarInst(Address(fTemp8SE, kStack)))), BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), FunCallInst("sinf", LoadVarInst(Address(fTemp8SE, kStack))))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 12 bytes
Heap size int* = 16 bytes
Heap size real = 4194360 bytes
Total heap size = 4194412 bytes
Stack size in compute = 28 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec5SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 1048576 size_bytes = 4194304 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iConst3KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec5SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 1048576 size_bytes = 4194304 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iConst3KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 19 write = 1 ratio = 20
Field = fVec0SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec1SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec5SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = iVec4SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec8SE size = 1048576 size_bytes = 4194304 read = 2 write = 1 ratio = 2.86102e-06
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec9SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = iConst3KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst5KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
