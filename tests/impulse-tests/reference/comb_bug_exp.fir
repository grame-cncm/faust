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
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("int[2]", iIIR0)("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fHslider2)("FAUSTFLOAT", fButton0)("float[2]", fVec0)("int[2]", iRec1)("FAUSTFLOAT", fHslider3)("float", fConst1)("int[2]", iIIR1)("float", fConst2)("float[2]", fRec2)("int", IOTA0)("float[2048]", fVec1)("FAUSTFLOAT", fHslider4)("float", fConst3)("float[2]", fIRM0)("float", fConst4)("float", fConst5)("float[2]", fRec0)("FAUSTFLOAT", fHslider5)("float[2]", fIIR2)("float[2]", fVec2)>)

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
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.01f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.1f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst3, kStruct), FunCallInst("expf", NegInst(BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("*", Float(0.9993265f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(1.0006735f), LoadVarInst(Address(fConst0, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.999f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(127.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(0.95f)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(0.95f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Float(2e+02f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Float(0.8f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
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
			StoreVarInst(Address(iRec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fIRM0, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
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

Instructions complexity : Load = 16 Store = 0 Binop = 9 [ { Real(*) = 4 } { Real(-) = 1 } { Real(/) = 2 } { Real(==) = 1 } { Real(>) = 1 } ] Mathop = 14 [ { max_f = 8 } { min_f = 6 } ] Numbers = 22 Declare = 13 Cast = 8 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(-0.999f), FunCallInst("min_f", Float(0.999f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(3.6666243e-12f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(0.001f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(0.001f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))))))
	DeclareVarInst("int", iSlow7, kStack, BinopInst("==", LoadVarInst(Address(fSlow5, kStack)), Float(0.0f)))
	DeclareVarInst("float", fSlow8, kStack, FunCallInst("max_f", Float(2e+02f), FunCallInst("min_f", Float(8e+02f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst3, kStruct))), LoadVarInst(Address(fSlow8, kStack))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 82 Store = 23 Binop = 51 [ { Int(&) = 4 } { Int(*) = 2 } { Int(+) = 6 } { Int(-) = 3 } { Int(<) = 1 } { Int(>) = 1 } { Real(*) = 15 } { Real(+) = 7 } { Real(-) = 5 } { Real(/) = 3 } { Real(<=) = 2 } { Real(>=) = 2 } ] Mathop = 12 [ { floorf = 2 } { max_f = 2 } { max_i = 3 } { min_f = 2 } { min_i = 3 } ] Numbers = 68 Declare = 13 Cast = 7 Select = 3 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
		StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fSlow5, kStack)))
		StoreVarInst(Address(iRec1, kStruct)[Int32(0)], Select2Inst(BinopInst("<=", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])) BinopInst("+", LoadVarInst(Address(iRec1, kStruct)[Int32(1)]), BinopInst(">", LoadVarInst(Address(iRec1, kStruct)[Int32(1)]), Int32(0))) Int32(1)))
		DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(iRec1, kStruct)[Int32(0)])))
		DeclareVarInst("int", iTemp2, kStack, BinopInst("+", LoadVarInst(Address(iSlow7, kStack)), BinopInst("*", LoadVarInst(Address(iSlow7, kStack)), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp2, kStack)))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), BinopInst("*", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), CastInst("float", BinopInst(">=", LoadVarInst(Address(fVec0, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow5, kStack)))))))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("*", BinopInst("*", CastInst("float", LoadVarInst(Address(iTemp0, kStack))), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp1, kStack))), BinopInst("+", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), BinopInst("-", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fTemp1, kStack)))))))), FunCallInst("max_f", Float(0.0f), BinopInst("-", FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)])), Float(1.0f)), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), CastInst("float", LoadVarInst(Address(iTemp2, kStack))))))))))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp3, kStack)))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fIRM0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIRM0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("/", LoadVarInst(Address(fConst0, kStruct)), LoadVarInst(Address(fTemp4, kStack))))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("-", LoadVarInst(Address(fTemp5, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp5, kStack)))))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("+", Float(-1.0f), Select2Inst(BinopInst("<=", LoadVarInst(Address(fTemp6, kStack)), Float(0.06f)) BinopInst("/", LoadVarInst(Address(fConst5, kStruct)), LoadVarInst(Address(fTemp4, kStack))) Select2Inst(BinopInst(">=", LoadVarInst(Address(fTemp6, kStack)), Float(0.95f)) BinopInst("/", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fTemp4, kStack))) LoadVarInst(Address(fTemp5, kStack))))))
		DeclareVarInst("int", iTemp8, kStack, CastInst("int", LoadVarInst(Address(fTemp7, kStack))))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("-", LoadVarInst(Address(fTemp7, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp7, kStack)))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp8, kStack))))), Int32(2047))]), BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), BinopInst("-", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", Int32(1), LoadVarInst(Address(iTemp8, kStack)))))), Int32(2047))]), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp8, kStack))))), Int32(2047))])))))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("+", LoadVarInst(Address(fSlow10, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
		StoreVarInst(Address(fVec2, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fTemp3, kStack)), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp10, kStack)))))
		DeclareVarInst("float", fTemp11, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp11, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp11, kStack))))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(iRec1, kStruct)[Int32(1)], LoadVarInst(Address(iRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(1)], LoadVarInst(Address(iIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fIRM0, kStruct)[Int32(1)], LoadVarInst(Address(fIRM0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "expf", "float", dummy0)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", iIIR0[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fButton0, kStruct)
	DeclareVarInst("float", fVec0[2], kStruct)
	DeclareVarInst("int", iRec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("int", iIIR1[2], kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec1[2048], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("float", fIRM0[2], kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("float", fConst5, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("float", fIIR2[2], kStruct)
	DeclareVarInst("float", fVec2[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.01f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", Float(0.1f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst3, kStruct), FunCallInst("expf", NegInst(BinopInst("/", Float(1e+03f), LoadVarInst(Address(fConst0, kStruct))))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("*", Float(0.9993265f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(1.0006735f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.999f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(127.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(0.95f)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(0.95f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Float(2e+02f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Float(0.8f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
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
			StoreVarInst(Address(iRec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fIRM0, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(-0.999f), FunCallInst("min_f", Float(0.999f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(127.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(3.6666243e-12f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(0.001f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fButton0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", Float(1.0f), FunCallInst("max_f", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), FunCallInst("max_f", Float(0.001f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))))))
	DeclareVarInst("int", iSlow7, kStack, BinopInst("==", LoadVarInst(Address(fSlow5, kStack)), Float(0.0f)))
	DeclareVarInst("float", fSlow8, kStack, FunCallInst("max_f", Float(2e+02f), FunCallInst("min_f", Float(8e+02f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst3, kStruct))), LoadVarInst(Address(fSlow8, kStack))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
			StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fSlow5, kStack)))
			StoreVarInst(Address(iRec1, kStruct)[Int32(0)], Select2Inst(BinopInst("<=", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])) BinopInst("+", LoadVarInst(Address(iRec1, kStruct)[Int32(1)]), BinopInst(">", LoadVarInst(Address(iRec1, kStruct)[Int32(1)]), Int32(0))) Int32(1)))
			DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(iRec1, kStruct)[Int32(0)])))
			DeclareVarInst("int", iTemp2, kStack, BinopInst("+", LoadVarInst(Address(iSlow7, kStack)), BinopInst("*", LoadVarInst(Address(iSlow7, kStack)), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp2, kStack)))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), BinopInst("*", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), CastInst("float", BinopInst(">=", LoadVarInst(Address(fVec0, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow5, kStack)))))))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("*", BinopInst("*", CastInst("float", LoadVarInst(Address(iTemp0, kStack))), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp1, kStack))), BinopInst("+", Float(1.0f), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), BinopInst("-", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fTemp1, kStack)))))))), FunCallInst("max_f", Float(0.0f), BinopInst("-", FunCallInst("min_f", BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)])), Float(1.0f)), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), CastInst("float", LoadVarInst(Address(iTemp2, kStack))))))))))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], LoadVarInst(Address(fTemp3, kStack)))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fIRM0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIRM0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("/", LoadVarInst(Address(fConst0, kStruct)), LoadVarInst(Address(fTemp4, kStack))))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("-", LoadVarInst(Address(fTemp5, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp5, kStack)))))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("+", Float(-1.0f), Select2Inst(BinopInst("<=", LoadVarInst(Address(fTemp6, kStack)), Float(0.06f)) BinopInst("/", LoadVarInst(Address(fConst5, kStruct)), LoadVarInst(Address(fTemp4, kStack))) Select2Inst(BinopInst(">=", LoadVarInst(Address(fTemp6, kStack)), Float(0.95f)) BinopInst("/", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fTemp4, kStack))) LoadVarInst(Address(fTemp5, kStack))))))
			DeclareVarInst("int", iTemp8, kStack, CastInst("int", LoadVarInst(Address(fTemp7, kStack))))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("-", LoadVarInst(Address(fTemp7, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp7, kStack)))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp8, kStack))))), Int32(2047))]), BinopInst("*", LoadVarInst(Address(fTemp9, kStack)), BinopInst("-", LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), BinopInst("+", Int32(1), LoadVarInst(Address(iTemp8, kStack)))))), Int32(2047))]), LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), FunCallInst("min_i", Int32(1025), FunCallInst("max_i", Int32(0), LoadVarInst(Address(iTemp8, kStack))))), Int32(2047))])))))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("+", LoadVarInst(Address(fSlow10, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
			StoreVarInst(Address(fVec2, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fTemp3, kStack)), BinopInst("*", Float(0.001f), LoadVarInst(Address(fTemp10, kStack)))))
			DeclareVarInst("float", fTemp11, kStack, BinopInst("*", Float(0.3f), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp11, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fTemp11, kStack))))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(iRec1, kStruct)[Int32(1)], LoadVarInst(Address(iRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(1)], LoadVarInst(Address(iIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fIRM0, kStruct)[Int32(1)], LoadVarInst(Address(fIRM0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 24 bytes
Heap size real = 8292 bytes
Total heap size = 8324 bytes
Stack size in compute = 60 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIRM0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = iRec1 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = IOTA0 size = 1 size_bytes = 4 read = 5 write = 1 ratio = 6
Field = fVec1 size = 2048 size_bytes = 8192 read = 3 write = 1 ratio = 0.00195312
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIRM0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            485
  eval() cache hits:       173 (35.6701%)
  eval() cache misses:     312
  Loop detector calls:     312
  Stack detector calls:    312

--- Phase 3: Propagation ---
  propagate() calls:       515
  propagate() cache hits:  86 (16.699%)
  propagate() cache misses:429

--- Box Type Computation ---
  getBoxType() calls:      961
  getBoxType() cache hits: 680 (70.7596%)
  getBoxType() computed:   281

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       3

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           2775
  Trees reused (hash):     15197 (84.5593% reuse rate)
  Property set ops:        1552
  Property get ops:        5083

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
