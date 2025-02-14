======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Freeverb")
	AddHorizontalSlider("Damp", fHslider1, 1.0f, 0.0f, 1.0f, 0.025f)
	AddHorizontalSlider("RoomSize", fHslider0, 1.0f, 0.0f, 1.0f, 0.025f)
	AddHorizontalSlider("Wet", fHslider2, 0.93f, 0.0f, 1.0f, 0.025f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("int", IOTA0)("float[2]", fVec0SE)("float[2048]", fVec3SE)("float[2]", fVec4SE)("float[2048]", fVec7SE)("float[2]", fVec8SE)("float[2048]", fVec11SE)("float[2]", fVec12SE)("float[2048]", fVec15SE)("float[2]", fVec16SE)("float[2048]", fVec19SE)("float[2]", fVec20SE)("float[2048]", fVec23SE)("float[2]", fVec24SE)("float[2048]", fVec27SE)("float[2]", fVec28SE)("float[2048]", fVec31SE)("float[2]", fRec8SE)("float[2]", fVec1SE)("float[2]", fVec5SE)("float[2]", fVec9SE)("float[2]", fVec13SE)("float[2]", fVec17SE)("float[2]", fVec21SE)("float[2]", fVec25SE)("float[2]", fVec29SE)("float[1024]", fVec32SE)("float[2]", fRec17SE)("float[512]", fVec51SE)("float[2]", fRec19SE)("float[512]", fVec55SE)("float[2]", fRec21SE)("float[256]", fVec59SE)("FAUSTFLOAT", fHslider2)("float[2]", fVec64SE)("float[2048]", fVec67SE)("float[2]", fVec68SE)("float[2048]", fVec71SE)("float[2]", fVec72SE)("float[2048]", fVec75SE)("float[2]", fVec76SE)("float[2048]", fVec79SE)("float[2]", fVec80SE)("float[2048]", fVec83SE)("float[2]", fVec84SE)("float[2048]", fVec87SE)("float[2]", fVec88SE)("float[2048]", fVec91SE)("float[2]", fVec92SE)("float[2048]", fVec95SE)("float[2]", fRec32SE)("float[2]", fVec65SE)("float[2]", fVec69SE)("float[2]", fVec73SE)("float[2]", fVec77SE)("float[2]", fVec81SE)("float[2]", fVec85SE)("float[2]", fVec89SE)("float[2]", fVec93SE)("float[1024]", fVec96SE)("float[2]", fRec41SE)("float[512]", fVec115SE)("float[2]", fRec43SE)("float[512]", fVec119SE)("float[2]", fRec45SE)("float[256]", fVec123SE)("int", fSampleRate)>)

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
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.93f)))
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
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2048))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2048))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2048))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2048))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2048))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2048))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2048))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2048))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29SE, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(1024))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(512))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec51SE, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19SE, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(512))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec55SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21SE, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(256))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec59SE, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec64SE, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2048))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec67SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec68SE, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2048))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec71SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec72SE, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2048))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec75SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec76SE, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2048))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec79SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec80SE, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2048))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec83SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec84SE, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2048))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec87SE, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec88SE, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2048))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec91SE, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec92SE, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(2048))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec95SE, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32SE, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec65SE, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec69SE, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec73SE, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec77SE, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec81SE, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec85SE, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec89SE, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(2))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec93SE, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(1024))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec96SE, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec41SE, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(512))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec115SE, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec43SE, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(512))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec119SE, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(2))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec45SE, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(256))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec123SE, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 9 Store = 0 Binop = 5 [ { Real(*) = 2 } { Real(+) = 3 } ] Mathop = 0 Numbers = 9 Declare = 9 Cast = 3 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("+", BinopInst("*", Float(0.28f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))), Float(0.7f)))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow1BE, kStack)))))
	DeclareVarInst("float", fSlow3BE, kStack, CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow3BE, kStack)))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 406 Store = 68 Binop = 367 [ { Int(&) = 160 } { Int(+) = 2 } { Int(-) = 64 } { Int(<) = 1 } { Real(*) = 61 } { Real(+) = 79 } ] Mathop = 0 Numbers = 236 Declare = 42 Cast = 4 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp0SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp1SE, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp2SE, kStack, BinopInst("*", Float(0.015f), BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack)))))
		StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fTemp2SE, kStack))))
		StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec19SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec23SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec29SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fRec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(556)), Int32(1023))]))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1116)), Int32(2047))]))
		DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1188)), Int32(2047))]))
		DeclareVarInst("float", fTemp4SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1277)), Int32(2047))]))
		DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1356)), Int32(2047))]))
		DeclareVarInst("float", fTemp6SE, kStack, LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec19SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1422)), Int32(2047))]))
		DeclareVarInst("float", fTemp7SE, kStack, LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec23SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1491)), Int32(2047))]))
		DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1557)), Int32(2047))]))
		DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec29SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1617)), Int32(2047))]))
		DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec29SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fRec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp3SE, kStack)), LoadVarInst(Address(fTemp4SE, kStack))), LoadVarInst(Address(fTemp5SE, kStack))), LoadVarInst(Address(fTemp6SE, kStack))), LoadVarInst(Address(fTemp7SE, kStack))), LoadVarInst(Address(fTemp8SE, kStack))), LoadVarInst(Address(fTemp9SE, kStack))), LoadVarInst(Address(fTemp10SE, kStack))), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp11SE, kStack)))))
		StoreVarInst(Address(fRec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(441)), Int32(511))]))
		DeclareVarInst("float", fRec18SE, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp11SE, kStack)), MinusInst(LoadVarInst(Address(fTemp3SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp4SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp5SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp6SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp7SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp8SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp9SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp10SE, kStack)))))
		DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fRec18SE, kStack)))
		DeclareVarInst("float", fTemp13SE, kStack, LoadVarInst(Address(fRec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fTemp12SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp13SE, kStack)))))
		StoreVarInst(Address(fRec19SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec55SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(341)), Int32(511))]))
		DeclareVarInst("float", fRec20SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp13SE, kStack)), MinusInst(LoadVarInst(Address(fTemp12SE, kStack)))))
		DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fRec20SE, kStack)))
		DeclareVarInst("float", fTemp15SE, kStack, LoadVarInst(Address(fRec19SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec55SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fTemp14SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp15SE, kStack)))))
		StoreVarInst(Address(fRec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec59SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(225)), Int32(255))]))
		DeclareVarInst("float", fRec22SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp15SE, kStack)), MinusInst(LoadVarInst(Address(fTemp14SE, kStack)))))
		DeclareVarInst("float", fTemp16SE, kStack, LoadVarInst(Address(fRec22SE, kStack)))
		DeclareVarInst("float", fTemp17SE, kStack, LoadVarInst(Address(fRec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec59SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(255))], BinopInst("+", LoadVarInst(Address(fTemp16SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp17SE, kStack)))))
		DeclareVarInst("float", fRec23SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp17SE, kStack)), MinusInst(LoadVarInst(Address(fTemp16SE, kStack)))))
		StoreVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec67SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec68SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec68SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec69SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec68SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec73SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec75SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec77SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec79SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec80SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec85SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec87SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec88SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec88SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec89SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec91SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec88SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec93SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec95SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(fRec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec96SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(579)), Int32(1023))]))
		StoreVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec67SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1139)), Int32(2047))]))
		DeclareVarInst("float", fTemp18SE, kStack, LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec69SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1211)), Int32(2047))]))
		DeclareVarInst("float", fTemp19SE, kStack, LoadVarInst(Address(fVec69SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec73SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec75SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1300)), Int32(2047))]))
		DeclareVarInst("float", fTemp20SE, kStack, LoadVarInst(Address(fVec73SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec77SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec79SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1379)), Int32(2047))]))
		DeclareVarInst("float", fTemp21SE, kStack, LoadVarInst(Address(fVec77SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1445)), Int32(2047))]))
		DeclareVarInst("float", fTemp22SE, kStack, LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec85SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec87SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1514)), Int32(2047))]))
		DeclareVarInst("float", fTemp23SE, kStack, LoadVarInst(Address(fVec85SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec89SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec91SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1580)), Int32(2047))]))
		DeclareVarInst("float", fTemp24SE, kStack, LoadVarInst(Address(fVec89SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec93SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec95SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1640)), Int32(2047))]))
		DeclareVarInst("float", fTemp25SE, kStack, LoadVarInst(Address(fVec93SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		DeclareVarInst("float", fTemp26SE, kStack, LoadVarInst(Address(fRec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec96SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp18SE, kStack)), LoadVarInst(Address(fTemp19SE, kStack))), LoadVarInst(Address(fTemp20SE, kStack))), LoadVarInst(Address(fTemp21SE, kStack))), LoadVarInst(Address(fTemp22SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp24SE, kStack))), LoadVarInst(Address(fTemp25SE, kStack))), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp26SE, kStack)))))
		StoreVarInst(Address(fRec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec115SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(464)), Int32(511))]))
		DeclareVarInst("float", fRec42SE, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp26SE, kStack)), MinusInst(LoadVarInst(Address(fTemp18SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp19SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp20SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp21SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp22SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp23SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp24SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp25SE, kStack)))))
		DeclareVarInst("float", fTemp27SE, kStack, LoadVarInst(Address(fRec42SE, kStack)))
		DeclareVarInst("float", fTemp28SE, kStack, LoadVarInst(Address(fRec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec115SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fTemp27SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp28SE, kStack)))))
		StoreVarInst(Address(fRec43SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec119SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(364)), Int32(511))]))
		DeclareVarInst("float", fRec44SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp28SE, kStack)), MinusInst(LoadVarInst(Address(fTemp27SE, kStack)))))
		DeclareVarInst("float", fTemp29SE, kStack, LoadVarInst(Address(fRec44SE, kStack)))
		DeclareVarInst("float", fTemp30SE, kStack, LoadVarInst(Address(fRec43SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec119SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fTemp29SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp30SE, kStack)))))
		StoreVarInst(Address(fRec45SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec123SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(248)), Int32(255))]))
		DeclareVarInst("float", fRec46SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp30SE, kStack)), MinusInst(LoadVarInst(Address(fTemp29SE, kStack)))))
		DeclareVarInst("float", fTemp31SE, kStack, LoadVarInst(Address(fRec46SE, kStack)))
		DeclareVarInst("float", fTemp32SE, kStack, LoadVarInst(Address(fRec45SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec123SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(255))], BinopInst("+", LoadVarInst(Address(fTemp31SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp32SE, kStack)))))
		DeclareVarInst("float", fRec47SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp32SE, kStack)), MinusInst(LoadVarInst(Address(fTemp31SE, kStack)))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fRec23SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fRec47SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
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
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay fVec0SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec0SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec3SE[2048], kStruct)
	// Recursion delay fVec4SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec4SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec7SE[2048], kStruct)
	// Recursion delay fVec8SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec8SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec11SE[2048], kStruct)
	// Recursion delay fVec12SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec12SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec15SE[2048], kStruct)
	// Recursion delay fVec16SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec16SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec19SE[2048], kStruct)
	// Recursion delay fVec20SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec20SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec23SE[2048], kStruct)
	// Recursion delay fVec24SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec24SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec27SE[2048], kStruct)
	// Recursion delay fVec28SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec28SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec31SE[2048], kStruct)
	// Recursion delay fRec8SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec8SE[2], kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	// Recursion delay fVec5SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec5SE[2], kStruct)
	// Recursion delay fVec9SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec9SE[2], kStruct)
	// Recursion delay fVec13SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec13SE[2], kStruct)
	// Recursion delay fVec17SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec17SE[2], kStruct)
	// Recursion delay fVec21SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec21SE[2], kStruct)
	// Recursion delay fVec25SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec25SE[2], kStruct)
	// Recursion delay fVec29SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec29SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec32SE[1024], kStruct)
	// Recursion delay fRec17SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec17SE[2], kStruct)
	// Recursion delay fRec18SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec51SE[512], kStruct)
	// Recursion delay fRec19SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec19SE[2], kStruct)
	// Recursion delay fRec20SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec55SE[512], kStruct)
	// Recursion delay fRec21SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec21SE[2], kStruct)
	// Recursion delay fRec22SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec59SE[256], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	// Recursion delay fRec23SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	// Recursion delay fVec64SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec64SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec67SE[2048], kStruct)
	// Recursion delay fVec68SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec68SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec71SE[2048], kStruct)
	// Recursion delay fVec72SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec72SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec75SE[2048], kStruct)
	// Recursion delay fVec76SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec76SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec79SE[2048], kStruct)
	// Recursion delay fVec80SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec80SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec83SE[2048], kStruct)
	// Recursion delay fVec84SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec84SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec87SE[2048], kStruct)
	// Recursion delay fVec88SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec88SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec91SE[2048], kStruct)
	// Recursion delay fVec92SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec92SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec95SE[2048], kStruct)
	// Recursion delay fRec32SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec32SE[2], kStruct)
	// Recursion delay fVec65SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec65SE[2], kStruct)
	// Recursion delay fVec69SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec69SE[2], kStruct)
	// Recursion delay fVec73SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec73SE[2], kStruct)
	// Recursion delay fVec77SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec77SE[2], kStruct)
	// Recursion delay fVec81SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec81SE[2], kStruct)
	// Recursion delay fVec85SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec85SE[2], kStruct)
	// Recursion delay fVec89SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec89SE[2], kStruct)
	// Recursion delay fVec93SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec93SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec96SE[1024], kStruct)
	// Recursion delay fRec41SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec41SE[2], kStruct)
	// Recursion delay fRec42SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec115SE[512], kStruct)
	// Recursion delay fRec43SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec43SE[2], kStruct)
	// Recursion delay fRec44SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec119SE[512], kStruct)
	// Recursion delay fRec45SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fRec45SE[2], kStruct)
	// Recursion delay fRec46SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec123SE[256], kStruct)
	// Recursion delay fRec47SE is of type kZeroDelay
	// While its definition is of type kZeroDelay
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.93f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2048))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2048))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2048))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2048))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2048))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2048))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2048))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2048))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29SE, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(1024))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(512))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec51SE, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19SE, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(512))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec55SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21SE, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(256))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec59SE, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec64SE, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2048))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec67SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec68SE, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2048))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec71SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec72SE, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2048))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec75SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec76SE, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2048))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec79SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec80SE, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2048))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec83SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec84SE, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2048))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec87SE, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(2))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec88SE, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(2048))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec91SE, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec92SE, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(2048))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec95SE, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(2))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32SE, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec65SE, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(2))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec69SE, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(2))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec73SE, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec77SE, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(2))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec81SE, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec85SE, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec89SE, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(2))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec93SE, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(1024))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec96SE, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec41SE, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(512))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec115SE, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(2))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec43SE, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(512))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec119SE, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(2))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec45SE, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(256))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec123SE, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0BE, kStack, BinopInst("+", BinopInst("*", Float(0.28f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))), Float(0.7f)))
	DeclareVarInst("float", fSlow1BE, kStack, BinopInst("*", Float(0.4f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow1BE, kStack)))))
	DeclareVarInst("float", fSlow3BE, kStack, CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("+", Float(1.0f), MinusInst(LoadVarInst(Address(fSlow3BE, kStack)))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp0SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp1SE, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp2SE, kStack, BinopInst("*", Float(0.015f), BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), LoadVarInst(Address(fTemp1SE, kStack)))))
			StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fTemp2SE, kStack))))
			StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec7SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec19SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec23SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec29SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fRec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(556)), Int32(1023))]))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1116)), Int32(2047))]))
			DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec7SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1188)), Int32(2047))]))
			DeclareVarInst("float", fTemp4SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1277)), Int32(2047))]))
			DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1356)), Int32(2047))]))
			DeclareVarInst("float", fTemp6SE, kStack, LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec19SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1422)), Int32(2047))]))
			DeclareVarInst("float", fTemp7SE, kStack, LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec23SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1491)), Int32(2047))]))
			DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1557)), Int32(2047))]))
			DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec25SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec29SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1617)), Int32(2047))]))
			DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec29SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fRec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp3SE, kStack)), LoadVarInst(Address(fTemp4SE, kStack))), LoadVarInst(Address(fTemp5SE, kStack))), LoadVarInst(Address(fTemp6SE, kStack))), LoadVarInst(Address(fTemp7SE, kStack))), LoadVarInst(Address(fTemp8SE, kStack))), LoadVarInst(Address(fTemp9SE, kStack))), LoadVarInst(Address(fTemp10SE, kStack))), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp11SE, kStack)))))
			StoreVarInst(Address(fRec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(441)), Int32(511))]))
			DeclareVarInst("float", fRec18SE, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp11SE, kStack)), MinusInst(LoadVarInst(Address(fTemp3SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp4SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp5SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp6SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp7SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp8SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp9SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp10SE, kStack)))))
			DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fRec18SE, kStack)))
			DeclareVarInst("float", fTemp13SE, kStack, LoadVarInst(Address(fRec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fTemp12SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp13SE, kStack)))))
			StoreVarInst(Address(fRec19SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec55SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(341)), Int32(511))]))
			DeclareVarInst("float", fRec20SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp13SE, kStack)), MinusInst(LoadVarInst(Address(fTemp12SE, kStack)))))
			DeclareVarInst("float", fTemp14SE, kStack, LoadVarInst(Address(fRec20SE, kStack)))
			DeclareVarInst("float", fTemp15SE, kStack, LoadVarInst(Address(fRec19SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec55SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fTemp14SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp15SE, kStack)))))
			StoreVarInst(Address(fRec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec59SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(225)), Int32(255))]))
			DeclareVarInst("float", fRec22SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp15SE, kStack)), MinusInst(LoadVarInst(Address(fTemp14SE, kStack)))))
			DeclareVarInst("float", fTemp16SE, kStack, LoadVarInst(Address(fRec22SE, kStack)))
			DeclareVarInst("float", fTemp17SE, kStack, LoadVarInst(Address(fRec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec59SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(255))], BinopInst("+", LoadVarInst(Address(fTemp16SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp17SE, kStack)))))
			DeclareVarInst("float", fRec23SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp17SE, kStack)), MinusInst(LoadVarInst(Address(fTemp16SE, kStack)))))
			StoreVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec67SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec68SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec68SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec69SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec68SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec73SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec75SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec77SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec79SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec80SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec85SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec87SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec88SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec88SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec89SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec91SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec88SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fVec93SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec95SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp2SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), LoadVarInst(Address(fVec92SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(fRec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec96SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(579)), Int32(1023))]))
			StoreVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec67SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1139)), Int32(2047))]))
			DeclareVarInst("float", fTemp18SE, kStack, LoadVarInst(Address(fVec65SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec69SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1211)), Int32(2047))]))
			DeclareVarInst("float", fTemp19SE, kStack, LoadVarInst(Address(fVec69SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec73SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec75SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1300)), Int32(2047))]))
			DeclareVarInst("float", fTemp20SE, kStack, LoadVarInst(Address(fVec73SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec77SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec79SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1379)), Int32(2047))]))
			DeclareVarInst("float", fTemp21SE, kStack, LoadVarInst(Address(fVec77SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1445)), Int32(2047))]))
			DeclareVarInst("float", fTemp22SE, kStack, LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec85SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec87SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1514)), Int32(2047))]))
			DeclareVarInst("float", fTemp23SE, kStack, LoadVarInst(Address(fVec85SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec89SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec91SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1580)), Int32(2047))]))
			DeclareVarInst("float", fTemp24SE, kStack, LoadVarInst(Address(fVec89SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec93SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec95SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1640)), Int32(2047))]))
			DeclareVarInst("float", fTemp25SE, kStack, LoadVarInst(Address(fVec93SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			DeclareVarInst("float", fTemp26SE, kStack, LoadVarInst(Address(fRec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec96SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp18SE, kStack)), LoadVarInst(Address(fTemp19SE, kStack))), LoadVarInst(Address(fTemp20SE, kStack))), LoadVarInst(Address(fTemp21SE, kStack))), LoadVarInst(Address(fTemp22SE, kStack))), LoadVarInst(Address(fTemp23SE, kStack))), LoadVarInst(Address(fTemp24SE, kStack))), LoadVarInst(Address(fTemp25SE, kStack))), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp26SE, kStack)))))
			StoreVarInst(Address(fRec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec115SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(464)), Int32(511))]))
			DeclareVarInst("float", fRec42SE, kStack, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp26SE, kStack)), MinusInst(LoadVarInst(Address(fTemp18SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp19SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp20SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp21SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp22SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp23SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp24SE, kStack)))), MinusInst(LoadVarInst(Address(fTemp25SE, kStack)))))
			DeclareVarInst("float", fTemp27SE, kStack, LoadVarInst(Address(fRec42SE, kStack)))
			DeclareVarInst("float", fTemp28SE, kStack, LoadVarInst(Address(fRec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec115SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fTemp27SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp28SE, kStack)))))
			StoreVarInst(Address(fRec43SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec119SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(364)), Int32(511))]))
			DeclareVarInst("float", fRec44SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp28SE, kStack)), MinusInst(LoadVarInst(Address(fTemp27SE, kStack)))))
			DeclareVarInst("float", fTemp29SE, kStack, LoadVarInst(Address(fRec44SE, kStack)))
			DeclareVarInst("float", fTemp30SE, kStack, LoadVarInst(Address(fRec43SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec119SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", LoadVarInst(Address(fTemp29SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp30SE, kStack)))))
			StoreVarInst(Address(fRec45SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec123SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(248)), Int32(255))]))
			DeclareVarInst("float", fRec46SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp30SE, kStack)), MinusInst(LoadVarInst(Address(fTemp29SE, kStack)))))
			DeclareVarInst("float", fTemp31SE, kStack, LoadVarInst(Address(fRec46SE, kStack)))
			DeclareVarInst("float", fTemp32SE, kStack, LoadVarInst(Address(fRec45SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec123SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(255))], BinopInst("+", LoadVarInst(Address(fTemp31SE, kStack)), BinopInst("*", Float(0.5f), LoadVarInst(Address(fTemp32SE, kStack)))))
			DeclareVarInst("float", fRec47SE, kStack, BinopInst("+", LoadVarInst(Address(fTemp32SE, kStack)), MinusInst(LoadVarInst(Address(fTemp31SE, kStack)))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fRec23SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fRec47SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
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
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec23SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec28SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec31SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec25SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec29SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fRec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec51SE size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec19SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec55SE size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec21SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec59SE size = 256 size_bytes = 1024 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec64SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec67SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec68SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec71SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec72SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec75SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec76SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec79SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec80SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec83SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec84SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec87SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec88SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec91SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec92SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec95SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec32SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec65SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec69SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec73SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec77SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec81SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec85SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec89SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec93SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec96SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fRec41SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec115SE size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec43SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec119SE size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec45SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec123SE size = 256 size_bytes = 1024 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec7SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec11SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec15SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec19SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec23SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec28SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec31SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec9SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec13SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec21SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec25SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec29SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fRec17SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec51SE size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec19SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec55SE size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec21SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec59SE size = 256 size_bytes = 1024 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec64SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec67SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec68SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec71SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec72SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec75SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec76SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec79SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec80SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec83SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec84SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec87SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec88SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec91SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec92SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec95SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec32SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec65SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec69SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec73SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec77SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec81SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec85SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec89SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec93SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec96SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fRec41SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec115SE size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec43SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec119SE size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fRec45SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec123SE size = 256 size_bytes = 1024 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 161 write = 1 ratio = 162
Field = fVec0SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec3SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec4SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec7SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec8SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec11SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec12SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec15SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec16SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec19SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec20SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec23SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec24SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec27SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec28SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec31SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec8SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec1SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec5SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec9SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec13SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec17SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec21SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec25SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec29SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec32SE size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = fRec17SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec51SE size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fRec19SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec55SE size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fRec21SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec59SE size = 256 size_bytes = 1024 read = 1 write = 1 ratio = 0.0078125
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec64SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec67SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec68SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec71SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec72SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec75SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec76SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec79SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec80SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec83SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec84SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec87SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec88SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec91SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec92SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec95SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec32SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec65SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec69SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec73SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec77SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec81SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec85SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec89SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec93SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec96SE size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = fRec41SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec115SE size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fRec43SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec119SE size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fRec45SE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fVec123SE size = 256 size_bytes = 1024 read = 1 write = 1 ratio = 0.0078125
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
