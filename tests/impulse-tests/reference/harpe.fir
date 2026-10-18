======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Harpe")
	AddMetaDeclareInst(fHslider0, "osc", "/1/fader3")
	AddHorizontalSlider("attenuation", fHslider0, 0.0f, 0.0f, 0.01f, 0.001f)
	AddMetaDeclareInst(fHslider2, "osc", "/accxyz/1 -10 10")
	AddHorizontalSlider("hand", fHslider2, 0.43f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fHslider1, "osc", "/accxyz/0 -10 10")
	AddMetaDeclareInst(fHslider1, "unit", "f")
	AddHorizontalSlider("level", fHslider1, 0.5f, 0.0f, 1.0f, 0.01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("int[2]", iIIR0)("FAUSTFLOAT", fHslider2)("float[2]", fIIR1)("float[2]", fRec2)("int[2]", iVec0)("float[2]", fRec1)("int", IOTA0)("float[32]", fVec1)("float[3]", fRec0)("int[2]", iVec2)("float[2]", fRec4)("float[64]", fVec3)("float[3]", fRec3)("int[2]", iVec4)("float[2]", fRec6)("float[128]", fVec5)("float[3]", fRec5)("int[2]", iVec6)("float[2]", fRec8)("float[32]", fVec7)("float[3]", fRec7)("int[2]", iVec8)("float[2]", fRec10)("float[64]", fVec9)("float[3]", fRec9)("int[2]", iVec10)("float[2]", fRec12)("float[128]", fVec11)("float[3]", fRec11)("int[2]", iVec12)("float[2]", fRec14)("float[64]", fVec13)("float[3]", fRec13)("int[2]", iVec14)("float[2]", fRec16)("float[64]", fVec15)("float[3]", fRec15)("int[2]", iVec16)("float[2]", fRec18)("float[128]", fVec17)("float[3]", fRec17)("int[2]", iVec18)("float[2]", fRec20)("float[64]", fVec19)("float[3]", fRec19)("int[2]", iVec20)("float[2]", fRec22)("float[128]", fVec21)("float[3]", fRec21)("int", fSampleRate)>)

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
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(0.43f)))
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
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
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
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(32))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2, kStruct)[LoadVarInst(Address(l7, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(64))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(3))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec4, kStruct)[LoadVarInst(Address(l11, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(128))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(3))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec6, kStruct)[LoadVarInst(Address(l15, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(32))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(3))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec8, kStruct)[LoadVarInst(Address(l19, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(64))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(3))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec10, kStruct)[LoadVarInst(Address(l23, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(128))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(3))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec12, kStruct)[LoadVarInst(Address(l27, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(64))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(3))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec14, kStruct)[LoadVarInst(Address(l31, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(64))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(3))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec16, kStruct)[LoadVarInst(Address(l35, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(128))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(3))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec18, kStruct)[LoadVarInst(Address(l39, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(64))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(3))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec20, kStruct)[LoadVarInst(Address(l43, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(128))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(3))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 29 Store = 0 Binop = 24 [ { Real(*) = 23 } { Real(-) = 1 } ] Mathop = 7 [ { max_f = 3 } { min_f = 3 } { mydsp_faustpower2_f = 1 } ] Numbers = 32 Declare = 29 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(0.01f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", Float(0.1f), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow26, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 254 Store = 98 Binop = 249 [ { Int(&) = 33 } { Int(*) = 1 } { Int(+) = 3 } { Int(-) = 22 } { Int(<) = 1 } { Real(*) = 68 } { Real(+) = 55 } { Real(-) = 11 } { Real(<) = 22 } { Real(>) = 33 } ] Mathop = 2 [ { max_f = 1 } { min_f = 1 } ] Numbers = 361 Declare = 8 Cast = 47 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
		DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(iTemp0, kStack))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp2, kStack))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp4, kStack, FunCallInst("min_f", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp5, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])))
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.95454544f)), BinopInst("<", Float(0.95454544f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), BinopInst("*", Float(0.039909296f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec0, kStruct)[Int32(0)]), LoadVarInst(Address(iVec0, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(24)), Int32(31))]))
		StoreVarInst(Address(iVec2, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.59090906f)), BinopInst("<", Float(0.59090906f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), BinopInst("*", Float(0.022921871f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec2, kStruct)[Int32(0)]), LoadVarInst(Address(iVec2, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fRec3, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec4, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(42)), Int32(63))]))
		StoreVarInst(Address(iVec4, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.22727273f)), BinopInst("<", Float(0.22727273f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), BinopInst("*", Float(0.013165158f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec4, kStruct)[Int32(0)]), LoadVarInst(Address(iVec4, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fRec5, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec6, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(74)), Int32(127))]))
		StoreVarInst(Address(iVec6, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.8636364f)), BinopInst("<", Float(0.8636364f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), BinopInst("*", Float(0.03474306f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec6, kStruct)[Int32(0)]), LoadVarInst(Address(iVec6, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec8, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(27)), Int32(31))]))
		StoreVarInst(Address(iVec8, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.5f)), BinopInst("<", Float(0.5f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec10, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), BinopInst("*", Float(0.019954648f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec8, kStruct)[Int32(0)]), LoadVarInst(Address(iVec8, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), LoadVarInst(Address(fRec9, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec10, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(49)), Int32(63))]))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("*", Float(0.70710677f), LoadVarInst(Address(fRec9, kStruct)[Int32(0)])))
		StoreVarInst(Address(iVec10, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.13636364f)), BinopInst("<", Float(0.13636364f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("*", Float(0.011460936f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec10, kStruct)[Int32(0)]), LoadVarInst(Address(iVec10, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), LoadVarInst(Address(fRec11, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec12, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec11, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(86)), Int32(127))]))
		StoreVarInst(Address(iVec12, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.77272725f)), BinopInst("<", Float(0.77272725f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), BinopInst("*", Float(0.030245591f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec12, kStruct)[Int32(0)]), LoadVarInst(Address(iVec12, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), BinopInst("+", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), LoadVarInst(Address(fRec13, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec14, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec13, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(32)), Int32(63))]))
		StoreVarInst(Address(iVec14, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.4090909f)), BinopInst("<", Float(0.4090909f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec16, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("*", Float(0.01737153f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec14, kStruct)[Int32(0)]), LoadVarInst(Address(iVec14, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), BinopInst("+", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), LoadVarInst(Address(fRec15, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec16, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec15, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(56)), Int32(63))]))
		StoreVarInst(Address(iVec16, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.045454547f)), BinopInst("<", Float(0.045454547f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec18, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), BinopInst("*", Float(0.009977324f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec16, kStruct)[Int32(0)]), LoadVarInst(Address(iVec16, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), LoadVarInst(Address(fRec17, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec18, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec17, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(99)), Int32(127))]))
		StoreVarInst(Address(iVec18, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.6818182f)), BinopInst("<", Float(0.6818182f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec20, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("*", Float(0.026330316f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec18, kStruct)[Int32(0)]), LoadVarInst(Address(iVec18, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec19, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("+", LoadVarInst(Address(fRec19, kStruct)[Int32(1)]), LoadVarInst(Address(fRec19, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec20, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec19, kStruct)[Int32(0)], LoadVarInst(Address(fVec19, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(36)), Int32(63))]))
		StoreVarInst(Address(iVec20, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.3181818f)), BinopInst("<", Float(0.3181818f), LoadVarInst(Address(fTemp5, kStack)))))
		StoreVarInst(Address(fRec22, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), BinopInst("*", Float(0.0151227955f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec20, kStruct)[Int32(0)]), LoadVarInst(Address(iVec20, kStruct)[Int32(1)]))), Float(0.0f)))))
		StoreVarInst(Address(fVec21, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStruct)[Int32(1)]), LoadVarInst(Address(fRec21, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec22, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec21, kStruct)[Int32(0)], LoadVarInst(Address(fVec21, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(65)), Int32(127))]))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fRec7, kStruct)[Int32(0)])), LoadVarInst(Address(fTemp6, kStack))), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fRec11, kStruct)[Int32(0)])))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fRec13, kStruct)[Int32(0)])), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))), BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))), BinopInst("+", BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fRec19, kStruct)[Int32(0)])), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fRec21, kStruct)[Int32(0)])))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6, kStack)), BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fRec17, kStruct)[Int32(0)])), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fRec7, kStruct)[Int32(0)])))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fRec11, kStruct)[Int32(0)])), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))), BinopInst("+", BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)])), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fRec19, kStruct)[Int32(0)])))))))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec2, kStruct)[Int32(1)], LoadVarInst(Address(iVec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec4, kStruct)[Int32(1)], LoadVarInst(Address(iVec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(2)], LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec6, kStruct)[Int32(1)], LoadVarInst(Address(iVec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(2)], LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec8, kStruct)[Int32(1)], LoadVarInst(Address(iVec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(2)], LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec10, kStruct)[Int32(1)], LoadVarInst(Address(iVec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(2)], LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec12, kStruct)[Int32(1)], LoadVarInst(Address(iVec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(2)], LoadVarInst(Address(fRec13, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec14, kStruct)[Int32(1)], LoadVarInst(Address(iVec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(2)], LoadVarInst(Address(fRec15, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec16, kStruct)[Int32(1)], LoadVarInst(Address(iVec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(2)], LoadVarInst(Address(fRec17, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec18, kStruct)[Int32(1)], LoadVarInst(Address(iVec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(2)], LoadVarInst(Address(fRec19, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec20, kStruct)[Int32(1)], LoadVarInst(Address(iVec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(2)], LoadVarInst(Address(fRec21, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", iIIR0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fIIR1[2], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("int", iVec0[2], kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec1[32], kStruct)
	DeclareVarInst("float", fRec0[3], kStruct)
	DeclareVarInst("int", iVec2[2], kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("float", fVec3[64], kStruct)
	DeclareVarInst("float", fRec3[3], kStruct)
	DeclareVarInst("int", iVec4[2], kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("float", fVec5[128], kStruct)
	DeclareVarInst("float", fRec5[3], kStruct)
	DeclareVarInst("int", iVec6[2], kStruct)
	DeclareVarInst("float", fRec8[2], kStruct)
	DeclareVarInst("float", fVec7[32], kStruct)
	DeclareVarInst("float", fRec7[3], kStruct)
	DeclareVarInst("int", iVec8[2], kStruct)
	DeclareVarInst("float", fRec10[2], kStruct)
	DeclareVarInst("float", fVec9[64], kStruct)
	DeclareVarInst("float", fRec9[3], kStruct)
	DeclareVarInst("int", iVec10[2], kStruct)
	DeclareVarInst("float", fRec12[2], kStruct)
	DeclareVarInst("float", fVec11[128], kStruct)
	DeclareVarInst("float", fRec11[3], kStruct)
	DeclareVarInst("int", iVec12[2], kStruct)
	DeclareVarInst("float", fRec14[2], kStruct)
	DeclareVarInst("float", fVec13[64], kStruct)
	DeclareVarInst("float", fRec13[3], kStruct)
	DeclareVarInst("int", iVec14[2], kStruct)
	DeclareVarInst("float", fRec16[2], kStruct)
	DeclareVarInst("float", fVec15[64], kStruct)
	DeclareVarInst("float", fRec15[3], kStruct)
	DeclareVarInst("int", iVec16[2], kStruct)
	DeclareVarInst("float", fRec18[2], kStruct)
	DeclareVarInst("float", fVec17[128], kStruct)
	DeclareVarInst("float", fRec17[3], kStruct)
	DeclareVarInst("int", iVec18[2], kStruct)
	DeclareVarInst("float", fRec20[2], kStruct)
	DeclareVarInst("float", fVec19[64], kStruct)
	DeclareVarInst("float", fRec19[3], kStruct)
	DeclareVarInst("int", iVec20[2], kStruct)
	DeclareVarInst("float", fRec22[2], kStruct)
	DeclareVarInst("float", fVec21[128], kStruct)
	DeclareVarInst("float", fRec21[3], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Float(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Float(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Float(0.43f)))
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
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
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
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(32))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2, kStruct)[LoadVarInst(Address(l7, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(64))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(3))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec4, kStruct)[LoadVarInst(Address(l11, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(128))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(3))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec6, kStruct)[LoadVarInst(Address(l15, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(32))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(3))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec8, kStruct)[LoadVarInst(Address(l19, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(64))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(3))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec10, kStruct)[LoadVarInst(Address(l23, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(128))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(3))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec12, kStruct)[LoadVarInst(Address(l27, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(64))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(3))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec14, kStruct)[LoadVarInst(Address(l31, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(64))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(3))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec16, kStruct)[LoadVarInst(Address(l35, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(128))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(3))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec18, kStruct)[LoadVarInst(Address(l39, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(64))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(3))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec20, kStruct)[LoadVarInst(Address(l43, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(128))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(3))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(0.01f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("mydsp_faustpower2_f", FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow5, kStack, FunCallInst("max_f", Float(0.0f), FunCallInst("min_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", Float(0.1f), LoadVarInst(Address(fSlow5, kStack))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow10, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow11, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow12, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow13, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow14, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow18, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow20, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow21, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow23, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	DeclareVarInst("float", fSlow25, kStack, BinopInst("*", Float(0.5f), LoadVarInst(Address(fSlow1, kStack))))
	DeclareVarInst("float", fSlow26, kStack, BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fSlow3, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("int", iTemp0, kStack, BinopInst("+", Int32(12345), BinopInst("*", Int32(1103515245), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
			DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(iTemp0, kStack))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fSlow5, kStack)), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp2, kStack))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp4, kStack, FunCallInst("min_f", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp5, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp3, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])))
			StoreVarInst(Address(iVec0, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.95454544f)), BinopInst("<", Float(0.95454544f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), BinopInst("*", Float(0.039909296f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec0, kStruct)[Int32(0)]), LoadVarInst(Address(iVec0, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(24)), Int32(31))]))
			StoreVarInst(Address(iVec2, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.59090906f)), BinopInst("<", Float(0.59090906f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), BinopInst("*", Float(0.022921871f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec2, kStruct)[Int32(0)]), LoadVarInst(Address(iVec2, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fRec3, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec4, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(42)), Int32(63))]))
			StoreVarInst(Address(iVec4, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.22727273f)), BinopInst("<", Float(0.22727273f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), BinopInst("*", Float(0.013165158f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec4, kStruct)[Int32(0)]), LoadVarInst(Address(iVec4, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fRec5, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec6, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(74)), Int32(127))]))
			StoreVarInst(Address(iVec6, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.8636364f)), BinopInst("<", Float(0.8636364f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), BinopInst("*", Float(0.03474306f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec6, kStruct)[Int32(0)]), LoadVarInst(Address(iVec6, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec8, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(27)), Int32(31))]))
			StoreVarInst(Address(iVec8, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.5f)), BinopInst("<", Float(0.5f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec10, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), BinopInst("*", Float(0.019954648f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec8, kStruct)[Int32(0)]), LoadVarInst(Address(iVec8, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), LoadVarInst(Address(fRec9, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec10, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(49)), Int32(63))]))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("*", Float(0.70710677f), LoadVarInst(Address(fRec9, kStruct)[Int32(0)])))
			StoreVarInst(Address(iVec10, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.13636364f)), BinopInst("<", Float(0.13636364f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), BinopInst("*", Float(0.011460936f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec10, kStruct)[Int32(0)]), LoadVarInst(Address(iVec10, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), LoadVarInst(Address(fRec11, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec12, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec11, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(86)), Int32(127))]))
			StoreVarInst(Address(iVec12, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.77272725f)), BinopInst("<", Float(0.77272725f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), BinopInst("*", Float(0.030245591f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec12, kStruct)[Int32(0)]), LoadVarInst(Address(iVec12, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), BinopInst("+", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), LoadVarInst(Address(fRec13, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec14, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec13, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(32)), Int32(63))]))
			StoreVarInst(Address(iVec14, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.4090909f)), BinopInst("<", Float(0.4090909f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec16, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), BinopInst("*", Float(0.01737153f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec14, kStruct)[Int32(0)]), LoadVarInst(Address(iVec14, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), BinopInst("+", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), LoadVarInst(Address(fRec15, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec16, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec15, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(56)), Int32(63))]))
			StoreVarInst(Address(iVec16, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.045454547f)), BinopInst("<", Float(0.045454547f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec18, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), BinopInst("*", Float(0.009977324f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec16, kStruct)[Int32(0)]), LoadVarInst(Address(iVec16, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), LoadVarInst(Address(fRec17, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec18, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec17, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(99)), Int32(127))]))
			StoreVarInst(Address(iVec18, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.6818182f)), BinopInst("<", Float(0.6818182f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec20, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), BinopInst("*", Float(0.026330316f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec18, kStruct)[Int32(0)]), LoadVarInst(Address(iVec18, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec19, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), BinopInst("+", LoadVarInst(Address(fRec19, kStruct)[Int32(1)]), LoadVarInst(Address(fRec19, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec20, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec19, kStruct)[Int32(0)], LoadVarInst(Address(fVec19, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(36)), Int32(63))]))
			StoreVarInst(Address(iVec20, kStruct)[Int32(0)], BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp4, kStack)), Float(0.3181818f)), BinopInst("<", Float(0.3181818f), LoadVarInst(Address(fTemp5, kStack)))))
			StoreVarInst(Address(fRec22, kStruct)[Int32(0)], BinopInst("+", BinopInst("-", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), BinopInst("*", Float(0.0151227955f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), Float(0.0f))))), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iVec20, kStruct)[Int32(0)]), LoadVarInst(Address(iVec20, kStruct)[Int32(1)]))), Float(0.0f)))))
			StoreVarInst(Address(fVec21, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStruct)[Int32(1)]), LoadVarInst(Address(fRec21, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), BinopInst("*", LoadVarInst(Address(fTemp1, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec22, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec21, kStruct)[Int32(0)], LoadVarInst(Address(fVec21, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(65)), Int32(127))]))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fRec7, kStruct)[Int32(0)])), LoadVarInst(Address(fTemp6, kStack))), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fRec11, kStruct)[Int32(0)])))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fRec13, kStruct)[Int32(0)])), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))), BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))), BinopInst("+", BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fRec19, kStruct)[Int32(0)])), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fRec21, kStruct)[Int32(0)])))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6, kStack)), BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))), BinopInst("+", BinopInst("+", BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fRec17, kStruct)[Int32(0)])), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fRec7, kStruct)[Int32(0)])))), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fRec11, kStruct)[Int32(0)])), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))), BinopInst("+", BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fRec5, kStruct)[Int32(0)])), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fRec19, kStruct)[Int32(0)])))))))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec2, kStruct)[Int32(1)], LoadVarInst(Address(iVec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec4, kStruct)[Int32(1)], LoadVarInst(Address(iVec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(2)], LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec6, kStruct)[Int32(1)], LoadVarInst(Address(iVec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(2)], LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec8, kStruct)[Int32(1)], LoadVarInst(Address(iVec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(2)], LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec10, kStruct)[Int32(1)], LoadVarInst(Address(iVec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(2)], LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec12, kStruct)[Int32(1)], LoadVarInst(Address(iVec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(2)], LoadVarInst(Address(fRec13, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec14, kStruct)[Int32(1)], LoadVarInst(Address(iVec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(2)], LoadVarInst(Address(fRec15, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec16, kStruct)[Int32(1)], LoadVarInst(Address(iVec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(2)], LoadVarInst(Address(fRec17, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec18, kStruct)[Int32(1)], LoadVarInst(Address(iVec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(2)], LoadVarInst(Address(fRec19, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec20, kStruct)[Int32(1)], LoadVarInst(Address(iVec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(2)], LoadVarInst(Address(fRec21, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 96 bytes
Heap size real = 3832 bytes
Total heap size = 3936 bytes
Stack size in compute = 124 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec9 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec11 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec13 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec15 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec17 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec19 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec21 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec9 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec11 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec13 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec15 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec17 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec19 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec21 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec2 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = iVec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec1 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = IOTA0 size = 1 size_bytes = 4 read = 23 write = 1 ratio = 24
Field = fVec1 size = 32 size_bytes = 128 read = 1 write = 1 ratio = 0.0625
Field = fRec0 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec4 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec3 size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec3 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec6 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec5 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec5 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec8 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec7 size = 32 size_bytes = 128 read = 1 write = 1 ratio = 0.0625
Field = fRec7 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec8 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec10 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec9 size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec9 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = iVec10 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec12 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec11 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec11 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec12 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec14 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec13 size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec13 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec14 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec16 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec15 size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec15 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec16 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec18 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec17 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec17 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec18 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec20 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec19 size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec19 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec20 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec22 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec21 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec21 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            2538
  eval() cache hits:       405 (15.9574%)
  eval() cache misses:     2133
  Loop detector calls:     2133
  Stack detector calls:    2133

--- Phase 3: Propagation ---
  propagate() calls:       1813
  propagate() cache hits:  268 (14.7821%)
  propagate() cache misses:1545

--- Box Type Computation ---
  getBoxType() calls:      3479
  getBoxType() cache hits: 2511 (72.1759%)
  getBoxType() computed:   968

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       192

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           13424
  Trees reused (hash):     28087 (67.6616% reuse rate)
  Property set ops:        5268
  Property get ops:        23116

--- Iteration Constructs ---
  par() iterations:        11
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
