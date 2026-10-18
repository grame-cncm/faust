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
	AddMetaDeclareInst(fHslider0, "style", "knob")
	AddHorizontalSlider("feedback", fHslider0, 87.11f, 0.0f, 1e+02f, 0.1f)
	AddMetaDeclareInst(fHslider2, "style", "knob")
	AddMetaDeclareInst(fHslider2, "unit", "ms")
	AddHorizontalSlider("interpolation", fHslider2, 68.0329f, 1.0f, 1e+02f, 0.1f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("int", IOTA0)("float[524288]", fVec0)("int", fSampleRate)("float", fConst0)("float", fConst1)("FAUSTFLOAT", fHslider1)("float", fConst2)("FAUSTFLOAT", fHslider2)("float[2]", fRec1)("float[2]", fRec2)("float[2]", fRec3)("float[2]", fRec4)("float[2]", fRec0)("float[524288]", fVec1)("float[2]", fRec5)>)

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
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(87.11f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(114.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(68.0329f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(524288))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(524288))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 12 Store = 0 Binop = 4 [ { Real(*) = 3 } { Real(/) = 1 } ] Mathop = 6 [ { max_f = 3 } { min_f = 3 } ] Numbers = 12 Declare = 10 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(5e+03f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))
	DeclareVarInst("float", fSlow4, kStack, NegInst(LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 73 Store = 18 Binop = 46 [ { Int(&) = 15 } { Int(+) = 2 } { Int(-) = 6 } { Int(<) = 1 } { Real(!=) = 5 } { Real(*) = 4 } { Real(+) = 5 } { Real(-) = 2 } { Real(<) = 1 } { Real(<=) = 1 } { Real(==) = 2 } { Real(>) = 1 } { Real(>=) = 1 } ] Mathop = 2 [ { max_f = 1 } { min_f = 1 } ] Numbers = 65 Declare = 6 Cast = 6 Select = 6 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], LoadVarInst(Address(fTemp0, kStack)))
		DeclareVarInst("float", fTemp1, kStack, Select2Inst(BinopInst("!=", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(0.0f)) Select2Inst(BinopInst("&", BinopInst(">", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(0.0f)), BinopInst("<", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(1.0f))) LoadVarInst(Address(fRec1, kStruct)[Int32(1)]) Float(0.0f)) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(0.0f)), BinopInst("!=", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))) LoadVarInst(Address(fSlow3, kStack)) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(1.0f)), BinopInst("!=", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))) LoadVarInst(Address(fSlow4, kStack)) Float(0.0f)))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp1, kStack))))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], Select2Inst(BinopInst("&", BinopInst(">=", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(1.0f)), BinopInst("!=", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow2, kStack)))) LoadVarInst(Address(fSlow2, kStack)) LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], Select2Inst(BinopInst("&", BinopInst("<=", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(0.0f)), BinopInst("!=", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow2, kStack)))) LoadVarInst(Address(fSlow2, kStack)) LoadVarInst(Address(fRec4, kStruct)[Int32(1)])))
		DeclareVarInst("int", iTemp2, kStack, BinopInst("&", CastInst("int", LoadVarInst(Address(fRec3, kStruct)[Int32(0)])), Int32(524287)))
		DeclareVarInst("int", iTemp3, kStack, BinopInst("&", CastInst("int", LoadVarInst(Address(fRec4, kStruct)[Int32(0)])), Int32(524287)))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp2, kStack))), Int32(524287))]), BinopInst("*", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), BinopInst("-", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp3, kStack))), Int32(524287))]), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp2, kStack))), Int32(524287))])))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], LoadVarInst(Address(fTemp4, kStack)))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp2, kStack))), Int32(524287))]), BinopInst("*", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), BinopInst("-", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp3, kStack))), Int32(524287))]), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp2, kStack))), Int32(524287))])))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec5, kStruct)[Int32(0)])))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
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
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec0[524288], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("float", fVec1[524288], kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(87.11f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(114.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(68.0329f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(524288))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(524288))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(5e+03f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))))
	DeclareVarInst("float", fSlow4, kStack, NegInst(LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("*", Float(0.01f), LoadVarInst(Address(fSlow0, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], LoadVarInst(Address(fTemp0, kStack)))
			DeclareVarInst("float", fTemp1, kStack, Select2Inst(BinopInst("!=", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(0.0f)) Select2Inst(BinopInst("&", BinopInst(">", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(0.0f)), BinopInst("<", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(1.0f))) LoadVarInst(Address(fRec1, kStruct)[Int32(1)]) Float(0.0f)) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(0.0f)), BinopInst("!=", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))) LoadVarInst(Address(fSlow3, kStack)) Select2Inst(BinopInst("&", BinopInst("==", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(1.0f)), BinopInst("!=", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))) LoadVarInst(Address(fSlow4, kStack)) Float(0.0f)))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp1, kStack))))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], Select2Inst(BinopInst("&", BinopInst(">=", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(1.0f)), BinopInst("!=", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow2, kStack)))) LoadVarInst(Address(fSlow2, kStack)) LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], Select2Inst(BinopInst("&", BinopInst("<=", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(0.0f)), BinopInst("!=", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow2, kStack)))) LoadVarInst(Address(fSlow2, kStack)) LoadVarInst(Address(fRec4, kStruct)[Int32(1)])))
			DeclareVarInst("int", iTemp2, kStack, BinopInst("&", CastInst("int", LoadVarInst(Address(fRec3, kStruct)[Int32(0)])), Int32(524287)))
			DeclareVarInst("int", iTemp3, kStack, BinopInst("&", CastInst("int", LoadVarInst(Address(fRec4, kStruct)[Int32(0)])), Int32(524287)))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp2, kStack))), Int32(524287))]), BinopInst("*", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), BinopInst("-", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp3, kStack))), Int32(524287))]), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp2, kStack))), Int32(524287))])))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], LoadVarInst(Address(fTemp4, kStack)))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp2, kStack))), Int32(524287))]), BinopInst("*", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), BinopInst("-", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp3, kStack))), Int32(524287))]), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp2, kStack))), Int32(524287))])))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec5, kStruct)[Int32(0)])))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
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
Stack size in compute = 56 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 9 write = 1 ratio = 10
Field = fVec0 size = 524288 size_bytes = 2097152 read = 3 write = 1 ratio = 7.62939e-06
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec2 size = 2 size_bytes = 8 read = 10 write = 2 ratio = 6
Field = fRec3 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fRec4 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec1 size = 524288 size_bytes = 2097152 read = 3 write = 1 ratio = 7.62939e-06
Field = fRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            908
  eval() cache hits:       176 (19.3833%)
  eval() cache misses:     732
  Loop detector calls:     732
  Stack detector calls:    732

--- Phase 3: Propagation ---
  propagate() calls:       485
  propagate() cache hits:  126 (25.9794%)
  propagate() cache misses:359

--- Box Type Computation ---
  getBoxType() calls:      750
  getBoxType() cache hits: 577 (76.9333%)
  getBoxType() computed:   173

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       44

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           6902
  Trees reused (hash):     14047 (67.0533% reuse rate)
  Property set ops:        3106
  Property get ops:        4739

--- Iteration Constructs ---
  par() iterations:        2
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
