======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("karplus32")
	OpenVerticalBox("excitator")
	AddHorizontalSlider("excitation (samples)", fHslider4, 128.0f, 2.0f, 512.0f, 1.0f)
	AddButtonInst("play"fButton0)
	CloseboxInst
	OpenVerticalBox("noise generator")
	AddHorizontalSlider("level", fHslider3, 0.5f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	AddHorizontalSlider("output volume", fHslider0, 0.4866f, 0.0f, 1.0f, 0.1f)
	OpenVerticalBox("resonator x32")
	AddHorizontalSlider("attenuation", fHslider2, 0.0f, 0.0f, 1.0f, 0.01f)
	AddHorizontalSlider("detune", fHslider6, 37.9904f, 0.0f, 512.0f, 1.0f)
	AddHorizontalSlider("duration (samples)", fHslider5, 128.0f, 2.0f, 512.0f, 1.0f)
	AddHorizontalSlider("polyphony", fHslider1, 14.0f, 0.0f, 32.0f, 1.0f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("FAUSTFLOAT", fHslider2)("FAUSTFLOAT", fHslider3)("int[2]", iRec1)("FAUSTFLOAT", fButton0)("float[2]", fVec0)("FAUSTFLOAT", fHslider4)("float[2]", fRec2)("int", IOTA0)("float[512]", fVec1)("FAUSTFLOAT", fHslider5)("float[3]", fRec0)("float[2048]", fVec2)("FAUSTFLOAT", fHslider6)("float[3]", fRec3)("float[4096]", fVec3)("float[3]", fRec4)("float[4096]", fVec4)("float[3]", fRec5)("float[4096]", fVec5)("float[3]", fRec6)("float[4096]", fVec6)("float[3]", fRec7)("float[4096]", fVec7)("float[3]", fRec8)("float[4096]", fVec8)("float[3]", fRec9)("float[4096]", fVec9)("float[3]", fRec10)("float[4096]", fVec10)("float[3]", fRec11)("float[4096]", fVec11)("float[3]", fRec12)("float[4096]", fVec12)("float[3]", fRec13)("float[4096]", fVec13)("float[3]", fRec14)("float[4096]", fVec14)("float[3]", fRec15)("float[4096]", fVec15)("float[3]", fRec16)("float[4096]", fVec16)("float[3]", fRec17)("float[1024]", fVec17)("float[3]", fRec18)("float[2048]", fVec18)("float[3]", fRec19)("float[4096]", fVec19)("float[3]", fRec20)("float[4096]", fVec20)("float[3]", fRec21)("float[4096]", fVec21)("float[3]", fRec22)("float[4096]", fVec22)("float[3]", fRec23)("float[4096]", fVec23)("float[3]", fRec24)("float[4096]", fVec24)("float[3]", fRec25)("float[4096]", fVec25)("float[3]", fRec26)("float[4096]", fVec26)("float[3]", fRec27)("float[4096]", fVec27)("float[3]", fRec28)("float[4096]", fVec28)("float[3]", fRec29)("float[4096]", fVec29)("float[3]", fRec30)("float[4096]", fVec30)("float[3]", fRec31)("float[4096]", fVec31)("float[3]", fRec32)("float[4096]", fVec32)("float[3]", fRec33)("int", fSampleRate)>)

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
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.4866f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(14.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(128.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(128.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(37.9904f)))
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
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(512))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(3))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2048))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(4096))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(3))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(4096))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(3))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(4096))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(3))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(4096))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(3))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(4096))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(3))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(4096))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(3))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(4096))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(3))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(4096))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(3))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(4096))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(3))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(4096))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(3))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(4096))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(3))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(4096))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(3))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(4096))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(3))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(4096))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(3))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(1024))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(3))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2048))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(3))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(4096))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(3))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(4096))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(3))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(4096))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(3))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(4096))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(3))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(4096))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(3))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(4096))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(3))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec25, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(4096))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(3))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(4096))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(3))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec27, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(4096))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(3))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(4096))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(3))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec29, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(4096))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(3))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(4096))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(3))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec31, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(4096))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(3))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(4096))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(3))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 105 Store = 0 Binop = 161 [ { Int(&) = 32 } { Real(*) = 32 } { Real(+) = 63 } { Real(-) = 1 } { Real(/) = 1 } { Real(>) = 32 } ] Mathop = 0 Numbers = 132 Declare = 74 Cast = 72 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(0.0f))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(0.5f), BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("int", iSlow8, kStack, BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow9, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(2.0f))))
	DeclareVarInst("float", fSlow10, kStack, CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))
	DeclareVarInst("int", iSlow11, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(4.0f))))
	DeclareVarInst("int", iSlow13, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(4.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow14, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(6.0f))))
	DeclareVarInst("int", iSlow15, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(6.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow16, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(8.0f))))
	DeclareVarInst("int", iSlow17, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(8.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow18, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(1e+01f))))
	DeclareVarInst("int", iSlow19, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(1e+01f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow20, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(12.0f))))
	DeclareVarInst("int", iSlow21, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(12.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(14.0f))))
	DeclareVarInst("int", iSlow23, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(14.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow24, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(16.0f))))
	DeclareVarInst("int", iSlow25, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(16.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(18.0f))))
	DeclareVarInst("int", iSlow27, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(18.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow28, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(2e+01f))))
	DeclareVarInst("int", iSlow29, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(2e+01f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow30, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(22.0f))))
	DeclareVarInst("int", iSlow31, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(22.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow32, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(24.0f))))
	DeclareVarInst("int", iSlow33, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(24.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow34, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(26.0f))))
	DeclareVarInst("int", iSlow35, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(26.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow36, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(28.0f))))
	DeclareVarInst("int", iSlow37, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(28.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow38, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(3e+01f))))
	DeclareVarInst("int", iSlow39, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(3e+01f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow40, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f))))
	DeclareVarInst("int", iSlow41, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow10, kStack))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow42, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(3.0f))))
	DeclareVarInst("int", iSlow43, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(3.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow44, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(5.0f))))
	DeclareVarInst("int", iSlow45, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(5.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow46, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(7.0f))))
	DeclareVarInst("int", iSlow47, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(7.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow48, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(9.0f))))
	DeclareVarInst("int", iSlow49, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(9.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow50, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(11.0f))))
	DeclareVarInst("int", iSlow51, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(11.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow52, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(13.0f))))
	DeclareVarInst("int", iSlow53, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(13.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow54, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(15.0f))))
	DeclareVarInst("int", iSlow55, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(15.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow56, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(17.0f))))
	DeclareVarInst("int", iSlow57, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(17.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow58, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(19.0f))))
	DeclareVarInst("int", iSlow59, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(19.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow60, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(21.0f))))
	DeclareVarInst("int", iSlow61, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(21.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow62, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(23.0f))))
	DeclareVarInst("int", iSlow63, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(23.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow64, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(25.0f))))
	DeclareVarInst("int", iSlow65, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(25.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow66, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(27.0f))))
	DeclareVarInst("int", iSlow67, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(27.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow68, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(29.0f))))
	DeclareVarInst("int", iSlow69, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(29.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow70, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(31.0f))))
	DeclareVarInst("int", iSlow71, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(31.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 405 Store = 138 Binop = 271 [ { Int(&) = 64 } { Int(*) = 1 } { Int(+) = 3 } { Int(-) = 32 } { Int(<) = 1 } { Real(*) = 69 } { Real(+) = 96 } { Real(-) = 2 } { Real(>) = 3 } ] Mathop = 0 Numbers = 344 Declare = 2 Cast = 6 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec1, kStruct)[Int32(1)])), Int32(12345)))
		StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fSlow5, kStack)))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", BinopInst("-", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])), Float(0.0f)))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(0.0f))))))
		DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(iRec1, kStruct)[Int32(0)])), BinopInst("+", CastInst("float", BinopInst(">", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), Float(0.0f))), Float(1.5258789e-05f)))))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))), LoadVarInst(Address(fTemp0, kStack))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow8, kStack))), Int32(511))]))
		StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow11, kStack))), Int32(2047))]))
		StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fRec4, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow13, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fRec5, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow15, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fRec6, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow17, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow19, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fRec8, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow21, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec8, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), LoadVarInst(Address(fRec9, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], LoadVarInst(Address(fVec8, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow23, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), LoadVarInst(Address(fRec10, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec10, kStruct)[Int32(0)], LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow25, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec10, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), LoadVarInst(Address(fRec11, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec11, kStruct)[Int32(0)], LoadVarInst(Address(fVec10, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow27, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), LoadVarInst(Address(fRec12, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow29, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec12, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), LoadVarInst(Address(fRec13, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec13, kStruct)[Int32(0)], LoadVarInst(Address(fVec12, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow31, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fRec14, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow33, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec14, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), LoadVarInst(Address(fRec15, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec15, kStruct)[Int32(0)], LoadVarInst(Address(fVec14, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow35, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), LoadVarInst(Address(fRec16, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec16, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow37, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec16, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), LoadVarInst(Address(fRec17, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec17, kStruct)[Int32(0)], LoadVarInst(Address(fVec16, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow39, kStack))), Int32(4095))]))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), LoadVarInst(Address(fRec18, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec18, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow41, kStack))), Int32(1023))]))
		StoreVarInst(Address(fVec18, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec19, kStruct)[Int32(1)]), LoadVarInst(Address(fRec19, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec19, kStruct)[Int32(0)], LoadVarInst(Address(fVec18, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow43, kStack))), Int32(2047))]))
		StoreVarInst(Address(fVec19, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), LoadVarInst(Address(fRec20, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec20, kStruct)[Int32(0)], LoadVarInst(Address(fVec19, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow45, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec20, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStruct)[Int32(1)]), LoadVarInst(Address(fRec21, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec21, kStruct)[Int32(0)], LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow47, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec21, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), LoadVarInst(Address(fRec22, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec22, kStruct)[Int32(0)], LoadVarInst(Address(fVec21, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow49, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec22, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec23, kStruct)[Int32(1)]), LoadVarInst(Address(fRec23, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec23, kStruct)[Int32(0)], LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow51, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec23, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), LoadVarInst(Address(fRec24, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec24, kStruct)[Int32(0)], LoadVarInst(Address(fVec23, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow53, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec24, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStruct)[Int32(1)]), LoadVarInst(Address(fRec25, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec25, kStruct)[Int32(0)], LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow55, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec25, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec26, kStruct)[Int32(1)]), LoadVarInst(Address(fRec26, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec26, kStruct)[Int32(0)], LoadVarInst(Address(fVec25, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow57, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec26, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec27, kStruct)[Int32(1)]), LoadVarInst(Address(fRec27, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec27, kStruct)[Int32(0)], LoadVarInst(Address(fVec26, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow59, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec27, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), LoadVarInst(Address(fRec28, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec28, kStruct)[Int32(0)], LoadVarInst(Address(fVec27, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow61, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec28, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec29, kStruct)[Int32(1)]), LoadVarInst(Address(fRec29, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec29, kStruct)[Int32(0)], LoadVarInst(Address(fVec28, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow63, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec29, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec30, kStruct)[Int32(1)]), LoadVarInst(Address(fRec30, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec30, kStruct)[Int32(0)], LoadVarInst(Address(fVec29, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow65, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec30, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec31, kStruct)[Int32(1)]), LoadVarInst(Address(fRec31, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec31, kStruct)[Int32(0)], LoadVarInst(Address(fVec30, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow67, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec31, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), LoadVarInst(Address(fRec32, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec32, kStruct)[Int32(0)], LoadVarInst(Address(fVec31, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow69, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec32, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec33, kStruct)[Int32(1)]), LoadVarInst(Address(fRec33, kStruct)[Int32(2)])))))
		StoreVarInst(Address(fRec33, kStruct)[Int32(0)], LoadVarInst(Address(fVec32, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow71, kStack))), Int32(4095))]))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fRec18, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow58, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow60, kStack)), LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow68, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))))))
		StoreVarInst(Address(iRec1, kStruct)[Int32(1)], LoadVarInst(Address(iRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(2)], LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(2)], LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(2)], LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(2)], LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(2)], LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(2)], LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(2)], LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(2)], LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(2)], LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(2)], LoadVarInst(Address(fRec13, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(2)], LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(2)], LoadVarInst(Address(fRec15, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(2)], LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(2)], LoadVarInst(Address(fRec17, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(2)], LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(2)], LoadVarInst(Address(fRec19, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(2)], LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(2)], LoadVarInst(Address(fRec21, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(2)], LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec23, kStruct)[Int32(2)], LoadVarInst(Address(fRec23, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec24, kStruct)[Int32(2)], LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec25, kStruct)[Int32(2)], LoadVarInst(Address(fRec25, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec25, kStruct)[Int32(1)], LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec26, kStruct)[Int32(2)], LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec27, kStruct)[Int32(2)], LoadVarInst(Address(fRec27, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec27, kStruct)[Int32(1)], LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec28, kStruct)[Int32(2)], LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec29, kStruct)[Int32(2)], LoadVarInst(Address(fRec29, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec29, kStruct)[Int32(1)], LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec30, kStruct)[Int32(2)], LoadVarInst(Address(fRec30, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec31, kStruct)[Int32(2)], LoadVarInst(Address(fRec31, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec31, kStruct)[Int32(1)], LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec32, kStruct)[Int32(2)], LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec33, kStruct)[Int32(2)], LoadVarInst(Address(fRec33, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
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
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("int", iRec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fButton0, kStruct)
	DeclareVarInst("float", fVec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec1[512], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("float", fRec0[3], kStruct)
	DeclareVarInst("float", fVec2[2048], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider6, kStruct)
	DeclareVarInst("float", fRec3[3], kStruct)
	DeclareVarInst("float", fVec3[4096], kStruct)
	DeclareVarInst("float", fRec4[3], kStruct)
	DeclareVarInst("float", fVec4[4096], kStruct)
	DeclareVarInst("float", fRec5[3], kStruct)
	DeclareVarInst("float", fVec5[4096], kStruct)
	DeclareVarInst("float", fRec6[3], kStruct)
	DeclareVarInst("float", fVec6[4096], kStruct)
	DeclareVarInst("float", fRec7[3], kStruct)
	DeclareVarInst("float", fVec7[4096], kStruct)
	DeclareVarInst("float", fRec8[3], kStruct)
	DeclareVarInst("float", fVec8[4096], kStruct)
	DeclareVarInst("float", fRec9[3], kStruct)
	DeclareVarInst("float", fVec9[4096], kStruct)
	DeclareVarInst("float", fRec10[3], kStruct)
	DeclareVarInst("float", fVec10[4096], kStruct)
	DeclareVarInst("float", fRec11[3], kStruct)
	DeclareVarInst("float", fVec11[4096], kStruct)
	DeclareVarInst("float", fRec12[3], kStruct)
	DeclareVarInst("float", fVec12[4096], kStruct)
	DeclareVarInst("float", fRec13[3], kStruct)
	DeclareVarInst("float", fVec13[4096], kStruct)
	DeclareVarInst("float", fRec14[3], kStruct)
	DeclareVarInst("float", fVec14[4096], kStruct)
	DeclareVarInst("float", fRec15[3], kStruct)
	DeclareVarInst("float", fVec15[4096], kStruct)
	DeclareVarInst("float", fRec16[3], kStruct)
	DeclareVarInst("float", fVec16[4096], kStruct)
	DeclareVarInst("float", fRec17[3], kStruct)
	DeclareVarInst("float", fVec17[1024], kStruct)
	DeclareVarInst("float", fRec18[3], kStruct)
	DeclareVarInst("float", fVec18[2048], kStruct)
	DeclareVarInst("float", fRec19[3], kStruct)
	DeclareVarInst("float", fVec19[4096], kStruct)
	DeclareVarInst("float", fRec20[3], kStruct)
	DeclareVarInst("float", fVec20[4096], kStruct)
	DeclareVarInst("float", fRec21[3], kStruct)
	DeclareVarInst("float", fVec21[4096], kStruct)
	DeclareVarInst("float", fRec22[3], kStruct)
	DeclareVarInst("float", fVec22[4096], kStruct)
	DeclareVarInst("float", fRec23[3], kStruct)
	DeclareVarInst("float", fVec23[4096], kStruct)
	DeclareVarInst("float", fRec24[3], kStruct)
	DeclareVarInst("float", fVec24[4096], kStruct)
	DeclareVarInst("float", fRec25[3], kStruct)
	DeclareVarInst("float", fVec25[4096], kStruct)
	DeclareVarInst("float", fRec26[3], kStruct)
	DeclareVarInst("float", fVec26[4096], kStruct)
	DeclareVarInst("float", fRec27[3], kStruct)
	DeclareVarInst("float", fVec27[4096], kStruct)
	DeclareVarInst("float", fRec28[3], kStruct)
	DeclareVarInst("float", fVec28[4096], kStruct)
	DeclareVarInst("float", fRec29[3], kStruct)
	DeclareVarInst("float", fVec29[4096], kStruct)
	DeclareVarInst("float", fRec30[3], kStruct)
	DeclareVarInst("float", fVec30[4096], kStruct)
	DeclareVarInst("float", fRec31[3], kStruct)
	DeclareVarInst("float", fVec31[4096], kStruct)
	DeclareVarInst("float", fRec32[3], kStruct)
	DeclareVarInst("float", fVec32[4096], kStruct)
	DeclareVarInst("float", fRec33[3], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.4866f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(14.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(128.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(128.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(37.9904f)))
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
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(512))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(3))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2048))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(4096))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(3))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(4096))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(3))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(4096))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(3))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(4096))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(3))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(4096))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec7, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(3))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(4096))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(3))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(4096))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(3))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(4096))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(3))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(4096))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(3))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(4096))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(3))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(4096))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(3))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(4096))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(3))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(4096))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(3))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(4096))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(3))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(1024))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(3))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2048))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(3))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(4096))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec19, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(3))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec20, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(4096))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec20, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(3))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(4096))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(3))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(4096))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(3))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(4096))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(3))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(4096))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec24, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(3))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec25, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(4096))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec25, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(3))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(4096))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(3))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec27, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(4096))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(3))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(4096))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(3))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec29, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(4096))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec29, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(3))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(4096))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(3))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec31, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(4096))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(3))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(4096))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(3))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fHslider1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(0.0f))))
	DeclareVarInst("float", fSlow3, kStack, BinopInst("*", Float(0.5f), BinopInst("-", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("int", iSlow8, kStack, BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow9, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(2.0f))))
	DeclareVarInst("float", fSlow10, kStack, CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))
	DeclareVarInst("int", iSlow11, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(4.0f))))
	DeclareVarInst("int", iSlow13, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(4.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow14, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(6.0f))))
	DeclareVarInst("int", iSlow15, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(6.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow16, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(8.0f))))
	DeclareVarInst("int", iSlow17, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(8.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow18, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(1e+01f))))
	DeclareVarInst("int", iSlow19, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(1e+01f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow20, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(12.0f))))
	DeclareVarInst("int", iSlow21, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(12.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(14.0f))))
	DeclareVarInst("int", iSlow23, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(14.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow24, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(16.0f))))
	DeclareVarInst("int", iSlow25, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(16.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(18.0f))))
	DeclareVarInst("int", iSlow27, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(18.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow28, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(2e+01f))))
	DeclareVarInst("int", iSlow29, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(2e+01f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow30, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(22.0f))))
	DeclareVarInst("int", iSlow31, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(22.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow32, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(24.0f))))
	DeclareVarInst("int", iSlow33, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(24.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow34, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(26.0f))))
	DeclareVarInst("int", iSlow35, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(26.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow36, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(28.0f))))
	DeclareVarInst("int", iSlow37, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(28.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow38, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(3e+01f))))
	DeclareVarInst("int", iSlow39, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(3e+01f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow40, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(1.0f))))
	DeclareVarInst("int", iSlow41, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fSlow10, kStack))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow42, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(3.0f))))
	DeclareVarInst("int", iSlow43, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(3.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow44, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(5.0f))))
	DeclareVarInst("int", iSlow45, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(5.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow46, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(7.0f))))
	DeclareVarInst("int", iSlow47, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(7.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow48, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(9.0f))))
	DeclareVarInst("int", iSlow49, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(9.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow50, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(11.0f))))
	DeclareVarInst("int", iSlow51, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(11.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow52, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(13.0f))))
	DeclareVarInst("int", iSlow53, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(13.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow54, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(15.0f))))
	DeclareVarInst("int", iSlow55, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(15.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow56, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(17.0f))))
	DeclareVarInst("int", iSlow57, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(17.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow58, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(19.0f))))
	DeclareVarInst("int", iSlow59, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(19.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow60, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(21.0f))))
	DeclareVarInst("int", iSlow61, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(21.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow62, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(23.0f))))
	DeclareVarInst("int", iSlow63, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(23.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow64, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(25.0f))))
	DeclareVarInst("int", iSlow65, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(25.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow66, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(27.0f))))
	DeclareVarInst("int", iSlow67, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(27.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow68, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(29.0f))))
	DeclareVarInst("int", iSlow69, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(29.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow70, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow1, kStack)), Float(31.0f))))
	DeclareVarInst("int", iSlow71, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow7, kStack)), BinopInst("*", Float(31.0f), LoadVarInst(Address(fSlow10, kStack)))), Float(-1.5f))), Int32(4095)))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec1, kStruct)[Int32(1)])), Int32(12345)))
			StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fSlow5, kStack)))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), CastInst("float", BinopInst(">", BinopInst("-", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])), Float(0.0f)))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fRec2, kStruct)[Int32(1)]), Float(0.0f))))))
			DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(iRec1, kStruct)[Int32(0)])), BinopInst("+", CastInst("float", BinopInst(">", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), Float(0.0f))), Float(1.5258789e-05f)))))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(1)]), LoadVarInst(Address(fRec0, kStruct)[Int32(2)]))), LoadVarInst(Address(fTemp0, kStack))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow8, kStack))), Int32(511))]))
			StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow11, kStack))), Int32(2047))]))
			StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec4, kStruct)[Int32(1)]), LoadVarInst(Address(fRec4, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow13, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(1)]), LoadVarInst(Address(fRec5, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow15, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fRec6, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow17, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec6, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(1)]), LoadVarInst(Address(fRec7, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], LoadVarInst(Address(fVec6, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow19, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec7, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec8, kStruct)[Int32(1)]), LoadVarInst(Address(fRec8, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], LoadVarInst(Address(fVec7, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow21, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec8, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec9, kStruct)[Int32(1)]), LoadVarInst(Address(fRec9, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], LoadVarInst(Address(fVec8, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow23, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec9, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec10, kStruct)[Int32(1)]), LoadVarInst(Address(fRec10, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec10, kStruct)[Int32(0)], LoadVarInst(Address(fVec9, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow25, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec10, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec11, kStruct)[Int32(1)]), LoadVarInst(Address(fRec11, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec11, kStruct)[Int32(0)], LoadVarInst(Address(fVec10, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow27, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec11, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec12, kStruct)[Int32(1)]), LoadVarInst(Address(fRec12, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], LoadVarInst(Address(fVec11, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow29, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec12, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec13, kStruct)[Int32(1)]), LoadVarInst(Address(fRec13, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec13, kStruct)[Int32(0)], LoadVarInst(Address(fVec12, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow31, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec13, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec14, kStruct)[Int32(1)]), LoadVarInst(Address(fRec14, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], LoadVarInst(Address(fVec13, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow33, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec14, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec15, kStruct)[Int32(1)]), LoadVarInst(Address(fRec15, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec15, kStruct)[Int32(0)], LoadVarInst(Address(fVec14, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow35, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec15, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(1)]), LoadVarInst(Address(fRec16, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec16, kStruct)[Int32(0)], LoadVarInst(Address(fVec15, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow37, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec16, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec17, kStruct)[Int32(1)]), LoadVarInst(Address(fRec17, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec17, kStruct)[Int32(0)], LoadVarInst(Address(fVec16, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow39, kStack))), Int32(4095))]))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(fVec17, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec18, kStruct)[Int32(1)]), LoadVarInst(Address(fRec18, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec18, kStruct)[Int32(0)], LoadVarInst(Address(fVec17, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow41, kStack))), Int32(1023))]))
			StoreVarInst(Address(fVec18, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec19, kStruct)[Int32(1)]), LoadVarInst(Address(fRec19, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec19, kStruct)[Int32(0)], LoadVarInst(Address(fVec18, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow43, kStack))), Int32(2047))]))
			StoreVarInst(Address(fVec19, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec20, kStruct)[Int32(1)]), LoadVarInst(Address(fRec20, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec20, kStruct)[Int32(0)], LoadVarInst(Address(fVec19, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow45, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec20, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec21, kStruct)[Int32(1)]), LoadVarInst(Address(fRec21, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec21, kStruct)[Int32(0)], LoadVarInst(Address(fVec20, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow47, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec21, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec22, kStruct)[Int32(1)]), LoadVarInst(Address(fRec22, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec22, kStruct)[Int32(0)], LoadVarInst(Address(fVec21, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow49, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec22, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec23, kStruct)[Int32(1)]), LoadVarInst(Address(fRec23, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec23, kStruct)[Int32(0)], LoadVarInst(Address(fVec22, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow51, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec23, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec24, kStruct)[Int32(1)]), LoadVarInst(Address(fRec24, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec24, kStruct)[Int32(0)], LoadVarInst(Address(fVec23, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow53, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec24, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec25, kStruct)[Int32(1)]), LoadVarInst(Address(fRec25, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec25, kStruct)[Int32(0)], LoadVarInst(Address(fVec24, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow55, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec25, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec26, kStruct)[Int32(1)]), LoadVarInst(Address(fRec26, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec26, kStruct)[Int32(0)], LoadVarInst(Address(fVec25, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow57, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec26, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec27, kStruct)[Int32(1)]), LoadVarInst(Address(fRec27, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec27, kStruct)[Int32(0)], LoadVarInst(Address(fVec26, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow59, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec27, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec28, kStruct)[Int32(1)]), LoadVarInst(Address(fRec28, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec28, kStruct)[Int32(0)], LoadVarInst(Address(fVec27, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow61, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec28, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec29, kStruct)[Int32(1)]), LoadVarInst(Address(fRec29, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec29, kStruct)[Int32(0)], LoadVarInst(Address(fVec28, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow63, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec29, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec30, kStruct)[Int32(1)]), LoadVarInst(Address(fRec30, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec30, kStruct)[Int32(0)], LoadVarInst(Address(fVec29, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow65, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec30, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec31, kStruct)[Int32(1)]), LoadVarInst(Address(fRec31, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec31, kStruct)[Int32(0)], LoadVarInst(Address(fVec30, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow67, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec31, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec32, kStruct)[Int32(1)]), LoadVarInst(Address(fRec32, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec32, kStruct)[Int32(0)], LoadVarInst(Address(fVec31, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow69, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec32, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), BinopInst("+", LoadVarInst(Address(fRec33, kStruct)[Int32(1)]), LoadVarInst(Address(fRec33, kStruct)[Int32(2)])))))
			StoreVarInst(Address(fRec33, kStruct)[Int32(0)], LoadVarInst(Address(fVec32, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow71, kStack))), Int32(4095))]))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fRec18, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow58, kStack)), LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow60, kStack)), LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow68, kStack)), LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))))))
			StoreVarInst(Address(iRec1, kStruct)[Int32(1)], LoadVarInst(Address(iRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(2)], LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(2)], LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(2)], LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(2)], LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(2)], LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(2)], LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(2)], LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(2)], LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(2)], LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(2)], LoadVarInst(Address(fRec13, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(2)], LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(2)], LoadVarInst(Address(fRec15, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(2)], LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(2)], LoadVarInst(Address(fRec17, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(2)], LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(2)], LoadVarInst(Address(fRec19, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(2)], LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(2)], LoadVarInst(Address(fRec21, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(2)], LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec23, kStruct)[Int32(2)], LoadVarInst(Address(fRec23, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec24, kStruct)[Int32(2)], LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec25, kStruct)[Int32(2)], LoadVarInst(Address(fRec25, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec25, kStruct)[Int32(1)], LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec26, kStruct)[Int32(2)], LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec27, kStruct)[Int32(2)], LoadVarInst(Address(fRec27, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec27, kStruct)[Int32(1)], LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec28, kStruct)[Int32(2)], LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec29, kStruct)[Int32(2)], LoadVarInst(Address(fRec29, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec29, kStruct)[Int32(1)], LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec30, kStruct)[Int32(2)], LoadVarInst(Address(fRec30, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec31, kStruct)[Int32(2)], LoadVarInst(Address(fRec31, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec31, kStruct)[Int32(1)], LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec32, kStruct)[Int32(2)], LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec33, kStruct)[Int32(2)], LoadVarInst(Address(fRec33, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 481712 bytes
Total heap size = 481728 bytes
Stack size in compute = 304 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec3 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec4 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec5 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec6 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec7 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec8 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec9 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec9 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec10 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec10 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec11 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec11 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec12 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec12 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec13 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec13 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec14 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec14 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec15 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec15 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec16 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec16 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec17 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec17 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fRec18 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec18 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec19 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec19 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec20 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec20 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec21 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec21 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec22 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec22 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec23 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec23 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec24 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec24 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec25 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec25 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec26 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec26 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec27 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec27 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec28 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec28 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec29 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec29 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec30 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec30 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec31 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec31 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec32 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec32 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec33 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec3 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec4 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec5 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec6 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec7 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec8 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec8 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec9 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec9 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec10 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec10 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec11 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec11 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec12 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec12 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec13 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec13 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec14 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec14 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec15 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec15 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec16 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec16 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec17 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec17 size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fRec18 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec18 size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fRec19 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec19 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec20 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec20 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec21 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec21 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec22 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec22 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec23 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec23 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec24 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec24 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec25 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec25 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec26 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec26 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec27 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec27 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec28 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec28 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec29 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec29 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec30 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec30 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec31 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec31 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec32 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec32 size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fRec33 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = IOTA0 size = 1 size_bytes = 4 read = 65 write = 1 ratio = 66
Field = fVec1 size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec2 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec3 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec4 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec4 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec5 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec5 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec6 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec6 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec7 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec7 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec8 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec8 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec9 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec9 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec10 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec10 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec11 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec11 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec12 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec12 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec13 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec13 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec14 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec14 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec15 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec15 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec16 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec16 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec17 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec17 size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = fRec18 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec18 size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fRec19 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec19 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec20 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec20 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec21 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec21 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec22 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec22 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec23 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec23 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec24 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec24 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec25 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec25 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec26 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec26 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec27 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec27 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec28 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec28 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec29 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec29 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec30 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec30 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec31 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec31 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec32 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fVec32 size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fRec33 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
