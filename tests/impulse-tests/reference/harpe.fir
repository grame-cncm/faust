======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Harpe")
	AddMetaDeclareInst(fHslider1, "osc", "/1/fader3")
	AddHorizontalSlider("attenuation", fHslider1, 0.0f, 0.0f, 0.01f, 0.001f)
	AddMetaDeclareInst(fHslider0, "osc", "/accxyz/1 -10 10")
	AddHorizontalSlider("hand", fHslider0, 0.43f, 0.0f, 1.0f, 0.01f)
	AddMetaDeclareInst(fHslider2, "osc", "/accxyz/0 -10 10")
	AddMetaDeclareInst(fHslider2, "unit", "f")
	AddHorizontalSlider("level", fHslider2, 0.5f, 0.0f, 1.0f, 0.01f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("float[2]", fRec0SE)("float[4]", fVec1SE)("FAUSTFLOAT", fHslider0)("float[2]", fVec2SE)("float[2]", fVec3SE)("int[2]", iVec6SE)("FAUSTFLOAT", fHslider1)("FAUSTFLOAT", fHslider2)("int[2]", iVec9SI)("float[2]", fVec11SE)("float[128]", fVec0SE)("float[2]", fRec4SE)("float[4]", fVec16SE)("int[2]", iVec17SE)("float[2]", fVec20SE)("float[128]", fVec15SE)("float[2]", fRec6SE)("float[4]", fVec25SE)("int[2]", iVec26SE)("float[2]", fVec29SE)("float[128]", fVec24SE)("float[2]", fRec8SE)("float[4]", fVec34SE)("int[2]", iVec35SE)("float[2]", fVec38SE)("float[128]", fVec33SE)("float[2]", fRec10SE)("float[4]", fVec43SE)("int[2]", iVec44SE)("float[2]", fVec47SE)("float[64]", fVec42SE)("float[2]", fRec12SE)("float[4]", fVec52SE)("int[2]", iVec53SE)("float[2]", fVec56SE)("float[64]", fVec51SE)("float[2]", fRec14SE)("float[4]", fVec61SE)("int[2]", iVec62SE)("float[2]", fVec65SE)("float[64]", fVec60SE)("float[2]", fRec16SE)("float[4]", fVec70SE)("int[2]", iVec71SE)("float[2]", fVec74SE)("float[64]", fVec69SE)("float[2]", fRec18SE)("float[4]", fVec79SE)("int[2]", iVec80SE)("float[2]", fVec83SE)("float[64]", fVec78SE)("float[2]", fRec20SE)("float[4]", fVec88SE)("int[2]", iVec89SE)("float[2]", fVec92SE)("float[32]", fVec87SE)("float[2]", fRec22SE)("float[4]", fVec97SE)("int[2]", iVec98SE)("float[2]", fVec101SE)("float[32]", fVec96SE)("int", fSampleRate)>)

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
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.43f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
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
			StoreVarInst(Address(fRec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
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
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec6SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec9SI, kStruct)[LoadVarInst(Address(l5, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(128))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(4))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec17SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(128))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(4))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec26SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(128))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(4))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec35SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec38SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(128))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec33SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(4))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec43SE, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec44SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec47SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(64))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec42SE, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12SE, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(4))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec52SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec53SE, kStruct)[LoadVarInst(Address(l30, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec56SE, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(64))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec51SE, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(4))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec61SE, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec62SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec65SE, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(64))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec60SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16SE, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(4))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec70SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec71SE, kStruct)[LoadVarInst(Address(l40, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec74SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(64))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec69SE, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18SE, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(4))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec79SE, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec80SE, kStruct)[LoadVarInst(Address(l45, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec83SE, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(64))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec78SE, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20SE, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(4))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec88SE, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec89SE, kStruct)[LoadVarInst(Address(l50, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec92SE, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(32))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec87SE, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22SE, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(4))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec97SE, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec98SE, kStruct)[LoadVarInst(Address(l55, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(2))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec101SE, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(32))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec96SE, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 5 Store = 0 Binop = 4 [ { Real(*) = 3 } { Real(+) = 1 } ] Mathop = 1 [ { mydsp_faustpower2_f = 1 } ] Numbers = 6 Declare = 5 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("*", Float(0.1f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("*", Float(0.5f), BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", Float(4.656613e-10f), FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 378 Store = 62 Binop = 423 [ { Int(&) = 163 } { Int(*) = 1 } { Int(+) = 14 } { Int(-) = 58 } { Int(<) = 1 } { Real(*) = 66 } { Real(+) = 65 } { Real(<) = 22 } { Real(>) = 33 } ] Mathop = 2 [ { max_f = 1 } { min_f = 1 } ] Numbers = 303 Declare = 39 Cast = 47 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(99)), Int32(127))]))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp2SE, kStack, FunCallInst("min_f", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))
		DeclareVarInst("float", fTemp3SE, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))
		DeclareVarInst("int", iTemp4SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.045454547f)), BinopInst("<", Float(0.045454547f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp4SE, kStack)))
		StoreVarInst(Address(iVec9SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec9SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
		DeclareVarInst("float", fTemp5SI, kStack, CastInst("float", LoadVarInst(Address(iVec9SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		DeclareVarInst("float", fTemp6SE, kStack, LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp4SE, kStack)), MinusInst(LoadVarInst(Address(iVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.009977324f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp6SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		StoreVarInst(Address(fRec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(86)), Int32(127))]))
		StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp7SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.13636364f)), BinopInst("<", Float(0.13636364f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp7SE, kStack)))
		DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp8SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp7SE, kStack)), MinusInst(LoadVarInst(Address(iVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.011460936f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp8SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		StoreVarInst(Address(fRec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(74)), Int32(127))]))
		StoreVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp9SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.22727273f)), BinopInst("<", Float(0.22727273f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp9SE, kStack)))
		DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec29SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec29SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp10SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp9SE, kStack)), MinusInst(LoadVarInst(Address(iVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.013165158f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp10SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec29SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		StoreVarInst(Address(fRec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec33SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(65)), Int32(127))]))
		StoreVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp11SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.3181818f)), BinopInst("<", Float(0.3181818f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec35SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp11SE, kStack)))
		DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp12SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp11SE, kStack)), MinusInst(LoadVarInst(Address(iVec35SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.0151227955f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp12SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec33SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		StoreVarInst(Address(fRec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(56)), Int32(63))]))
		StoreVarInst(Address(fVec43SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp13SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.4090909f)), BinopInst("<", Float(0.4090909f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec44SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp13SE, kStack)))
		DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fVec47SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec47SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp14SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp13SE, kStack)), MinusInst(LoadVarInst(Address(iVec44SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.01737153f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp14SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec43SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec47SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		StoreVarInst(Address(fRec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(49)), Int32(63))]))
		StoreVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp15SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.5f)), BinopInst("<", Float(0.5f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec53SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp15SE, kStack)))
		DeclareVarInst("float", fTemp16SE, kStack, LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp16SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp15SE, kStack)), MinusInst(LoadVarInst(Address(iVec53SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.019954648f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp16SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		StoreVarInst(Address(fRec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec60SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(42)), Int32(63))]))
		StoreVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp17SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.59090906f)), BinopInst("<", Float(0.59090906f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec62SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp17SE, kStack)))
		DeclareVarInst("float", fTemp18SE, kStack, LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp18SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp17SE, kStack)), MinusInst(LoadVarInst(Address(iVec62SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.022921871f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp18SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec60SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		StoreVarInst(Address(fRec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec69SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(36)), Int32(63))]))
		StoreVarInst(Address(fVec70SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp19SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.6818182f)), BinopInst("<", Float(0.6818182f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp19SE, kStack)))
		DeclareVarInst("float", fTemp20SE, kStack, LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp20SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp19SE, kStack)), MinusInst(LoadVarInst(Address(iVec71SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.026330316f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp20SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec69SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec70SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		StoreVarInst(Address(fRec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec78SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(32)), Int32(63))]))
		StoreVarInst(Address(fVec79SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp21SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.77272725f)), BinopInst("<", Float(0.77272725f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp21SE, kStack)))
		DeclareVarInst("float", fTemp22SE, kStack, LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp22SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp21SE, kStack)), MinusInst(LoadVarInst(Address(iVec80SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.030245591f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp22SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec78SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec79SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		StoreVarInst(Address(fRec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec87SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(27)), Int32(31))]))
		StoreVarInst(Address(fVec88SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp23SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.8636364f)), BinopInst("<", Float(0.8636364f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec89SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp23SE, kStack)))
		DeclareVarInst("float", fTemp24SE, kStack, LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp23SE, kStack)), MinusInst(LoadVarInst(Address(iVec89SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.03474306f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp24SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec87SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec88SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		StoreVarInst(Address(fRec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec96SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(24)), Int32(31))]))
		StoreVarInst(Address(fVec97SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("int", iTemp25SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.95454544f)), BinopInst("<", Float(0.95454544f), LoadVarInst(Address(fTemp3SE, kStack)))))
		StoreVarInst(Address(iVec98SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp25SE, kStack)))
		DeclareVarInst("float", fTemp26SE, kStack, LoadVarInst(Address(fVec101SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec101SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp26SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp25SE, kStack)), MinusInst(LoadVarInst(Address(iVec98SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.039909296f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp26SE, kStack)), Float(0.0f))))))
		StoreVarInst(Address(fVec96SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec22SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec97SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec101SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
		DeclareVarInst("float", fTemp27SE, kStack, LoadVarInst(Address(fRec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp28SE, kStack, LoadVarInst(Address(fRec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp29SE, kStack, LoadVarInst(Address(fRec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp30SE, kStack, LoadVarInst(Address(fRec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp31SE, kStack, LoadVarInst(Address(fRec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp32SE, kStack, BinopInst("*", Float(0.70710677f), LoadVarInst(Address(fRec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		DeclareVarInst("float", fTemp33SE, kStack, LoadVarInst(Address(fRec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp34SE, kStack, LoadVarInst(Address(fRec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp35SE, kStack, LoadVarInst(Address(fRec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp36SE, kStack, LoadVarInst(Address(fRec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp37SE, kStack, LoadVarInst(Address(fRec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fTemp27SE, kStack))), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fTemp28SE, kStack)))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fTemp29SE, kStack)))), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fTemp30SE, kStack)))), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fTemp31SE, kStack)))), LoadVarInst(Address(fTemp32SE, kStack))), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fTemp33SE, kStack)))), BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fTemp34SE, kStack)))), BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fTemp35SE, kStack)))), BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fTemp36SE, kStack)))), BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fTemp37SE, kStack))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp32SE, kStack)), BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fTemp27SE, kStack)))), BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fTemp28SE, kStack)))), BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fTemp29SE, kStack)))), BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fTemp30SE, kStack)))), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fTemp31SE, kStack)))), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fTemp33SE, kStack)))), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fTemp34SE, kStack)))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fTemp35SE, kStack)))), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fTemp36SE, kStack)))), BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fTemp37SE, kStack))))))
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
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay fRec0SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec0SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec1SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	// Recursion delay fVec2SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec2SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec3SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec6SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	// Recursion delay iVec9SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec9SI[2], kStruct)
	// Recursion delay fVec11SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec11SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0SE[128], kStruct)
	// Recursion delay fRec4SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec4SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec16SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec17SE[2], kStruct)
	// Recursion delay fVec20SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec20SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec15SE[128], kStruct)
	// Recursion delay fRec6SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec6SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec25SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec26SE[2], kStruct)
	// Recursion delay fVec29SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec29SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec24SE[128], kStruct)
	// Recursion delay fRec8SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec8SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec34SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec35SE[2], kStruct)
	// Recursion delay fVec38SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec38SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec33SE[128], kStruct)
	// Recursion delay fRec10SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec10SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec43SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec44SE[2], kStruct)
	// Recursion delay fVec47SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec47SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec42SE[64], kStruct)
	// Recursion delay fRec12SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec12SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec52SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec53SE[2], kStruct)
	// Recursion delay fVec56SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec56SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec51SE[64], kStruct)
	// Recursion delay fRec14SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec14SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec61SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec62SE[2], kStruct)
	// Recursion delay fVec65SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec65SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec60SE[64], kStruct)
	// Recursion delay fRec16SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec16SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec70SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec71SE[2], kStruct)
	// Recursion delay fVec74SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec74SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec69SE[64], kStruct)
	// Recursion delay fRec18SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec18SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec79SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec80SE[2], kStruct)
	// Recursion delay fVec83SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec83SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec78SE[64], kStruct)
	// Recursion delay fRec20SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec20SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec88SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec89SE[2], kStruct)
	// Recursion delay fVec92SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec92SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec87SE[32], kStruct)
	// Recursion delay fRec22SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec22SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec97SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("int", iVec98SE[2], kStruct)
	// Recursion delay fVec101SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec101SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec96SE[32], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.43f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
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
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec6SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec9SI, kStruct)[LoadVarInst(Address(l5, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(128))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(4))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec17SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(128))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(4))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec26SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(128))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(4))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec35SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec38SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(128))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec33SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(4))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec43SE, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec44SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec47SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(64))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec42SE, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12SE, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(4))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec52SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec53SE, kStruct)[LoadVarInst(Address(l30, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec56SE, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(64))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec51SE, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(4))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec61SE, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec62SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec65SE, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(64))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec60SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16SE, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(4))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec70SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec71SE, kStruct)[LoadVarInst(Address(l40, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec74SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(64))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec69SE, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18SE, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(4))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec79SE, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec80SE, kStruct)[LoadVarInst(Address(l45, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec83SE, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(64))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec78SE, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20SE, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(4))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec88SE, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec89SE, kStruct)[LoadVarInst(Address(l50, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec92SE, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(32))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec87SE, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22SE, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(4))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec97SE, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec98SE, kStruct)[LoadVarInst(Address(l55, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(2))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec101SE, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(32))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec96SE, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("*", Float(0.1f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("*", Float(0.5f), BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", Float(4.656613e-10f), FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(99)), Int32(127))]))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp1SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp2SE, kStack, FunCallInst("min_f", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))
			DeclareVarInst("float", fTemp3SE, kStack, FunCallInst("max_f", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))
			DeclareVarInst("int", iTemp4SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.045454547f)), BinopInst("<", Float(0.045454547f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp4SE, kStack)))
			StoreVarInst(Address(iVec9SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec9SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
			DeclareVarInst("float", fTemp5SI, kStack, CastInst("float", LoadVarInst(Address(iVec9SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			DeclareVarInst("float", fTemp6SE, kStack, LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp6SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp4SE, kStack)), MinusInst(LoadVarInst(Address(iVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.009977324f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp6SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			StoreVarInst(Address(fRec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(86)), Int32(127))]))
			StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp7SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.13636364f)), BinopInst("<", Float(0.13636364f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp7SE, kStack)))
			DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp8SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp7SE, kStack)), MinusInst(LoadVarInst(Address(iVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.011460936f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp8SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			StoreVarInst(Address(fRec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(74)), Int32(127))]))
			StoreVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp9SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.22727273f)), BinopInst("<", Float(0.22727273f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp9SE, kStack)))
			DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec29SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec29SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp10SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp9SE, kStack)), MinusInst(LoadVarInst(Address(iVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.013165158f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp10SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec29SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			StoreVarInst(Address(fRec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec33SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(65)), Int32(127))]))
			StoreVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp11SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.3181818f)), BinopInst("<", Float(0.3181818f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec35SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp11SE, kStack)))
			DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp12SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp11SE, kStack)), MinusInst(LoadVarInst(Address(iVec35SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.0151227955f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp12SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec33SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(127))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			StoreVarInst(Address(fRec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(56)), Int32(63))]))
			StoreVarInst(Address(fVec43SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp13SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.4090909f)), BinopInst("<", Float(0.4090909f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec44SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp13SE, kStack)))
			DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fVec47SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec47SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp14SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp13SE, kStack)), MinusInst(LoadVarInst(Address(iVec44SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.01737153f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp14SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec43SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec47SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			StoreVarInst(Address(fRec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(49)), Int32(63))]))
			StoreVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp15SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.5f)), BinopInst("<", Float(0.5f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec53SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp15SE, kStack)))
			DeclareVarInst("float", fTemp16SE, kStack, LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp16SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp15SE, kStack)), MinusInst(LoadVarInst(Address(iVec53SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.019954648f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp16SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			StoreVarInst(Address(fRec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec60SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(42)), Int32(63))]))
			StoreVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp17SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.59090906f)), BinopInst("<", Float(0.59090906f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec62SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp17SE, kStack)))
			DeclareVarInst("float", fTemp18SE, kStack, LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp18SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp17SE, kStack)), MinusInst(LoadVarInst(Address(iVec62SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.022921871f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp18SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec60SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			StoreVarInst(Address(fRec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec69SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(36)), Int32(63))]))
			StoreVarInst(Address(fVec70SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp19SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.6818182f)), BinopInst("<", Float(0.6818182f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp19SE, kStack)))
			DeclareVarInst("float", fTemp20SE, kStack, LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp20SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp19SE, kStack)), MinusInst(LoadVarInst(Address(iVec71SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.026330316f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp20SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec69SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec70SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			StoreVarInst(Address(fRec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec78SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(32)), Int32(63))]))
			StoreVarInst(Address(fVec79SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp21SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.77272725f)), BinopInst("<", Float(0.77272725f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp21SE, kStack)))
			DeclareVarInst("float", fTemp22SE, kStack, LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp22SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp21SE, kStack)), MinusInst(LoadVarInst(Address(iVec80SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.030245591f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp22SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec78SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(63))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec79SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			StoreVarInst(Address(fRec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec87SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(27)), Int32(31))]))
			StoreVarInst(Address(fVec88SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp23SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.8636364f)), BinopInst("<", Float(0.8636364f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec89SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp23SE, kStack)))
			DeclareVarInst("float", fTemp24SE, kStack, LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp24SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp23SE, kStack)), MinusInst(LoadVarInst(Address(iVec89SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.03474306f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp24SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec87SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec88SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			StoreVarInst(Address(fRec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec96SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(24)), Int32(31))]))
			StoreVarInst(Address(fVec97SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fRec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("int", iTemp25SE, kStack, BinopInst("&", BinopInst("<", LoadVarInst(Address(fTemp2SE, kStack)), Float(0.95454544f)), BinopInst("<", Float(0.95454544f), LoadVarInst(Address(fTemp3SE, kStack)))))
			StoreVarInst(Address(iVec98SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(iTemp25SE, kStack)))
			DeclareVarInst("float", fTemp26SE, kStack, LoadVarInst(Address(fVec101SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec101SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp26SE, kStack)), CastInst("float", BinopInst(">", CastInst("float", BinopInst("+", LoadVarInst(Address(iTemp25SE, kStack)), MinusInst(LoadVarInst(Address(iVec98SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])))), Float(0.0f)))), BinopInst("*", Float(-0.039909296f), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp26SE, kStack)), Float(0.0f))))))
			StoreVarInst(Address(fVec96SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(31))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), BinopInst("+", LoadVarInst(Address(fRec22SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec97SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", LoadVarInst(Address(fTemp5SI, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fVec101SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f)))))))
			DeclareVarInst("float", fTemp27SE, kStack, LoadVarInst(Address(fRec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp28SE, kStack, LoadVarInst(Address(fRec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp29SE, kStack, LoadVarInst(Address(fRec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp30SE, kStack, LoadVarInst(Address(fRec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp31SE, kStack, LoadVarInst(Address(fRec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp32SE, kStack, BinopInst("*", Float(0.70710677f), LoadVarInst(Address(fRec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			DeclareVarInst("float", fTemp33SE, kStack, LoadVarInst(Address(fRec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp34SE, kStack, LoadVarInst(Address(fRec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp35SE, kStack, LoadVarInst(Address(fRec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp36SE, kStack, LoadVarInst(Address(fRec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp37SE, kStack, LoadVarInst(Address(fRec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fTemp27SE, kStack))), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fTemp28SE, kStack)))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fTemp29SE, kStack)))), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fTemp30SE, kStack)))), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fTemp31SE, kStack)))), LoadVarInst(Address(fTemp32SE, kStack))), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fTemp33SE, kStack)))), BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fTemp34SE, kStack)))), BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fTemp35SE, kStack)))), BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fTemp36SE, kStack)))), BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fTemp37SE, kStack))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp32SE, kStack)), BinopInst("*", Float(0.21320072f), LoadVarInst(Address(fTemp27SE, kStack)))), BinopInst("*", Float(0.36927447f), LoadVarInst(Address(fTemp28SE, kStack)))), BinopInst("*", Float(0.4767313f), LoadVarInst(Address(fTemp29SE, kStack)))), BinopInst("*", Float(0.56407607f), LoadVarInst(Address(fTemp30SE, kStack)))), BinopInst("*", Float(0.6396021f), LoadVarInst(Address(fTemp31SE, kStack)))), BinopInst("*", Float(0.76870614f), LoadVarInst(Address(fTemp33SE, kStack)))), BinopInst("*", Float(0.8257228f), LoadVarInst(Address(fTemp34SE, kStack)))), BinopInst("*", Float(0.87904906f), LoadVarInst(Address(fTemp35SE, kStack)))), BinopInst("*", Float(0.9293204f), LoadVarInst(Address(fTemp36SE, kStack)))), BinopInst("*", Float(0.9770084f), LoadVarInst(Address(fTemp37SE, kStack))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 96 bytes
Heap size real = 3964 bytes
Total heap size = 4068 bytes
Stack size in compute = 28 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec9SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15SE size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec25SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec29SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec34SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec35SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec38SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec33SE size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec43SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec44SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec47SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec42SE size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec52SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec53SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec56SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec51SE size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec14SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec61SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec62SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec65SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec60SE size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec70SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec71SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec74SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec69SE size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec18SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec79SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec80SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec83SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec78SE size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec88SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec89SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec92SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec87SE size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fRec22SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec97SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec98SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec101SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec96SE size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec9SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15SE size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec25SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec29SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec34SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec35SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec38SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec33SE size = 128 size_bytes = 512 read = 0 write = 0 ratio = 0
Field = fRec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec43SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec44SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec47SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec42SE size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec52SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec53SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec56SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec51SE size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec14SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec61SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec62SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec65SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec60SE size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec70SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec71SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec74SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec69SE size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec18SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec79SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec80SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec83SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec78SE size = 64 size_bytes = 256 read = 0 write = 0 ratio = 0
Field = fRec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec88SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec89SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec92SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec87SE size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fRec22SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec97SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = iVec98SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec101SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec96SE size = 32 size_bytes = 128 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 153 write = 1 ratio = 154
Field = fRec0SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec1SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec3SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = iVec6SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec9SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec11SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec0SE size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec4SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec16SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = iVec17SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec20SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec15SE size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec6SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec25SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = iVec26SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec29SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec24SE size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec8SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec34SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = iVec35SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec38SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec33SE size = 128 size_bytes = 512 read = 1 write = 1 ratio = 0.015625
Field = fRec10SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec43SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = iVec44SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec47SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec42SE size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec12SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec52SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = iVec53SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec56SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec51SE size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec14SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec61SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = iVec62SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec65SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec60SE size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec16SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec70SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = iVec71SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec74SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec69SE size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec18SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec79SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = iVec80SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec83SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec78SE size = 64 size_bytes = 256 read = 1 write = 1 ratio = 0.03125
Field = fRec20SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec88SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = iVec89SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec92SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec87SE size = 32 size_bytes = 128 read = 1 write = 1 ratio = 0.0625
Field = fRec22SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec97SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = iVec98SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec101SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec96SE size = 32 size_bytes = 128 read = 1 write = 1 ratio = 0.0625
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
