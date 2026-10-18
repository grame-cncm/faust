======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG0",("int[2]", iIIR0)>)

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
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 16 Store = 4 Binop = 18 [ { Int(&) = 2 } { Int(+) = 3 } { Int(<) = 1 } { Real(*) = 5 } { Real(+) = 2 } { Real(-) = 1 } { Real(<) = 1 } { Real(<=) = 3 } ] Mathop = 0 Numbers = 17 Declare = 5 Cast = 3 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp2, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp2, kStack)))
		DeclareVarInst("float", fTemp3, kStack, CastInst("float", BinopInst("+", Int32(-1), LoadVarInst(Address(iTemp2, kStack)))))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("*", Float(0.001953125f), LoadVarInst(Address(fTemp3, kStack))))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("*", Float(0.00390625f), LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", CastInst("float", BinopInst("&", BinopInst("<=", Float(0.0f), LoadVarInst(Address(fTemp4, kStack))), BinopInst("<=", LoadVarInst(Address(fTemp4, kStack)), Float(0.5f)))), BinopInst("+", Float(-0.5f), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", CastInst("float", BinopInst("&", BinopInst("<", Float(0.5f), LoadVarInst(Address(fTemp4, kStack))), BinopInst("<=", LoadVarInst(Address(fTemp4, kStack)), Float(1.0f)))), BinopInst("-", Float(1.5f), LoadVarInst(Address(fTemp5, kStack)))))))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
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
	AddMetaDeclareInst(fHslider2, "OWL", "PARAMETER_D")
	AddMetaDeclareInst(fHslider2, "unit", "%")
	AddHorizontalSlider("Depth", fHslider2, 2e+01f, 3.0f, 1e+02f, 1.0f)
	AddMetaDeclareInst(fHslider3, "OWL", "PARAMETER_C")
	AddHorizontalSlider("L-R Offset", fHslider3, 0.0f, 0.0f, 1.0f, 0.001f)
	AddMetaDeclareInst(fHslider1, "OWL", "PARAMETER_A")
	AddMetaDeclareInst(fHslider1, "unit", "hz")
	AddHorizontalSlider("Rate", fHslider1, 0.1f, 0.0f, 1.0f, 0.001f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareVarInst("float", ftbl0mydspSIG0[513], kStaticStruct)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("float[4096]", fVec0)("int", fSampleRate)("float", fConst0)("float", fConst1)("FAUSTFLOAT", fHslider0)("float", fConst2)("float[2]", fIRM0)("float", fConst3)("FAUSTFLOAT", fHslider1)("float[2]", fRec0)("float", fConst4)("float", fConst5)("FAUSTFLOAT", fHslider2)("float[2]", fIIR1)("float", fConst6)("float[4096]", fVec1)("float", fConst7)("float", fConst8)("FAUSTFLOAT", fHslider3)("float[2]", fIIR2)>)

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
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(513), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("expf", NegInst(BinopInst("/", Float(2e+02f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(0.01f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst4, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(1e+01f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.1f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(2e+01f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
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
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIRM0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4096))
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
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 11 Store = 0 Binop = 3 [ { Real(*) = 2 } { Real(-) = 1 } ] Mathop = 8 [ { max_f = 4 } { min_f = 4 } ] Numbers = 13 Declare = 9 Cast = 4 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.5f), FunCallInst("min_f", Float(2e+01f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("max_f", Float(3.0f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 122 Store = 14 Binop = 89 [ { Int(&) = 16 } { Int(+) = 7 } { Int(-) = 8 } { Int(<) = 1 } { Real(*) = 26 } { Real(+) = 18 } { Real(-) = 13 } ] Mathop = 17 [ { floorf = 3 } { fmodf = 2 } { max_i = 6 } { min_i = 6 } ] Numbers = 65 Declare = 31 Cast = 12 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp0, kStack)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fIRM0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIRM0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("+", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp6, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp6, kStack)))))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("*", Float(512.0f), FunCallInst("fmodf", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), Float(1.0f))))
		DeclareVarInst("int", iTemp8, kStack, CastInst("int", LoadVarInst(Address(fTemp7, kStack))))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("-", LoadVarInst(Address(fTemp7, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp7, kStack)))))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("+", LoadVarInst(Address(fSlow3, kStack)), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
		DeclareVarInst("float", fTemp11, kStack, BinopInst("*", LoadVarInst(Address(fConst5, kStruct)), LoadVarInst(Address(fTemp10, kStack))))
		DeclareVarInst("float", fTemp12, kStack, BinopInst("*", BinopInst("+", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp8, kStack)), Int32(512)))]), BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), BinopInst("-", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp8, kStack))), Int32(512)))]), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp8, kStack)), Int32(512)))])))), LoadVarInst(Address(fTemp11, kStack))))
		DeclareVarInst("float", fTemp13, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp12, kStack))))))
		DeclareVarInst("int", iTemp14, kStack, CastInst("int", LoadVarInst(Address(fTemp13, kStack))))
		DeclareVarInst("float", fTemp15, kStack, CastInst("float", LoadVarInst(Address(iTemp14, kStack))))
		DeclareVarInst("float", fTemp16, kStack, NegInst(LoadVarInst(Address(fTemp12, kStack))))
		DeclareVarInst("float", fTemp17, kStack, BinopInst("*", LoadVarInst(Address(fConst6, kStruct)), LoadVarInst(Address(fTemp1, kStack))))
		DeclareVarInst("int", iTemp18, kStack, CastInst("int", LoadVarInst(Address(fTemp17, kStack))))
		DeclareVarInst("int", iTemp19, kStack, BinopInst("&", LoadVarInst(Address(iTemp18, kStack)), Int32(4095)))
		DeclareVarInst("float", fTemp20, kStack, CastInst("float", LoadVarInst(Address(iTemp18, kStack))))
		DeclareVarInst("float", fTemp21, kStack, BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp17, kStack))), LoadVarInst(Address(fTemp20, kStack))))
		DeclareVarInst("float", fTemp22, kStack, BinopInst("-", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp20, kStack))))
		DeclareVarInst("int", iTemp23, kStack, BinopInst("&", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp18, kStack))), Int32(4095)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp19, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp21, kStack))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp14, kStack)), Int32(4095))), Int32(4095))]), BinopInst("+", LoadVarInst(Address(fTemp15, kStack)), BinopInst("+", Float(1.0f), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), BinopInst("-", LoadVarInst(Address(fTemp16, kStack)), Float(1.0f)))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp13, kStack)), LoadVarInst(Address(fTemp15, kStack))), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp14, kStack))), Int32(4095))), Int32(4095))])))), BinopInst("*", LoadVarInst(Address(fTemp22, kStack)), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp23, kStack))), Int32(4095))])))))
		DeclareVarInst("float", fTemp24, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp24, kStack)))
		DeclareVarInst("float", fTemp25, kStack, BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp25, kStack)))
		DeclareVarInst("float", fTemp26, kStack, BinopInst("*", Float(512.0f), FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fTemp25, kStack)))), Float(1.0f))))
		DeclareVarInst("int", iTemp27, kStack, CastInst("int", LoadVarInst(Address(fTemp26, kStack))))
		DeclareVarInst("float", fTemp28, kStack, BinopInst("-", LoadVarInst(Address(fTemp26, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp26, kStack)))))
		DeclareVarInst("float", fTemp29, kStack, BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("+", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp27, kStack)), Int32(512)))]), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), BinopInst("-", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp27, kStack))), Int32(512)))]), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp27, kStack)), Int32(512)))]))))))
		DeclareVarInst("float", fTemp30, kStack, BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp29, kStack))))))
		DeclareVarInst("int", iTemp31, kStack, CastInst("int", LoadVarInst(Address(fTemp30, kStack))))
		DeclareVarInst("float", fTemp32, kStack, CastInst("float", LoadVarInst(Address(iTemp31, kStack))))
		DeclareVarInst("float", fTemp33, kStack, NegInst(LoadVarInst(Address(fTemp29, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp21, kStack)), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp19, kStack))), Int32(4095))])), BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp31, kStack)), Int32(4095))), Int32(4095))]), BinopInst("+", LoadVarInst(Address(fTemp32, kStack)), BinopInst("+", Float(1.0f), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), BinopInst("-", LoadVarInst(Address(fTemp33, kStack)), Float(1.0f)))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp30, kStack)), LoadVarInst(Address(fTemp32, kStack))), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp31, kStack))), Int32(4095))), Int32(4095))])))), BinopInst("*", LoadVarInst(Address(fTemp22, kStack)), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp23, kStack))), Int32(4095))])))))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fIRM0, kStruct)[Int32(1)], LoadVarInst(Address(fIRM0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
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
	DeclareVarInst("float", ftbl0mydspSIG0[513], kStaticStruct)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec0[4096], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("float", fIRM0[2], kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("float", fConst5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fIIR1[2], kStruct)
	DeclareVarInst("float", fConst6, kStruct)
	DeclareVarInst("float", fVec1[4096], kStruct)
	DeclareVarInst("float", fConst7, kStruct)
	DeclareVarInst("float", fConst8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fIIR2[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("expf", NegInst(BinopInst("/", Float(2e+02f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(0.01f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("*", Float(0.001f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(1e+01f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.1f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(2e+01f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(4096))
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
			StoreVarInst(Address(fIRM0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4096))
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
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(513), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareVarInst("int", iIIR0[2], kStruct)
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
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
			DeclareVarInst("int", iTemp2, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp2, kStack)))
			DeclareVarInst("float", fTemp3, kStack, CastInst("float", BinopInst("+", Int32(-1), LoadVarInst(Address(iTemp2, kStack)))))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("*", Float(0.001953125f), LoadVarInst(Address(fTemp3, kStack))))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("*", Float(0.00390625f), LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], BinopInst("*", Float(2.0f), BinopInst("+", BinopInst("*", CastInst("float", BinopInst("&", BinopInst("<=", Float(0.0f), LoadVarInst(Address(fTemp4, kStack))), BinopInst("<=", LoadVarInst(Address(fTemp4, kStack)), Float(0.5f)))), BinopInst("+", Float(-0.5f), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", CastInst("float", BinopInst("&", BinopInst("<", Float(0.5f), LoadVarInst(Address(fTemp4, kStack))), BinopInst("<=", LoadVarInst(Address(fTemp4, kStack)), Float(1.0f)))), BinopInst("-", Float(1.5f), LoadVarInst(Address(fTemp5, kStack)))))))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.5f), FunCallInst("min_f", Float(2e+01f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("max_f", Float(3.0f), FunCallInst("min_f", Float(1e+02f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp0, kStack)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fIRM0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIRM0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("+", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp6, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp6, kStack)))))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("*", Float(512.0f), FunCallInst("fmodf", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), Float(1.0f))))
			DeclareVarInst("int", iTemp8, kStack, CastInst("int", LoadVarInst(Address(fTemp7, kStack))))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("-", LoadVarInst(Address(fTemp7, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp7, kStack)))))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("+", LoadVarInst(Address(fSlow3, kStack)), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
			DeclareVarInst("float", fTemp11, kStack, BinopInst("*", LoadVarInst(Address(fConst5, kStruct)), LoadVarInst(Address(fTemp10, kStack))))
			DeclareVarInst("float", fTemp12, kStack, BinopInst("*", BinopInst("+", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp8, kStack)), Int32(512)))]), BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), BinopInst("-", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp8, kStack))), Int32(512)))]), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp8, kStack)), Int32(512)))])))), LoadVarInst(Address(fTemp11, kStack))))
			DeclareVarInst("float", fTemp13, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp12, kStack))))))
			DeclareVarInst("int", iTemp14, kStack, CastInst("int", LoadVarInst(Address(fTemp13, kStack))))
			DeclareVarInst("float", fTemp15, kStack, CastInst("float", LoadVarInst(Address(iTemp14, kStack))))
			DeclareVarInst("float", fTemp16, kStack, NegInst(LoadVarInst(Address(fTemp12, kStack))))
			DeclareVarInst("float", fTemp17, kStack, BinopInst("*", LoadVarInst(Address(fConst6, kStruct)), LoadVarInst(Address(fTemp1, kStack))))
			DeclareVarInst("int", iTemp18, kStack, CastInst("int", LoadVarInst(Address(fTemp17, kStack))))
			DeclareVarInst("int", iTemp19, kStack, BinopInst("&", LoadVarInst(Address(iTemp18, kStack)), Int32(4095)))
			DeclareVarInst("float", fTemp20, kStack, CastInst("float", LoadVarInst(Address(iTemp18, kStack))))
			DeclareVarInst("float", fTemp21, kStack, BinopInst("+", BinopInst("-", Float(1.0f), LoadVarInst(Address(fTemp17, kStack))), LoadVarInst(Address(fTemp20, kStack))))
			DeclareVarInst("float", fTemp22, kStack, BinopInst("-", LoadVarInst(Address(fTemp17, kStack)), LoadVarInst(Address(fTemp20, kStack))))
			DeclareVarInst("int", iTemp23, kStack, BinopInst("&", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp18, kStack))), Int32(4095)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp19, kStack))), Int32(4095))]), LoadVarInst(Address(fTemp21, kStack))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp14, kStack)), Int32(4095))), Int32(4095))]), BinopInst("+", LoadVarInst(Address(fTemp15, kStack)), BinopInst("+", Float(1.0f), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), BinopInst("-", LoadVarInst(Address(fTemp16, kStack)), Float(1.0f)))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp13, kStack)), LoadVarInst(Address(fTemp15, kStack))), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp14, kStack))), Int32(4095))), Int32(4095))])))), BinopInst("*", LoadVarInst(Address(fTemp22, kStack)), LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp23, kStack))), Int32(4095))])))))
			DeclareVarInst("float", fTemp24, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp24, kStack)))
			DeclareVarInst("float", fTemp25, kStack, BinopInst("+", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp25, kStack)))
			DeclareVarInst("float", fTemp26, kStack, BinopInst("*", Float(512.0f), FunCallInst("fmodf", BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fTemp25, kStack)))), Float(1.0f))))
			DeclareVarInst("int", iTemp27, kStack, CastInst("int", LoadVarInst(Address(fTemp26, kStack))))
			DeclareVarInst("float", fTemp28, kStack, BinopInst("-", LoadVarInst(Address(fTemp26, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp26, kStack)))))
			DeclareVarInst("float", fTemp29, kStack, BinopInst("*", LoadVarInst(Address(fTemp11, kStack)), BinopInst("+", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp27, kStack)), Int32(512)))]), BinopInst("*", LoadVarInst(Address(fTemp28, kStack)), BinopInst("-", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp27, kStack))), Int32(512)))]), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp27, kStack)), Int32(512)))]))))))
			DeclareVarInst("float", fTemp30, kStack, BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), BinopInst("+", Float(1.0f), LoadVarInst(Address(fTemp29, kStack))))))
			DeclareVarInst("int", iTemp31, kStack, CastInst("int", LoadVarInst(Address(fTemp30, kStack))))
			DeclareVarInst("float", fTemp32, kStack, CastInst("float", LoadVarInst(Address(iTemp31, kStack))))
			DeclareVarInst("float", fTemp33, kStack, NegInst(LoadVarInst(Address(fTemp29, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fTemp21, kStack)), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp19, kStack))), Int32(4095))])), BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", LoadVarInst(Address(iTemp31, kStack)), Int32(4095))), Int32(4095))]), BinopInst("+", LoadVarInst(Address(fTemp32, kStack)), BinopInst("+", Float(1.0f), BinopInst("*", LoadVarInst(Address(fTemp17, kStack)), BinopInst("-", LoadVarInst(Address(fTemp33, kStack)), Float(1.0f)))))), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp30, kStack)), LoadVarInst(Address(fTemp32, kStack))), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), BinopInst("&", BinopInst("+", Int32(1), LoadVarInst(Address(iTemp31, kStack))), Int32(4095))), Int32(4095))])))), BinopInst("*", LoadVarInst(Address(fTemp22, kStack)), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iTemp23, kStack))), Int32(4095))])))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fIRM0, kStruct)[Int32(1)], LoadVarInst(Address(fIRM0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 32852 bytes
Total heap size = 32868 bytes
Stack size in compute = 52 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 11 write = 1 ratio = 12
Field = fVec0 size = 4096 size_bytes = 16384 read = 4 write = 1 ratio = 0.0012207
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fIRM0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1 size = 4096 size_bytes = 16384 read = 4 write = 1 ratio = 0.0012207
Field = fConst7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            3951
  eval() cache hits:       1263 (31.9666%)
  eval() cache misses:     2688
  Loop detector calls:     2688
  Stack detector calls:    2688

--- Phase 3: Propagation ---
  propagate() calls:       1886
  propagate() cache hits:  639 (33.8812%)
  propagate() cache misses:1247

--- Box Type Computation ---
  getBoxType() calls:      3492
  getBoxType() cache hits: 2654 (76.0023%)
  getBoxType() computed:   838

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       75

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           28389
  Trees reused (hash):     73588 (72.1614% reuse rate)
  Property set ops:        16747
  Property get ops:        12382

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
