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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("int[2]", iRec1)("FAUSTFLOAT", fHslider2)("float[2]", fRec3)("int[2]", iVec0)("float[2]", fRec2)("int", IOTA0)("float[128]", fVec1)("float[3]", fRec0)("int[2]", iVec2)("float[2]", fRec5)("float[128]", fVec3)("float[3]", fRec4)("int[2]", iVec4)("float[2]", fRec7)("float[128]", fVec5)("float[3]", fRec6)("int[2]", iVec6)("float[2]", fRec9)("float[128]", fVec7)("float[3]", fRec8)("int[2]", iVec8)("float[2]", fRec11)("float[64]", fVec9)("float[3]", fRec10)("int[2]", iVec10)("float[2]", fRec13)("float[64]", fVec11)("float[3]", fRec12)("int[2]", iVec12)("float[2]", fRec15)("float[64]", fVec13)("float[3]", fRec14)("int[2]", iVec14)("float[2]", fRec17)("float[64]", fVec15)("float[3]", fRec16)("int[2]", iVec16)("float[2]", fRec19)("float[64]", fVec17)("float[3]", fRec18)("int[2]", iVec18)("float[2]", fRec21)("float[32]", fVec19)("float[3]", fRec20)("int[2]", iVec20)("float[2]", fRec23)("float[32]", fVec21)("float[3]", fRec22)("int", fSampleRate)>)

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
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.43f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec1, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(128))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(3))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2, kStruct)[LoadVarInst(Address(l6, kLoop))], Int32(0))
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
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(128))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(3))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec4, kStruct)[LoadVarInst(Address(l10, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(128))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(3))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec6, kStruct)[LoadVarInst(Address(l14, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(128))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(3))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec8, kStruct)[LoadVarInst(Address(l18, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(64))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(3))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec10, kStruct)[LoadVarInst(Address(l22, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(64))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(3))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec12, kStruct)[LoadVarInst(Address(l26, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(64))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(3))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec14, kStruct)[LoadVarInst(Address(l30, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(64))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(3))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec16, kStruct)[LoadVarInst(Address(l34, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(64))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(3))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec18, kStruct)[LoadVarInst(Address(l38, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(32))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(3))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec20, kStruct)[LoadVarInst(Address(l42, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(32))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(3))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 5 Store = 0 Binop = 4 [ { Real(*) = 3 } { Real(-) = 1 } ] Mathop = 1 [ { mydsp_faustpower2_f = 1 } ] Numbers = 6 Declare = 5 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.5f), BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(4.656613e-10f), FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(0.1f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 259 Store = 96 Binop = 246 [ { Int(&) = 33 } { Int(*) = 1 } { Int(+) = 3 } { Int(-) = 22 } { Int(<) = 1 } { Real(*) = 66 } { Real(+) = 54 } { Real(-) = 11 } { Real(<) = 22 } { Real(>) = 33 } ] Mathop = 2 [ { max_f = 1 } { min_f = 1 } ] Numbers = 347 Declare = 16 Cast = 47 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec1, kStruct)[Int32(1)])), Int32(12345)))
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(iRec1, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow2, kStack)), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp1, kStack, FunCallInst("min_f", LoadVarInst(Address(fRec3, kStruct)[Int32(0)]), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp2, kStack, FunCallInst("max_f", LoadVarInst(Address(fRec3, kStruct)[Int32(0)]), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
		DeclareVarInst("int", iTemp3, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.045454547f)), BinopInst("<", Float(0.045454547f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp3, kStack)))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp3, kStack)), LoadVarInst(Address(iVec0, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.009977324f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(99)), Int32(127))]))
		DeclareVarInst("int", iTemp4, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.13636364f)), BinopInst("<", Float(0.13636364f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec2, kStruct)[Int32(0)], LoadVarInst(Address(iTemp4, kStack)))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp4, kStack)), LoadVarInst(Address(iVec2, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.011460936f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fRec4, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec5, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(86)), Int32(127))]))
		DeclareVarInst("int", iTemp5, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.22727273f)), BinopInst("<", Float(0.22727273f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec4, kStruct)[Int32(0)], LoadVarInst(Address(iTemp5, kStack)))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp5, kStack)), LoadVarInst(Address(iVec4, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.013165158f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fRec6, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec7, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(74)), Int32(127))]))
		DeclareVarInst("int", iTemp6, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.3181818f)), BinopInst("<", Float(0.3181818f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec6, kStruct)[Int32(0)], LoadVarInst(Address(iTemp6, kStack)))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp6, kStack)), LoadVarInst(Address(iVec6, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.0151227955f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fRec8, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec9, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(65)), Int32(127))]))
		DeclareVarInst("int", iTemp7, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.4090909f)), BinopInst("<", Float(0.4090909f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec8, kStruct)[Int32(0)], LoadVarInst(Address(iTemp7, kStack)))
		StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp7, kStack)), LoadVarInst(Address(iVec8, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.01737153f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), LoadVarInst(Address(fRec10, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec11, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec10, kStruct)[Int32(0)], LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(56)), Int32(63))]))
		DeclareVarInst("int", iTemp8, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.5f)), BinopInst("<", Float(0.5f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec10, kStruct)[Int32(0)], LoadVarInst(Address(iTemp8, kStack)))
		StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp8, kStack)), LoadVarInst(Address(iVec10, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.019954648f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), LoadVarInst(Address(fRec12, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(49)), Int32(63))]))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("*", Float(0.70710677f), LoadVarInst(Address(fRec12, kStruct)[Int32(0)])))
		DeclareVarInst("int", iTemp10, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.59090906f)), BinopInst("<", Float(0.59090906f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec12, kStruct)[Int32(0)], LoadVarInst(Address(iTemp10, kStack)))
		StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp10, kStack)), LoadVarInst(Address(iVec12, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.022921871f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fRec14, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(42)), Int32(63))]))
		DeclareVarInst("int", iTemp11, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.6818182f)), BinopInst("<", Float(0.6818182f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec14, kStruct)[Int32(0)], LoadVarInst(Address(iTemp11, kStack)))
		StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp11, kStack)), LoadVarInst(Address(iVec14, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.026330316f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), LoadVarInst(Address(fRec16, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec17, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec16, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(36)), Int32(63))]))
		DeclareVarInst("int", iTemp12, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.77272725f)), BinopInst("<", Float(0.77272725f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec16, kStruct)[Int32(0)], LoadVarInst(Address(iTemp12, kStack)))
		StoreVarInst(Address(fRec19, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec19, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp12, kStack)), LoadVarInst(Address(iVec16, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.030245591f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec19, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), LoadVarInst(Address(fRec18, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec19, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec18, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(32)), Int32(63))]))
		DeclareVarInst("int", iTemp13, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.8636364f)), BinopInst("<", Float(0.8636364f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec18, kStruct)[Int32(0)], LoadVarInst(Address(iTemp13, kStack)))
		StoreVarInst(Address(fRec21, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec21, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp13, kStack)), LoadVarInst(Address(iVec18, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.03474306f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec21, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec19, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), LoadVarInst(Address(fRec20, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec21, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec20, kStruct)[Int32(0)], LoadVarInst(Address(fVec19, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(27)), Int32(31))]))
		DeclareVarInst("int", iTemp14, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.95454544f)), BinopInst("<", Float(0.95454544f), LoadVarInst(Address(fTemp2, kStack)))))
		StoreVarInst(Address(iVec20, kStruct)[Int32(0)], LoadVarInst(Address(iTemp14, kStack)))
		StoreVarInst(Address(fRec23, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec23, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp14, kStack)), LoadVarInst(Address(iVec20, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.039909296f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec23, kStruct)[Int32(1)]), Float(0.0f))))))
		StoreVarInst(Address(fVec21, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), LoadVarInst(Address(fRec22, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec23, kStruct)[Int32(0)]), Float(0.0f)))))))
		StoreVarInst(Address(fRec22, kStruct)[Int32(0)], LoadVarInst(Address(fVec21, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(24)), Int32(31))]))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))), LoadVarInst(Address(fTemp9, kStack))), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))), BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))), BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))), BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))), BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fRec22, kStruct)[Int32(0)])))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp9, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))), BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fRec10, kStruct)[Int32(0)])))), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))), BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fRec22, kStruct)[Int32(0)])))))
		StoreVarInst(Address(iRec1, kStruct)[Int32(1)], LoadVarInst(Address(iRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec2, kStruct)[Int32(1)], LoadVarInst(Address(iVec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(2)], LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec4, kStruct)[Int32(1)], LoadVarInst(Address(iVec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(2)], LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec6, kStruct)[Int32(1)], LoadVarInst(Address(iVec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(2)], LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec8, kStruct)[Int32(1)], LoadVarInst(Address(iVec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(2)], LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec10, kStruct)[Int32(1)], LoadVarInst(Address(iVec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(2)], LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec12, kStruct)[Int32(1)], LoadVarInst(Address(iVec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(2)], LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec14, kStruct)[Int32(1)], LoadVarInst(Address(iVec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(2)], LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec16, kStruct)[Int32(1)], LoadVarInst(Address(iVec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(2)], LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec18, kStruct)[Int32(1)], LoadVarInst(Address(iVec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(2)], LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec20, kStruct)[Int32(1)], LoadVarInst(Address(iVec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(2)], LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", iRec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("int", iVec0[2], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec1[128], kStruct)
	DeclareVarInst("float", fRec0[3], kStruct)
	DeclareVarInst("int", iVec2[2], kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("float", fVec3[128], kStruct)
	DeclareVarInst("float", fRec4[3], kStruct)
	DeclareVarInst("int", iVec4[2], kStruct)
	DeclareVarInst("float", fRec7[2], kStruct)
	DeclareVarInst("float", fVec5[128], kStruct)
	DeclareVarInst("float", fRec6[3], kStruct)
	DeclareVarInst("int", iVec6[2], kStruct)
	DeclareVarInst("float", fRec9[2], kStruct)
	DeclareVarInst("float", fVec7[128], kStruct)
	DeclareVarInst("float", fRec8[3], kStruct)
	DeclareVarInst("int", iVec8[2], kStruct)
	DeclareVarInst("float", fRec11[2], kStruct)
	DeclareVarInst("float", fVec9[64], kStruct)
	DeclareVarInst("float", fRec10[3], kStruct)
	DeclareVarInst("int", iVec10[2], kStruct)
	DeclareVarInst("float", fRec13[2], kStruct)
	DeclareVarInst("float", fVec11[64], kStruct)
	DeclareVarInst("float", fRec12[3], kStruct)
	DeclareVarInst("int", iVec12[2], kStruct)
	DeclareVarInst("float", fRec15[2], kStruct)
	DeclareVarInst("float", fVec13[64], kStruct)
	DeclareVarInst("float", fRec14[3], kStruct)
	DeclareVarInst("int", iVec14[2], kStruct)
	DeclareVarInst("float", fRec17[2], kStruct)
	DeclareVarInst("float", fVec15[64], kStruct)
	DeclareVarInst("float", fRec16[3], kStruct)
	DeclareVarInst("int", iVec16[2], kStruct)
	DeclareVarInst("float", fRec19[2], kStruct)
	DeclareVarInst("float", fVec17[64], kStruct)
	DeclareVarInst("float", fRec18[3], kStruct)
	DeclareVarInst("int", iVec18[2], kStruct)
	DeclareVarInst("float", fRec21[2], kStruct)
	DeclareVarInst("float", fVec19[32], kStruct)
	DeclareVarInst("float", fRec20[3], kStruct)
	DeclareVarInst("int", iVec20[2], kStruct)
	DeclareVarInst("float", fRec23[2], kStruct)
	DeclareVarInst("float", fVec21[32], kStruct)
	DeclareVarInst("float", fRec22[3], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.43f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec1, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(128))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(3))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2, kStruct)[LoadVarInst(Address(l6, kLoop))], Int32(0))
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
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(128))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(3))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec4, kStruct)[LoadVarInst(Address(l10, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(128))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(3))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec6, kStruct)[LoadVarInst(Address(l14, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(128))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(3))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec8, kStruct)[LoadVarInst(Address(l18, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(64))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(3))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec10, kStruct)[LoadVarInst(Address(l22, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(64))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(3))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec12, kStruct)[LoadVarInst(Address(l26, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(64))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(3))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec14, kStruct)[LoadVarInst(Address(l30, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(64))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(3))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec16, kStruct)[LoadVarInst(Address(l34, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(64))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(3))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec18, kStruct)[LoadVarInst(Address(l38, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(32))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(3))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec20, kStruct)[LoadVarInst(Address(l42, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(32))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(3))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.5f), BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("*", Float(4.656613e-10f), FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(0.1f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec1, kStruct)[Int32(1)])), Int32(12345)))
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(iRec1, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow2, kStack)), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp1, kStack, FunCallInst("min_f", LoadVarInst(Address(fRec3, kStruct)[Int32(0)]), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp2, kStack, FunCallInst("max_f", LoadVarInst(Address(fRec3, kStruct)[Int32(0)]), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))
			DeclareVarInst("int", iTemp3, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.045454547f)), BinopInst("<", Float(0.045454547f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp3, kStack)))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp3, kStack)), LoadVarInst(Address(iVec0, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.009977324f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(99)), Int32(127))]))
			DeclareVarInst("int", iTemp4, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.13636364f)), BinopInst("<", Float(0.13636364f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec2, kStruct)[Int32(0)], LoadVarInst(Address(iTemp4, kStack)))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp4, kStack)), LoadVarInst(Address(iVec2, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.011460936f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fRec4, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec5, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(86)), Int32(127))]))
			DeclareVarInst("int", iTemp5, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.22727273f)), BinopInst("<", Float(0.22727273f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec4, kStruct)[Int32(0)], LoadVarInst(Address(iTemp5, kStack)))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp5, kStack)), LoadVarInst(Address(iVec4, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.013165158f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fRec6, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec7, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(74)), Int32(127))]))
			DeclareVarInst("int", iTemp6, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.3181818f)), BinopInst("<", Float(0.3181818f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec6, kStruct)[Int32(0)], LoadVarInst(Address(iTemp6, kStack)))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp6, kStack)), LoadVarInst(Address(iVec6, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.0151227955f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fRec8, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec9, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(65)), Int32(127))]))
			DeclareVarInst("int", iTemp7, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.4090909f)), BinopInst("<", Float(0.4090909f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec8, kStruct)[Int32(0)], LoadVarInst(Address(iTemp7, kStack)))
			StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp7, kStack)), LoadVarInst(Address(iVec8, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.01737153f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), LoadVarInst(Address(fRec10, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec11, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec10, kStruct)[Int32(0)], LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(56)), Int32(63))]))
			DeclareVarInst("int", iTemp8, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.5f)), BinopInst("<", Float(0.5f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec10, kStruct)[Int32(0)], LoadVarInst(Address(iTemp8, kStack)))
			StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp8, kStack)), LoadVarInst(Address(iVec10, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.019954648f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), LoadVarInst(Address(fRec12, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec13, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(49)), Int32(63))]))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("*", Float(0.70710677f), LoadVarInst(Address(fRec12, kStruct)[Int32(0)])))
			DeclareVarInst("int", iTemp10, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.59090906f)), BinopInst("<", Float(0.59090906f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec12, kStruct)[Int32(0)], LoadVarInst(Address(iTemp10, kStack)))
			StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp10, kStack)), LoadVarInst(Address(iVec12, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.022921871f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fRec14, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(42)), Int32(63))]))
			DeclareVarInst("int", iTemp11, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.6818182f)), BinopInst("<", Float(0.6818182f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec14, kStruct)[Int32(0)], LoadVarInst(Address(iTemp11, kStack)))
			StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp11, kStack)), LoadVarInst(Address(iVec14, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.026330316f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), LoadVarInst(Address(fRec16, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec17, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec16, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(36)), Int32(63))]))
			DeclareVarInst("int", iTemp12, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.77272725f)), BinopInst("<", Float(0.77272725f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec16, kStruct)[Int32(0)], LoadVarInst(Address(iTemp12, kStack)))
			StoreVarInst(Address(fRec19, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec19, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp12, kStack)), LoadVarInst(Address(iVec16, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.030245591f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec19, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), LoadVarInst(Address(fRec18, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec19, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec18, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(32)), Int32(63))]))
			DeclareVarInst("int", iTemp13, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.8636364f)), BinopInst("<", Float(0.8636364f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec18, kStruct)[Int32(0)], LoadVarInst(Address(iTemp13, kStack)))
			StoreVarInst(Address(fRec21, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec21, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp13, kStack)), LoadVarInst(Address(iVec18, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.03474306f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec21, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec19, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), LoadVarInst(Address(fRec20, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec21, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec20, kStruct)[Int32(0)], LoadVarInst(Address(fVec19, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(27)), Int32(31))]))
			DeclareVarInst("int", iTemp14, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp1, kStack)), Float(0.95454544f)), BinopInst("<", Float(0.95454544f), LoadVarInst(Address(fTemp2, kStack)))))
			StoreVarInst(Address(iVec20, kStruct)[Int32(0)], LoadVarInst(Address(iTemp14, kStack)))
			StoreVarInst(Address(fRec23, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec23, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", CastInst("float", BinopInst("-", LoadVarInst(Address(iTemp14, kStack)), LoadVarInst(Address(iVec20, kStruct)[Int32(1)]))), Float(0.0f)))), BinopInst("*", Float(0.039909296f), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec23, kStruct)[Int32(1)]), Float(0.0f))))))
			StoreVarInst(Address(fVec21, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), LoadVarInst(Address(fRec22, kStruct)[Int32(2)]))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), BinopInst("*", LoadVarInst(Address(fTemp0, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec23, kStruct)[Int32(0)]), Float(0.0f)))))))
			StoreVarInst(Address(fRec22, kStruct)[Int32(0)], LoadVarInst(Address(fVec21, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(24)), Int32(31))]))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))), LoadVarInst(Address(fTemp9, kStack))), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))), BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))), BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))), BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))), BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fRec22, kStruct)[Int32(0)])))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp9, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))), BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fRec10, kStruct)[Int32(0)])))), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))), BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fRec22, kStruct)[Int32(0)])))))
			StoreVarInst(Address(iRec1, kStruct)[Int32(1)], LoadVarInst(Address(iRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec2, kStruct)[Int32(1)], LoadVarInst(Address(iVec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(2)], LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec4, kStruct)[Int32(1)], LoadVarInst(Address(iVec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(2)], LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec6, kStruct)[Int32(1)], LoadVarInst(Address(iVec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(2)], LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec8, kStruct)[Int32(1)], LoadVarInst(Address(iVec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(2)], LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec10, kStruct)[Int32(1)], LoadVarInst(Address(iVec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(2)], LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec12, kStruct)[Int32(1)], LoadVarInst(Address(iVec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(2)], LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec14, kStruct)[Int32(1)], LoadVarInst(Address(iVec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(2)], LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec16, kStruct)[Int32(1)], LoadVarInst(Address(iVec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(2)], LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec18, kStruct)[Int32(1)], LoadVarInst(Address(iVec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(2)], LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec20, kStruct)[Int32(1)], LoadVarInst(Address(iVec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(2)], LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 96 bytes
Heap size real = 3824 bytes
Total heap size = 3928 bytes
Stack size in compute = 28 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec10 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec12 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec14 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec16 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec18 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19 size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fRec20 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21 size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fRec22 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec10 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec12 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec14 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec16 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec18 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19 size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fRec20 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = iVec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21 size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fRec22 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 6 write = 2 ratio = 4
Field = iVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec2 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = IOTA0 size = 1 size_bytes = 4 read = 23 write = 1 ratio = 24
Field = fVec1 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec0 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec5 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec3 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec4 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec4 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec7 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec5 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec6 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec6 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec9 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec7 size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec8 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec8 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec11 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec9 size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec10 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec10 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec13 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec11 size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec12 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = iVec12 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec15 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec13 size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec14 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec14 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec17 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec15 size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec16 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec16 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec19 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec17 size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec18 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec18 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec21 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec19 size = 32 size_bytes = 128 read = 1 write = 1 ratio = 0.0625
Field = fRec20 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = iVec20 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec23 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fVec21 size = 32 size_bytes = 128 read = 1 write = 1 ratio = 0.0625
Field = fRec22 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
