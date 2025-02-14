======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("priority1")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("float[2]", fVec0SE)("float[2]", fVec2SE)("float[2]", fVec4SE)("float[2]", fVec6SE)("float[2]", fVec8SE)("float[2]", fVec10SE)("float[2]", fVec12SE)("float[2]", fVec14SE)("float[2]", fVec16SE)("float[2]", fVec18SE)("float[2]", fVec20SE)("float[2]", fVec22SE)("float[2]", fVec24SE)("float[2]", fVec26SE)("float[2]", fVec28SE)("float[2]", fVec30SE)("float[2]", fVec32SE)("float[2]", fVec34SE)("float[2]", fVec36SE)("float[2]", fVec38SE)("float[2]", fVec40SE)("float[2]", fVec42SE)("float[2]", fVec44SE)("float[2]", fVec46SE)("float[2]", fVec48SE)("float[2]", fVec50SE)("float[2]", fVec52SE)("float[2]", fVec54SI)("float[2]", fVec56SI)("float[2]", fVec58SE)("float[2]", fVec60SI)("float[2]", fVec62SI)("float[2]", fVec64SE)("float[2]", fVec66SE)("float[2]", fVec68SE)("float[2]", fVec70SE)("float[2]", fVec72SE)("float[2]", fVec74SE)("float[2]", fVec76SE)("float[2]", fVec78SE)("float[2]", fVec80SE)("float[2]", fVec82SE)("float[2]", fVec84SE)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(110))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(31))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

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
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
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
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec36SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec38SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec40SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec42SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec44SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec46SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec48SE, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec50SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec52SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec54SI, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec56SI, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec58SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec60SI, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec62SI, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec66SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec70SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec74SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec78SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec82SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
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
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 141 Store = 0 Binop = 0 Mathop = 0 Numbers = 141 Declare = 141 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", input6, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", input7, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", input8, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", input9, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", input10, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("FAUSTFLOAT*", input11, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(11)]))
	DeclareVarInst("FAUSTFLOAT*", input12, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(12)]))
	DeclareVarInst("FAUSTFLOAT*", input13, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(13)]))
	DeclareVarInst("FAUSTFLOAT*", input14, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(14)]))
	DeclareVarInst("FAUSTFLOAT*", input15, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(15)]))
	DeclareVarInst("FAUSTFLOAT*", input16, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(16)]))
	DeclareVarInst("FAUSTFLOAT*", input17, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(17)]))
	DeclareVarInst("FAUSTFLOAT*", input18, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(18)]))
	DeclareVarInst("FAUSTFLOAT*", input19, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(19)]))
	DeclareVarInst("FAUSTFLOAT*", input20, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(20)]))
	DeclareVarInst("FAUSTFLOAT*", input21, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(21)]))
	DeclareVarInst("FAUSTFLOAT*", input22, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(22)]))
	DeclareVarInst("FAUSTFLOAT*", input23, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(23)]))
	DeclareVarInst("FAUSTFLOAT*", input24, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(24)]))
	DeclareVarInst("FAUSTFLOAT*", input25, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(25)]))
	DeclareVarInst("FAUSTFLOAT*", input26, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(26)]))
	DeclareVarInst("FAUSTFLOAT*", input27, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(27)]))
	DeclareVarInst("FAUSTFLOAT*", input28, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(28)]))
	DeclareVarInst("FAUSTFLOAT*", input29, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(29)]))
	DeclareVarInst("FAUSTFLOAT*", input30, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(30)]))
	DeclareVarInst("FAUSTFLOAT*", input31, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(31)]))
	DeclareVarInst("FAUSTFLOAT*", input32, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(32)]))
	DeclareVarInst("FAUSTFLOAT*", input33, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(33)]))
	DeclareVarInst("FAUSTFLOAT*", input34, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(34)]))
	DeclareVarInst("FAUSTFLOAT*", input35, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(35)]))
	DeclareVarInst("FAUSTFLOAT*", input36, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(36)]))
	DeclareVarInst("FAUSTFLOAT*", input37, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(37)]))
	DeclareVarInst("FAUSTFLOAT*", input38, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(38)]))
	DeclareVarInst("FAUSTFLOAT*", input39, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(39)]))
	DeclareVarInst("FAUSTFLOAT*", input40, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(40)]))
	DeclareVarInst("FAUSTFLOAT*", input41, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(41)]))
	DeclareVarInst("FAUSTFLOAT*", input42, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(42)]))
	DeclareVarInst("FAUSTFLOAT*", input43, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(43)]))
	DeclareVarInst("FAUSTFLOAT*", input44, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(44)]))
	DeclareVarInst("FAUSTFLOAT*", input45, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(45)]))
	DeclareVarInst("FAUSTFLOAT*", input46, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(46)]))
	DeclareVarInst("FAUSTFLOAT*", input47, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(47)]))
	DeclareVarInst("FAUSTFLOAT*", input48, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(48)]))
	DeclareVarInst("FAUSTFLOAT*", input49, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(49)]))
	DeclareVarInst("FAUSTFLOAT*", input50, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(50)]))
	DeclareVarInst("FAUSTFLOAT*", input51, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(51)]))
	DeclareVarInst("FAUSTFLOAT*", input52, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(52)]))
	DeclareVarInst("FAUSTFLOAT*", input53, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(53)]))
	DeclareVarInst("FAUSTFLOAT*", input54, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(54)]))
	DeclareVarInst("FAUSTFLOAT*", input55, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(55)]))
	DeclareVarInst("FAUSTFLOAT*", input56, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(56)]))
	DeclareVarInst("FAUSTFLOAT*", input57, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(57)]))
	DeclareVarInst("FAUSTFLOAT*", input58, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(58)]))
	DeclareVarInst("FAUSTFLOAT*", input59, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(59)]))
	DeclareVarInst("FAUSTFLOAT*", input60, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(60)]))
	DeclareVarInst("FAUSTFLOAT*", input61, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(61)]))
	DeclareVarInst("FAUSTFLOAT*", input62, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(62)]))
	DeclareVarInst("FAUSTFLOAT*", input63, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(63)]))
	DeclareVarInst("FAUSTFLOAT*", input64, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(64)]))
	DeclareVarInst("FAUSTFLOAT*", input65, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(65)]))
	DeclareVarInst("FAUSTFLOAT*", input66, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(66)]))
	DeclareVarInst("FAUSTFLOAT*", input67, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(67)]))
	DeclareVarInst("FAUSTFLOAT*", input68, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(68)]))
	DeclareVarInst("FAUSTFLOAT*", input69, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(69)]))
	DeclareVarInst("FAUSTFLOAT*", input70, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(70)]))
	DeclareVarInst("FAUSTFLOAT*", input71, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(71)]))
	DeclareVarInst("FAUSTFLOAT*", input72, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(72)]))
	DeclareVarInst("FAUSTFLOAT*", input73, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(73)]))
	DeclareVarInst("FAUSTFLOAT*", input74, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(74)]))
	DeclareVarInst("FAUSTFLOAT*", input75, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(75)]))
	DeclareVarInst("FAUSTFLOAT*", input76, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(76)]))
	DeclareVarInst("FAUSTFLOAT*", input77, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(77)]))
	DeclareVarInst("FAUSTFLOAT*", input78, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(78)]))
	DeclareVarInst("FAUSTFLOAT*", input79, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(79)]))
	DeclareVarInst("FAUSTFLOAT*", input80, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(80)]))
	DeclareVarInst("FAUSTFLOAT*", input81, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(81)]))
	DeclareVarInst("FAUSTFLOAT*", input82, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(82)]))
	DeclareVarInst("FAUSTFLOAT*", input83, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(83)]))
	DeclareVarInst("FAUSTFLOAT*", input84, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(84)]))
	DeclareVarInst("FAUSTFLOAT*", input85, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(85)]))
	DeclareVarInst("FAUSTFLOAT*", input86, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(86)]))
	DeclareVarInst("FAUSTFLOAT*", input87, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(87)]))
	DeclareVarInst("FAUSTFLOAT*", input88, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(88)]))
	DeclareVarInst("FAUSTFLOAT*", input89, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(89)]))
	DeclareVarInst("FAUSTFLOAT*", input90, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(90)]))
	DeclareVarInst("FAUSTFLOAT*", input91, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(91)]))
	DeclareVarInst("FAUSTFLOAT*", input92, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(92)]))
	DeclareVarInst("FAUSTFLOAT*", input93, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(93)]))
	DeclareVarInst("FAUSTFLOAT*", input94, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(94)]))
	DeclareVarInst("FAUSTFLOAT*", input95, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(95)]))
	DeclareVarInst("FAUSTFLOAT*", input96, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(96)]))
	DeclareVarInst("FAUSTFLOAT*", input97, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(97)]))
	DeclareVarInst("FAUSTFLOAT*", input98, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(98)]))
	DeclareVarInst("FAUSTFLOAT*", input99, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(99)]))
	DeclareVarInst("FAUSTFLOAT*", input100, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(100)]))
	DeclareVarInst("FAUSTFLOAT*", input101, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(101)]))
	DeclareVarInst("FAUSTFLOAT*", input102, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(102)]))
	DeclareVarInst("FAUSTFLOAT*", input103, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(103)]))
	DeclareVarInst("FAUSTFLOAT*", input104, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(104)]))
	DeclareVarInst("FAUSTFLOAT*", input105, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(105)]))
	DeclareVarInst("FAUSTFLOAT*", input106, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(106)]))
	DeclareVarInst("FAUSTFLOAT*", input107, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(107)]))
	DeclareVarInst("FAUSTFLOAT*", input108, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(108)]))
	DeclareVarInst("FAUSTFLOAT*", input109, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(109)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output8, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", output9, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", output10, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("FAUSTFLOAT*", output11, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(11)]))
	DeclareVarInst("FAUSTFLOAT*", output12, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(12)]))
	DeclareVarInst("FAUSTFLOAT*", output13, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(13)]))
	DeclareVarInst("FAUSTFLOAT*", output14, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(14)]))
	DeclareVarInst("FAUSTFLOAT*", output15, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(15)]))
	DeclareVarInst("FAUSTFLOAT*", output16, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(16)]))
	DeclareVarInst("FAUSTFLOAT*", output17, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(17)]))
	DeclareVarInst("FAUSTFLOAT*", output18, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(18)]))
	DeclareVarInst("FAUSTFLOAT*", output19, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(19)]))
	DeclareVarInst("FAUSTFLOAT*", output20, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(20)]))
	DeclareVarInst("FAUSTFLOAT*", output21, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(21)]))
	DeclareVarInst("FAUSTFLOAT*", output22, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(22)]))
	DeclareVarInst("FAUSTFLOAT*", output23, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(23)]))
	DeclareVarInst("FAUSTFLOAT*", output24, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(24)]))
	DeclareVarInst("FAUSTFLOAT*", output25, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(25)]))
	DeclareVarInst("FAUSTFLOAT*", output26, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(26)]))
	DeclareVarInst("FAUSTFLOAT*", output27, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(27)]))
	DeclareVarInst("FAUSTFLOAT*", output28, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(28)]))
	DeclareVarInst("FAUSTFLOAT*", output29, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(29)]))
	DeclareVarInst("FAUSTFLOAT*", output30, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(30)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 442 Store = 76 Binop = 443 [ { Int(!=) = 1 } { Int(%) = 3 } { Int(&) = 137 } { Int(*) = 5 } { Int(+) = 37 } { Int(-) = 43 } { Int(<) = 2 } { Int(<<) = 7 } { Int(<=) = 5 } { Int(==) = 1 } { Int(>=) = 1 } { Int(>>) = 4 } { Int(^) = 5 } { Int(|) = 6 } { Real(*) = 138 } { Real(+) = 46 } { Real(/) = 2 } ] Mathop = 2 [ { fmodf = 2 } ] Numbers = 337 Declare = 1 Cast = 234 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input8, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input10, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input11, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input12, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input13, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input14, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input15, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input16, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input17, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input18, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input19, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input20, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input21, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input22, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input23, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input24, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("%", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input25, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input26, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input27, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input28, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input29, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec44SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input30, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input31, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input32, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec44SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input33, kStack)[LoadVarInst(Address(i0, kLoop))])))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input36, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input37, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input38, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input39, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input40, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input41, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input42, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input43, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input44, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec54SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", Float(0.1f), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec54SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec56SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", Float(0.1f), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec56SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec58SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input51, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input52, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input53, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec58SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec60SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", Float(0.1f), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec60SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec62SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", Float(0.1f), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec62SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("==", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input60, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("!=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input61, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input62, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input63, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input64, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input65, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec68SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input66, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input67, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input68, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec68SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec70SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input69, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input70, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input71, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec70SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input72, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input73, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input74, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input75, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("|", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input76, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input77, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input78, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("^", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input79, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input80, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec78SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("+", BinopInst("+", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input82, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input81, kStack)[LoadVarInst(Address(i0, kLoop))]))))), Int32(3)), MinusInst(CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input83, kStack)[LoadVarInst(Address(i0, kLoop))])))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input84, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec78SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input86, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input85, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input87, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input88, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input89, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input90, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input91, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input92, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec80SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">=", BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input93, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input94, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), BinopInst("|", BinopInst("+", BinopInst("+", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input96, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input95, kStack)[LoadVarInst(Address(i0, kLoop))]))))), Int32(3)), MinusInst(CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input97, kStack)[LoadVarInst(Address(i0, kLoop))])))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input98, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("+", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input99, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input100, kStack)[LoadVarInst(Address(i0, kLoop))]))))), MinusInst(CastInst("int", CastInst("float", LoadVarInst(Address(input101, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input103, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input102, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input104, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input105, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input106, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input107, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input108, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input109, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), BinopInst("+", LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec44SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec54SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec56SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec58SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec60SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec62SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec68SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec70SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec78SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
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
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay fVec0SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec0SE[2], kStruct)
	// Recursion delay fVec2SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec2SE[2], kStruct)
	// Recursion delay fVec4SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec4SE[2], kStruct)
	// Recursion delay fVec6SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec6SE[2], kStruct)
	// Recursion delay fVec8SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec8SE[2], kStruct)
	// Recursion delay fVec10SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec10SE[2], kStruct)
	// Recursion delay fVec12SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec12SE[2], kStruct)
	// Recursion delay fVec14SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec14SE[2], kStruct)
	// Recursion delay fVec16SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec16SE[2], kStruct)
	// Recursion delay fVec18SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec18SE[2], kStruct)
	// Recursion delay fVec20SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec20SE[2], kStruct)
	// Recursion delay fVec22SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec22SE[2], kStruct)
	// Recursion delay fVec24SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec24SE[2], kStruct)
	// Recursion delay fVec26SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec26SE[2], kStruct)
	// Recursion delay fVec28SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec28SE[2], kStruct)
	// Recursion delay fVec30SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec30SE[2], kStruct)
	// Recursion delay fVec32SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec32SE[2], kStruct)
	// Recursion delay fVec34SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec34SE[2], kStruct)
	// Recursion delay fVec36SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec36SE[2], kStruct)
	// Recursion delay fVec38SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec38SE[2], kStruct)
	// Recursion delay fVec40SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec40SE[2], kStruct)
	// Recursion delay fVec42SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec42SE[2], kStruct)
	// Recursion delay fVec44SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec44SE[2], kStruct)
	// Recursion delay fVec46SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec46SE[2], kStruct)
	// Recursion delay fVec48SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec48SE[2], kStruct)
	// Recursion delay fVec50SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec50SE[2], kStruct)
	// Recursion delay fVec52SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec52SE[2], kStruct)
	// Recursion delay fVec54SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec54SI[2], kStruct)
	// Recursion delay fVec56SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec56SI[2], kStruct)
	// Recursion delay fVec58SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec58SE[2], kStruct)
	// Recursion delay fVec60SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec60SI[2], kStruct)
	// Recursion delay fVec62SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec62SI[2], kStruct)
	// Recursion delay fVec64SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec64SE[2], kStruct)
	// Recursion delay fVec66SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec66SE[2], kStruct)
	// Recursion delay fVec68SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec68SE[2], kStruct)
	// Recursion delay fVec70SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec70SE[2], kStruct)
	// Recursion delay fVec72SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec72SE[2], kStruct)
	// Recursion delay fVec74SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec74SE[2], kStruct)
	// Recursion delay fVec76SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec76SE[2], kStruct)
	// Recursion delay fVec78SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec78SE[2], kStruct)
	// Recursion delay fVec80SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec80SE[2], kStruct)
	// Recursion delay fVec82SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec82SE[2], kStruct)
	// Recursion delay fVec84SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec84SE[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
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
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec10SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec14SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
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
			StoreVarInst(Address(fVec20SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec22SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec26SE, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec30SE, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec32SE, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec34SE, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec36SE, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec38SE, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec40SE, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec42SE, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec44SE, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec46SE, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec48SE, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec50SE, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec52SE, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec54SI, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec56SI, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec58SE, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec60SI, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec62SI, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec66SE, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec70SE, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec74SE, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec78SE, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec82SE, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
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
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", input6, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", input7, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", input8, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", input9, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", input10, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("FAUSTFLOAT*", input11, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(11)]))
	DeclareVarInst("FAUSTFLOAT*", input12, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(12)]))
	DeclareVarInst("FAUSTFLOAT*", input13, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(13)]))
	DeclareVarInst("FAUSTFLOAT*", input14, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(14)]))
	DeclareVarInst("FAUSTFLOAT*", input15, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(15)]))
	DeclareVarInst("FAUSTFLOAT*", input16, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(16)]))
	DeclareVarInst("FAUSTFLOAT*", input17, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(17)]))
	DeclareVarInst("FAUSTFLOAT*", input18, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(18)]))
	DeclareVarInst("FAUSTFLOAT*", input19, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(19)]))
	DeclareVarInst("FAUSTFLOAT*", input20, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(20)]))
	DeclareVarInst("FAUSTFLOAT*", input21, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(21)]))
	DeclareVarInst("FAUSTFLOAT*", input22, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(22)]))
	DeclareVarInst("FAUSTFLOAT*", input23, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(23)]))
	DeclareVarInst("FAUSTFLOAT*", input24, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(24)]))
	DeclareVarInst("FAUSTFLOAT*", input25, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(25)]))
	DeclareVarInst("FAUSTFLOAT*", input26, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(26)]))
	DeclareVarInst("FAUSTFLOAT*", input27, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(27)]))
	DeclareVarInst("FAUSTFLOAT*", input28, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(28)]))
	DeclareVarInst("FAUSTFLOAT*", input29, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(29)]))
	DeclareVarInst("FAUSTFLOAT*", input30, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(30)]))
	DeclareVarInst("FAUSTFLOAT*", input31, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(31)]))
	DeclareVarInst("FAUSTFLOAT*", input32, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(32)]))
	DeclareVarInst("FAUSTFLOAT*", input33, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(33)]))
	DeclareVarInst("FAUSTFLOAT*", input34, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(34)]))
	DeclareVarInst("FAUSTFLOAT*", input35, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(35)]))
	DeclareVarInst("FAUSTFLOAT*", input36, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(36)]))
	DeclareVarInst("FAUSTFLOAT*", input37, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(37)]))
	DeclareVarInst("FAUSTFLOAT*", input38, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(38)]))
	DeclareVarInst("FAUSTFLOAT*", input39, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(39)]))
	DeclareVarInst("FAUSTFLOAT*", input40, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(40)]))
	DeclareVarInst("FAUSTFLOAT*", input41, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(41)]))
	DeclareVarInst("FAUSTFLOAT*", input42, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(42)]))
	DeclareVarInst("FAUSTFLOAT*", input43, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(43)]))
	DeclareVarInst("FAUSTFLOAT*", input44, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(44)]))
	DeclareVarInst("FAUSTFLOAT*", input45, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(45)]))
	DeclareVarInst("FAUSTFLOAT*", input46, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(46)]))
	DeclareVarInst("FAUSTFLOAT*", input47, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(47)]))
	DeclareVarInst("FAUSTFLOAT*", input48, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(48)]))
	DeclareVarInst("FAUSTFLOAT*", input49, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(49)]))
	DeclareVarInst("FAUSTFLOAT*", input50, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(50)]))
	DeclareVarInst("FAUSTFLOAT*", input51, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(51)]))
	DeclareVarInst("FAUSTFLOAT*", input52, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(52)]))
	DeclareVarInst("FAUSTFLOAT*", input53, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(53)]))
	DeclareVarInst("FAUSTFLOAT*", input54, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(54)]))
	DeclareVarInst("FAUSTFLOAT*", input55, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(55)]))
	DeclareVarInst("FAUSTFLOAT*", input56, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(56)]))
	DeclareVarInst("FAUSTFLOAT*", input57, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(57)]))
	DeclareVarInst("FAUSTFLOAT*", input58, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(58)]))
	DeclareVarInst("FAUSTFLOAT*", input59, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(59)]))
	DeclareVarInst("FAUSTFLOAT*", input60, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(60)]))
	DeclareVarInst("FAUSTFLOAT*", input61, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(61)]))
	DeclareVarInst("FAUSTFLOAT*", input62, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(62)]))
	DeclareVarInst("FAUSTFLOAT*", input63, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(63)]))
	DeclareVarInst("FAUSTFLOAT*", input64, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(64)]))
	DeclareVarInst("FAUSTFLOAT*", input65, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(65)]))
	DeclareVarInst("FAUSTFLOAT*", input66, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(66)]))
	DeclareVarInst("FAUSTFLOAT*", input67, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(67)]))
	DeclareVarInst("FAUSTFLOAT*", input68, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(68)]))
	DeclareVarInst("FAUSTFLOAT*", input69, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(69)]))
	DeclareVarInst("FAUSTFLOAT*", input70, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(70)]))
	DeclareVarInst("FAUSTFLOAT*", input71, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(71)]))
	DeclareVarInst("FAUSTFLOAT*", input72, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(72)]))
	DeclareVarInst("FAUSTFLOAT*", input73, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(73)]))
	DeclareVarInst("FAUSTFLOAT*", input74, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(74)]))
	DeclareVarInst("FAUSTFLOAT*", input75, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(75)]))
	DeclareVarInst("FAUSTFLOAT*", input76, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(76)]))
	DeclareVarInst("FAUSTFLOAT*", input77, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(77)]))
	DeclareVarInst("FAUSTFLOAT*", input78, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(78)]))
	DeclareVarInst("FAUSTFLOAT*", input79, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(79)]))
	DeclareVarInst("FAUSTFLOAT*", input80, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(80)]))
	DeclareVarInst("FAUSTFLOAT*", input81, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(81)]))
	DeclareVarInst("FAUSTFLOAT*", input82, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(82)]))
	DeclareVarInst("FAUSTFLOAT*", input83, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(83)]))
	DeclareVarInst("FAUSTFLOAT*", input84, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(84)]))
	DeclareVarInst("FAUSTFLOAT*", input85, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(85)]))
	DeclareVarInst("FAUSTFLOAT*", input86, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(86)]))
	DeclareVarInst("FAUSTFLOAT*", input87, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(87)]))
	DeclareVarInst("FAUSTFLOAT*", input88, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(88)]))
	DeclareVarInst("FAUSTFLOAT*", input89, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(89)]))
	DeclareVarInst("FAUSTFLOAT*", input90, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(90)]))
	DeclareVarInst("FAUSTFLOAT*", input91, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(91)]))
	DeclareVarInst("FAUSTFLOAT*", input92, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(92)]))
	DeclareVarInst("FAUSTFLOAT*", input93, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(93)]))
	DeclareVarInst("FAUSTFLOAT*", input94, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(94)]))
	DeclareVarInst("FAUSTFLOAT*", input95, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(95)]))
	DeclareVarInst("FAUSTFLOAT*", input96, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(96)]))
	DeclareVarInst("FAUSTFLOAT*", input97, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(97)]))
	DeclareVarInst("FAUSTFLOAT*", input98, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(98)]))
	DeclareVarInst("FAUSTFLOAT*", input99, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(99)]))
	DeclareVarInst("FAUSTFLOAT*", input100, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(100)]))
	DeclareVarInst("FAUSTFLOAT*", input101, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(101)]))
	DeclareVarInst("FAUSTFLOAT*", input102, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(102)]))
	DeclareVarInst("FAUSTFLOAT*", input103, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(103)]))
	DeclareVarInst("FAUSTFLOAT*", input104, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(104)]))
	DeclareVarInst("FAUSTFLOAT*", input105, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(105)]))
	DeclareVarInst("FAUSTFLOAT*", input106, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(106)]))
	DeclareVarInst("FAUSTFLOAT*", input107, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(107)]))
	DeclareVarInst("FAUSTFLOAT*", input108, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(108)]))
	DeclareVarInst("FAUSTFLOAT*", input109, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(109)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output8, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(8)]))
	DeclareVarInst("FAUSTFLOAT*", output9, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(9)]))
	DeclareVarInst("FAUSTFLOAT*", output10, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(10)]))
	DeclareVarInst("FAUSTFLOAT*", output11, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(11)]))
	DeclareVarInst("FAUSTFLOAT*", output12, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(12)]))
	DeclareVarInst("FAUSTFLOAT*", output13, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(13)]))
	DeclareVarInst("FAUSTFLOAT*", output14, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(14)]))
	DeclareVarInst("FAUSTFLOAT*", output15, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(15)]))
	DeclareVarInst("FAUSTFLOAT*", output16, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(16)]))
	DeclareVarInst("FAUSTFLOAT*", output17, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(17)]))
	DeclareVarInst("FAUSTFLOAT*", output18, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(18)]))
	DeclareVarInst("FAUSTFLOAT*", output19, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(19)]))
	DeclareVarInst("FAUSTFLOAT*", output20, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(20)]))
	DeclareVarInst("FAUSTFLOAT*", output21, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(21)]))
	DeclareVarInst("FAUSTFLOAT*", output22, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(22)]))
	DeclareVarInst("FAUSTFLOAT*", output23, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(23)]))
	DeclareVarInst("FAUSTFLOAT*", output24, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(24)]))
	DeclareVarInst("FAUSTFLOAT*", output25, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(25)]))
	DeclareVarInst("FAUSTFLOAT*", output26, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(26)]))
	DeclareVarInst("FAUSTFLOAT*", output27, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(27)]))
	DeclareVarInst("FAUSTFLOAT*", output28, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(28)]))
	DeclareVarInst("FAUSTFLOAT*", output29, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(29)]))
	DeclareVarInst("FAUSTFLOAT*", output30, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(30)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input8, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input10, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input11, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input12, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input13, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input14, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input15, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input16, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input17, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input18, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input19, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input20, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input21, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input22, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input23, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input24, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("%", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input25, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input26, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input27, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input28, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input29, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec44SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input30, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input31, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input32, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec44SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input33, kStack)[LoadVarInst(Address(i0, kLoop))])))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input36, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input37, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input38, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input39, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input40, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input41, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input42, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input43, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input44, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec54SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", Float(0.1f), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec54SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec56SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", Float(0.1f), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec56SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec58SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input51, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input52, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input53, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec58SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec60SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", Float(0.1f), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec60SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec62SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", Float(0.1f), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec62SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("==", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input60, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("!=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input61, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input62, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input63, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input64, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input65, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec68SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input66, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input67, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input68, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec68SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec70SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input69, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input70, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input71, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec70SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input72, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input73, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input74, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input75, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("|", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input76, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input77, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input78, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("^", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input79, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input80, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec78SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("+", BinopInst("+", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input82, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input81, kStack)[LoadVarInst(Address(i0, kLoop))]))))), Int32(3)), MinusInst(CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input83, kStack)[LoadVarInst(Address(i0, kLoop))])))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input84, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec78SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input86, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input85, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input87, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input88, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input89, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input90, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input91, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input92, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec80SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">=", BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input93, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input94, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), BinopInst("|", BinopInst("+", BinopInst("+", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input96, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input95, kStack)[LoadVarInst(Address(i0, kLoop))]))))), Int32(3)), MinusInst(CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input97, kStack)[LoadVarInst(Address(i0, kLoop))])))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input98, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("+", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input99, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input100, kStack)[LoadVarInst(Address(i0, kLoop))]))))), MinusInst(CastInst("int", CastInst("float", LoadVarInst(Address(input101, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input103, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input102, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input104, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input105, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input106, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input107, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input108, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input109, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec14SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fVec16SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec20SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fVec22SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fVec24SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec26SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])), LoadVarInst(Address(fVec28SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fVec30SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), BinopInst("+", LoadVarInst(Address(fVec32SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), LoadVarInst(Address(fVec34SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec36SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec38SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec40SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec42SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec44SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec46SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec48SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec50SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec52SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec54SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec56SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec58SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec60SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec62SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec64SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec66SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec68SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec70SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec72SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec74SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec76SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec78SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec80SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec82SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fVec84SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 344 bytes
Total heap size = 352 bytes
Stack size in compute = 1128 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec14SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec18SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec28SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec30SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec34SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec36SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec38SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec40SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec42SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec44SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec46SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec48SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec50SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec52SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec54SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec56SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec58SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec60SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec62SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec64SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec66SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec68SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec70SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec72SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec74SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec76SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec78SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec80SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec82SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec84SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec12SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec14SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec16SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec18SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec20SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec22SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec24SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec26SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec28SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec30SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec32SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec34SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec36SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec38SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec40SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec42SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec44SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec46SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec48SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec50SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec52SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec54SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec56SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec58SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec60SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec62SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec64SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec66SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec68SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec70SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec72SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec74SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec76SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec78SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec80SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec82SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec84SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 130 write = 1 ratio = 131
Field = fVec0SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec2SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec4SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec6SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec8SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec10SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec12SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec14SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec16SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec18SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec20SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec22SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec24SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec26SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec28SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec30SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec32SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec34SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec36SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec38SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec40SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec42SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec44SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec46SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec48SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec50SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec52SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec54SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec56SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec58SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec60SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec62SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec64SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec66SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec68SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec70SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec72SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec74SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec76SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec78SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec80SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec82SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec84SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
