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

DeclareStructTypeInst(StructType<"mydspSIG0",("int[2]", iRec4)>)

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
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec4, kStruct)[LoadVarInst(Address(l5, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 4 Binop = 5 [ { Int(+) = 3 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { sinf = 1 } ] Numbers = 10 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(iRec4, kStruct)[Int32(1)]), Int32(1)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iRec4, kStruct)[Int32(0)]), Int32(-1))))))
		StoreVarInst(Address(iRec4, kStruct)[Int32(1)], LoadVarInst(Address(iRec4, kStruct)[Int32(0)]))
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

DeclareStructTypeInst(StructType<"mydspSIG1",("int[2]", iRec6)>)

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
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec6, kStruct)[LoadVarInst(Address(l7, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 4 Binop = 5 [ { Int(+) = 3 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { cosf = 1 } ] Numbers = 10 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i2, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i2, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i2, kLoop), BinopInst("+", LoadVarInst(Address(i2, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iRec6, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(iRec6, kStruct)[Int32(1)]), Int32(1)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i2, kLoop))], FunCallInst("cosf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iRec6, kStruct)[Int32(0)]), Int32(-1))))))
		StoreVarInst(Address(iRec6, kStruct)[Int32(1)], LoadVarInst(Address(iRec6, kStruct)[Int32(0)]))
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
	DeclareVarInst("float", ftbl0mydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst("float", ftbl1mydspSIG1[65536], kStaticStruct)
	DeclareFunInst("float", "sinf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("float", fConst1)("FAUSTFLOAT", fHslider0)("float[2]", fRec1)("int[2]", iRec2)("FAUSTFLOAT", fHslider1)("int[2]", iRec0)("int", IOTA0)("float[1048576]", fVec0)("float", fConst2)("FAUSTFLOAT", fHslider2)("float[2]", fRec3)("float[2]", fRec5)>)

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
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DeclareVarInst("mydspSIG1", sig1, kStack, FunCallInst("newmydspSIG1"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG1", LoadVarInst(Address(sig1, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG1", LoadVarInst(Address(sig1, kStack)), Int32(65536), LoadVarInst(Address(ftbl1mydspSIG1, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	DropInst(FunCallInst("deletemydspSIG1", LoadVarInst(Address(sig1, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("*", Float(0.0005f), LoadVarInst(Address(fConst0, kStruct))))
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
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec2, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec0, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(1048576))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 7 Store = 0 Binop = 2 [ { Real(*) = 1 } { Real(/) = 1 } ] Mathop = 0 Numbers = 2 Declare = 5 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("/", LoadVarInst(Address(fConst1, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 53 Store = 14 Binop = 36 [ { Int(&) = 3 } { Int(*) = 2 } { Int(+) = 4 } { Int(-) = 2 } { Int(<) = 1 } { Real(*) = 11 } { Real(+) = 6 } { Real(-) = 4 } { Real(<=) = 1 } { Real(>) = 2 } ] Mathop = 9 [ { cosf = 1 } { floorf = 3 } { max_i = 2 } { min_i = 2 } { sinf = 1 } ] Numbers = 53 Declare = 8 Cast = 6 Select = 2 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))))
		DeclareVarInst("int", iTemp0, kStack, BinopInst("*", BinopInst(">", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), Float(0.0001f)), BinopInst("<=", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(0.0001f))))
		StoreVarInst(Address(iRec2, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec2, kStruct)[Int32(1)])), Int32(12345)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(iRec2, kStruct)[Int32(0)]))), Float(1.0f)))
		StoreVarInst(Address(iRec0, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iTemp0, kStack)) BinopInst(">", BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp1, kStack))), LoadVarInst(Address(fSlow1, kStack))) LoadVarInst(Address(iRec0, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp2, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1048575))], LoadVarInst(Address(fTemp2, kStack)))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iTemp0, kStack)) BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fTemp1, kStack))) LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
		DeclareVarInst("int", iTemp3, kStack, CastInst("int", LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
		DeclareVarInst("float", fTemp4, kStack, FunCallInst("floorf", LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), FunCallInst("floorf", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
		DeclareVarInst("int", iTemp5, kStack, CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("*", Float(3.1415927f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", CastInst("float", LoadVarInst(Address(iRec0, kStruct)[Int32(0)])), BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(524289), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp3, kStack))))), Int32(1048575))]), BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fRec3, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp4, kStack))), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(524289), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(Address(iTemp3, kStack)), Int32(1))))), Int32(1048575))])))), BinopInst("+", BinopInst("*", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[LoadVarInst(Address(iTemp5, kStack))]), FunCallInst("cosf", LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(ftbl1mydspSIG1, kStaticStruct)[LoadVarInst(Address(iTemp5, kStack))]), FunCallInst("sinf", LoadVarInst(Address(fTemp6, kStack))))))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(iRec2, kStruct)[Int32(1)], LoadVarInst(Address(iRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(iRec0, kStruct)[Int32(1)], LoadVarInst(Address(iRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0mydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "cosf", "float", dummy0)
	DeclareVarInst("float", ftbl1mydspSIG1[65536], kStaticStruct)
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("int", iRec2[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", iRec0[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec0[1048576], kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("*", Float(0.0005f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.2f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec2, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec0, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(1048576))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DeclareVarInst("mydspSIG1", sig1, kStack, FunCallInst("newmydspSIG1"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG1", LoadVarInst(Address(sig1, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG1", LoadVarInst(Address(sig1, kStack)), Int32(65536), LoadVarInst(Address(ftbl1mydspSIG1, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	DropInst(FunCallInst("deletemydspSIG1", LoadVarInst(Address(sig1, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst("int", iRec4[2], kStruct)
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec4, kStruct)[LoadVarInst(Address(l5, kLoop))], Int32(0))
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
			StoreVarInst(Address(iRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(iRec4, kStruct)[Int32(1)]), Int32(1)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iRec4, kStruct)[Int32(0)]), Int32(-1))))))
			StoreVarInst(Address(iRec4, kStruct)[Int32(1)], LoadVarInst(Address(iRec4, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Declaration part ==========
	DeclareVarInst("int", iRec6[2], kStruct)
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec6, kStruct)[LoadVarInst(Address(l7, kLoop))], Int32(0))
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
			StoreVarInst(Address(iRec6, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(iRec6, kStruct)[Int32(1)]), Int32(1)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i2, kLoop))], FunCallInst("cosf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iRec6, kStruct)[Int32(0)]), Int32(-1))))))
			StoreVarInst(Address(iRec6, kStruct)[Int32(1)], LoadVarInst(Address(iRec6, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("/", LoadVarInst(Address(fConst1, kStruct)), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))))
			DeclareVarInst("int", iTemp0, kStack, BinopInst("*", BinopInst(">", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), Float(0.0001f)), BinopInst("<=", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(0.0001f))))
			StoreVarInst(Address(iRec2, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec2, kStruct)[Int32(1)])), Int32(12345)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(iRec2, kStruct)[Int32(0)]))), Float(1.0f)))
			StoreVarInst(Address(iRec0, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iTemp0, kStack)) BinopInst(">", BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp1, kStack))), LoadVarInst(Address(fSlow1, kStack))) LoadVarInst(Address(iRec0, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp2, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1048575))], LoadVarInst(Address(fTemp2, kStack)))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], Select2Inst(LoadVarInst(Address(iTemp0, kStack)) BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fTemp1, kStack))) LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
			DeclareVarInst("int", iTemp3, kStack, CastInst("int", LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
			DeclareVarInst("float", fTemp4, kStack, FunCallInst("floorf", LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), FunCallInst("floorf", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
			DeclareVarInst("int", iTemp5, kStack, CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("*", Float(3.1415927f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", CastInst("float", LoadVarInst(Address(iRec0, kStruct)[Int32(0)])), BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(524289), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp3, kStack))))), Int32(1048575))]), BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fRec3, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp4, kStack))), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(524289), FunCallInst("max_i", Int32(0), BinopInst("+", LoadVarInst(Address(iTemp3, kStack)), Int32(1))))), Int32(1048575))])))), BinopInst("+", BinopInst("*", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[LoadVarInst(Address(iTemp5, kStack))]), FunCallInst("cosf", LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(ftbl1mydspSIG1, kStaticStruct)[LoadVarInst(Address(iTemp5, kStack))]), FunCallInst("sinf", LoadVarInst(Address(fTemp6, kStack))))))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(iRec2, kStruct)[Int32(1)], LoadVarInst(Address(iRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(iRec0, kStruct)[Int32(1)], LoadVarInst(Address(iRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 16 bytes
Heap size real = 4194352 bytes
Total heap size = 4194392 bytes
Stack size in compute = 28 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 1048576 size_bytes = 4194304 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 1048576 size_bytes = 4194304 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 6 write = 2 ratio = 4
Field = iRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = IOTA0 size = 1 size_bytes = 4 read = 4 write = 1 ratio = 5
Field = fVec0 size = 1048576 size_bytes = 4194304 read = 2 write = 1 ratio = 2.86102e-06
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 6 write = 2 ratio = 4
Field = fRec5 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
