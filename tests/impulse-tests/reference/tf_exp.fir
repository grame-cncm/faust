======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("tf_exp")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", iConst0KC)("int", IOTA0)("int[2]", iVec0KC)("float[2]", fVec2SC)("int", fSampleRate)("float", fConst1KI)("float", fConst2KI)("float", fConst3KI)("float", fConst4KI)("float", fConst5KI)("float[2]", fVec3SI)("float", fConst6KI)("float", fConst7KI)("float", fConst8KI)("float", fConst9KI)("float", fConst10KI)("float[2]", fVec7SI)("float[4]", fVec6SI)("float", fConst11KI)("float", fConst12KI)("float", fConst13KI)("float", fConst14KI)("float", fConst15KI)("float", fConst16KI)("float", fConst17KI)("float", fConst18KI)("float", fConst19KI)("float[2]", fVec12SI)("float[4]", fVec11SI)("float[2]", fVec14SI)("float[2]", fVec17SI)("float[4]", fVec16SI)("float[2]", fVec21SI)("float", fConst20KI)("float[2]", fVec22SI)("float", fConst21KI)("float", fConst22KI)("float[2]", fVec26SI)("float[4]", fVec25SI)("float", fConst23KI)("float[2]", fVec28SI)("float[2]", fVec31SI)("float[4]", fVec30SI)>)

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
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(iConst0KC, kStruct), Int32(1))
	StoreVarInst(Address(fConst1KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst2KI, kStruct), FunCallInst("tanf", BinopInst("/", Float(3553.1414f), LoadVarInst(Address(fConst1KI, kStruct)))))
	StoreVarInst(Address(fConst3KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst2KI, kStruct))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst3KI, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst3KI, kStruct)))))
	StoreVarInst(Address(fConst6KI, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3KI, kStruct)), Float(1.0f)), LoadVarInst(Address(fConst2KI, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst7KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst6KI, kStruct))))
	StoreVarInst(Address(fConst8KI, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3KI, kStruct)), Float(-1.0f)), LoadVarInst(Address(fConst2KI, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst9KI, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst2KI, kStruct))))
	StoreVarInst(Address(fConst10KI, kStruct), BinopInst("*", Float(2.0f), BinopInst("+", Float(1.0f), MinusInst(BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst9KI, kStruct)))))))
	StoreVarInst(Address(fConst11KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fConst6KI, kStruct)))))
	StoreVarInst(Address(fConst12KI, kStruct), FunCallInst("tanf", BinopInst("/", Float(1776.5707f), LoadVarInst(Address(fConst1KI, kStruct)))))
	StoreVarInst(Address(fConst13KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst12KI, kStruct))))
	StoreVarInst(Address(fConst14KI, kStruct), BinopInst("+", LoadVarInst(Address(fConst13KI, kStruct)), Float(1.0f)))
	StoreVarInst(Address(fConst15KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", LoadVarInst(Address(fConst14KI, kStruct)), LoadVarInst(Address(fConst12KI, kStruct))), Float(1.0f))))
	StoreVarInst(Address(fConst16KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst13KI, kStruct)))))
	StoreVarInst(Address(fConst17KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(BinopInst("/", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fConst12KI, kStruct))))))
	StoreVarInst(Address(fConst18KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst12KI, kStruct)))))
	StoreVarInst(Address(fConst19KI, kStruct), BinopInst("*", Float(2.0f), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst18KI, kStruct))))))
	StoreVarInst(Address(fConst20KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst14KI, kStruct))))
	StoreVarInst(Address(fConst21KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst13KI, kStruct)), Float(1.0f)), LoadVarInst(Address(fConst12KI, kStruct))), Float(1.0f))))
	StoreVarInst(Address(fConst22KI, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst13KI, kStruct)), Float(-1.0f)), LoadVarInst(Address(fConst12KI, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst23KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst12KI, kStruct)), LoadVarInst(Address(fConst6KI, kStruct)))))
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
			StoreVarInst(Address(fVec2SC, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SI, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(4))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SI, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SI, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(4))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SI, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14SI, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SI, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(4))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SI, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SI, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22SI, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SI, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(4))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25SI, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28SI, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31SI, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(4))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30SI, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
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

Instructions complexity : Load = 157 Store = 20 Binop = 149 [ { Int(&) = 53 } { Int(+) = 3 } { Int(-) = 22 } { Int(<) = 1 } { Real(*) = 36 } { Real(+) = 34 } ] Mathop = 0 Numbers = 83 Declare = 16 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iConst0KC, kStruct)))
		DeclareVarInst("float", fTemp0SC, kStack, CastInst("float", BinopInst("+", Int32(1), MinusInst(LoadVarInst(Address(iVec0KC, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
		StoreVarInst(Address(fVec2SC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp0SC, kStack)))
		DeclareVarInst("float", fTemp1SC, kStack, LoadVarInst(Address(fVec2SC, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), BinopInst("+", LoadVarInst(Address(fTemp0SC, kStack)), MinusInst(LoadVarInst(Address(fTemp1SC, kStack))))))))))
		DeclareVarInst("float", fTemp2SI, kStack, LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), MinusInst(BinopInst("*", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fTemp2SI, kStack))), BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fVec7SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp3SI, kStack, LoadVarInst(Address(fVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp3SI, kStack)))
		DeclareVarInst("float", fTemp4SI, kStack, LoadVarInst(Address(fVec11SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst11KI, kStruct)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp2SI, kStack)), LoadVarInst(Address(fVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", Float(-2.0f), LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))), MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst17KI, kStruct)), LoadVarInst(Address(fTemp4SI, kStack))), BinopInst("*", LoadVarInst(Address(fConst19KI, kStruct)), LoadVarInst(Address(fVec12SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp5SI, kStack, LoadVarInst(Address(fVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec11SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp5SI, kStack)))
		StoreVarInst(Address(fVec14SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fVec14SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp0SC, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SC, kStack)))))))
		DeclareVarInst("float", fTemp6SI, kStack, LoadVarInst(Address(fVec16SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec17SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec14SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), MinusInst(BinopInst("*", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fTemp6SI, kStack))), BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fVec17SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp7SI, kStack, LoadVarInst(Address(fVec17SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec16SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp7SI, kStack)))
		DeclareVarInst("float", fTemp8SI, kStack, LoadVarInst(Address(fVec17SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp9SI, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fVec16SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))
		StoreVarInst(Address(fVec21SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SI, kStack)), LoadVarInst(Address(fTemp8SI, kStack))), LoadVarInst(Address(fTemp9SI, kStack))))
		DeclareVarInst("float", fTemp10SI, kStack, LoadVarInst(Address(fVec21SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec22SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst20KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec22SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(BinopInst("*", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SI, kStack)), LoadVarInst(Address(fTemp8SI, kStack))), LoadVarInst(Address(fTemp9SI, kStack))), LoadVarInst(Address(fTemp10SI, kStack)))))))))
		DeclareVarInst("float", fTemp11SI, kStack, LoadVarInst(Address(fVec25SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec26SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec22SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), MinusInst(BinopInst("*", LoadVarInst(Address(fConst21KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst22KI, kStruct)), LoadVarInst(Address(fTemp11SI, kStack))), BinopInst("*", LoadVarInst(Address(fConst19KI, kStruct)), LoadVarInst(Address(fVec26SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp12SI, kStack, LoadVarInst(Address(fVec26SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec25SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp12SI, kStack)))
		StoreVarInst(Address(fVec28SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst20KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec28SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(BinopInst("*", LoadVarInst(Address(fConst23KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SI, kStack)), LoadVarInst(Address(fTemp8SI, kStack))), LoadVarInst(Address(fTemp9SI, kStack))), MinusInst(LoadVarInst(Address(fTemp10SI, kStack))))))))))
		DeclareVarInst("float", fTemp13SI, kStack, LoadVarInst(Address(fVec30SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
		StoreVarInst(Address(fVec31SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec28SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), MinusInst(BinopInst("*", LoadVarInst(Address(fConst21KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst22KI, kStruct)), LoadVarInst(Address(fTemp13SI, kStack))), BinopInst("*", LoadVarInst(Address(fConst19KI, kStruct)), LoadVarInst(Address(fVec31SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
		DeclareVarInst("float", fTemp14SI, kStack, LoadVarInst(Address(fVec31SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec30SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp14SI, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst17KI, kStruct)), LoadVarInst(Address(fVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fConst19KI, kStruct)), LoadVarInst(Address(fVec11SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))))), BinopInst("*", LoadVarInst(Address(fConst21KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp11SI, kStack)), LoadVarInst(Address(fVec26SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", Float(2.0f), LoadVarInst(Address(fVec25SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fConst18KI, kStruct)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp13SI, kStack)), LoadVarInst(Address(fVec31SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", Float(-2.0f), LoadVarInst(Address(fVec30SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))))))))
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
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("int", iConst0KC, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec0KC[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec2SC[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst1KI, kStruct)
	DeclareVarInst("float", fConst2KI, kStruct)
	DeclareVarInst("float", fConst3KI, kStruct)
	DeclareVarInst("float", fConst4KI, kStruct)
	DeclareVarInst("float", fConst5KI, kStruct)
	// Recursion delay fVec3SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec3SI[2], kStruct)
	DeclareVarInst("float", fConst6KI, kStruct)
	DeclareVarInst("float", fConst7KI, kStruct)
	DeclareVarInst("float", fConst8KI, kStruct)
	DeclareVarInst("float", fConst9KI, kStruct)
	DeclareVarInst("float", fConst10KI, kStruct)
	// Recursion delay fVec7SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec7SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec6SI[4], kStruct)
	DeclareVarInst("float", fConst11KI, kStruct)
	DeclareVarInst("float", fConst12KI, kStruct)
	DeclareVarInst("float", fConst13KI, kStruct)
	DeclareVarInst("float", fConst14KI, kStruct)
	DeclareVarInst("float", fConst15KI, kStruct)
	DeclareVarInst("float", fConst16KI, kStruct)
	DeclareVarInst("float", fConst17KI, kStruct)
	DeclareVarInst("float", fConst18KI, kStruct)
	DeclareVarInst("float", fConst19KI, kStruct)
	// Recursion delay fVec12SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec12SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec11SI[4], kStruct)
	// Recursion delay fVec14SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec14SI[2], kStruct)
	// Recursion delay fVec17SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec17SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec16SI[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec21SI[2], kStruct)
	DeclareVarInst("float", fConst20KI, kStruct)
	// Recursion delay fVec22SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec22SI[2], kStruct)
	DeclareVarInst("float", fConst21KI, kStruct)
	DeclareVarInst("float", fConst22KI, kStruct)
	// Recursion delay fVec26SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec26SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec25SI[4], kStruct)
	DeclareVarInst("float", fConst23KI, kStruct)
	// Recursion delay fVec28SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec28SI[2], kStruct)
	// Recursion delay fVec31SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec31SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec30SI[4], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(iConst0KC, kStruct), Int32(1))
	StoreVarInst(Address(fConst1KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst2KI, kStruct), FunCallInst("tanf", BinopInst("/", Float(3553.1414f), LoadVarInst(Address(fConst1KI, kStruct)))))
	StoreVarInst(Address(fConst3KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst2KI, kStruct))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst3KI, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst3KI, kStruct)))))
	StoreVarInst(Address(fConst6KI, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3KI, kStruct)), Float(1.0f)), LoadVarInst(Address(fConst2KI, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst7KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst6KI, kStruct))))
	StoreVarInst(Address(fConst8KI, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3KI, kStruct)), Float(-1.0f)), LoadVarInst(Address(fConst2KI, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst9KI, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst2KI, kStruct))))
	StoreVarInst(Address(fConst10KI, kStruct), BinopInst("*", Float(2.0f), BinopInst("+", Float(1.0f), MinusInst(BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst9KI, kStruct)))))))
	StoreVarInst(Address(fConst11KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst9KI, kStruct)), LoadVarInst(Address(fConst6KI, kStruct)))))
	StoreVarInst(Address(fConst12KI, kStruct), FunCallInst("tanf", BinopInst("/", Float(1776.5707f), LoadVarInst(Address(fConst1KI, kStruct)))))
	StoreVarInst(Address(fConst13KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst12KI, kStruct))))
	StoreVarInst(Address(fConst14KI, kStruct), BinopInst("+", LoadVarInst(Address(fConst13KI, kStruct)), Float(1.0f)))
	StoreVarInst(Address(fConst15KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", LoadVarInst(Address(fConst14KI, kStruct)), LoadVarInst(Address(fConst12KI, kStruct))), Float(1.0f))))
	StoreVarInst(Address(fConst16KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst13KI, kStruct)))))
	StoreVarInst(Address(fConst17KI, kStruct), BinopInst("+", Float(1.0f), MinusInst(BinopInst("/", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fConst12KI, kStruct))))))
	StoreVarInst(Address(fConst18KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst12KI, kStruct)))))
	StoreVarInst(Address(fConst19KI, kStruct), BinopInst("*", Float(2.0f), BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fConst18KI, kStruct))))))
	StoreVarInst(Address(fConst20KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst14KI, kStruct))))
	StoreVarInst(Address(fConst21KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst13KI, kStruct)), Float(1.0f)), LoadVarInst(Address(fConst12KI, kStruct))), Float(1.0f))))
	StoreVarInst(Address(fConst22KI, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst13KI, kStruct)), Float(-1.0f)), LoadVarInst(Address(fConst12KI, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst23KI, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst12KI, kStruct)), LoadVarInst(Address(fConst6KI, kStruct)))))
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
			StoreVarInst(Address(fVec2SC, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SI, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(4))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SI, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SI, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(4))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SI, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14SI, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SI, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(4))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SI, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SI, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22SI, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SI, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(4))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25SI, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28SI, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31SI, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(4))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30SI, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
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
			DeclareVarInst("float", fTemp0SC, kStack, CastInst("float", BinopInst("+", Int32(1), MinusInst(LoadVarInst(Address(iVec0KC, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))
			StoreVarInst(Address(fVec2SC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp0SC, kStack)))
			DeclareVarInst("float", fTemp1SC, kStack, LoadVarInst(Address(fVec2SC, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), BinopInst("+", LoadVarInst(Address(fTemp0SC, kStack)), MinusInst(LoadVarInst(Address(fTemp1SC, kStack))))))))))
			DeclareVarInst("float", fTemp2SI, kStack, LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), MinusInst(BinopInst("*", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fTemp2SI, kStack))), BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fVec7SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp3SI, kStack, LoadVarInst(Address(fVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec6SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp3SI, kStack)))
			DeclareVarInst("float", fTemp4SI, kStack, LoadVarInst(Address(fVec11SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst11KI, kStruct)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp2SI, kStack)), LoadVarInst(Address(fVec7SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", Float(-2.0f), LoadVarInst(Address(fVec6SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))), MinusInst(BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst17KI, kStruct)), LoadVarInst(Address(fTemp4SI, kStack))), BinopInst("*", LoadVarInst(Address(fConst19KI, kStruct)), LoadVarInst(Address(fVec12SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp5SI, kStack, LoadVarInst(Address(fVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec11SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp5SI, kStack)))
			StoreVarInst(Address(fVec14SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fVec14SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(LoadVarInst(Address(fTemp0SC, kStack)))), MinusInst(LoadVarInst(Address(fTemp1SC, kStack)))))))
			DeclareVarInst("float", fTemp6SI, kStack, LoadVarInst(Address(fVec16SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec17SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec14SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), MinusInst(BinopInst("*", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst8KI, kStruct)), LoadVarInst(Address(fTemp6SI, kStack))), BinopInst("*", LoadVarInst(Address(fConst10KI, kStruct)), LoadVarInst(Address(fVec17SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp7SI, kStack, LoadVarInst(Address(fVec17SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec16SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp7SI, kStack)))
			DeclareVarInst("float", fTemp8SI, kStack, LoadVarInst(Address(fVec17SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp9SI, kStack, BinopInst("*", Float(2.0f), LoadVarInst(Address(fVec16SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))
			StoreVarInst(Address(fVec21SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SI, kStack)), LoadVarInst(Address(fTemp8SI, kStack))), LoadVarInst(Address(fTemp9SI, kStack))))
			DeclareVarInst("float", fTemp10SI, kStack, LoadVarInst(Address(fVec21SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec22SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst20KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec22SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(BinopInst("*", LoadVarInst(Address(fConst7KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SI, kStack)), LoadVarInst(Address(fTemp8SI, kStack))), LoadVarInst(Address(fTemp9SI, kStack))), LoadVarInst(Address(fTemp10SI, kStack)))))))))
			DeclareVarInst("float", fTemp11SI, kStack, LoadVarInst(Address(fVec25SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec26SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec22SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), MinusInst(BinopInst("*", LoadVarInst(Address(fConst21KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst22KI, kStruct)), LoadVarInst(Address(fTemp11SI, kStack))), BinopInst("*", LoadVarInst(Address(fConst19KI, kStruct)), LoadVarInst(Address(fVec26SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp12SI, kStack, LoadVarInst(Address(fVec26SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec25SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp12SI, kStack)))
			StoreVarInst(Address(fVec28SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], MinusInst(BinopInst("*", LoadVarInst(Address(fConst20KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16KI, kStruct)), LoadVarInst(Address(fVec28SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), MinusInst(BinopInst("*", LoadVarInst(Address(fConst23KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SI, kStack)), LoadVarInst(Address(fTemp8SI, kStack))), LoadVarInst(Address(fTemp9SI, kStack))), MinusInst(LoadVarInst(Address(fTemp10SI, kStack))))))))))
			DeclareVarInst("float", fTemp13SI, kStack, LoadVarInst(Address(fVec30SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))
			StoreVarInst(Address(fVec31SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fVec28SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), MinusInst(BinopInst("*", LoadVarInst(Address(fConst21KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst22KI, kStruct)), LoadVarInst(Address(fTemp13SI, kStack))), BinopInst("*", LoadVarInst(Address(fConst19KI, kStruct)), LoadVarInst(Address(fVec31SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))))))
			DeclareVarInst("float", fTemp14SI, kStack, LoadVarInst(Address(fVec31SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec30SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp14SI, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp4SI, kStack)), BinopInst("*", LoadVarInst(Address(fConst15KI, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst17KI, kStruct)), LoadVarInst(Address(fVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fConst19KI, kStruct)), LoadVarInst(Address(fVec11SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))))), BinopInst("*", LoadVarInst(Address(fConst21KI, kStruct)), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp11SI, kStack)), LoadVarInst(Address(fVec26SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", Float(2.0f), LoadVarInst(Address(fVec25SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fConst18KI, kStruct)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp13SI, kStack)), LoadVarInst(Address(fVec31SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", Float(-2.0f), LoadVarInst(Address(fVec30SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))])))))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 12 bytes
Heap size int* = 8 bytes
Heap size real = 260 bytes
Total heap size = 280 bytes
Stack size in compute = 8 bytes

======= Variable access in Control ==========

Field = iConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0KC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec3SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst8KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst9KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec7SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fConst11KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst16KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst18KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst19KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec12SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec14SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec21SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst20KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec22SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst21KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec26SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec25SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fConst23KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec28SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec31SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec30SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = iConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0KC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec3SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst8KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst9KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec7SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fConst11KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst16KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst18KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst19KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec12SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec14SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec21SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst20KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec22SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst21KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec26SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec25SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fConst23KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec28SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec31SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec30SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = iConst0KC size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 54 write = 1 ratio = 55
Field = iVec0KC size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec2SC size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst4KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst5KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec3SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst6KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7KI size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fConst8KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst9KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec7SI size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec6SI size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fConst11KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst12KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst16KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst17KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst18KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst19KI size = 1 size_bytes = 4 read = 4 write = 0 ratio = 4
Field = fVec12SI size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec11SI size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fVec14SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec17SI size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec16SI size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fVec21SI size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fConst20KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec22SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fConst21KI size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fConst22KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec26SI size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec25SI size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fConst23KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec28SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec31SI size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec30SI size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
