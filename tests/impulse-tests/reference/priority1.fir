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

DeclareStructTypeInst(StructType<"mydsp",("float[2]", fRec0)("float[2]", fRec1)("float[2]", fRec2)("float[2]", fRec3)("float[2]", fRec4)("float[2]", fRec5)("float[2]", fRec6)("float[2]", fRec7)("float[2]", fRec8)("float[2]", fRec9)("float[2]", fRec10)("float[2]", fRec11)("float[2]", fRec12)("float[2]", fRec13)("float[2]", fRec14)("float[2]", fRec15)("float[2]", fRec16)("float[2]", fRec17)("float[2]", fRec18)("float[2]", fRec19)("float[2]", fRec20)("float[2]", fRec21)("float[2]", fRec22)("float[2]", fRec23)("float[2]", fRec24)("float[2]", fRec25)("float[2]", fRec26)("float[2]", fRec27)("float[2]", fRec28)("float[2]", fRec29)("float[2]", fRec30)("float[2]", fRec31)("float[2]", fRec32)("float[2]", fRec33)("float[2]", fRec34)("float[2]", fRec35)("float[2]", fRec36)("float[2]", fRec37)("float[2]", fRec38)("float[2]", fRec39)("float[2]", fRec40)("float[2]", fRec41)("float[2]", fRec42)("int", fSampleRate)>)

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
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec25, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec27, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec29, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec31, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec37, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec40, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec41, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec42, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
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

Instructions complexity : Load = 383 Store = 118 Binop = 298 [ { Int(!=) = 3 } { Int(%) = 3 } { Int(&) = 8 } { Int(*) = 5 } { Int(+) = 38 } { Int(-) = 3 } { Int(<) = 4 } { Int(<<) = 8 } { Int(<=) = 7 } { Int(==) = 3 } { Int(>=) = 1 } { Int(>>) = 5 } { Int(^) = 5 } { Int(|) = 6 } { Real(*) = 151 } { Real(+) = 46 } { Real(/) = 2 } ] Mathop = 2 [ { fmodf = 2 } ] Numbers = 393 Declare = 1 Cast = 266 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec3, kStruct)[Int32(0)]), LoadVarInst(Address(fRec4, kStruct)[Int32(0)])), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input8, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec6, kStruct)[Int32(0)]), LoadVarInst(Address(fRec7, kStruct)[Int32(0)])), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec10, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input10, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input11, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec9, kStruct)[Int32(0)]), LoadVarInst(Address(fRec10, kStruct)[Int32(0)])), LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec12, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input12, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input13, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec13, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input14, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec12, kStruct)[Int32(0)]), LoadVarInst(Address(fRec13, kStruct)[Int32(0)])), LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))))
		StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input15, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec15, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec16, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input16, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input17, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec17, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(0)]), LoadVarInst(Address(fRec17, kStruct)[Int32(0)])))))
		StoreVarInst(Address(fRec18, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input18, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input19, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input20, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec18, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec19, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input21, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input22, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input23, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec19, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec19, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec20, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input24, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("%", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input25, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input26, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec20, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec21, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input27, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input28, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input29, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec21, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec21, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec22, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input30, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input31, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input32, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec22, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec23, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input33, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst(">>", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input34, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input35, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec23, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec23, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec24, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input36, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input37, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input38, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec24, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec25, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input39, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input40, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input41, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec25, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec25, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec26, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input42, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input43, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input44, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec26, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec27, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input45, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input46, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input47, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec27, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec27, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec28, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input48, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input49, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input50, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec28, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec29, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input51, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input52, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input53, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec29, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec29, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec30, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("!=", BinopInst("==", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input54, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input55, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input56, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec30, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec30, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec31, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("!=", BinopInst("==", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input57, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input58, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input59, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec31, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec31, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec32, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("==", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input60, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("!=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input61, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input62, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec32, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec33, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input63, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input64, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input65, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec33, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec33, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec34, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input66, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input67, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input68, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec34, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec35, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input69, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input70, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input71, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec35, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec36, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input72, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input73, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input74, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec36, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec37, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input75, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("|", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input76, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input77, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec37, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec38, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input78, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("^", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input79, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input80, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec38, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec39, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("+", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input82, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input81, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("-", Int32(3), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input83, kStack)[LoadVarInst(Address(i0, kLoop))])))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input84, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec39, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec39, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec40, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input86, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input85, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input87, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input88, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input89, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input90, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input91, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input92, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec40, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec40, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec41, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">=", BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input93, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input94, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), BinopInst("|", BinopInst("+", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input96, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input95, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("-", Int32(3), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input97, kStack)[LoadVarInst(Address(i0, kLoop))])))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input98, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec41, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec41, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec42, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("-", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input99, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input100, kStack)[LoadVarInst(Address(i0, kLoop))]))))), CastInst("int", CastInst("float", LoadVarInst(Address(input101, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input103, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input102, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input104, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input105, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input106, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input107, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input108, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input109, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))))
		StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec42, kStruct)[Int32(0)])))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec25, kStruct)[Int32(1)], LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec27, kStruct)[Int32(1)], LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec29, kStruct)[Int32(1)], LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec31, kStruct)[Int32(1)], LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec37, kStruct)[Int32(1)], LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec40, kStruct)[Int32(1)], LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec41, kStruct)[Int32(1)], LoadVarInst(Address(fRec41, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec42, kStruct)[Int32(1)], LoadVarInst(Address(fRec42, kStruct)[Int32(0)]))
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
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("float", fRec7[2], kStruct)
	DeclareVarInst("float", fRec8[2], kStruct)
	DeclareVarInst("float", fRec9[2], kStruct)
	DeclareVarInst("float", fRec10[2], kStruct)
	DeclareVarInst("float", fRec11[2], kStruct)
	DeclareVarInst("float", fRec12[2], kStruct)
	DeclareVarInst("float", fRec13[2], kStruct)
	DeclareVarInst("float", fRec14[2], kStruct)
	DeclareVarInst("float", fRec15[2], kStruct)
	DeclareVarInst("float", fRec16[2], kStruct)
	DeclareVarInst("float", fRec17[2], kStruct)
	DeclareVarInst("float", fRec18[2], kStruct)
	DeclareVarInst("float", fRec19[2], kStruct)
	DeclareVarInst("float", fRec20[2], kStruct)
	DeclareVarInst("float", fRec21[2], kStruct)
	DeclareVarInst("float", fRec22[2], kStruct)
	DeclareVarInst("float", fRec23[2], kStruct)
	DeclareVarInst("float", fRec24[2], kStruct)
	DeclareVarInst("float", fRec25[2], kStruct)
	DeclareVarInst("float", fRec26[2], kStruct)
	DeclareVarInst("float", fRec27[2], kStruct)
	DeclareVarInst("float", fRec28[2], kStruct)
	DeclareVarInst("float", fRec29[2], kStruct)
	DeclareVarInst("float", fRec30[2], kStruct)
	DeclareVarInst("float", fRec31[2], kStruct)
	DeclareVarInst("float", fRec32[2], kStruct)
	DeclareVarInst("float", fRec33[2], kStruct)
	DeclareVarInst("float", fRec34[2], kStruct)
	DeclareVarInst("float", fRec35[2], kStruct)
	DeclareVarInst("float", fRec36[2], kStruct)
	DeclareVarInst("float", fRec37[2], kStruct)
	DeclareVarInst("float", fRec38[2], kStruct)
	DeclareVarInst("float", fRec39[2], kStruct)
	DeclareVarInst("float", fRec40[2], kStruct)
	DeclareVarInst("float", fRec41[2], kStruct)
	DeclareVarInst("float", fRec42[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec9, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec10, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec11, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec12, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec13, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec14, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec15, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec16, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec17, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec18, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec19, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec21, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec22, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec23, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec24, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec25, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec26, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec27, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec28, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec29, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec30, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec31, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec32, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec33, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec34, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec36, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec37, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec38, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec39, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec40, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec41, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec42, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec3, kStruct)[Int32(0)]), LoadVarInst(Address(fRec4, kStruct)[Int32(0)])), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec6, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input8, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec8, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec6, kStruct)[Int32(0)]), LoadVarInst(Address(fRec7, kStruct)[Int32(0)])), LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec9, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec9, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec10, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input10, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec10, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec11, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input11, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec11, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec9, kStruct)[Int32(0)]), LoadVarInst(Address(fRec10, kStruct)[Int32(0)])), LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec12, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input12, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec12, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec13, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input13, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec13, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec14, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input14, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec14, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", LoadVarInst(Address(fRec12, kStruct)[Int32(0)]), LoadVarInst(Address(fRec13, kStruct)[Int32(0)])), LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))))
			StoreVarInst(Address(fRec15, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input15, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec15, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec16, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input16, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec16, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec17, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(1.05f), CastInst("float", LoadVarInst(Address(input17, kStack)[LoadVarInst(Address(i0, kLoop))]))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec17, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fRec15, kStruct)[Int32(0)]), BinopInst("+", LoadVarInst(Address(fRec16, kStruct)[Int32(0)]), LoadVarInst(Address(fRec17, kStruct)[Int32(0)])))))
			StoreVarInst(Address(fRec18, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input18, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input19, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input20, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec18, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec18, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec19, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input21, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input22, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input23, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec19, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec19, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec20, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("*", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input24, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("%", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input25, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input26, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec20, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec20, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec21, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input27, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input28, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input29, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec21, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec21, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec22, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input30, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input31, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input32, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec22, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec22, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec23, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input33, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst(">>", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input34, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input35, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec23, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec23, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec24, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input36, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input37, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input38, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec24, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec24, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec25, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input39, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input40, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input41, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec25, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec25, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec26, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input42, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input43, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input44, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec26, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec26, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec27, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input45, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input46, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input47, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec27, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec27, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec28, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<=", BinopInst("<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input48, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input49, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input50, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec28, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec28, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec29, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("<", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input51, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input52, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input53, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec29, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec29, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec30, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("!=", BinopInst("==", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input54, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input55, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input56, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec30, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec30, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec31, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("!=", BinopInst("==", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input57, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input58, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input59, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec31, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec31, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec32, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("==", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input60, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("!=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input61, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input62, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec32, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec32, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec33, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input63, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input64, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input65, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec33, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec33, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec34, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input66, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input67, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input68, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec34, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec34, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec35, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input69, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input70, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input71, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec35, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec35, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec36, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input72, kStack)[LoadVarInst(Address(i0, kLoop))])))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input73, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input74, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec36, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec36, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec37, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input75, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("|", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input76, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input77, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec37, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec37, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec38, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("&", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input78, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("^", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input79, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input80, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec38, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec38, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec39, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("+", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input82, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input81, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("-", Int32(3), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input83, kStack)[LoadVarInst(Address(i0, kLoop))])))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input84, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec39, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec39, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec40, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input86, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input85, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input87, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input88, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input89, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input90, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input91, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input92, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec40, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec40, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec41, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst(">=", BinopInst("<=", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input93, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input94, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), BinopInst("|", BinopInst("+", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input96, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input95, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("-", Int32(3), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input97, kStack)[LoadVarInst(Address(i0, kLoop))])))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input98, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec41, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec41, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec42, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Float(0.1f), CastInst("float", BinopInst("|", BinopInst("-", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input99, kStack)[LoadVarInst(Address(i0, kLoop))]))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input100, kStack)[LoadVarInst(Address(i0, kLoop))]))))), CastInst("int", CastInst("float", LoadVarInst(Address(input101, kStack)[LoadVarInst(Address(i0, kLoop))])))), BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input103, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input102, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input104, kStack)[LoadVarInst(Address(i0, kLoop))])))))), CastInst("float", BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input105, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input106, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input107, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3))), CastInst("int", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input108, kStack)[LoadVarInst(Address(i0, kLoop))]))))), BinopInst("+", CastInst("int", CastInst("float", LoadVarInst(Address(input109, kStack)[LoadVarInst(Address(i0, kLoop))]))), Int32(3)))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fRec42, kStruct)[Int32(1)]))))
			StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fRec42, kStruct)[Int32(0)])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec9, kStruct)[Int32(1)], LoadVarInst(Address(fRec9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec10, kStruct)[Int32(1)], LoadVarInst(Address(fRec10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec11, kStruct)[Int32(1)], LoadVarInst(Address(fRec11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec12, kStruct)[Int32(1)], LoadVarInst(Address(fRec12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec13, kStruct)[Int32(1)], LoadVarInst(Address(fRec13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec14, kStruct)[Int32(1)], LoadVarInst(Address(fRec14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec15, kStruct)[Int32(1)], LoadVarInst(Address(fRec15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec16, kStruct)[Int32(1)], LoadVarInst(Address(fRec16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec17, kStruct)[Int32(1)], LoadVarInst(Address(fRec17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec18, kStruct)[Int32(1)], LoadVarInst(Address(fRec18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec19, kStruct)[Int32(1)], LoadVarInst(Address(fRec19, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec20, kStruct)[Int32(1)], LoadVarInst(Address(fRec20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec21, kStruct)[Int32(1)], LoadVarInst(Address(fRec21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec22, kStruct)[Int32(1)], LoadVarInst(Address(fRec22, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec23, kStruct)[Int32(1)], LoadVarInst(Address(fRec23, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec24, kStruct)[Int32(1)], LoadVarInst(Address(fRec24, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec25, kStruct)[Int32(1)], LoadVarInst(Address(fRec25, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec26, kStruct)[Int32(1)], LoadVarInst(Address(fRec26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec27, kStruct)[Int32(1)], LoadVarInst(Address(fRec27, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec28, kStruct)[Int32(1)], LoadVarInst(Address(fRec28, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec29, kStruct)[Int32(1)], LoadVarInst(Address(fRec29, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec30, kStruct)[Int32(1)], LoadVarInst(Address(fRec30, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec31, kStruct)[Int32(1)], LoadVarInst(Address(fRec31, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec32, kStruct)[Int32(1)], LoadVarInst(Address(fRec32, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec33, kStruct)[Int32(1)], LoadVarInst(Address(fRec33, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec34, kStruct)[Int32(1)], LoadVarInst(Address(fRec34, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec35, kStruct)[Int32(1)], LoadVarInst(Address(fRec35, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec36, kStruct)[Int32(1)], LoadVarInst(Address(fRec36, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec37, kStruct)[Int32(1)], LoadVarInst(Address(fRec37, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec38, kStruct)[Int32(1)], LoadVarInst(Address(fRec38, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec39, kStruct)[Int32(1)], LoadVarInst(Address(fRec39, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec40, kStruct)[Int32(1)], LoadVarInst(Address(fRec40, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec41, kStruct)[Int32(1)], LoadVarInst(Address(fRec41, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec42, kStruct)[Int32(1)], LoadVarInst(Address(fRec42, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 344 bytes
Total heap size = 348 bytes
Stack size in compute = 1128 bytes

======= Variable access in Control ==========

Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec27 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec33 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec34 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec35 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec36 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec37 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec38 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec39 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec41 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec42 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec27 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec33 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec34 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec35 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec36 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec37 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec38 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec39 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec41 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec42 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fRec0 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec3 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec7 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec8 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec9 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec10 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec11 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec12 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec13 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec14 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec15 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec16 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec17 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec18 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec19 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec20 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec21 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec22 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec23 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec24 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec25 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec26 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec27 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec28 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec29 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec30 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec31 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec32 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec33 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec34 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec35 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec36 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec37 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec38 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec39 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec40 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec41 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec42 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
