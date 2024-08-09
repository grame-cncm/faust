======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Freeverb")
	AddHorizontalSlider("Damp", fHslider2, 1.0f, 0.0f, 1.0f, 0.025f)
	AddHorizontalSlider("RoomSize", fHslider1, 1.0f, 0.0f, 1.0f, 0.025f)
	AddHorizontalSlider("Wet", fHslider0, 0.93f, 0.0f, 1.0f, 0.025f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("FAUSTFLOAT", fHslider2)("float[2]", fRec9)("int", IOTA0)("float[2048]", fVec0)("float[2]", fRec8)("float[2]", fRec11)("float[2048]", fVec1)("float[2]", fRec10)("float[2]", fRec13)("float[2048]", fVec2)("float[2]", fRec12)("float[2]", fRec15)("float[2048]", fVec3)("float[2]", fRec14)("float[2]", fRec17)("float[2048]", fVec4)("float[2]", fRec16)("float[2]", fRec19)("float[2048]", fVec5)("float[2]", fRec18)("float[2]", fRec21)("float[2048]", fVec6)("float[2]", fRec20)("float[2]", fRec23)("float[2048]", fVec7)("float[2]", fRec22)("float[1024]", fVec8)("float[2]", fRec6)("float[512]", fVec9)("float[2]", fRec4)("float[512]", fVec10)("float[2]", fRec2)("float[256]", fVec11)("float[2]", fRec0)("float[2]", fRec33)("float[2048]", fVec12)("float[2]", fRec32)("float[2]", fRec35)("float[2048]", fVec13)("float[2]", fRec34)("float[2]", fRec37)("float[2048]", fVec14)("float[2]", fRec36)("float[2]", fRec39)("float[2048]", fVec15)("float[2]", fRec38)("float[2]", fRec41)("float[2048]", fVec16)("float[2]", fRec40)("float[2]", fRec43)("float[2048]", fVec17)("float[2]", fRec42)("float[2]", fRec45)("float[2048]", fVec18)("float[2]", fRec44)("float[2]", fRec47)("float[2048]", fVec19)("float[2]", fRec46)("float[1024]", fVec20)("float[2]", fRec30)("float[512]", fVec21)("float[2]", fRec28)("float[512]", fVec22)("float[2]", fRec26)("float[256]", fVec23)("float[2]", fRec24)("int", fSampleRate)>)

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
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.93f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2048))
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
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2048))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2048))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2048))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2048))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2048))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2048))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2048))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(1024))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(512))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(512))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(256))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2048))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec35, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2048))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec37, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2048))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2048))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec41, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2048))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec40, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(2))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec43, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2048))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec42, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec45, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2048))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec44, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec47, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2048))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec46, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(1024))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(2))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(512))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(512))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(2))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(256))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(2))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 9 Store = 0 Binop = 5 [ { Real(*) = 2 } { Real(+) = 1 } { Real(-) = 2 } ] Mathop = 0 Numbers = 9 Declare = 9 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("+", BinopInst("*", Float(0.28f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))), Float(0.7f)))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 292 Store = 108 Binop = 201 [ { Int(&) = 48 } { Int(+) = 2 } { Int(-) = 24 } { Int(<) = 1 } { Real(*) = 61 } { Real(+) = 57 } { Real(-) = 8 } ] Mathop = 0 Numbers = 284 Declare = 14 Cast = 4 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))))
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("*", Float(0.015f), BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp1, kStack)))))
		StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(0)])), LoadVarInst(Address(fTemp2, kStack))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1116)), Int32(2047))]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec11, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec10, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1188)), Int32(2047))]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1277)), Int32(2047))]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec15, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1356)), Int32(2047))]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec17, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec16, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1422)), Int32(2047))]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec19, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec18, kStruct)[Int32(0)], LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1491)), Int32(2047))]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec20, kStruct)[Int32(0)], LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1557)), Int32(2047))]))
		StoreVarInst(Address(fRec23, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec23, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec22, kStruct)[Int32(0)], LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1617)), Int32(2047))]))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(0)]), LoadVarInst(Address(fRec10, kStruct)[Int32(0)])), LoadVarInst(Address(fRec12, kStruct)[Int32(0)])), LoadVarInst(Address(fRec14, kStruct)[Int32(0)])), LoadVarInst(Address(fRec16, kStruct)[Int32(0)])), LoadVarInst(Address(fRec18, kStruct)[Int32(0)])), LoadVarInst(Address(fRec20, kStruct)[Int32(0)])), LoadVarInst(Address(fRec22, kStruct)[Int32(0)])))
		StoreVarInst(Address(fVec8, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", LoadVarInst(Address(fTemp3, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], LoadVarInst(Address(fVec8, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(556)), Int32(1023))]))
		DeclareVarInst("float", fRec7, kStack, BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fRec7, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(441)), Int32(511))]))
		DeclareVarInst("float", fRec5, kStack, BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStack))))
		StoreVarInst(Address(fVec10, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fRec5, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], LoadVarInst(Address(fVec10, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(341)), Int32(511))]))
		DeclareVarInst("float", fRec3, kStack, BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fRec5, kStack))))
		StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(255))], BinopInst("+", LoadVarInst(Address(fRec3, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(225)), Int32(255))]))
		DeclareVarInst("float", fRec1, kStack, BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fRec3, kStack))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec1, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp0, kStack))))))
		StoreVarInst(Address(fRec33, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec12, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec32, kStruct)[Int32(0)], LoadVarInst(Address(fVec12, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1139)), Int32(2047))]))
		StoreVarInst(Address(fRec35, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec34, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1211)), Int32(2047))]))
		StoreVarInst(Address(fRec37, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec14, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec36, kStruct)[Int32(0)], LoadVarInst(Address(fVec14, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1300)), Int32(2047))]))
		StoreVarInst(Address(fRec39, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec38, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1379)), Int32(2047))]))
		StoreVarInst(Address(fRec41, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec41, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec40, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec16, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec41, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec40, kStruct)[Int32(0)], LoadVarInst(Address(fVec16, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1445)), Int32(2047))]))
		StoreVarInst(Address(fRec43, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec42, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1514)), Int32(2047))]))
		StoreVarInst(Address(fRec45, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec18, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec44, kStruct)[Int32(0)], LoadVarInst(Address(fVec18, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1580)), Int32(2047))]))
		StoreVarInst(Address(fRec47, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec47, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec19, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec47, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec46, kStruct)[Int32(0)], LoadVarInst(Address(fVec19, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1640)), Int32(2047))]))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(0)]), LoadVarInst(Address(fRec34, kStruct)[Int32(0)])), LoadVarInst(Address(fRec36, kStruct)[Int32(0)])), LoadVarInst(Address(fRec38, kStruct)[Int32(0)])), LoadVarInst(Address(fRec40, kStruct)[Int32(0)])), LoadVarInst(Address(fRec42, kStruct)[Int32(0)])), LoadVarInst(Address(fRec44, kStruct)[Int32(0)])), LoadVarInst(Address(fRec46, kStruct)[Int32(0)])))
		StoreVarInst(Address(fVec20, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec30, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec30, kStruct)[Int32(0)], LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(579)), Int32(1023))]))
		DeclareVarInst("float", fRec31, kStack, BinopInst("-", LoadVarInst(Address(fRec30, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp4, kStack))))
		StoreVarInst(Address(fVec21, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fRec31, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec28, kStruct)[Int32(0)], LoadVarInst(Address(fVec21, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(464)), Int32(511))]))
		DeclareVarInst("float", fRec29, kStack, BinopInst("-", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), LoadVarInst(Address(fRec31, kStack))))
		StoreVarInst(Address(fVec22, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fRec29, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec26, kStruct)[Int32(0)], LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(364)), Int32(511))]))
		DeclareVarInst("float", fRec27, kStack, BinopInst("-", LoadVarInst(Address(fRec26, kStruct)[Int32(1)]), LoadVarInst(Address(fRec29, kStack))))
		StoreVarInst(Address(fVec23, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(255))], BinopInst("+", LoadVarInst(Address(fRec27, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec24, kStruct)[Int32(0)], LoadVarInst(Address(fVec23, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(248)), Int32(255))]))
		DeclareVarInst("float", fRec25, kStack, BinopInst("-", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), LoadVarInst(Address(fRec27, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec25, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec37, kStruct)[Int32(1)], LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec41, kStruct)[Int32(1)], LoadVarInst(Address(fRec41, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec40, kStruct)[Int32(1)], LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec43, kStruct)[Int32(1)], LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec42, kStruct)[Int32(1)], LoadVarInst(Address(fRec42, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec45, kStruct)[Int32(1)], LoadVarInst(Address(fRec45, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec44, kStruct)[Int32(1)], LoadVarInst(Address(fRec44, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec47, kStruct)[Int32(1)], LoadVarInst(Address(fRec47, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec46, kStruct)[Int32(1)], LoadVarInst(Address(fRec46, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
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
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("float", fRec9[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec0[2048], kStruct)
	DeclareVarInst("float", fRec8[2], kStruct)
	DeclareVarInst("float", fRec11[2], kStruct)
	DeclareVarInst("float", fVec1[2048], kStruct)
	DeclareVarInst("float", fRec10[2], kStruct)
	DeclareVarInst("float", fRec13[2], kStruct)
	DeclareVarInst("float", fVec2[2048], kStruct)
	DeclareVarInst("float", fRec12[2], kStruct)
	DeclareVarInst("float", fRec15[2], kStruct)
	DeclareVarInst("float", fVec3[2048], kStruct)
	DeclareVarInst("float", fRec14[2], kStruct)
	DeclareVarInst("float", fRec17[2], kStruct)
	DeclareVarInst("float", fVec4[2048], kStruct)
	DeclareVarInst("float", fRec16[2], kStruct)
	DeclareVarInst("float", fRec19[2], kStruct)
	DeclareVarInst("float", fVec5[2048], kStruct)
	DeclareVarInst("float", fRec18[2], kStruct)
	DeclareVarInst("float", fRec21[2], kStruct)
	DeclareVarInst("float", fVec6[2048], kStruct)
	DeclareVarInst("float", fRec20[2], kStruct)
	DeclareVarInst("float", fRec23[2], kStruct)
	DeclareVarInst("float", fVec7[2048], kStruct)
	DeclareVarInst("float", fRec22[2], kStruct)
	DeclareVarInst("float", fVec8[1024], kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("float", fVec9[512], kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("float", fVec10[512], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("float", fVec11[256], kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("float", fRec33[2], kStruct)
	DeclareVarInst("float", fVec12[2048], kStruct)
	DeclareVarInst("float", fRec32[2], kStruct)
	DeclareVarInst("float", fRec35[2], kStruct)
	DeclareVarInst("float", fVec13[2048], kStruct)
	DeclareVarInst("float", fRec34[2], kStruct)
	DeclareVarInst("float", fRec37[2], kStruct)
	DeclareVarInst("float", fVec14[2048], kStruct)
	DeclareVarInst("float", fRec36[2], kStruct)
	DeclareVarInst("float", fRec39[2], kStruct)
	DeclareVarInst("float", fVec15[2048], kStruct)
	DeclareVarInst("float", fRec38[2], kStruct)
	DeclareVarInst("float", fRec41[2], kStruct)
	DeclareVarInst("float", fVec16[2048], kStruct)
	DeclareVarInst("float", fRec40[2], kStruct)
	DeclareVarInst("float", fRec43[2], kStruct)
	DeclareVarInst("float", fVec17[2048], kStruct)
	DeclareVarInst("float", fRec42[2], kStruct)
	DeclareVarInst("float", fRec45[2], kStruct)
	DeclareVarInst("float", fVec18[2048], kStruct)
	DeclareVarInst("float", fRec44[2], kStruct)
	DeclareVarInst("float", fRec47[2], kStruct)
	DeclareVarInst("float", fVec19[2048], kStruct)
	DeclareVarInst("float", fRec46[2], kStruct)
	DeclareVarInst("float", fVec20[1024], kStruct)
	DeclareVarInst("float", fRec30[2], kStruct)
	DeclareVarInst("float", fVec21[512], kStruct)
	DeclareVarInst("float", fRec28[2], kStruct)
	DeclareVarInst("float", fVec22[512], kStruct)
	DeclareVarInst("float", fRec26[2], kStruct)
	DeclareVarInst("float", fVec23[256], kStruct)
	DeclareVarInst("float", fRec24[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.93f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2048))
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
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2048))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2048))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2048))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2048))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2048))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2048))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2048))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(1024))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(512))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(512))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(256))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2048))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec35, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2048))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec37, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2048))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2048))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec41, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2048))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec40, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(2))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec43, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2048))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec42, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec45, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2048))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec44, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec47, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2048))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec46, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(1024))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(2))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(512))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(2))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(512))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(2))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(256))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(2))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("+", BinopInst("*", Float(0.28f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))), Float(0.7f)))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow2, kStack))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("-", Float(1.0f), LoadVarInst(Address(fSlow0, kStack))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))))
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("*", Float(0.015f), BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fTemp1, kStack)))))
			StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(0)])), LoadVarInst(Address(fTemp2, kStack))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1116)), Int32(2047))]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec11, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec10, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1188)), Int32(2047))]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1277)), Int32(2047))]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec15, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1356)), Int32(2047))]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec17, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec16, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1422)), Int32(2047))]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec19, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec18, kStruct)[Int32(0)], LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1491)), Int32(2047))]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec20, kStruct)[Int32(0)], LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1557)), Int32(2047))]))
			StoreVarInst(Address(fRec23, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec23, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec22, kStruct)[Int32(0)], LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1617)), Int32(2047))]))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(0)]), LoadVarInst(Address(fRec10, kStruct)[Int32(0)])), LoadVarInst(Address(fRec12, kStruct)[Int32(0)])), LoadVarInst(Address(fRec14, kStruct)[Int32(0)])), LoadVarInst(Address(fRec16, kStruct)[Int32(0)])), LoadVarInst(Address(fRec18, kStruct)[Int32(0)])), LoadVarInst(Address(fRec20, kStruct)[Int32(0)])), LoadVarInst(Address(fRec22, kStruct)[Int32(0)])))
			StoreVarInst(Address(fVec8, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", LoadVarInst(Address(fTemp3, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], LoadVarInst(Address(fVec8, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(556)), Int32(1023))]))
			DeclareVarInst("float", fRec7, kStack, BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fRec7, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(441)), Int32(511))]))
			DeclareVarInst("float", fRec5, kStack, BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStack))))
			StoreVarInst(Address(fVec10, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fRec5, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], LoadVarInst(Address(fVec10, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(341)), Int32(511))]))
			DeclareVarInst("float", fRec3, kStack, BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), LoadVarInst(Address(fRec5, kStack))))
			StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(255))], BinopInst("+", LoadVarInst(Address(fRec3, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(225)), Int32(255))]))
			DeclareVarInst("float", fRec1, kStack, BinopInst("-", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fRec3, kStack))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec1, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp0, kStack))))))
			StoreVarInst(Address(fRec33, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec12, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec32, kStruct)[Int32(0)], LoadVarInst(Address(fVec12, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1139)), Int32(2047))]))
			StoreVarInst(Address(fRec35, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec34, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1211)), Int32(2047))]))
			StoreVarInst(Address(fRec37, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec14, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec36, kStruct)[Int32(0)], LoadVarInst(Address(fVec14, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1300)), Int32(2047))]))
			StoreVarInst(Address(fRec39, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec38, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1379)), Int32(2047))]))
			StoreVarInst(Address(fRec41, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec41, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec40, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec16, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec41, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec40, kStruct)[Int32(0)], LoadVarInst(Address(fVec16, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1445)), Int32(2047))]))
			StoreVarInst(Address(fRec43, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec42, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1514)), Int32(2047))]))
			StoreVarInst(Address(fRec45, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec44, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec18, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec45, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec44, kStruct)[Int32(0)], LoadVarInst(Address(fVec18, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1580)), Int32(2047))]))
			StoreVarInst(Address(fRec47, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec47, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec46, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec19, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec47, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec46, kStruct)[Int32(0)], LoadVarInst(Address(fVec19, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1640)), Int32(2047))]))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(0)]), LoadVarInst(Address(fRec34, kStruct)[Int32(0)])), LoadVarInst(Address(fRec36, kStruct)[Int32(0)])), LoadVarInst(Address(fRec38, kStruct)[Int32(0)])), LoadVarInst(Address(fRec40, kStruct)[Int32(0)])), LoadVarInst(Address(fRec42, kStruct)[Int32(0)])), LoadVarInst(Address(fRec44, kStruct)[Int32(0)])), LoadVarInst(Address(fRec46, kStruct)[Int32(0)])))
			StoreVarInst(Address(fVec20, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", LoadVarInst(Address(fTemp4, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec30, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec30, kStruct)[Int32(0)], LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(579)), Int32(1023))]))
			DeclareVarInst("float", fRec31, kStack, BinopInst("-", LoadVarInst(Address(fRec30, kStruct)[Int32(1)]), LoadVarInst(Address(fTemp4, kStack))))
			StoreVarInst(Address(fVec21, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fRec31, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec28, kStruct)[Int32(0)], LoadVarInst(Address(fVec21, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(464)), Int32(511))]))
			DeclareVarInst("float", fRec29, kStack, BinopInst("-", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), LoadVarInst(Address(fRec31, kStack))))
			StoreVarInst(Address(fVec22, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fRec29, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec26, kStruct)[Int32(0)], LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(364)), Int32(511))]))
			DeclareVarInst("float", fRec27, kStack, BinopInst("-", LoadVarInst(Address(fRec26, kStruct)[Int32(1)]), LoadVarInst(Address(fRec29, kStack))))
			StoreVarInst(Address(fVec23, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(255))], BinopInst("+", LoadVarInst(Address(fRec27, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec24, kStruct)[Int32(0)], LoadVarInst(Address(fVec23, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(248)), Int32(255))]))
			DeclareVarInst("float", fRec25, kStack, BinopInst("-", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), LoadVarInst(Address(fRec27, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fRec25, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec37, kStruct)[Int32(1)], LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec41, kStruct)[Int32(1)], LoadVarInst(Address(fRec41, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec40, kStruct)[Int32(1)], LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec43, kStruct)[Int32(1)], LoadVarInst(Address(fRec43, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec42, kStruct)[Int32(1)], LoadVarInst(Address(fRec42, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec45, kStruct)[Int32(1)], LoadVarInst(Address(fRec45, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec44, kStruct)[Int32(1)], LoadVarInst(Address(fRec44, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec47, kStruct)[Int32(1)], LoadVarInst(Address(fRec47, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec46, kStruct)[Int32(1)], LoadVarInst(Address(fRec46, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 149836 bytes
Total heap size = 149844 bytes
Stack size in compute = 52 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec10 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 256 size_bytes = 1024 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec33 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec35 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec34 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec37 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec14 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec36 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec39 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec38 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec41 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec43 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec42 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec45 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec18 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec44 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec47 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec46 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec20 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec23 size = 256 size_bytes = 1024 read = 0 write = 0 ratio = 0
Field = fRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec10 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11 size = 256 size_bytes = 1024 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec33 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec35 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec34 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec37 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec14 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec36 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec39 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec38 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec41 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec43 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec42 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec45 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec18 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec44 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec47 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec46 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec20 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec23 size = 256 size_bytes = 1024 read = 0 write = 0 ratio = 0
Field = fRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = IOTA0 size = 1 size_bytes = 4 read = 49 write = 1 ratio = 50
Field = fVec0 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec8 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec11 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec1 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec10 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec13 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec2 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec12 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec15 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec3 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec14 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec17 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec4 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec16 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec19 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec5 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec18 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec21 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec6 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec20 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec23 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec7 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec22 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec8 size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec9 size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec10 size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec11 size = 256 size_bytes = 1024 read = 1 write = 1 ratio = 0.0078125
Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec33 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec12 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec32 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec35 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec13 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec34 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec37 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec14 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec36 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec39 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec15 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec38 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec41 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec16 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec40 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec43 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec17 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec42 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec45 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec18 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec44 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec47 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec19 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec46 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec20 size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = fRec30 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec21 size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fRec28 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec22 size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fRec26 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec23 size = 256 size_bytes = 1024 read = 1 write = 1 ratio = 0.0078125
Field = fRec24 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
