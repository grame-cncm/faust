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

DeclareStructTypeInst(StructType<"mydspSIG0",("int", iConst5KC)("int", IOTA1)("int[2]", iVec20KC)("int[2]", iVec22SI)>)

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

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(iConst5KC, kStruct), Int32(1))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec20KC, kStruct)[LoadVarInst(Address(l10, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec22SI, kStruct)[LoadVarInst(Address(l11, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 14 Store = 5 Binop = 13 [ { Int(%) = 1 } { Int(&) = 5 } { Int(+) = 3 } { Int(-) = 2 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { sinf = 1 } ] Numbers = 12 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec20KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], LoadVarInst(Address(iConst5KC, kStruct)))
		StoreVarInst(Address(iVec22SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("%", BinopInst("+", LoadVarInst(Address(iVec20KC, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(iVec22SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))])), Int32(65536)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", LoadVarInst(Address(iVec22SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))])))))
		StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("priority")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0SImydspSIG0[65536], kStaticStruct)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", iConst0KC)("int", IOTA0)("int[2]", iVec0KC)("int", fSampleRate)("float", fConst1KI)("int", iConst2KI)("int[2]", iVec2SI)("int[2]", iVec3SI)("int[2]", iVec6SI)("int", iConst3KI)("int[2]", iVec7SI)("int[2]", iVec8SI)("int[2]", iVec11SI)("float", fConst4KI)("int[2]", iVec13SI)("int[2]", iVec16SI)("float[2]", fVec12SI)>)

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

======= Static Init begin ==========

BlockInst 
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(iConst0KC, kStruct), Int32(1))
	StoreVarInst(Address(fConst1KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(iConst2KI, kStruct), CastInst("int", BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst1KI, kStruct)))))
	StoreVarInst(Address(iConst3KI, kStruct), CastInst("int", LoadVarInst(Address(fConst1KI, kStruct))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst1KI, kStruct))))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0KC, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
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
			StoreVarInst(Address(iVec3SI, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec6SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec7SI, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec8SI, kStruct)[LoadVarInst(Address(l5, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec11SI, kStruct)[LoadVarInst(Address(l6, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec13SI, kStruct)[LoadVarInst(Address(l7, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec16SI, kStruct)[LoadVarInst(Address(l8, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SI, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 1 Store = 0 Binop = 0 Mathop = 0 Numbers = 1 Declare = 1 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 64 Store = 13 Binop = 61 [ { Int(%) = 4 } { Int(&) = 27 } { Int(*) = 2 } { Int(+) = 8 } { Int(-) = 10 } { Int(<) = 1 } { Int(<=) = 2 } { Int(>) = 2 } { Real(*) = 2 } { Real(+) = 3 } ] Mathop = 3 [ { floorf = 1 } { max_i = 1 } { min_i = 1 } ] Numbers = 48 Declare = 6 Cast = 3 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iConst0KC, kStruct)))
		DeclareVarInst("int", iTemp0SC, kStack, LoadVarInst(Address(iVec0KC, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp0SC, kStack)), LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), LoadVarInst(Address(iConst2KI, kStruct))))
		StoreVarInst(Address(iVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp1SI, kStack, BinopInst("<=", LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(iVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
		StoreVarInst(Address(iVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp1SI, kStack)))
		StoreVarInst(Address(iVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp0SC, kStack)), LoadVarInst(Address(iVec7SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), LoadVarInst(Address(iConst3KI, kStruct))))
		StoreVarInst(Address(iVec8SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp2SI, kStack, BinopInst("<=", LoadVarInst(Address(iVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(iVec8SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
		StoreVarInst(Address(iVec11SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp2SI, kStack)))
		DeclareVarInst("float", fTemp3SI, kStack, LoadVarInst(Address(fVec12SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(iVec13SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec13SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst(">", LoadVarInst(Address(iTemp1SI, kStack)), LoadVarInst(Address(iVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(iVec16SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec16SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst(">", LoadVarInst(Address(iTemp2SI, kStack)), LoadVarInst(Address(iVec11SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp4SI, kStack, BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), CastInst("float", BinopInst("*", Int32(200), BinopInst("+", BinopInst("+", BinopInst("%", LoadVarInst(Address(iVec13SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Int32(2)), BinopInst("*", Int32(2), BinopInst("%", LoadVarInst(Address(iVec16SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Int32(2)))), Int32(1))))))
		StoreVarInst(Address(fVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp3SI, kStack)), LoadVarInst(Address(fTemp4SI, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fTemp3SI, kStack)), LoadVarInst(Address(fTemp4SI, kStack)))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), Int32(65535)))])))
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
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0SImydspSIG0[65536], kStaticStruct)
	DeclareVarInst("int", iConst0KC, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec0KC[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst1KI, kStruct)
	DeclareVarInst("int", iConst2KI, kStruct)
	// Recursion delay iVec2SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec2SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec3SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec6SI[2], kStruct)
	DeclareVarInst("int", iConst3KI, kStruct)
	// Recursion delay iVec7SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec7SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec8SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec11SI[2], kStruct)
	DeclareVarInst("float", fConst4KI, kStruct)
	// Recursion delay iVec13SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec13SI[2], kStruct)
	// Recursion delay iVec16SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec16SI[2], kStruct)
	// Recursion delay fVec12SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec12SI[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(iConst0KC, kStruct), Int32(1))
	StoreVarInst(Address(fConst1KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(iConst2KI, kStruct), CastInst("int", BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst1KI, kStruct)))))
	StoreVarInst(Address(iConst3KI, kStruct), CastInst("int", LoadVarInst(Address(fConst1KI, kStruct))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst1KI, kStruct))))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0KC, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
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
			StoreVarInst(Address(iVec3SI, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec6SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec7SI, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec8SI, kStruct)[LoadVarInst(Address(l5, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec11SI, kStruct)[LoadVarInst(Address(l6, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec13SI, kStruct)[LoadVarInst(Address(l7, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec16SI, kStruct)[LoadVarInst(Address(l8, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SI, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst("int", iConst5KC, kStruct)
	DeclareVarInst("int", IOTA1, kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec20KC[2], kStruct)
	// Recursion delay iVec22SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec22SI[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(iConst5KC, kStruct), Int32(1))
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec20KC, kStruct)[LoadVarInst(Address(l10, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec22SI, kStruct)[LoadVarInst(Address(l11, kLoop))], Int32(0))
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
			StoreVarInst(Address(iVec20KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], LoadVarInst(Address(iConst5KC, kStruct)))
			StoreVarInst(Address(iVec22SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("%", BinopInst("+", LoadVarInst(Address(iVec20KC, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(iVec22SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))])), Int32(65536)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", LoadVarInst(Address(iVec22SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))])))))
			StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iConst0KC, kStruct)))
			DeclareVarInst("int", iTemp0SC, kStack, LoadVarInst(Address(iVec0KC, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp0SC, kStack)), LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), LoadVarInst(Address(iConst2KI, kStruct))))
			StoreVarInst(Address(iVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp1SI, kStack, BinopInst("<=", LoadVarInst(Address(iVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(iVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
			StoreVarInst(Address(iVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp1SI, kStack)))
			StoreVarInst(Address(iVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("%", BinopInst("+", LoadVarInst(Address(iTemp0SC, kStack)), LoadVarInst(Address(iVec7SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), LoadVarInst(Address(iConst3KI, kStruct))))
			StoreVarInst(Address(iVec8SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp2SI, kStack, BinopInst("<=", LoadVarInst(Address(iVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(iVec8SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
			StoreVarInst(Address(iVec11SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp2SI, kStack)))
			DeclareVarInst("float", fTemp3SI, kStack, LoadVarInst(Address(fVec12SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(iVec13SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec13SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst(">", LoadVarInst(Address(iTemp1SI, kStack)), LoadVarInst(Address(iVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(iVec16SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec16SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst(">", LoadVarInst(Address(iTemp2SI, kStack)), LoadVarInst(Address(iVec11SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp4SI, kStack, BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), CastInst("float", BinopInst("*", Int32(200), BinopInst("+", BinopInst("+", BinopInst("%", LoadVarInst(Address(iVec13SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Int32(2)), BinopInst("*", Int32(2), BinopInst("%", LoadVarInst(Address(iVec16SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Int32(2)))), Int32(1))))))
			StoreVarInst(Address(fVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp3SI, kStack)), LoadVarInst(Address(fTemp4SI, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fTemp3SI, kStack)), LoadVarInst(Address(fTemp4SI, kStack)))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), Int32(65535)))])))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 20 bytes
Heap size int* = 72 bytes
Heap size real = 16 bytes
Total heap size = 132 bytes
Stack size in compute = 8 bytes

======= Variable access in Control ==========

Field = iConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0KC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec2SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec3SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec6SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec7SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec8SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec11SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec13SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec16SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = iConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0KC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec2SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec3SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec6SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec7SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec8SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec11SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec13SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec16SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = iConst0KC size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 28 write = 1 ratio = 29
Field = iVec0KC size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst2KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec2SI size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = iVec3SI size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = iVec6SI size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = iConst3KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec7SI size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = iVec8SI size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = iVec11SI size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fConst4KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec13SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = iVec16SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec12SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
