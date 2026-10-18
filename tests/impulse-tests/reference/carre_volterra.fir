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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fCheckbox0)("int", fSampleRate)("float", fConst0)("float", fConst1)("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("float", fConst2)("FAUSTFLOAT", fHslider2)("float", fConst3)("int[2]", iVec0)("float", fConst4)("float[2]", fRec0)("float[2]", fVec1)("int", IOTA0)("float[4096]", fVec2)("FAUSTFLOAT", fHslider3)("float[2]", fRec1)("float[2]", fVec3)("float[4096]", fVec4)("float", fConst5)("float[2]", fIIR4)("float[2]", fIIR3)("float[2]", fIIR2)("float[2]", fIIR1)("float[2]", fIIR7)("float[2]", fIIR6)("float[2]", fIIR5)("float[2]", fIIR0)>)

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
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(7e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(4.4e+02f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(2.0f)))
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
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(4096))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
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
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 47 Store = 0 Binop = 25 [ { Int(+) = 2 } { Real(*) = 5 } { Real(+) = 4 } { Real(-) = 4 } { Real(/) = 9 } { Real(>) = 1 } ] Mathop = 18 [ { fabsf = 2 } { max_f = 10 } { min_f = 6 } ] Numbers = 27 Declare = 32 Cast = 10 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.33333334f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("+", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow2, kStack)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("/", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fSlow5, kStack))), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(8e+03f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow8, kStack, FunCallInst("max_f", LoadVarInst(Address(fSlow7, kStack)), Float(23.44895f)))
	DeclareVarInst("float", fSlow9, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fSlow8, kStack))))))
	DeclareVarInst("int", iSlow10, kStack, CastInst("int", LoadVarInst(Address(fSlow9, kStack))))
	DeclareVarInst("float", fSlow11, kStack, CastInst("float", LoadVarInst(Address(iSlow10, kStack))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("-", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow11, kStack))), LoadVarInst(Address(fSlow9, kStack))))
	DeclareVarInst("float", fSlow13, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow8, kStack)))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("-", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("int", iSlow17, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iSlow10, kStack))))
	DeclareVarInst("float", fSlow18, kStack, FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(6.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))), Float(23.44895f)))
	DeclareVarInst("float", fSlow19, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fSlow18, kStack))))))
	DeclareVarInst("int", iSlow20, kStack, CastInst("int", LoadVarInst(Address(fSlow19, kStack))))
	DeclareVarInst("float", fSlow21, kStack, CastInst("float", LoadVarInst(Address(iSlow20, kStack))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("-", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow21, kStack))), LoadVarInst(Address(fSlow19, kStack))))
	DeclareVarInst("float", fSlow23, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow18, kStack)))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow26, kStack, BinopInst("-", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fSlow21, kStack))))
	DeclareVarInst("int", iSlow27, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iSlow20, kStack))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow3, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 133 Store = 31 Binop = 82 [ { Int(&) = 6 } { Int(+) = 2 } { Int(-) = 4 } { Int(<) = 1 } { Real(*) = 40 } { Real(+) = 19 } { Real(-) = 10 } ] Mathop = 9 [ { floorf = 2 } { mydsp_faustpower2_f = 2 } { mydsp_faustpower3_f = 5 } ] Numbers = 68 Declare = 26 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp1, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp1, kStack)))))
		DeclareVarInst("float", fTemp2, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", Float(-1.0f), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))))
		StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp3, kStack)))))
		StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp4, kStack)))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp5, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp5, kStack)))))
		DeclareVarInst("float", fTemp6, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", Float(-1.0f), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))))
		StoreVarInst(Address(fVec3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("-", LoadVarInst(Address(fTemp6, kStack)), LoadVarInst(Address(fVec3, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp7, kStack)))))
		StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp8, kStack)))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst5, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fTemp3, kStack))), BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fTemp7, kStack)))))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow10, kStack))), Int32(4095))])), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow17, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow20, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow27, kStack))), Int32(4095))])))))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fTemp9, kStack))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
		DeclareVarInst("float", fTemp11, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp10, kStack))))
		DeclareVarInst("float", fTemp12, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp11, kStack))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
		DeclareVarInst("float", fTemp13, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp12, kStack))))
		DeclareVarInst("float", fTemp14, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp13, kStack))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp14, kStack)))
		DeclareVarInst("float", fTemp15, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp14, kStack))))
		DeclareVarInst("float", fTemp16, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp15, kStack))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp16, kStack)))
		DeclareVarInst("float", fTemp17, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp16, kStack))))
		DeclareVarInst("float", fTemp18, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp15, kStack))))
		DeclareVarInst("float", fTemp19, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp13, kStack))))
		DeclareVarInst("float", fTemp20, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp11, kStack))))
		DeclareVarInst("float", fTemp21, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("-", FunCallInst("mydsp_faustpower3_f", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fTemp9, kStack)))), LoadVarInst(Address(fTemp20, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp21, kStack)))
		DeclareVarInst("float", fTemp22, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("+", BinopInst("-", LoadVarInst(Address(fTemp20, kStack)), LoadVarInst(Address(fTemp19, kStack))), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp21, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp22, kStack)))
		DeclareVarInst("float", fTemp23, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("+", BinopInst("-", LoadVarInst(Address(fTemp19, kStack)), LoadVarInst(Address(fTemp18, kStack))), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp22, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp23, kStack)))
		DeclareVarInst("float", fTemp24, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("+", BinopInst("-", LoadVarInst(Address(fTemp18, kStack)), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp17, kStack)))), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp23, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp24, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("-", LoadVarInst(Address(fTemp17, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp24, kStack)))))))
		StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec3, kStruct)[Int32(1)], LoadVarInst(Address(fVec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("int", iVec0[2], kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("float", fVec1[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec2[4096], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("float", fVec3[2], kStruct)
	DeclareVarInst("float", fVec4[4096], kStruct)
	DeclareVarInst("float", fConst5, kStruct)
	DeclareVarInst("float", fIIR4[2], kStruct)
	DeclareVarInst("float", fIIR3[2], kStruct)
	DeclareVarInst("float", fIIR2[2], kStruct)
	DeclareVarInst("float", fIIR1[2], kStruct)
	DeclareVarInst("float", fIIR7[2], kStruct)
	DeclareVarInst("float", fIIR6[2], kStruct)
	DeclareVarInst("float", fIIR5[2], kStruct)
	DeclareVarInst("float", fIIR0[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(6.2831855f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("*", Float(0.25f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(7e+02f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(4.4e+02f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Float(2.0f)))
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
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(4096))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
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
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", BinopInst(">", CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct))), Float(0.0f))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(0.33333334f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("max_f", Float(1.0f), FunCallInst("min_f", Float(2e+04f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("+", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fSlow2, kStack)))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("/", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fSlow5, kStack))), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("min_f", Float(8e+03f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow8, kStack, FunCallInst("max_f", LoadVarInst(Address(fSlow7, kStack)), Float(23.44895f)))
	DeclareVarInst("float", fSlow9, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fSlow8, kStack))))))
	DeclareVarInst("int", iSlow10, kStack, CastInst("int", LoadVarInst(Address(fSlow9, kStack))))
	DeclareVarInst("float", fSlow11, kStack, CastInst("float", LoadVarInst(Address(iSlow10, kStack))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("-", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow11, kStack))), LoadVarInst(Address(fSlow9, kStack))))
	DeclareVarInst("float", fSlow13, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow8, kStack)))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("-", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fSlow11, kStack))))
	DeclareVarInst("int", iSlow17, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iSlow10, kStack))))
	DeclareVarInst("float", fSlow18, kStack, FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(6.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))), Float(23.44895f)))
	DeclareVarInst("float", fSlow19, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(2047.0f), BinopInst("/", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fSlow18, kStack))))))
	DeclareVarInst("int", iSlow20, kStack, CastInst("int", LoadVarInst(Address(fSlow19, kStack))))
	DeclareVarInst("float", fSlow21, kStack, CastInst("float", LoadVarInst(Address(iSlow20, kStack))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("-", BinopInst("+", Float(1.0f), LoadVarInst(Address(fSlow21, kStack))), LoadVarInst(Address(fSlow19, kStack))))
	DeclareVarInst("float", fSlow23, kStack, FunCallInst("max_f", Float(2e+01f), FunCallInst("fabsf", LoadVarInst(Address(fSlow18, kStack)))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow26, kStack, BinopInst("-", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fSlow21, kStack))))
	DeclareVarInst("int", iSlow27, kStack, BinopInst("+", Int32(1), LoadVarInst(Address(iSlow20, kStack))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow13, kStack))))
	DeclareVarInst("float", fSlow29, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow23, kStack))))
	DeclareVarInst("float", fSlow30, kStack, BinopInst("/", Float(1.0f), LoadVarInst(Address(fSlow3, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(iVec0, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp1, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp1, kStack)))))
			DeclareVarInst("float", fTemp2, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", Float(-1.0f), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])))))
			StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp3, kStack)))))
			StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp4, kStack)))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("+", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp5, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp5, kStack)))))
			DeclareVarInst("float", fTemp6, kStack, FunCallInst("mydsp_faustpower2_f", BinopInst("+", Float(-1.0f), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])))))
			StoreVarInst(Address(fVec3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("-", LoadVarInst(Address(fTemp6, kStack)), LoadVarInst(Address(fVec3, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp7, kStack)))))
			StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], LoadVarInst(Address(fTemp8, kStack)))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst5, kStruct)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fTemp3, kStack))), BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fTemp7, kStack)))))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow10, kStack))), Int32(4095))])), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow17, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow20, kStack))), Int32(4095))]))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow27, kStack))), Int32(4095))])))))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fTemp9, kStack))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
			DeclareVarInst("float", fTemp11, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp10, kStack))))
			DeclareVarInst("float", fTemp12, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp11, kStack))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
			DeclareVarInst("float", fTemp13, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp12, kStack))))
			DeclareVarInst("float", fTemp14, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp13, kStack))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp14, kStack)))
			DeclareVarInst("float", fTemp15, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp14, kStack))))
			DeclareVarInst("float", fTemp16, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp15, kStack))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp16, kStack)))
			DeclareVarInst("float", fTemp17, kStack, BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp16, kStack))))
			DeclareVarInst("float", fTemp18, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp15, kStack))))
			DeclareVarInst("float", fTemp19, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp13, kStack))))
			DeclareVarInst("float", fTemp20, kStack, FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp11, kStack))))
			DeclareVarInst("float", fTemp21, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("-", FunCallInst("mydsp_faustpower3_f", BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fTemp9, kStack)))), LoadVarInst(Address(fTemp20, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp21, kStack)))
			DeclareVarInst("float", fTemp22, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("+", BinopInst("-", LoadVarInst(Address(fTemp20, kStack)), LoadVarInst(Address(fTemp19, kStack))), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp21, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp22, kStack)))
			DeclareVarInst("float", fTemp23, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("+", BinopInst("-", LoadVarInst(Address(fTemp19, kStack)), LoadVarInst(Address(fTemp18, kStack))), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp22, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp23, kStack)))
			DeclareVarInst("float", fTemp24, kStack, BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("+", BinopInst("-", LoadVarInst(Address(fTemp18, kStack)), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fTemp17, kStack)))), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp23, kStack))))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp24, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("-", LoadVarInst(Address(fTemp17, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fTemp24, kStack)))))))
			StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec3, kStruct)[Int32(1)], LoadVarInst(Address(fVec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 32908 bytes
Total heap size = 32924 bytes
Stack size in compute = 132 bytes

======= Variable access in Control ==========

Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec4 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst2 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst3 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec4 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 8 write = 0 ratio = 8
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = IOTA0 size = 1 size_bytes = 4 read = 7 write = 1 ratio = 8
Field = fVec2 size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec4 size = 4096 size_bytes = 16384 read = 2 write = 1 ratio = 0.000732422
Field = fConst5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR4 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR7 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR6 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR5 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            1412
  eval() cache hits:       299 (21.1756%)
  eval() cache misses:     1113
  Loop detector calls:     1113
  Stack detector calls:    1113

--- Phase 3: Propagation ---
  propagate() calls:       925
  propagate() cache hits:  220 (23.7838%)
  propagate() cache misses:705

--- Box Type Computation ---
  getBoxType() calls:      1512
  getBoxType() cache hits: 1177 (77.8439%)
  getBoxType() computed:   335

--- Environment Operations ---
  Environment lookups:     30
  Average lookup depth:    0
  Env layers pushed:       78

--- Pattern Matching ---
  build automaton calls:        6
  build total time (ms):        0.037874
  build avg time (ms):          0.00631233
  apply calls:                  44
  apply total time (ms):        0.029621
  apply avg time (ms):          0.000673205

--- Tree Operations ---
  Trees created:           28037
  Trees reused (hash):     77057 (73.322% reuse rate)
  Property set ops:        17107
  Property get ops:        7850

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        2
  sum() iterations:        0
  prod() iterations:       0

==========================================
