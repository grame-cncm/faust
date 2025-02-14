======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("karplus32")
	OpenVerticalBox("excitator")
	AddHorizontalSlider("excitation (samples)", fHslider2, 128.0f, 2.0f, 512.0f, 1.0f)
	AddButtonInst("play"fButton0)
	CloseboxInst
	OpenVerticalBox("noise generator")
	AddHorizontalSlider("level", fHslider1, 0.5f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	AddHorizontalSlider("output volume", fHslider5, 0.4866f, 0.0f, 1.0f, 0.1f)
	OpenVerticalBox("resonator x32")
	AddHorizontalSlider("attenuation", fHslider0, 0.0f, 0.0f, 1.0f, 0.01f)
	AddHorizontalSlider("detune", fHslider4, 37.9904f, 0.0f, 512.0f, 1.0f)
	AddHorizontalSlider("duration (samples)", fHslider3, 128.0f, 2.0f, 512.0f, 1.0f)
	AddHorizontalSlider("polyphony", fHslider6, 14.0f, 0.0f, 32.0f, 1.0f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fButton0)("int", IOTA0)("float[2]", fVec0BE)("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("int[2]", iVec3SI)("FAUSTFLOAT", fHslider2)("float[2]", fVec5SE)("float[512]", fVec8SE)("FAUSTFLOAT", fHslider3)("float[2]", fVec1SE)("float[4]", fVec2SE)("float[2048]", fVec13SE)("FAUSTFLOAT", fHslider4)("float[2]", fVec11SE)("float[4]", fVec12SE)("float[4096]", fVec18SE)("float[2]", fVec16SE)("float[4]", fVec17SE)("float[4096]", fVec23SE)("float[2]", fVec21SE)("float[4]", fVec22SE)("float[4096]", fVec28SE)("float[2]", fVec26SE)("float[4]", fVec27SE)("float[4096]", fVec33SE)("float[2]", fVec31SE)("float[4]", fVec32SE)("float[4096]", fVec38SE)("float[2]", fVec36SE)("float[4]", fVec37SE)("float[4096]", fVec43SE)("float[2]", fVec41SE)("float[4]", fVec42SE)("float[4096]", fVec48SE)("float[2]", fVec46SE)("float[4]", fVec47SE)("float[4096]", fVec53SE)("float[2]", fVec51SE)("float[4]", fVec52SE)("float[4096]", fVec58SE)("float[2]", fVec56SE)("float[4]", fVec57SE)("float[4096]", fVec63SE)("float[2]", fVec61SE)("float[4]", fVec62SE)("float[4096]", fVec68SE)("float[2]", fVec66SE)("float[4]", fVec67SE)("float[4096]", fVec73SE)("float[2]", fVec71SE)("float[4]", fVec72SE)("float[4096]", fVec78SE)("float[2]", fVec76SE)("float[4]", fVec77SE)("float[4096]", fVec83SE)("float[2]", fVec81SE)("float[4]", fVec82SE)("FAUSTFLOAT", fHslider5)("FAUSTFLOAT", fHslider6)("float[1024]", fVec104SE)("float[2]", fVec102SE)("float[4]", fVec103SE)("float[2048]", fVec109SE)("float[2]", fVec107SE)("float[4]", fVec108SE)("float[4096]", fVec114SE)("float[2]", fVec112SE)("float[4]", fVec113SE)("float[4096]", fVec119SE)("float[2]", fVec117SE)("float[4]", fVec118SE)("float[4096]", fVec124SE)("float[2]", fVec122SE)("float[4]", fVec123SE)("float[4096]", fVec129SE)("float[2]", fVec127SE)("float[4]", fVec128SE)("float[4096]", fVec134SE)("float[2]", fVec132SE)("float[4]", fVec133SE)("float[4096]", fVec139SE)("float[2]", fVec137SE)("float[4]", fVec138SE)("float[4096]", fVec144SE)("float[2]", fVec142SE)("float[4]", fVec143SE)("float[4096]", fVec149SE)("float[2]", fVec147SE)("float[4]", fVec148SE)("float[4096]", fVec154SE)("float[2]", fVec152SE)("float[4]", fVec153SE)("float[4096]", fVec159SE)("float[2]", fVec157SE)("float[4]", fVec158SE)("float[4096]", fVec164SE)("float[2]", fVec162SE)("float[4]", fVec163SE)("float[4096]", fVec169SE)("float[2]", fVec167SE)("float[4]", fVec168SE)("float[4096]", fVec174SE)("float[2]", fVec172SE)("float[4]", fVec173SE)("float[4096]", fVec179SE)("float[2]", fVec177SE)("float[4]", fVec178SE)("int", fSampleRate)>)

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
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(128.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(128.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(37.9904f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.4866f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(14.0f)))
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
			StoreVarInst(Address(fVec0BE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec3SI, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(512))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2048))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(4))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(4096))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(4))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(4096))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(4))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(4096))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(4))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(4096))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec33SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(4))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(4096))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec38SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec36SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(4))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec37SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(4096))
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
			StoreVarInst(Address(fVec41SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(4))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec42SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(4096))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec48SE, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec46SE, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(4))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec47SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(4096))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec53SE, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec51SE, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(4))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec52SE, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(4096))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec58SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec56SE, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(4))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec57SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(4096))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec63SE, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec61SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(4))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec62SE, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(4096))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec68SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec66SE, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(4))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec67SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(4096))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec73SE, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec71SE, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(4))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec72SE, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(4096))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec78SE, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec76SE, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(4))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec77SE, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(4096))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec83SE, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec81SE, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(4))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec82SE, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(1024))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec104SE, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec102SE, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(4))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec103SE, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2048))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec109SE, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec107SE, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(4))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec108SE, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(4096))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec114SE, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec112SE, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(4))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec113SE, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(4096))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec119SE, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(2))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec117SE, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(4))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec118SE, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(4096))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec124SE, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(2))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec122SE, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(4))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec123SE, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(4096))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec129SE, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(2))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec127SE, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(4))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec128SE, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(4096))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec134SE, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(2))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec132SE, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(4))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec133SE, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(4096))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec139SE, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(2))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec137SE, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(4))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec138SE, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(4096))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec144SE, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l76, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l76, kLoop)), Int32(2))
		StoreVarInst(Address(l76, kLoop), BinopInst("+", LoadVarInst(Address(l76, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec142SE, kStruct)[LoadVarInst(Address(l76, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l77, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l77, kLoop)), Int32(4))
		StoreVarInst(Address(l77, kLoop), BinopInst("+", LoadVarInst(Address(l77, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec143SE, kStruct)[LoadVarInst(Address(l77, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l78, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l78, kLoop)), Int32(4096))
		StoreVarInst(Address(l78, kLoop), BinopInst("+", LoadVarInst(Address(l78, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec149SE, kStruct)[LoadVarInst(Address(l78, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l79, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l79, kLoop)), Int32(2))
		StoreVarInst(Address(l79, kLoop), BinopInst("+", LoadVarInst(Address(l79, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec147SE, kStruct)[LoadVarInst(Address(l79, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l80, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l80, kLoop)), Int32(4))
		StoreVarInst(Address(l80, kLoop), BinopInst("+", LoadVarInst(Address(l80, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec148SE, kStruct)[LoadVarInst(Address(l80, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l81, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l81, kLoop)), Int32(4096))
		StoreVarInst(Address(l81, kLoop), BinopInst("+", LoadVarInst(Address(l81, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec154SE, kStruct)[LoadVarInst(Address(l81, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l82, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l82, kLoop)), Int32(2))
		StoreVarInst(Address(l82, kLoop), BinopInst("+", LoadVarInst(Address(l82, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec152SE, kStruct)[LoadVarInst(Address(l82, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l83, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l83, kLoop)), Int32(4))
		StoreVarInst(Address(l83, kLoop), BinopInst("+", LoadVarInst(Address(l83, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec153SE, kStruct)[LoadVarInst(Address(l83, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l84, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l84, kLoop)), Int32(4096))
		StoreVarInst(Address(l84, kLoop), BinopInst("+", LoadVarInst(Address(l84, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec159SE, kStruct)[LoadVarInst(Address(l84, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l85, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l85, kLoop)), Int32(2))
		StoreVarInst(Address(l85, kLoop), BinopInst("+", LoadVarInst(Address(l85, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec157SE, kStruct)[LoadVarInst(Address(l85, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l86, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l86, kLoop)), Int32(4))
		StoreVarInst(Address(l86, kLoop), BinopInst("+", LoadVarInst(Address(l86, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec158SE, kStruct)[LoadVarInst(Address(l86, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l87, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l87, kLoop)), Int32(4096))
		StoreVarInst(Address(l87, kLoop), BinopInst("+", LoadVarInst(Address(l87, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec164SE, kStruct)[LoadVarInst(Address(l87, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l88, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l88, kLoop)), Int32(2))
		StoreVarInst(Address(l88, kLoop), BinopInst("+", LoadVarInst(Address(l88, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec162SE, kStruct)[LoadVarInst(Address(l88, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l89, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l89, kLoop)), Int32(4))
		StoreVarInst(Address(l89, kLoop), BinopInst("+", LoadVarInst(Address(l89, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec163SE, kStruct)[LoadVarInst(Address(l89, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l90, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l90, kLoop)), Int32(4096))
		StoreVarInst(Address(l90, kLoop), BinopInst("+", LoadVarInst(Address(l90, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec169SE, kStruct)[LoadVarInst(Address(l90, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l91, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l91, kLoop)), Int32(2))
		StoreVarInst(Address(l91, kLoop), BinopInst("+", LoadVarInst(Address(l91, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec167SE, kStruct)[LoadVarInst(Address(l91, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l92, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l92, kLoop)), Int32(4))
		StoreVarInst(Address(l92, kLoop), BinopInst("+", LoadVarInst(Address(l92, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec168SE, kStruct)[LoadVarInst(Address(l92, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l93, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l93, kLoop)), Int32(4096))
		StoreVarInst(Address(l93, kLoop), BinopInst("+", LoadVarInst(Address(l93, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec174SE, kStruct)[LoadVarInst(Address(l93, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l94, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l94, kLoop)), Int32(2))
		StoreVarInst(Address(l94, kLoop), BinopInst("+", LoadVarInst(Address(l94, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec172SE, kStruct)[LoadVarInst(Address(l94, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l95, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l95, kLoop)), Int32(4))
		StoreVarInst(Address(l95, kLoop), BinopInst("+", LoadVarInst(Address(l95, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec173SE, kStruct)[LoadVarInst(Address(l95, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l96, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l96, kLoop)), Int32(4096))
		StoreVarInst(Address(l96, kLoop), BinopInst("+", LoadVarInst(Address(l96, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec179SE, kStruct)[LoadVarInst(Address(l96, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l97, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l97, kLoop)), Int32(2))
		StoreVarInst(Address(l97, kLoop), BinopInst("+", LoadVarInst(Address(l97, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec177SE, kStruct)[LoadVarInst(Address(l97, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l98, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l98, kLoop)), Int32(4))
		StoreVarInst(Address(l98, kLoop), BinopInst("+", LoadVarInst(Address(l98, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec178SE, kStruct)[LoadVarInst(Address(l98, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 106 Store = 0 Binop = 161 [ { Int(&) = 32 } { Real(*) = 32 } { Real(+) = 64 } { Real(/) = 1 } { Real(>) = 32 } ] Mathop = 0 Numbers = 132 Declare = 75 Cast = 72 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, LoadVarInst(Address(fSlow0BE, kStack)))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", Float(0.5f), BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow5BE, kStack, CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))
	DeclareVarInst("int", iSlow6BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow7BE, kStack, CastInst("float", LoadVarInst(Address(fHslider4, kStruct))))
	DeclareVarInst("int", iSlow8BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow9BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(4.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow10BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(6.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow11BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(8.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow12BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(1e+01f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow13BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(12.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow14BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(14.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow15BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(16.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow16BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(18.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow17BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(2e+01f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow18BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(22.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow19BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(24.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow20BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(26.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow21BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(28.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow22BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(3e+01f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow23BE, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("float", fSlow24BE, kStack, CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))
	DeclareVarInst("float", fSlow25BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(0.0f))))
	DeclareVarInst("float", fSlow26BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(2.0f))))
	DeclareVarInst("float", fSlow27BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(4.0f))))
	DeclareVarInst("float", fSlow28BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(6.0f))))
	DeclareVarInst("float", fSlow29BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(8.0f))))
	DeclareVarInst("float", fSlow30BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(1e+01f))))
	DeclareVarInst("float", fSlow31BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(12.0f))))
	DeclareVarInst("float", fSlow32BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(14.0f))))
	DeclareVarInst("float", fSlow33BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(16.0f))))
	DeclareVarInst("float", fSlow34BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(18.0f))))
	DeclareVarInst("float", fSlow35BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(2e+01f))))
	DeclareVarInst("float", fSlow36BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(22.0f))))
	DeclareVarInst("float", fSlow37BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(24.0f))))
	DeclareVarInst("float", fSlow38BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(26.0f))))
	DeclareVarInst("float", fSlow39BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(28.0f))))
	DeclareVarInst("float", fSlow40BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(3e+01f))))
	DeclareVarInst("int", iSlow41BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fSlow7BE, kStack))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow42BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(3.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow43BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(5.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow44BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(7.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow45BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(9.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow46BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(11.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow47BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(13.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow48BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(15.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow49BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(17.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow50BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(19.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow51BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(21.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow52BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(23.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow53BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(25.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow54BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(27.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow55BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(29.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow56BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(31.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow57BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow58BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(3.0f))))
	DeclareVarInst("float", fSlow59BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(5.0f))))
	DeclareVarInst("float", fSlow60BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(7.0f))))
	DeclareVarInst("float", fSlow61BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(9.0f))))
	DeclareVarInst("float", fSlow62BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(11.0f))))
	DeclareVarInst("float", fSlow63BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(13.0f))))
	DeclareVarInst("float", fSlow64BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(15.0f))))
	DeclareVarInst("float", fSlow65BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(17.0f))))
	DeclareVarInst("float", fSlow66BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(19.0f))))
	DeclareVarInst("float", fSlow67BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(21.0f))))
	DeclareVarInst("float", fSlow68BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(23.0f))))
	DeclareVarInst("float", fSlow69BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(25.0f))))
	DeclareVarInst("float", fSlow70BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(27.0f))))
	DeclareVarInst("float", fSlow71BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(29.0f))))
	DeclareVarInst("float", fSlow72BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(31.0f))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 571 Store = 103 Binop = 538 [ { Int(&) = 264 } { Int(*) = 1 } { Int(+) = 3 } { Int(-) = 99 } { Int(<) = 1 } { Real(*) = 69 } { Real(+) = 98 } { Real(>) = 3 } ] Mathop = 0 Numbers = 340 Declare = 3 Cast = 6 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fSlow1BE, kStack)))
		StoreVarInst(Address(iVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
		DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), CastInst("float", BinopInst(">", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), MinusInst(LoadVarInst(Address(fVec0BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), Float(0.0f)))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp0SE, kStack)), Float(0.0f)))))))
		DeclareVarInst("float", fTemp1SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(iVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("+", CastInst("float", BinopInst(">", LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f))), Float(1.5258789e-05f)))))
		StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), LoadVarInst(Address(fTemp1SE, kStack))))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow6BE, kStack))), Int32(511))]))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow8BE, kStack))), Int32(2047))]))
		StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow9BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec23SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec23SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow10BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow11BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec33SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec33SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow12BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec37SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow13BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec37SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec43SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec43SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow14BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec47SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow15BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec47SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec53SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec53SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow16BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec58SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec57SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec58SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow17BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec57SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec63SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec62SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec63SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow18BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec62SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec68SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec67SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec68SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow19BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec67SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec73SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec73SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow20BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec78SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec77SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec78SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow21BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec77SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow22BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec104SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec102SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec103SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec102SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec104SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow41BE, kStack))), Int32(1023))]))
		StoreVarInst(Address(fVec103SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec102SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec109SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec108SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec109SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow42BE, kStack))), Int32(2047))]))
		StoreVarInst(Address(fVec108SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec114SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec112SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec113SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec112SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec114SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow43BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec113SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec112SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec119SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec118SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec119SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow44BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec118SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec124SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec122SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec123SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec122SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec124SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow45BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec123SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec122SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec129SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec128SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec127SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec129SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow46BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec128SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec134SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec132SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec133SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec132SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec134SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow47BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec133SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec132SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec139SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec137SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec138SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec137SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec139SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow48BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec138SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec137SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec144SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec142SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec143SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec142SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec144SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow49BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec143SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec142SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec149SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec147SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec148SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec147SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec149SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow50BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec148SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec147SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec154SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec152SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec153SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec152SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec154SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow51BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec153SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec152SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec159SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec157SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec158SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec157SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec159SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow52BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec158SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec157SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec164SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec162SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec163SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec162SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec164SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow53BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec163SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec162SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec169SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec167SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec168SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec167SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec169SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow54BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec168SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec167SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec174SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec172SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec173SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec172SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec174SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow55BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec173SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec172SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec179SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec177SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec178SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
		StoreVarInst(Address(fVec177SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec179SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow56BE, kStack))), Int32(4095))]))
		StoreVarInst(Address(fVec178SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec177SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow25BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow26BE, kStack)), LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow27BE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow28BE, kStack)), LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow29BE, kStack)), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow30BE, kStack)), LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow31BE, kStack)), LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow32BE, kStack)), LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow34BE, kStack)), LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow35BE, kStack)), LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow36BE, kStack)), LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow38BE, kStack)), LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow39BE, kStack)), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow40BE, kStack)), LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow57BE, kStack)), LoadVarInst(Address(fVec102SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow58BE, kStack)), LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow59BE, kStack)), LoadVarInst(Address(fVec112SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow60BE, kStack)), LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow61BE, kStack)), LoadVarInst(Address(fVec122SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow62BE, kStack)), LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow63BE, kStack)), LoadVarInst(Address(fVec132SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow64BE, kStack)), LoadVarInst(Address(fVec137SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow65BE, kStack)), LoadVarInst(Address(fVec142SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), LoadVarInst(Address(fVec147SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow67BE, kStack)), LoadVarInst(Address(fVec152SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow68BE, kStack)), LoadVarInst(Address(fVec157SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow69BE, kStack)), LoadVarInst(Address(fVec162SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow70BE, kStack)), LoadVarInst(Address(fVec167SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow71BE, kStack)), LoadVarInst(Address(fVec172SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow72BE, kStack)), LoadVarInst(Address(fVec177SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
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
	DeclareVarInst("FAUSTFLOAT", fButton0, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec0BE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	// Recursion delay iVec3SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec3SI[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	// Recursion delay fVec5SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec5SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec8SE[512], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec2SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec13SE[2048], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	// Recursion delay fVec11SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec11SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec12SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec18SE[4096], kStruct)
	// Recursion delay fVec16SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec16SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec17SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec23SE[4096], kStruct)
	// Recursion delay fVec21SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec21SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec22SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec28SE[4096], kStruct)
	// Recursion delay fVec26SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec26SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec27SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec33SE[4096], kStruct)
	// Recursion delay fVec31SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec31SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec32SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec38SE[4096], kStruct)
	// Recursion delay fVec36SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec36SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec37SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec43SE[4096], kStruct)
	// Recursion delay fVec41SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec41SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec42SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec48SE[4096], kStruct)
	// Recursion delay fVec46SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec46SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec47SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec53SE[4096], kStruct)
	// Recursion delay fVec51SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec51SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec52SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec58SE[4096], kStruct)
	// Recursion delay fVec56SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec56SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec57SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec63SE[4096], kStruct)
	// Recursion delay fVec61SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec61SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec62SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec68SE[4096], kStruct)
	// Recursion delay fVec66SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec66SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec67SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec73SE[4096], kStruct)
	// Recursion delay fVec71SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec71SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec72SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec78SE[4096], kStruct)
	// Recursion delay fVec76SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec76SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec77SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec83SE[4096], kStruct)
	// Recursion delay fVec81SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec81SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec82SE[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider6, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec104SE[1024], kStruct)
	// Recursion delay fVec102SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec102SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec103SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec109SE[2048], kStruct)
	// Recursion delay fVec107SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec107SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec108SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec114SE[4096], kStruct)
	// Recursion delay fVec112SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec112SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec113SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec119SE[4096], kStruct)
	// Recursion delay fVec117SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec117SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec118SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec124SE[4096], kStruct)
	// Recursion delay fVec122SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec122SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec123SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec129SE[4096], kStruct)
	// Recursion delay fVec127SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec127SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec128SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec134SE[4096], kStruct)
	// Recursion delay fVec132SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec132SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec133SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec139SE[4096], kStruct)
	// Recursion delay fVec137SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec137SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec138SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec144SE[4096], kStruct)
	// Recursion delay fVec142SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec142SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec143SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec149SE[4096], kStruct)
	// Recursion delay fVec147SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec147SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec148SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec154SE[4096], kStruct)
	// Recursion delay fVec152SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec152SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec153SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec159SE[4096], kStruct)
	// Recursion delay fVec157SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec157SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec158SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec164SE[4096], kStruct)
	// Recursion delay fVec162SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec162SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec163SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec169SE[4096], kStruct)
	// Recursion delay fVec167SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec167SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec168SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec174SE[4096], kStruct)
	// Recursion delay fVec172SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec172SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec173SE[4], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec179SE[4096], kStruct)
	// Recursion delay fVec177SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec177SE[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec178SE[4], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fButton0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.5f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(128.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(128.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(37.9904f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.4866f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(14.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0BE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec3SI, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(512))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec8SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(4))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2048))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec13SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec11SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(4))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(4096))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec16SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(4))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec17SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(4096))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec23SE, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(4))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22SE, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(4096))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec28SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(4))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec27SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(4096))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec33SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec31SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(4))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(4096))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec38SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec36SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(4))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec37SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(4096))
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
			StoreVarInst(Address(fVec41SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(4))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec42SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(4096))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec48SE, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec46SE, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(4))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec47SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(4096))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec53SE, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec51SE, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(4))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec52SE, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(4096))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec58SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec56SE, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(4))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec57SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(4096))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec63SE, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec61SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(4))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec62SE, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(4096))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec68SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec66SE, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(4))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec67SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(4096))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec73SE, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l43, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l43, kLoop)), Int32(2))
		StoreVarInst(Address(l43, kLoop), BinopInst("+", LoadVarInst(Address(l43, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec71SE, kStruct)[LoadVarInst(Address(l43, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l44, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l44, kLoop)), Int32(4))
		StoreVarInst(Address(l44, kLoop), BinopInst("+", LoadVarInst(Address(l44, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec72SE, kStruct)[LoadVarInst(Address(l44, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l45, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l45, kLoop)), Int32(4096))
		StoreVarInst(Address(l45, kLoop), BinopInst("+", LoadVarInst(Address(l45, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec78SE, kStruct)[LoadVarInst(Address(l45, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l46, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l46, kLoop)), Int32(2))
		StoreVarInst(Address(l46, kLoop), BinopInst("+", LoadVarInst(Address(l46, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec76SE, kStruct)[LoadVarInst(Address(l46, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l47, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l47, kLoop)), Int32(4))
		StoreVarInst(Address(l47, kLoop), BinopInst("+", LoadVarInst(Address(l47, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec77SE, kStruct)[LoadVarInst(Address(l47, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l48, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l48, kLoop)), Int32(4096))
		StoreVarInst(Address(l48, kLoop), BinopInst("+", LoadVarInst(Address(l48, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec83SE, kStruct)[LoadVarInst(Address(l48, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l49, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l49, kLoop)), Int32(2))
		StoreVarInst(Address(l49, kLoop), BinopInst("+", LoadVarInst(Address(l49, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec81SE, kStruct)[LoadVarInst(Address(l49, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l50, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l50, kLoop)), Int32(4))
		StoreVarInst(Address(l50, kLoop), BinopInst("+", LoadVarInst(Address(l50, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec82SE, kStruct)[LoadVarInst(Address(l50, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l51, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l51, kLoop)), Int32(1024))
		StoreVarInst(Address(l51, kLoop), BinopInst("+", LoadVarInst(Address(l51, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec104SE, kStruct)[LoadVarInst(Address(l51, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l52, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l52, kLoop)), Int32(2))
		StoreVarInst(Address(l52, kLoop), BinopInst("+", LoadVarInst(Address(l52, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec102SE, kStruct)[LoadVarInst(Address(l52, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l53, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l53, kLoop)), Int32(4))
		StoreVarInst(Address(l53, kLoop), BinopInst("+", LoadVarInst(Address(l53, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec103SE, kStruct)[LoadVarInst(Address(l53, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l54, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l54, kLoop)), Int32(2048))
		StoreVarInst(Address(l54, kLoop), BinopInst("+", LoadVarInst(Address(l54, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec109SE, kStruct)[LoadVarInst(Address(l54, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l55, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l55, kLoop)), Int32(2))
		StoreVarInst(Address(l55, kLoop), BinopInst("+", LoadVarInst(Address(l55, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec107SE, kStruct)[LoadVarInst(Address(l55, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l56, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l56, kLoop)), Int32(4))
		StoreVarInst(Address(l56, kLoop), BinopInst("+", LoadVarInst(Address(l56, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec108SE, kStruct)[LoadVarInst(Address(l56, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l57, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l57, kLoop)), Int32(4096))
		StoreVarInst(Address(l57, kLoop), BinopInst("+", LoadVarInst(Address(l57, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec114SE, kStruct)[LoadVarInst(Address(l57, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l58, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l58, kLoop)), Int32(2))
		StoreVarInst(Address(l58, kLoop), BinopInst("+", LoadVarInst(Address(l58, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec112SE, kStruct)[LoadVarInst(Address(l58, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l59, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l59, kLoop)), Int32(4))
		StoreVarInst(Address(l59, kLoop), BinopInst("+", LoadVarInst(Address(l59, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec113SE, kStruct)[LoadVarInst(Address(l59, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l60, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l60, kLoop)), Int32(4096))
		StoreVarInst(Address(l60, kLoop), BinopInst("+", LoadVarInst(Address(l60, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec119SE, kStruct)[LoadVarInst(Address(l60, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l61, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l61, kLoop)), Int32(2))
		StoreVarInst(Address(l61, kLoop), BinopInst("+", LoadVarInst(Address(l61, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec117SE, kStruct)[LoadVarInst(Address(l61, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l62, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l62, kLoop)), Int32(4))
		StoreVarInst(Address(l62, kLoop), BinopInst("+", LoadVarInst(Address(l62, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec118SE, kStruct)[LoadVarInst(Address(l62, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l63, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l63, kLoop)), Int32(4096))
		StoreVarInst(Address(l63, kLoop), BinopInst("+", LoadVarInst(Address(l63, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec124SE, kStruct)[LoadVarInst(Address(l63, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l64, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l64, kLoop)), Int32(2))
		StoreVarInst(Address(l64, kLoop), BinopInst("+", LoadVarInst(Address(l64, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec122SE, kStruct)[LoadVarInst(Address(l64, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l65, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l65, kLoop)), Int32(4))
		StoreVarInst(Address(l65, kLoop), BinopInst("+", LoadVarInst(Address(l65, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec123SE, kStruct)[LoadVarInst(Address(l65, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l66, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l66, kLoop)), Int32(4096))
		StoreVarInst(Address(l66, kLoop), BinopInst("+", LoadVarInst(Address(l66, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec129SE, kStruct)[LoadVarInst(Address(l66, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l67, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l67, kLoop)), Int32(2))
		StoreVarInst(Address(l67, kLoop), BinopInst("+", LoadVarInst(Address(l67, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec127SE, kStruct)[LoadVarInst(Address(l67, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l68, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l68, kLoop)), Int32(4))
		StoreVarInst(Address(l68, kLoop), BinopInst("+", LoadVarInst(Address(l68, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec128SE, kStruct)[LoadVarInst(Address(l68, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l69, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l69, kLoop)), Int32(4096))
		StoreVarInst(Address(l69, kLoop), BinopInst("+", LoadVarInst(Address(l69, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec134SE, kStruct)[LoadVarInst(Address(l69, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l70, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l70, kLoop)), Int32(2))
		StoreVarInst(Address(l70, kLoop), BinopInst("+", LoadVarInst(Address(l70, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec132SE, kStruct)[LoadVarInst(Address(l70, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l71, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l71, kLoop)), Int32(4))
		StoreVarInst(Address(l71, kLoop), BinopInst("+", LoadVarInst(Address(l71, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec133SE, kStruct)[LoadVarInst(Address(l71, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l72, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l72, kLoop)), Int32(4096))
		StoreVarInst(Address(l72, kLoop), BinopInst("+", LoadVarInst(Address(l72, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec139SE, kStruct)[LoadVarInst(Address(l72, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l73, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l73, kLoop)), Int32(2))
		StoreVarInst(Address(l73, kLoop), BinopInst("+", LoadVarInst(Address(l73, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec137SE, kStruct)[LoadVarInst(Address(l73, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l74, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l74, kLoop)), Int32(4))
		StoreVarInst(Address(l74, kLoop), BinopInst("+", LoadVarInst(Address(l74, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec138SE, kStruct)[LoadVarInst(Address(l74, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l75, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l75, kLoop)), Int32(4096))
		StoreVarInst(Address(l75, kLoop), BinopInst("+", LoadVarInst(Address(l75, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec144SE, kStruct)[LoadVarInst(Address(l75, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l76, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l76, kLoop)), Int32(2))
		StoreVarInst(Address(l76, kLoop), BinopInst("+", LoadVarInst(Address(l76, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec142SE, kStruct)[LoadVarInst(Address(l76, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l77, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l77, kLoop)), Int32(4))
		StoreVarInst(Address(l77, kLoop), BinopInst("+", LoadVarInst(Address(l77, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec143SE, kStruct)[LoadVarInst(Address(l77, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l78, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l78, kLoop)), Int32(4096))
		StoreVarInst(Address(l78, kLoop), BinopInst("+", LoadVarInst(Address(l78, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec149SE, kStruct)[LoadVarInst(Address(l78, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l79, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l79, kLoop)), Int32(2))
		StoreVarInst(Address(l79, kLoop), BinopInst("+", LoadVarInst(Address(l79, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec147SE, kStruct)[LoadVarInst(Address(l79, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l80, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l80, kLoop)), Int32(4))
		StoreVarInst(Address(l80, kLoop), BinopInst("+", LoadVarInst(Address(l80, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec148SE, kStruct)[LoadVarInst(Address(l80, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l81, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l81, kLoop)), Int32(4096))
		StoreVarInst(Address(l81, kLoop), BinopInst("+", LoadVarInst(Address(l81, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec154SE, kStruct)[LoadVarInst(Address(l81, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l82, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l82, kLoop)), Int32(2))
		StoreVarInst(Address(l82, kLoop), BinopInst("+", LoadVarInst(Address(l82, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec152SE, kStruct)[LoadVarInst(Address(l82, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l83, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l83, kLoop)), Int32(4))
		StoreVarInst(Address(l83, kLoop), BinopInst("+", LoadVarInst(Address(l83, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec153SE, kStruct)[LoadVarInst(Address(l83, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l84, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l84, kLoop)), Int32(4096))
		StoreVarInst(Address(l84, kLoop), BinopInst("+", LoadVarInst(Address(l84, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec159SE, kStruct)[LoadVarInst(Address(l84, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l85, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l85, kLoop)), Int32(2))
		StoreVarInst(Address(l85, kLoop), BinopInst("+", LoadVarInst(Address(l85, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec157SE, kStruct)[LoadVarInst(Address(l85, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l86, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l86, kLoop)), Int32(4))
		StoreVarInst(Address(l86, kLoop), BinopInst("+", LoadVarInst(Address(l86, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec158SE, kStruct)[LoadVarInst(Address(l86, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l87, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l87, kLoop)), Int32(4096))
		StoreVarInst(Address(l87, kLoop), BinopInst("+", LoadVarInst(Address(l87, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec164SE, kStruct)[LoadVarInst(Address(l87, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l88, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l88, kLoop)), Int32(2))
		StoreVarInst(Address(l88, kLoop), BinopInst("+", LoadVarInst(Address(l88, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec162SE, kStruct)[LoadVarInst(Address(l88, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l89, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l89, kLoop)), Int32(4))
		StoreVarInst(Address(l89, kLoop), BinopInst("+", LoadVarInst(Address(l89, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec163SE, kStruct)[LoadVarInst(Address(l89, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l90, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l90, kLoop)), Int32(4096))
		StoreVarInst(Address(l90, kLoop), BinopInst("+", LoadVarInst(Address(l90, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec169SE, kStruct)[LoadVarInst(Address(l90, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l91, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l91, kLoop)), Int32(2))
		StoreVarInst(Address(l91, kLoop), BinopInst("+", LoadVarInst(Address(l91, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec167SE, kStruct)[LoadVarInst(Address(l91, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l92, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l92, kLoop)), Int32(4))
		StoreVarInst(Address(l92, kLoop), BinopInst("+", LoadVarInst(Address(l92, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec168SE, kStruct)[LoadVarInst(Address(l92, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l93, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l93, kLoop)), Int32(4096))
		StoreVarInst(Address(l93, kLoop), BinopInst("+", LoadVarInst(Address(l93, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec174SE, kStruct)[LoadVarInst(Address(l93, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l94, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l94, kLoop)), Int32(2))
		StoreVarInst(Address(l94, kLoop), BinopInst("+", LoadVarInst(Address(l94, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec172SE, kStruct)[LoadVarInst(Address(l94, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l95, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l95, kLoop)), Int32(4))
		StoreVarInst(Address(l95, kLoop), BinopInst("+", LoadVarInst(Address(l95, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec173SE, kStruct)[LoadVarInst(Address(l95, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l96, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l96, kLoop)), Int32(4096))
		StoreVarInst(Address(l96, kLoop), BinopInst("+", LoadVarInst(Address(l96, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec179SE, kStruct)[LoadVarInst(Address(l96, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l97, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l97, kLoop)), Int32(2))
		StoreVarInst(Address(l97, kLoop), BinopInst("+", LoadVarInst(Address(l97, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec177SE, kStruct)[LoadVarInst(Address(l97, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l98, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l98, kLoop)), Int32(4))
		StoreVarInst(Address(l98, kLoop), BinopInst("+", LoadVarInst(Address(l98, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec178SE, kStruct)[LoadVarInst(Address(l98, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fButton0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, LoadVarInst(Address(fSlow0BE, kStack)))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", Float(0.5f), BinopInst("+", Float(1.0f), MinusInst(CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("/", Float(1.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow5BE, kStack, CastInst("float", LoadVarInst(Address(fHslider3, kStruct))))
	DeclareVarInst("int", iSlow6BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow7BE, kStack, CastInst("float", LoadVarInst(Address(fHslider4, kStruct))))
	DeclareVarInst("int", iSlow8BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(2.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow9BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(4.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow10BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(6.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow11BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(8.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow12BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(1e+01f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow13BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(12.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow14BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(14.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow15BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(16.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow16BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(18.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow17BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(2e+01f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow18BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(22.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow19BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(24.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow20BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(26.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow21BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(28.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow22BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(3e+01f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow23BE, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("float", fSlow24BE, kStack, CastInst("float", LoadVarInst(Address(fHslider6, kStruct))))
	DeclareVarInst("float", fSlow25BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(0.0f))))
	DeclareVarInst("float", fSlow26BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(2.0f))))
	DeclareVarInst("float", fSlow27BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(4.0f))))
	DeclareVarInst("float", fSlow28BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(6.0f))))
	DeclareVarInst("float", fSlow29BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(8.0f))))
	DeclareVarInst("float", fSlow30BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(1e+01f))))
	DeclareVarInst("float", fSlow31BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(12.0f))))
	DeclareVarInst("float", fSlow32BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(14.0f))))
	DeclareVarInst("float", fSlow33BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(16.0f))))
	DeclareVarInst("float", fSlow34BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(18.0f))))
	DeclareVarInst("float", fSlow35BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(2e+01f))))
	DeclareVarInst("float", fSlow36BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(22.0f))))
	DeclareVarInst("float", fSlow37BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(24.0f))))
	DeclareVarInst("float", fSlow38BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(26.0f))))
	DeclareVarInst("float", fSlow39BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(28.0f))))
	DeclareVarInst("float", fSlow40BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(3e+01f))))
	DeclareVarInst("int", iSlow41BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fSlow7BE, kStack))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow42BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(3.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow43BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(5.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow44BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(7.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow45BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(9.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow46BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(11.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow47BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(13.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow48BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(15.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow49BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(17.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow50BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(19.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow51BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(21.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow52BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(23.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow53BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(25.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow54BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(27.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow55BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(29.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("int", iSlow56BE, kStack, BinopInst("&", CastInst("int", BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("*", Float(31.0f), LoadVarInst(Address(fSlow7BE, kStack)))), Float(-1.5f))), Int32(4095)))
	DeclareVarInst("float", fSlow57BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow58BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(3.0f))))
	DeclareVarInst("float", fSlow59BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(5.0f))))
	DeclareVarInst("float", fSlow60BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(7.0f))))
	DeclareVarInst("float", fSlow61BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(9.0f))))
	DeclareVarInst("float", fSlow62BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(11.0f))))
	DeclareVarInst("float", fSlow63BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(13.0f))))
	DeclareVarInst("float", fSlow64BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(15.0f))))
	DeclareVarInst("float", fSlow65BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(17.0f))))
	DeclareVarInst("float", fSlow66BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(19.0f))))
	DeclareVarInst("float", fSlow67BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(21.0f))))
	DeclareVarInst("float", fSlow68BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(23.0f))))
	DeclareVarInst("float", fSlow69BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(25.0f))))
	DeclareVarInst("float", fSlow70BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(27.0f))))
	DeclareVarInst("float", fSlow71BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(29.0f))))
	DeclareVarInst("float", fSlow72BE, kStack, CastInst("float", BinopInst(">", LoadVarInst(Address(fSlow24BE, kStack)), Float(31.0f))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0BE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fSlow1BE, kStack)))
			StoreVarInst(Address(iVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec3SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
			DeclareVarInst("float", fTemp0SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp0SE, kStack)), CastInst("float", BinopInst(">", BinopInst("+", LoadVarInst(Address(fSlow0BE, kStack)), MinusInst(LoadVarInst(Address(fVec0BE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), Float(0.0f)))), MinusInst(BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), CastInst("float", BinopInst(">", LoadVarInst(Address(fTemp0SE, kStack)), Float(0.0f)))))))
			DeclareVarInst("float", fTemp1SE, kStack, BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), BinopInst("*", CastInst("float", LoadVarInst(Address(iVec3SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("+", CastInst("float", BinopInst(">", LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), Float(0.0f))), Float(1.5258789e-05f)))))
			StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(511))], BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), LoadVarInst(Address(fTemp1SE, kStack))))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow6BE, kStack))), Int32(511))]))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec13SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec13SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow8BE, kStack))), Int32(2047))]))
			StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec17SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow9BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec17SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec23SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec23SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow10BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec27SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow11BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec27SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec33SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec33SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow12BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec37SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow13BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec37SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec43SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec43SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow14BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec47SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow15BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec47SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec53SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec53SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow16BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec58SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec57SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec58SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow17BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec57SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec63SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec62SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec63SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow18BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec62SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec68SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec67SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec68SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow19BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec67SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec73SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec73SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow20BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec78SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec77SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec78SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow21BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec77SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec83SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec83SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow22BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec104SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1023))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec102SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec103SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec102SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec104SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow41BE, kStack))), Int32(1023))]))
			StoreVarInst(Address(fVec103SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec102SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec109SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(2047))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec108SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec109SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow42BE, kStack))), Int32(2047))]))
			StoreVarInst(Address(fVec108SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec114SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec112SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec113SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec112SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec114SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow43BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec113SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec112SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec119SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec118SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec119SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow44BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec118SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec124SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec122SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec123SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec122SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec124SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow45BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec123SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec122SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec129SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec128SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec127SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec129SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow46BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec128SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec134SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec132SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec133SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec132SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec134SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow47BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec133SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec132SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec139SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec137SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec138SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec137SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec139SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow48BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec138SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec137SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec144SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec142SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec143SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec142SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec144SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow49BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec143SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec142SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec149SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec147SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec148SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec147SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec149SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow50BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec148SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec147SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec154SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec152SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec153SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec152SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec154SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow51BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec153SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec152SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec159SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec157SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec158SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec157SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec159SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow52BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec158SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec157SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec164SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec162SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec163SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec162SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec164SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow53BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec163SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec162SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec169SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec167SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec168SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec167SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec169SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow54BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec168SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec167SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec174SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec172SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec173SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec172SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec174SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow55BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec173SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec172SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec179SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(4095))], BinopInst("+", LoadVarInst(Address(fTemp1SE, kStack)), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("+", LoadVarInst(Address(fVec177SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]), LoadVarInst(Address(fVec178SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])))))
			StoreVarInst(Address(fVec177SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec179SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow56BE, kStack))), Int32(4095))]))
			StoreVarInst(Address(fVec178SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec177SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow25BE, kStack)), LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow26BE, kStack)), LoadVarInst(Address(fVec11SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow27BE, kStack)), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow28BE, kStack)), LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow29BE, kStack)), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow30BE, kStack)), LoadVarInst(Address(fVec31SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow31BE, kStack)), LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow32BE, kStack)), LoadVarInst(Address(fVec41SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow34BE, kStack)), LoadVarInst(Address(fVec51SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow35BE, kStack)), LoadVarInst(Address(fVec56SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow36BE, kStack)), LoadVarInst(Address(fVec61SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow37BE, kStack)), LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow38BE, kStack)), LoadVarInst(Address(fVec71SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow39BE, kStack)), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow40BE, kStack)), LoadVarInst(Address(fVec81SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow57BE, kStack)), LoadVarInst(Address(fVec102SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), BinopInst("*", LoadVarInst(Address(fSlow58BE, kStack)), LoadVarInst(Address(fVec107SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow59BE, kStack)), LoadVarInst(Address(fVec112SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow60BE, kStack)), LoadVarInst(Address(fVec117SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow61BE, kStack)), LoadVarInst(Address(fVec122SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow62BE, kStack)), LoadVarInst(Address(fVec127SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow63BE, kStack)), LoadVarInst(Address(fVec132SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow64BE, kStack)), LoadVarInst(Address(fVec137SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow65BE, kStack)), LoadVarInst(Address(fVec142SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), LoadVarInst(Address(fVec147SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow67BE, kStack)), LoadVarInst(Address(fVec152SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow68BE, kStack)), LoadVarInst(Address(fVec157SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow69BE, kStack)), LoadVarInst(Address(fVec162SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow70BE, kStack)), LoadVarInst(Address(fVec167SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow71BE, kStack)), LoadVarInst(Address(fVec172SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))), BinopInst("*", LoadVarInst(Address(fSlow72BE, kStack)), LoadVarInst(Address(fVec177SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 482096 bytes
Total heap size = 482112 bytes
Stack size in compute = 308 bytes

======= Variable access in Control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec3SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec13SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec11SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec18SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec23SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec21SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec28SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec33SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec31SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec38SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec36SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec37SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec43SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec41SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec42SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec48SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec46SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec47SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec53SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec51SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec52SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec58SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec56SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec57SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec63SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec61SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec62SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec68SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec66SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec67SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec73SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec71SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec72SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec78SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec76SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec77SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec83SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec81SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec82SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec104SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fVec102SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec103SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec109SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec107SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec108SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec114SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec112SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec113SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec119SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec117SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec118SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec124SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec122SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec123SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec129SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec127SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec128SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec134SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec132SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec133SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec139SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec137SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec138SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec144SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec142SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec143SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec149SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec147SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec148SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec154SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec152SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec153SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec159SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec157SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec158SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec164SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec162SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec163SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec169SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec167SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec168SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec174SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec172SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec173SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec179SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec177SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec178SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fButton0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0BE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec3SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 512 size_bytes = 2048 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec13SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec11SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec18SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec17SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec23SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec21SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec28SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec27SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec33SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec31SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec38SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec36SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec37SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec43SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec41SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec42SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec48SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec46SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec47SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec53SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec51SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec52SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec58SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec56SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec57SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec63SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec61SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec62SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec68SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec66SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec67SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec73SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec71SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec72SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec78SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec76SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec77SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec83SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec81SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec82SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec104SE size = 1024 size_bytes = 4096 read = 0 write = 0 ratio = 0
Field = fVec102SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec103SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec109SE size = 2048 size_bytes = 8192 read = 0 write = 0 ratio = 0
Field = fVec107SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec108SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec114SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec112SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec113SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec119SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec117SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec118SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec124SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec122SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec123SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec129SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec127SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec128SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec134SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec132SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec133SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec139SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec137SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec138SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec144SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec142SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec143SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec149SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec147SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec148SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec154SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec152SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec153SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec159SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec157SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec158SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec164SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec162SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec163SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec169SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec167SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec168SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec174SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec172SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec173SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec179SE size = 4096 size_bytes = 16384 read = 0 write = 0 ratio = 0
Field = fVec177SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec178SE size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fButton0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 265 write = 1 ratio = 266
Field = fVec0BE size = 2 size_bytes = 8 read = 1 write = 1 ratio = 1
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec3SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec8SE size = 512 size_bytes = 2048 read = 1 write = 1 ratio = 0.00390625
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec2SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec13SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec11SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec12SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec18SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec16SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec17SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec23SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec21SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec22SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec28SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec26SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec27SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec33SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec31SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec32SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec38SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec36SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec37SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec43SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec41SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec42SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec48SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec46SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec47SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec53SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec51SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec52SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec58SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec56SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec57SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec63SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec61SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec62SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec68SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec66SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec67SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec73SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec71SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec72SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec78SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec76SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec77SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec83SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec81SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec82SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec104SE size = 1024 size_bytes = 4096 read = 1 write = 1 ratio = 0.00195312
Field = fVec102SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec103SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec109SE size = 2048 size_bytes = 8192 read = 1 write = 1 ratio = 0.000976562
Field = fVec107SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec108SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec114SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec112SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec113SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec119SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec117SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec118SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec124SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec122SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec123SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec129SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec127SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec128SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec134SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec132SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec133SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec139SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec137SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec138SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec144SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec142SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec143SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec149SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec147SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec148SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec154SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec152SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec153SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec159SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec157SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec158SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec164SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec162SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec163SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec169SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec167SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec168SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec174SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec172SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec173SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fVec179SE size = 4096 size_bytes = 16384 read = 1 write = 1 ratio = 0.000488281
Field = fVec177SE size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec178SE size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
