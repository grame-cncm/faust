======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("carre_volterra")
	AddCheckButtonInst("NL"fCheckbox0)
	AddHorizontalSlider("delta", fHslider1, 2.0f, 0.0f, 6.0f, 0.1f)
	AddHorizontalSlider("freq carre", fHslider0, 4.4e+02f, 2e+01f, 8e+03f, 1.0f)
	AddMetaDeclareInst(fHslider2, "unit", "Hz")
	AddHorizontalSlider("freq", fHslider2, 7e+02f, 1.0f, 2e+04f, 1.0f)
	AddHorizontalSlider("level", fHslider3, 0.5f, 0.0f, 1.0f, 0.01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", iConst0KC)("int", IOTA0)("int[2]", iVec0KC)("FAUSTFLOAT", fHslider0)("int", fSampleRate)("float", fConst1KI)("float", fConst2KI)("float[2]", fVec1SE)("float[2]", fVec3SE)("FAUSTFLOAT", fHslider1)("float[2]", fVec4SE)("float[2]", fVec6SE)("FAUSTFLOAT", fHslider2)("float", fConst3KI)("FAUSTFLOAT", fHslider3)("float", fConst4KI)("float", fConst5KI)("float[4096]", fVec15SE)("float[4096]", fVec14SE)("float[2]", fVec10SE)("float[2]", fVec9SE)("float[2]", fVec8SE)("float[2]", fVec7SE)("FAUSTFLOAT", fCheckbox0)("float[2]", fVec27SE)("float[2]", fVec26SE)("float[2]", fVec25SE)("float[2]", fVec24SE)>)

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
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst1KI, kStruct))))
	StoreVarInst(Address(fConst3KI, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst1KI, kStruct))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst1KI, kStruct))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst1KI, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(4.4e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(7e+02f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(Address(iVec0KC, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
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
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4096))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(4096))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 44 Store = 0 Binop = 23 [ { Int(+) = 2 } { Real(*) = 6 } { Real(+) = 8 } { Real(/) = 7 } ] Mathop = 10 [ { fabsf = 2 } { max_f = 6 } { min_f = 2 } ] Numbers = 18 Declare = 30 Cast = 9 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, FunCallInst("max_f", LoadVarInst(Address(fSlow0BE, kStack)), Float(23.44895f)))
	DeclareVarInst("float", fSlow2BE, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow1BE, kStack)))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow4BE, kStack, FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))), Float(23.44895f)))
	DeclareVarInst("float", fSlow5BE, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow4BE, kStack)))))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fSlow5BE, kStack))))
	DeclareVarInst("float", fSlow7BE, kStack, CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), LoadVarInst(Address(fSlow7BE, kStack))))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fSlow8BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow10BE, kStack, CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))
	DeclareVarInst("float", fSlow11BE, kStack, BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fSlow7BE, kStack)))))
	DeclareVarInst("float", fSlow12BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow13BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow5BE, kStack))))
	DeclareVarInst("float", fSlow14BE, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fSlow4BE, kStack))))))
	DeclareVarInst("int", iSlow15BE, kStack, CastInst("int", LoadVarInst(Address(fSlow14BE, kStack))))
	DeclareVarInst("float", fSlow16BE, kStack, CastInst("float", LoadVarInst(Address(iSlow15BE, kStack))))
	DeclareVarInst("float", fSlow17BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow14BE, kStack)), MinusInst(LoadVarInst(Address(fSlow16BE, kStack)))))
	DeclareVarInst("int", iSlow18BE, kStack, BinopInst("+", LoadVarInst(Address(iSlow15BE, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow19BE, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fSlow1BE, kStack))))))
	DeclareVarInst("int", iSlow20BE, kStack, CastInst("int", LoadVarInst(Address(fSlow19BE, kStack))))
	DeclareVarInst("float", fSlow21BE, kStack, CastInst("float", LoadVarInst(Address(iSlow20BE, kStack))))
	DeclareVarInst("float", fSlow22BE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow21BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow19BE, kStack)))))
	DeclareVarInst("float", fSlow23BE, kStack, BinopInst("/", LoadVarInst(Address(fConst4KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow24BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow19BE, kStack)), MinusInst(LoadVarInst(Address(fSlow21BE, kStack)))))
	DeclareVarInst("int", iSlow25BE, kStack, BinopInst("+", LoadVarInst(Address(iSlow20BE, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow26BE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow16BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow14BE, kStack)))))
	DeclareVarInst("float", fSlow27BE, kStack, BinopInst("/", LoadVarInst(Address(fConst4KI, kStruct)), LoadVarInst(Address(fSlow5BE, kStack))))
	DeclareVarInst("float", fSlow28BE, kStack, BinopInst("*", Float(0.33333334f), CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 143 Store = 18 Binop = 125 [ { Int(&) = 42 } { Int(+) = 2 } { Int(-) = 17 } { Int(<) = 1 } { Real(*) = 32 } { Real(+) = 31 } ] Mathop = 9 [ { floorf = 2 } { mydsp_faustpower2_f = 2 } { mydsp_faustpower3_f = 5 } ] Numbers = 62 Declare = 18 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iConst0KC, kStruct)))
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))))))
		DeclareVarInst("float", fTemp1SE, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(-1.0f))))
		StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp1SE, kStack)))
		DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack)))))))
		DeclareVarInst("float", fTemp3SE, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(-1.0f))))
		StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp3SE, kStack)))
		DeclareVarInst("float", fTemp4SC, kStack, CastInst("float", LoadVarInst(Address(iVec0KC, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
		DeclareVarInst("float", fTemp5SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), MinusInst(LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp6SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp3SE, kStack)), MinusInst(LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp7SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp4SC, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))))
		StoreVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp7SE, kStack)))
		DeclareVarInst("float", fTemp8SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow27BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp4SC, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
		StoreVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp8SE, kStack)))
		DeclareVarInst("float", fTemp9SE, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp4SC, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow17BE, kStack)), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow18BE, kStack))), Int32(4095))])))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow20BE, kStack))), Int32(4095))])))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow24BE, kStack)), LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow25BE, kStack))), Int32(4095))])))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow26BE, kStack)), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow15BE, kStack))), Int32(4095))])))))
		StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), LoadVarInst(Address(fTemp9SE, kStack))))))
		DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack))))))
		DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fTemp11SE, kStack))))))
		DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack))))))
		DeclareVarInst("float", fTemp13SE, kStack, LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp14SE, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp12SE, kStack))))
		DeclareVarInst("float", fTemp15SE, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp11SE, kStack))))
		DeclareVarInst("float", fTemp16SE, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp10SE, kStack))))
		StoreVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("+", FunCallInst("mydsp_faustpower3_f", BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp9SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp16SE, kStack))))))))
		StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fTemp16SE, kStack))), MinusInst(LoadVarInst(Address(fTemp15SE, kStack))))))))
		StoreVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fTemp15SE, kStack))), MinusInst(LoadVarInst(Address(fTemp14SE, kStack))))))))
		StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fTemp14SE, kStack))), MinusInst(FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp13SE, kStack)))))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fTemp13SE, kStack)), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow28BE, kStack)), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
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
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("int", iConst0KC, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec0KC[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst1KI, kStruct)
	DeclareVarInst("float", fConst2KI, kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec3SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	// Recursion delay fVec4SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec4SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec6SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fConst3KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fConst4KI, kStruct)
	DeclareVarInst("float", fConst5KI, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec15SE[4096], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec14SE[4096], kStruct)
	// Recursion delay fVec10SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec10SE[2], kStruct)
	// Recursion delay fVec9SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec9SE[2], kStruct)
	// Recursion delay fVec8SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec8SE[2], kStruct)
	// Recursion delay fVec7SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec7SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	// Recursion delay fVec27SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec27SE[2], kStruct)
	// Recursion delay fVec26SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec26SE[2], kStruct)
	// Recursion delay fVec25SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec25SE[2], kStruct)
	// Recursion delay fVec24SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec24SE[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(iConst0KC, kStruct), Int32(1))
	StoreVarInst(Address(fConst1KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst2KI, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst1KI, kStruct))))
	StoreVarInst(Address(fConst3KI, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst1KI, kStruct))))
	StoreVarInst(Address(fConst4KI, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst1KI, kStruct))))
	StoreVarInst(Address(fConst5KI, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst1KI, kStruct))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(4.4e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(7e+02f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4096))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(4096))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, FunCallInst("max_f", LoadVarInst(Address(fSlow0BE, kStack)), Float(23.44895f)))
	DeclareVarInst("float", fSlow2BE, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow1BE, kStack)))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow4BE, kStack, FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))), Float(23.44895f)))
	DeclareVarInst("float", fSlow5BE, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow4BE, kStack)))))
	DeclareVarInst("float", fSlow6BE, kStack, BinopInst("*", LoadVarInst(Address(fConst2KI, kStruct)), LoadVarInst(Address(fSlow5BE, kStack))))
	DeclareVarInst("float", fSlow7BE, kStack, CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))
	DeclareVarInst("float", fSlow8BE, kStack, BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), LoadVarInst(Address(fSlow7BE, kStack))))
	DeclareVarInst("float", fSlow9BE, kStack, BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fSlow8BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow10BE, kStack, CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))
	DeclareVarInst("float", fSlow11BE, kStack, BinopInst("*", LoadVarInst(Address(fConst3KI, kStruct)), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fSlow7BE, kStack)))))
	DeclareVarInst("float", fSlow12BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow13BE, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow5BE, kStack))))
	DeclareVarInst("float", fSlow14BE, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fSlow4BE, kStack))))))
	DeclareVarInst("int", iSlow15BE, kStack, CastInst("int", LoadVarInst(Address(fSlow14BE, kStack))))
	DeclareVarInst("float", fSlow16BE, kStack, CastInst("float", LoadVarInst(Address(iSlow15BE, kStack))))
	DeclareVarInst("float", fSlow17BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow14BE, kStack)), MinusInst(LoadVarInst(Address(fSlow16BE, kStack)))))
	DeclareVarInst("int", iSlow18BE, kStack, BinopInst("+", LoadVarInst(Address(iSlow15BE, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow19BE, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst5KI, kStruct)), LoadVarInst(Address(fSlow1BE, kStack))))))
	DeclareVarInst("int", iSlow20BE, kStack, CastInst("int", LoadVarInst(Address(fSlow19BE, kStack))))
	DeclareVarInst("float", fSlow21BE, kStack, CastInst("float", LoadVarInst(Address(iSlow20BE, kStack))))
	DeclareVarInst("float", fSlow22BE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow21BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow19BE, kStack)))))
	DeclareVarInst("float", fSlow23BE, kStack, BinopInst("/", LoadVarInst(Address(fConst4KI, kStruct)), LoadVarInst(Address(fSlow2BE, kStack))))
	DeclareVarInst("float", fSlow24BE, kStack, BinopInst("+", LoadVarInst(Address(fSlow19BE, kStack)), MinusInst(LoadVarInst(Address(fSlow21BE, kStack)))))
	DeclareVarInst("int", iSlow25BE, kStack, BinopInst("+", LoadVarInst(Address(iSlow20BE, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow26BE, kStack, BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow16BE, kStack)), Float(1.0f)), MinusInst(LoadVarInst(Address(fSlow14BE, kStack)))))
	DeclareVarInst("float", fSlow27BE, kStack, BinopInst("/", LoadVarInst(Address(fConst4KI, kStruct)), LoadVarInst(Address(fSlow5BE, kStack))))
	DeclareVarInst("float", fSlow28BE, kStack, BinopInst("*", Float(0.33333334f), CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0KC, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iConst0KC, kStruct)))
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))))))
			DeclareVarInst("float", fTemp1SE, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(-1.0f))))
			StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp1SE, kStack)))
			DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack)))))))
			DeclareVarInst("float", fTemp3SE, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), Float(-1.0f))))
			StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fTemp3SE, kStack)))
			DeclareVarInst("float", fTemp4SC, kStack, CastInst("float", LoadVarInst(Address(iVec0KC, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))
			DeclareVarInst("float", fTemp5SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), MinusInst(LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp6SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp3SE, kStack)), MinusInst(LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp7SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp4SC, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))))
			StoreVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp7SE, kStack)))
			DeclareVarInst("float", fTemp8SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow27BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp4SC, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
			StoreVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp8SE, kStack)))
			DeclareVarInst("float", fTemp9SE, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst4KI, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp4SC, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow17BE, kStack)), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow18BE, kStack))), Int32(4095))])))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow20BE, kStack))), Int32(4095))])))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow24BE, kStack)), LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow25BE, kStack))), Int32(4095))])))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow26BE, kStack)), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow15BE, kStack))), Int32(4095))])))))
			StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), LoadVarInst(Address(fTemp9SE, kStack))))))
			DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack))))))
			DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fTemp11SE, kStack))))))
			DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack))))))
			DeclareVarInst("float", fTemp13SE, kStack, LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp14SE, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp12SE, kStack))))
			DeclareVarInst("float", fTemp15SE, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp11SE, kStack))))
			DeclareVarInst("float", fTemp16SE, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp10SE, kStack))))
			StoreVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("+", FunCallInst("mydsp_faustpower3_f", BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp9SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp16SE, kStack))))))))
			StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fTemp16SE, kStack))), MinusInst(LoadVarInst(Address(fTemp15SE, kStack))))))))
			StoreVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fTemp15SE, kStack))), MinusInst(LoadVarInst(Address(fTemp14SE, kStack))))))))
			StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fTemp14SE, kStack))), MinusInst(FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp13SE, kStack)))))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", LoadVarInst(Address(fTemp13SE, kStack)), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow28BE, kStack)), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 12 bytes
Heap size int* = 8 bytes
Heap size real = 32904 bytes
Total heap size = 32924 bytes
Stack size in compute = 124 bytes

======= Variable access in Control ==========

Field = iConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0KC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec15SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec14SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec27SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec25SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = iConst0KC size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0KC size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst3KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst4KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst5KI size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fVec15SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec14SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec27SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec25SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = iConst0KC size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 43 write = 1 ratio = 44
Field = iVec0KC size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec3SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec6SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst5KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec15SE size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fVec14SE size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fVec10SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec9SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec8SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec7SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec27SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec26SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec25SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec24SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
