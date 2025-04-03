======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("carre_volterra")
	AddCheckButtonInst("NL"fCheckbox0)
	AddHorizontalSlider("delta", fHslider3, 2.0f, 0.0f, 6.0f, 0.1f)
	AddHorizontalSlider("freq carre", fHslider2, 4.4e+02f, 2e+01f, 8e+03f, 1.0f)
	AddMetaDeclareInst(fHslider0, "unit", "Hz")
	AddHorizontalSlider("freq", fHslider0, 7e+02f, 1.0f, 2e+04f, 1.0f)
	AddHorizontalSlider("level", fHslider1, 0.5f, 0.0f, 1.0f, 0.01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
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

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("float", fConst1)("FAUSTFLOAT", fHslider0)("int[2]", iVec0)("FAUSTFLOAT", fHslider1)("float", fConst2)("FAUSTFLOAT", fHslider2)("float", fConst3)("float[2]", fRec4)("float[2]", fVec1)("FAUSTFLOAT", fHslider3)("float[2]", fRec5)("float[2]", fVec2)("float", fConst4)("int", IOTA0)("float[4096]", fVec3)("float[4096]", fVec4)("float[2]", fRec3)("float[2]", fRec2)("float[2]", fRec1)("float[2]", fRec0)("FAUSTFLOAT", fCheckbox0)("float[2]", fRec9)("float[2]", fRec8)("float[2]", fRec7)("float[2]", fRec6)>)

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
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(7e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(4.4e+02f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4096))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(4096))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 44 Store = 0 Binop = 23 [ { Int(+) = 2 } { Real(*) = 6 } { Real(+) = 4 } { Real(-) = 4 } { Real(/) = 7 } ] Mathop = 10 [ { fabsf = 2 } { max_f = 6 } { min_f = 2 } ] Numbers = 18 Declare = 30 Cast = 9 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow3, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fSlow0, kStack)))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("max_f", LoadVarInst(Address(fSlow5, kStack)), Float(23.44895f)))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow6, kStack)))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))), Float(23.44895f)))
	DeclareVarInst("float", fSlow11, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow10, kStack)))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow14, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow10, kStack))))))
	DeclareVarInst("int", iSlow15, kStack, CastInst("int", LoadVarInst(Address(fSlow14, kStack))))
	DeclareVarInst("float", fSlow16, kStack, CastInst("float", LoadVarInst(Address(iSlow15, kStack))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("-", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("int", iSlow19, kStack, BinopInst("+", LoadVarInst(Address(iSlow15, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow20, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow6, kStack))))))
	DeclareVarInst("int", iSlow21, kStack, CastInst("int", LoadVarInst(Address(fSlow20, kStack))))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", LoadVarInst(Address(iSlow21, kStack))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("+", LoadVarInst(Address(fSlow22, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow20, kStack)))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("-", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("int", iSlow26, kStack, BinopInst("+", LoadVarInst(Address(iSlow21, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("+", LoadVarInst(Address(fSlow16, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow14, kStack)))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("*", Float(0.33333334f), CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 113 Store = 31 Binop = 76 [ { Int(&) = 6 } { Int(+) = 2 } { Int(-) = 4 } { Int(<) = 1 } { Real(*) = 32 } { Real(+) = 21 } { Real(-) = 10 } ] Mathop = 9 [ { floorf = 2 } { mydsp_faustpower2_f = 2 } { mydsp_faustpower3_f = 5 } ] Numbers = 82 Declare = 12 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp1, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec4, kStruct)[Int32(0)])), Float(-1.0f))))
		StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("-", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow13, kStack)), BinopInst("-", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow13, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp3, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)])), Float(-1.0f))))
		StoreVarInst(Address(fVec2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("-", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp4, kStack)))))
		StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp5, kStack)))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp6, kStack)))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fTemp2, kStack))), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fTemp4, kStack)))))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow19, kStack))), Int32(4095))])), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow21, kStack))), Int32(4095))])), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow26, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow15, kStack))), Int32(4095))]))))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)])))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))))
		DeclareVarInst("float", fTemp8, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("-", FunCallInst("mydsp_faustpower3_f", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fTemp7, kStack)))), LoadVarInst(Address(fTemp8, kStack)))))))
		DeclareVarInst("float", fTemp9, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fRec2, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp8, kStack))), LoadVarInst(Address(fTemp9, kStack)))))))
		DeclareVarInst("float", fTemp10, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp9, kStack))), LoadVarInst(Address(fTemp10, kStack)))))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp10, kStack))), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])))))
		StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "fabsf", "float", dummy0)
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
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("int", iVec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("float", fVec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("float", fVec2[2], kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec3[4096], kStruct)
	DeclareVarInst("float", fVec4[4096], kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("float", fRec9[2], kStruct)
	DeclareVarInst("float", fRec8[2], kStruct)
	DeclareVarInst("float", fRec7[2], kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(7e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(4.4e+02f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(2.0f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4096))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(4096))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow3, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fSlow0, kStack)))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("max_f", LoadVarInst(Address(fSlow5, kStack)), Float(23.44895f)))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow6, kStack)))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))), Float(23.44895f)))
	DeclareVarInst("float", fSlow11, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow10, kStack)))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("float", fSlow14, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow10, kStack))))))
	DeclareVarInst("int", iSlow15, kStack, CastInst("int", LoadVarInst(Address(fSlow14, kStack))))
	DeclareVarInst("float", fSlow16, kStack, CastInst("float", LoadVarInst(Address(iSlow15, kStack))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("-", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fSlow16, kStack))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("int", iSlow19, kStack, BinopInst("+", LoadVarInst(Address(iSlow15, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow20, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow6, kStack))))))
	DeclareVarInst("int", iSlow21, kStack, CastInst("int", LoadVarInst(Address(fSlow20, kStack))))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", LoadVarInst(Address(iSlow21, kStack))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("+", LoadVarInst(Address(fSlow22, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow20, kStack)))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fSlow7, kStack))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("-", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fSlow22, kStack))))
	DeclareVarInst("int", iSlow26, kStack, BinopInst("+", LoadVarInst(Address(iSlow21, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("+", LoadVarInst(Address(fSlow16, kStack)), BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow14, kStack)))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("*", Float(0.33333334f), CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp1, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec4, kStruct)[Int32(0)])), Float(-1.0f))))
			StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("-", LoadVarInst(Address(fTemp1, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow13, kStack)), BinopInst("-", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow13, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp3, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)])), Float(-1.0f))))
			StoreVarInst(Address(fVec2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("-", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp4, kStack)))))
			StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp5, kStack)))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp6, kStack)))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fTemp2, kStack))), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fTemp4, kStack)))))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow19, kStack))), Int32(4095))])), BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow21, kStack))), Int32(4095))])), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow26, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow15, kStack))), Int32(4095))]))))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)])))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))))
			DeclareVarInst("float", fTemp8, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("-", FunCallInst("mydsp_faustpower3_f", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fTemp7, kStack)))), LoadVarInst(Address(fTemp8, kStack)))))))
			DeclareVarInst("float", fTemp9, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fRec2, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp8, kStack))), LoadVarInst(Address(fTemp9, kStack)))))))
			DeclareVarInst("float", fTemp10, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp9, kStack))), LoadVarInst(Address(fTemp10, kStack)))))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(0)]), LoadVarInst(Address(fTemp10, kStack))), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])))))
			StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 32904 bytes
Total heap size = 32920 bytes
Stack size in compute = 124 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec3 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec4 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst3 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec3 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec4 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 7 write = 1 ratio = 8
Field = fVec3 size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fVec4 size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fRec3 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec2 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec1 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fRec0 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec8 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec7 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
