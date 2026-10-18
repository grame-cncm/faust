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
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("float[2]", fIIR0)("float[2]", fIIR1)("float[2]", fIIR2)("float[2]", fIIR3)("float[2]", fIIR4)("float[2]", fIIR5)("float[2]", fIIR6)("float[2]", fIIR7)("float[2]", fIIR8)("float[2]", fIIR9)("float[2]", fIIR10)("float[2]", fIIR11)("float[2]", fIIR12)("float[2]", fIIR13)("float[2]", fIIR14)("float[2]", fIIR15)("float[2]", fIIR16)("float[2]", fIIR17)("float[2]", fIIR18)("float[2]", fIIR19)("float[2]", fIIR20)("float[2]", fIIR21)("float[2]", fIIR22)("float[2]", fIIR23)("float[2]", fIIR24)("float[2]", fIIR25)("float[2]", fIIR26)("float[2]", fIIR27)("float[2]", fIIR28)("float[2]", fIIR29)("float[2]", fIIR30)("float[2]", fIIR31)("float[2]", fIIR32)("float[2]", fIIR33)("float[2]", fIIR34)("float[2]", fIIR35)("float[2]", fIIR36)("float[2]", fIIR37)("float[2]", fIIR38)("float[2]", fIIR39)("float[2]", fIIR40)("float[2]", fIIR41)("float[2]", fIIR42)("int", fSampleRate)>)

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
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR8, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR9, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR10, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR11, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR12, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR13, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR14, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR15, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR16, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR17, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR18, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR19, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR20, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR21, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR22, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR23, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR24, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR25, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR26, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR27, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR28, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR29, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR30, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR31, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR32, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR33, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR34, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR35, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR36, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR37, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR38, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR39, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR40, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR41, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR42, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
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

Instructions complexity : Load = 426 Store = 118 Binop = 300 [ { Int(!=) = 3 } { Int(%) = 3 } { Int(&) = 8 } { Int(*) = 5 } { Int(+) = 40 } { Int(-) = 3 } { Int(<) = 4 } { Int(<<) = 8 } { Int(<=) = 7 } { Int(==) = 3 } { Int(>=) = 1 } { Int(>>) = 5 } { Int(^) = 5 } { Int(|) = 6 } { Real(*) = 151 } { Real(+) = 46 } { Real(/) = 2 } ] Mathop = 186 [ { fmodf = 2 } { max_f = 92 } { min_f = 92 } ] Numbers = 536 Declare = 44 Cast = 266 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp2, kStack))))))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp5, kStack)))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp3, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp5, kStack))))))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp7, kStack)))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input8, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp8, kStack)))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp6, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp7, kStack)))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp8, kStack))))))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR9, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp9, kStack)))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input10, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR10, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR10, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
		DeclareVarInst("float", fTemp11, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input11, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR11, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR11, kStruct)[Int32(0)], LoadVarInst(Address(fTemp11, kStack)))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp9, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp10, kStack)))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp11, kStack))))))
		DeclareVarInst("float", fTemp12, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input12, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR12, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR12, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
		DeclareVarInst("float", fTemp13, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input13, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR13, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR13, kStruct)[Int32(0)], LoadVarInst(Address(fTemp13, kStack)))
		DeclareVarInst("float", fTemp14, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input14, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR14, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR14, kStruct)[Int32(0)], LoadVarInst(Address(fTemp14, kStack)))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp12, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp13, kStack)))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp14, kStack))))))
		DeclareVarInst("float", fTemp15, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input15, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR15, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR15, kStruct)[Int32(0)], LoadVarInst(Address(fTemp15, kStack)))
		DeclareVarInst("float", fTemp16, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input16, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR16, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR16, kStruct)[Int32(0)], LoadVarInst(Address(fTemp16, kStack)))
		DeclareVarInst("float", fTemp17, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input17, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR17, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR17, kStruct)[Int32(0)], LoadVarInst(Address(fTemp17, kStack)))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp15, kStack))), BinopInst("+", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp16, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp17, kStack)))))))
		DeclareVarInst("float", fTemp18, kStack, BinopInst("+", CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input18, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input19, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input20, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR18, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR18, kStruct)[Int32(0)], LoadVarInst(Address(fTemp18, kStack)))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp18, kStack)))))
		DeclareVarInst("float", fTemp19, kStack, BinopInst("+", CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input21, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input22, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input23, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR19, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR19, kStruct)[Int32(0)], LoadVarInst(Address(fTemp19, kStack)))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp19, kStack)))))
		DeclareVarInst("float", fTemp20, kStack, BinopInst("+", CastInst("float", BinopInst("*", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input24, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("%", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input25, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input26, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR20, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR20, kStruct)[Int32(0)], LoadVarInst(Address(fTemp20, kStack)))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp20, kStack)))))
		DeclareVarInst("float", fTemp21, kStack, BinopInst("+", CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input27, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input28, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input29, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR21, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR21, kStruct)[Int32(0)], LoadVarInst(Address(fTemp21, kStack)))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp21, kStack)))))
		DeclareVarInst("float", fTemp22, kStack, BinopInst("+", CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input30, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input31, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input32, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR22, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR22, kStruct)[Int32(0)], LoadVarInst(Address(fTemp22, kStack)))
		StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp22, kStack)))))
		DeclareVarInst("float", fTemp23, kStack, BinopInst("+", CastInst("float", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input33, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst(">>", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input34, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input35, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR23, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR23, kStruct)[Int32(0)], LoadVarInst(Address(fTemp23, kStack)))
		StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp23, kStack)))))
		DeclareVarInst("float", fTemp24, kStack, BinopInst("+", CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input36, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input37, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input38, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR24, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR24, kStruct)[Int32(0)], LoadVarInst(Address(fTemp24, kStack)))
		StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp24, kStack)))))
		DeclareVarInst("float", fTemp25, kStack, BinopInst("+", CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input39, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input40, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input41, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR25, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR25, kStruct)[Int32(0)], LoadVarInst(Address(fTemp25, kStack)))
		StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp25, kStack)))))
		DeclareVarInst("float", fTemp26, kStack, BinopInst("+", CastInst("float", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input42, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("<=", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input43, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input44, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR26, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR26, kStruct)[Int32(0)], LoadVarInst(Address(fTemp26, kStack)))
		StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp26, kStack)))))
		DeclareVarInst("float", fTemp27, kStack, BinopInst("+", CastInst("float", BinopInst("<=", BinopInst("<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input45, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input46, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input47, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR27, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR27, kStruct)[Int32(0)], LoadVarInst(Address(fTemp27, kStack)))
		StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp27, kStack)))))
		DeclareVarInst("float", fTemp28, kStack, BinopInst("+", CastInst("float", BinopInst("<=", BinopInst("<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input48, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input49, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input50, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR28, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR28, kStruct)[Int32(0)], LoadVarInst(Address(fTemp28, kStack)))
		StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp28, kStack)))))
		DeclareVarInst("float", fTemp29, kStack, BinopInst("+", CastInst("float", BinopInst("<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input51, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("<=", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input52, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input53, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR29, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR29, kStruct)[Int32(0)], LoadVarInst(Address(fTemp29, kStack)))
		StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp29, kStack)))))
		DeclareVarInst("float", fTemp30, kStack, BinopInst("+", CastInst("float", BinopInst("!=", BinopInst("==", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input54, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input55, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input56, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR30, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR30, kStruct)[Int32(0)], LoadVarInst(Address(fTemp30, kStack)))
		StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp30, kStack)))))
		DeclareVarInst("float", fTemp31, kStack, BinopInst("+", CastInst("float", BinopInst("!=", BinopInst("==", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input57, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input58, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input59, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR31, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR31, kStruct)[Int32(0)], LoadVarInst(Address(fTemp31, kStack)))
		StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp31, kStack)))))
		DeclareVarInst("float", fTemp32, kStack, BinopInst("+", CastInst("float", BinopInst("==", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input60, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("!=", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input61, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input62, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR32, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR32, kStruct)[Int32(0)], LoadVarInst(Address(fTemp32, kStack)))
		StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp32, kStack)))))
		DeclareVarInst("float", fTemp33, kStack, BinopInst("+", CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input63, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input64, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input65, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR33, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR33, kStruct)[Int32(0)], LoadVarInst(Address(fTemp33, kStack)))
		StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp33, kStack)))))
		DeclareVarInst("float", fTemp34, kStack, BinopInst("+", CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input66, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input67, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input68, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR34, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR34, kStruct)[Int32(0)], LoadVarInst(Address(fTemp34, kStack)))
		StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp34, kStack)))))
		DeclareVarInst("float", fTemp35, kStack, BinopInst("+", CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input69, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input70, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input71, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR35, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR35, kStruct)[Int32(0)], LoadVarInst(Address(fTemp35, kStack)))
		StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp35, kStack)))))
		DeclareVarInst("float", fTemp36, kStack, BinopInst("+", CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input72, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input73, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input74, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR36, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR36, kStruct)[Int32(0)], LoadVarInst(Address(fTemp36, kStack)))
		StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp36, kStack)))))
		DeclareVarInst("float", fTemp37, kStack, BinopInst("+", CastInst("float", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input75, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("|", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input76, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input77, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR37, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR37, kStruct)[Int32(0)], LoadVarInst(Address(fTemp37, kStack)))
		StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp37, kStack)))))
		DeclareVarInst("float", fTemp38, kStack, BinopInst("+", CastInst("float", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input78, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("^", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input79, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input80, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR38, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR38, kStruct)[Int32(0)], LoadVarInst(Address(fTemp38, kStack)))
		StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp38, kStack)))))
		DeclareVarInst("float", fTemp39, kStack, BinopInst("+", CastInst("float", BinopInst("|", BinopInst("-", BinopInst("+", BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input82, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input81, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input83, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input84, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR39, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR39, kStruct)[Int32(0)], LoadVarInst(Address(fTemp39, kStack)))
		StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp39, kStack)))))
		DeclareVarInst("float", fTemp40, kStack, BinopInst("+", CastInst("float", BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input85, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input86, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), CastInst("float", BinopInst("+", Int32(1), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input87, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))))), CastInst("float", BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input88, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input89, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input90, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input91, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input92, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR40, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR40, kStruct)[Int32(0)], LoadVarInst(Address(fTemp40, kStack)))
		StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp40, kStack)))))
		DeclareVarInst("float", fTemp41, kStack, BinopInst("+", CastInst("float", BinopInst(">=", BinopInst("<=", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input93, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input94, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))), BinopInst("|", BinopInst("-", BinopInst("+", BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input96, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input95, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input97, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input98, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR41, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR41, kStruct)[Int32(0)], LoadVarInst(Address(fTemp41, kStack)))
		StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp41, kStack)))))
		DeclareVarInst("float", fTemp42, kStack, BinopInst("+", CastInst("float", BinopInst("|", BinopInst("-", BinopInst("+", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input99, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input100, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input101, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))), BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input102, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input103, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), CastInst("float", BinopInst("+", Int32(1), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input104, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))))), CastInst("float", BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input105, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input106, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input107, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input108, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input109, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR42, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR42, kStruct)[Int32(0)], LoadVarInst(Address(fTemp42, kStack)))
		StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp42, kStack)))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR8, kStruct)[Int32(1)], LoadVarInst(Address(fIIR8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR9, kStruct)[Int32(1)], LoadVarInst(Address(fIIR9, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR10, kStruct)[Int32(1)], LoadVarInst(Address(fIIR10, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR11, kStruct)[Int32(1)], LoadVarInst(Address(fIIR11, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR12, kStruct)[Int32(1)], LoadVarInst(Address(fIIR12, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR13, kStruct)[Int32(1)], LoadVarInst(Address(fIIR13, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR14, kStruct)[Int32(1)], LoadVarInst(Address(fIIR14, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR15, kStruct)[Int32(1)], LoadVarInst(Address(fIIR15, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR16, kStruct)[Int32(1)], LoadVarInst(Address(fIIR16, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR17, kStruct)[Int32(1)], LoadVarInst(Address(fIIR17, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR18, kStruct)[Int32(1)], LoadVarInst(Address(fIIR18, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR19, kStruct)[Int32(1)], LoadVarInst(Address(fIIR19, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR20, kStruct)[Int32(1)], LoadVarInst(Address(fIIR20, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR21, kStruct)[Int32(1)], LoadVarInst(Address(fIIR21, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR22, kStruct)[Int32(1)], LoadVarInst(Address(fIIR22, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR23, kStruct)[Int32(1)], LoadVarInst(Address(fIIR23, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR24, kStruct)[Int32(1)], LoadVarInst(Address(fIIR24, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR25, kStruct)[Int32(1)], LoadVarInst(Address(fIIR25, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR26, kStruct)[Int32(1)], LoadVarInst(Address(fIIR26, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR27, kStruct)[Int32(1)], LoadVarInst(Address(fIIR27, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR28, kStruct)[Int32(1)], LoadVarInst(Address(fIIR28, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR29, kStruct)[Int32(1)], LoadVarInst(Address(fIIR29, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR30, kStruct)[Int32(1)], LoadVarInst(Address(fIIR30, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR31, kStruct)[Int32(1)], LoadVarInst(Address(fIIR31, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR32, kStruct)[Int32(1)], LoadVarInst(Address(fIIR32, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR33, kStruct)[Int32(1)], LoadVarInst(Address(fIIR33, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR34, kStruct)[Int32(1)], LoadVarInst(Address(fIIR34, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR35, kStruct)[Int32(1)], LoadVarInst(Address(fIIR35, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR36, kStruct)[Int32(1)], LoadVarInst(Address(fIIR36, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR37, kStruct)[Int32(1)], LoadVarInst(Address(fIIR37, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR38, kStruct)[Int32(1)], LoadVarInst(Address(fIIR38, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR39, kStruct)[Int32(1)], LoadVarInst(Address(fIIR39, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR40, kStruct)[Int32(1)], LoadVarInst(Address(fIIR40, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR41, kStruct)[Int32(1)], LoadVarInst(Address(fIIR41, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR42, kStruct)[Int32(1)], LoadVarInst(Address(fIIR42, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "fmodf", "float", dummy0, "float", dummy1)
	DeclareVarInst("float", fIIR0[2], kStruct)
	DeclareVarInst("float", fIIR1[2], kStruct)
	DeclareVarInst("float", fIIR2[2], kStruct)
	DeclareVarInst("float", fIIR3[2], kStruct)
	DeclareVarInst("float", fIIR4[2], kStruct)
	DeclareVarInst("float", fIIR5[2], kStruct)
	DeclareVarInst("float", fIIR6[2], kStruct)
	DeclareVarInst("float", fIIR7[2], kStruct)
	DeclareVarInst("float", fIIR8[2], kStruct)
	DeclareVarInst("float", fIIR9[2], kStruct)
	DeclareVarInst("float", fIIR10[2], kStruct)
	DeclareVarInst("float", fIIR11[2], kStruct)
	DeclareVarInst("float", fIIR12[2], kStruct)
	DeclareVarInst("float", fIIR13[2], kStruct)
	DeclareVarInst("float", fIIR14[2], kStruct)
	DeclareVarInst("float", fIIR15[2], kStruct)
	DeclareVarInst("float", fIIR16[2], kStruct)
	DeclareVarInst("float", fIIR17[2], kStruct)
	DeclareVarInst("float", fIIR18[2], kStruct)
	DeclareVarInst("float", fIIR19[2], kStruct)
	DeclareVarInst("float", fIIR20[2], kStruct)
	DeclareVarInst("float", fIIR21[2], kStruct)
	DeclareVarInst("float", fIIR22[2], kStruct)
	DeclareVarInst("float", fIIR23[2], kStruct)
	DeclareVarInst("float", fIIR24[2], kStruct)
	DeclareVarInst("float", fIIR25[2], kStruct)
	DeclareVarInst("float", fIIR26[2], kStruct)
	DeclareVarInst("float", fIIR27[2], kStruct)
	DeclareVarInst("float", fIIR28[2], kStruct)
	DeclareVarInst("float", fIIR29[2], kStruct)
	DeclareVarInst("float", fIIR30[2], kStruct)
	DeclareVarInst("float", fIIR31[2], kStruct)
	DeclareVarInst("float", fIIR32[2], kStruct)
	DeclareVarInst("float", fIIR33[2], kStruct)
	DeclareVarInst("float", fIIR34[2], kStruct)
	DeclareVarInst("float", fIIR35[2], kStruct)
	DeclareVarInst("float", fIIR36[2], kStruct)
	DeclareVarInst("float", fIIR37[2], kStruct)
	DeclareVarInst("float", fIIR38[2], kStruct)
	DeclareVarInst("float", fIIR39[2], kStruct)
	DeclareVarInst("float", fIIR40[2], kStruct)
	DeclareVarInst("float", fIIR41[2], kStruct)
	DeclareVarInst("float", fIIR42[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR8, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR9, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR10, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR11, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(2))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR12, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR13, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(2))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR14, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(2))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR15, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l16, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l16, kLoop)), Int32(2))
		StoreVarInst(Address(l16, kLoop), BinopInst("+", LoadVarInst(Address(l16, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR16, kStruct)[LoadVarInst(Address(l16, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l17, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l17, kLoop)), Int32(2))
		StoreVarInst(Address(l17, kLoop), BinopInst("+", LoadVarInst(Address(l17, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR17, kStruct)[LoadVarInst(Address(l17, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l18, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l18, kLoop)), Int32(2))
		StoreVarInst(Address(l18, kLoop), BinopInst("+", LoadVarInst(Address(l18, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR18, kStruct)[LoadVarInst(Address(l18, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l19, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l19, kLoop)), Int32(2))
		StoreVarInst(Address(l19, kLoop), BinopInst("+", LoadVarInst(Address(l19, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR19, kStruct)[LoadVarInst(Address(l19, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l20, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l20, kLoop)), Int32(2))
		StoreVarInst(Address(l20, kLoop), BinopInst("+", LoadVarInst(Address(l20, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR20, kStruct)[LoadVarInst(Address(l20, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l21, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l21, kLoop)), Int32(2))
		StoreVarInst(Address(l21, kLoop), BinopInst("+", LoadVarInst(Address(l21, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR21, kStruct)[LoadVarInst(Address(l21, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l22, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l22, kLoop)), Int32(2))
		StoreVarInst(Address(l22, kLoop), BinopInst("+", LoadVarInst(Address(l22, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR22, kStruct)[LoadVarInst(Address(l22, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l23, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l23, kLoop)), Int32(2))
		StoreVarInst(Address(l23, kLoop), BinopInst("+", LoadVarInst(Address(l23, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR23, kStruct)[LoadVarInst(Address(l23, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l24, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l24, kLoop)), Int32(2))
		StoreVarInst(Address(l24, kLoop), BinopInst("+", LoadVarInst(Address(l24, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR24, kStruct)[LoadVarInst(Address(l24, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l25, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l25, kLoop)), Int32(2))
		StoreVarInst(Address(l25, kLoop), BinopInst("+", LoadVarInst(Address(l25, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR25, kStruct)[LoadVarInst(Address(l25, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l26, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l26, kLoop)), Int32(2))
		StoreVarInst(Address(l26, kLoop), BinopInst("+", LoadVarInst(Address(l26, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR26, kStruct)[LoadVarInst(Address(l26, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l27, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l27, kLoop)), Int32(2))
		StoreVarInst(Address(l27, kLoop), BinopInst("+", LoadVarInst(Address(l27, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR27, kStruct)[LoadVarInst(Address(l27, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l28, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l28, kLoop)), Int32(2))
		StoreVarInst(Address(l28, kLoop), BinopInst("+", LoadVarInst(Address(l28, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR28, kStruct)[LoadVarInst(Address(l28, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l29, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l29, kLoop)), Int32(2))
		StoreVarInst(Address(l29, kLoop), BinopInst("+", LoadVarInst(Address(l29, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR29, kStruct)[LoadVarInst(Address(l29, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l30, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l30, kLoop)), Int32(2))
		StoreVarInst(Address(l30, kLoop), BinopInst("+", LoadVarInst(Address(l30, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR30, kStruct)[LoadVarInst(Address(l30, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l31, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l31, kLoop)), Int32(2))
		StoreVarInst(Address(l31, kLoop), BinopInst("+", LoadVarInst(Address(l31, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR31, kStruct)[LoadVarInst(Address(l31, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l32, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l32, kLoop)), Int32(2))
		StoreVarInst(Address(l32, kLoop), BinopInst("+", LoadVarInst(Address(l32, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR32, kStruct)[LoadVarInst(Address(l32, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l33, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l33, kLoop)), Int32(2))
		StoreVarInst(Address(l33, kLoop), BinopInst("+", LoadVarInst(Address(l33, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR33, kStruct)[LoadVarInst(Address(l33, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l34, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l34, kLoop)), Int32(2))
		StoreVarInst(Address(l34, kLoop), BinopInst("+", LoadVarInst(Address(l34, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR34, kStruct)[LoadVarInst(Address(l34, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l35, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l35, kLoop)), Int32(2))
		StoreVarInst(Address(l35, kLoop), BinopInst("+", LoadVarInst(Address(l35, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR35, kStruct)[LoadVarInst(Address(l35, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l36, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l36, kLoop)), Int32(2))
		StoreVarInst(Address(l36, kLoop), BinopInst("+", LoadVarInst(Address(l36, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR36, kStruct)[LoadVarInst(Address(l36, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l37, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l37, kLoop)), Int32(2))
		StoreVarInst(Address(l37, kLoop), BinopInst("+", LoadVarInst(Address(l37, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR37, kStruct)[LoadVarInst(Address(l37, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l38, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l38, kLoop)), Int32(2))
		StoreVarInst(Address(l38, kLoop), BinopInst("+", LoadVarInst(Address(l38, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR38, kStruct)[LoadVarInst(Address(l38, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l39, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l39, kLoop)), Int32(2))
		StoreVarInst(Address(l39, kLoop), BinopInst("+", LoadVarInst(Address(l39, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR39, kStruct)[LoadVarInst(Address(l39, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l40, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l40, kLoop)), Int32(2))
		StoreVarInst(Address(l40, kLoop), BinopInst("+", LoadVarInst(Address(l40, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR40, kStruct)[LoadVarInst(Address(l40, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l41, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l41, kLoop)), Int32(2))
		StoreVarInst(Address(l41, kLoop), BinopInst("+", LoadVarInst(Address(l41, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR41, kStruct)[LoadVarInst(Address(l41, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l42, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l42, kLoop)), Int32(2))
		StoreVarInst(Address(l42, kLoop), BinopInst("+", LoadVarInst(Address(l42, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR42, kStruct)[LoadVarInst(Address(l42, kLoop))], Float(0.0f))
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
			DeclareVarInst("float", fTemp0, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp2, kStack))))))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp5, kStack)))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp3, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp5, kStack))))))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp7, kStack)))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input8, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR8, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR8, kStruct)[Int32(0)], LoadVarInst(Address(fTemp8, kStack)))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp6, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp7, kStack)))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp8, kStack))))))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input9, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR9, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR9, kStruct)[Int32(0)], LoadVarInst(Address(fTemp9, kStack)))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input10, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR10, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR10, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
			DeclareVarInst("float", fTemp11, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input11, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR11, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR11, kStruct)[Int32(0)], LoadVarInst(Address(fTemp11, kStack)))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp9, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp10, kStack)))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp11, kStack))))))
			DeclareVarInst("float", fTemp12, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input12, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR12, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR12, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
			DeclareVarInst("float", fTemp13, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input13, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR13, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR13, kStruct)[Int32(0)], LoadVarInst(Address(fTemp13, kStack)))
			DeclareVarInst("float", fTemp14, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input14, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR14, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR14, kStruct)[Int32(0)], LoadVarInst(Address(fTemp14, kStack)))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp12, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp13, kStack)))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp14, kStack))))))
			DeclareVarInst("float", fTemp15, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input15, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR15, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR15, kStruct)[Int32(0)], LoadVarInst(Address(fTemp15, kStack)))
			DeclareVarInst("float", fTemp16, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input16, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR16, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR16, kStruct)[Int32(0)], LoadVarInst(Address(fTemp16, kStack)))
			DeclareVarInst("float", fTemp17, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(input17, kStack)[LoadVarInst(Address(i0, kLoop))])), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR17, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR17, kStruct)[Int32(0)], LoadVarInst(Address(fTemp17, kStack)))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp15, kStack))), BinopInst("+", BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp16, kStack))), BinopInst("*", Float(1.05f), LoadVarInst(Address(fTemp17, kStack)))))))
			DeclareVarInst("float", fTemp18, kStack, BinopInst("+", CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input18, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input19, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input20, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR18, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR18, kStruct)[Int32(0)], LoadVarInst(Address(fTemp18, kStack)))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp18, kStack)))))
			DeclareVarInst("float", fTemp19, kStack, BinopInst("+", CastInst("float", BinopInst("%", BinopInst("*", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input21, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input22, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input23, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR19, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR19, kStruct)[Int32(0)], LoadVarInst(Address(fTemp19, kStack)))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp19, kStack)))))
			DeclareVarInst("float", fTemp20, kStack, BinopInst("+", CastInst("float", BinopInst("*", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input24, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("%", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input25, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input26, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR20, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR20, kStruct)[Int32(0)], LoadVarInst(Address(fTemp20, kStack)))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp20, kStack)))))
			DeclareVarInst("float", fTemp21, kStack, BinopInst("+", CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input27, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input28, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input29, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR21, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR21, kStruct)[Int32(0)], LoadVarInst(Address(fTemp21, kStack)))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp21, kStack)))))
			DeclareVarInst("float", fTemp22, kStack, BinopInst("+", CastInst("float", BinopInst(">>", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input30, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input31, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input32, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR22, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR22, kStruct)[Int32(0)], LoadVarInst(Address(fTemp22, kStack)))
			StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp22, kStack)))))
			DeclareVarInst("float", fTemp23, kStack, BinopInst("+", CastInst("float", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input33, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst(">>", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input34, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input35, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR23, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR23, kStruct)[Int32(0)], LoadVarInst(Address(fTemp23, kStack)))
			StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp23, kStack)))))
			DeclareVarInst("float", fTemp24, kStack, BinopInst("+", CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input36, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input37, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input38, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR24, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR24, kStruct)[Int32(0)], LoadVarInst(Address(fTemp24, kStack)))
			StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp24, kStack)))))
			DeclareVarInst("float", fTemp25, kStack, BinopInst("+", CastInst("float", BinopInst("<=", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input39, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input40, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input41, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR25, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR25, kStruct)[Int32(0)], LoadVarInst(Address(fTemp25, kStack)))
			StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp25, kStack)))))
			DeclareVarInst("float", fTemp26, kStack, BinopInst("+", CastInst("float", BinopInst("<<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input42, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("<=", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input43, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input44, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR26, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR26, kStruct)[Int32(0)], LoadVarInst(Address(fTemp26, kStack)))
			StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp26, kStack)))))
			DeclareVarInst("float", fTemp27, kStack, BinopInst("+", CastInst("float", BinopInst("<=", BinopInst("<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input45, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input46, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input47, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR27, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR27, kStruct)[Int32(0)], LoadVarInst(Address(fTemp27, kStack)))
			StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp27, kStack)))))
			DeclareVarInst("float", fTemp28, kStack, BinopInst("+", CastInst("float", BinopInst("<=", BinopInst("<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input48, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input49, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input50, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR28, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR28, kStruct)[Int32(0)], LoadVarInst(Address(fTemp28, kStack)))
			StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp28, kStack)))))
			DeclareVarInst("float", fTemp29, kStack, BinopInst("+", CastInst("float", BinopInst("<", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input51, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("<=", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input52, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input53, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR29, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR29, kStruct)[Int32(0)], LoadVarInst(Address(fTemp29, kStack)))
			StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp29, kStack)))))
			DeclareVarInst("float", fTemp30, kStack, BinopInst("+", CastInst("float", BinopInst("!=", BinopInst("==", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input54, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input55, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input56, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR30, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR30, kStruct)[Int32(0)], LoadVarInst(Address(fTemp30, kStack)))
			StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp30, kStack)))))
			DeclareVarInst("float", fTemp31, kStack, BinopInst("+", CastInst("float", BinopInst("!=", BinopInst("==", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input57, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input58, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input59, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR31, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR31, kStruct)[Int32(0)], LoadVarInst(Address(fTemp31, kStack)))
			StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp31, kStack)))))
			DeclareVarInst("float", fTemp32, kStack, BinopInst("+", CastInst("float", BinopInst("==", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input60, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("!=", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input61, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input62, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR32, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR32, kStruct)[Int32(0)], LoadVarInst(Address(fTemp32, kStack)))
			StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp32, kStack)))))
			DeclareVarInst("float", fTemp33, kStack, BinopInst("+", CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input63, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input64, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input65, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR33, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR33, kStruct)[Int32(0)], LoadVarInst(Address(fTemp33, kStack)))
			StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp33, kStack)))))
			DeclareVarInst("float", fTemp34, kStack, BinopInst("+", CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input66, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input67, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input68, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR34, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR34, kStruct)[Int32(0)], LoadVarInst(Address(fTemp34, kStack)))
			StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp34, kStack)))))
			DeclareVarInst("float", fTemp35, kStack, BinopInst("+", CastInst("float", BinopInst("|", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input69, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input70, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input71, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR35, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR35, kStruct)[Int32(0)], LoadVarInst(Address(fTemp35, kStack)))
			StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp35, kStack)))))
			DeclareVarInst("float", fTemp36, kStack, BinopInst("+", CastInst("float", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input72, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input73, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input74, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR36, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR36, kStruct)[Int32(0)], LoadVarInst(Address(fTemp36, kStack)))
			StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp36, kStack)))))
			DeclareVarInst("float", fTemp37, kStack, BinopInst("+", CastInst("float", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input75, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("|", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input76, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input77, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR37, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR37, kStruct)[Int32(0)], LoadVarInst(Address(fTemp37, kStack)))
			StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp37, kStack)))))
			DeclareVarInst("float", fTemp38, kStack, BinopInst("+", CastInst("float", BinopInst("&", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input78, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("^", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input79, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input80, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR38, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR38, kStruct)[Int32(0)], LoadVarInst(Address(fTemp38, kStack)))
			StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp38, kStack)))))
			DeclareVarInst("float", fTemp39, kStack, BinopInst("+", CastInst("float", BinopInst("|", BinopInst("-", BinopInst("+", BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input82, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input81, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input83, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input84, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR39, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR39, kStruct)[Int32(0)], LoadVarInst(Address(fTemp39, kStack)))
			StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp39, kStack)))))
			DeclareVarInst("float", fTemp40, kStack, BinopInst("+", CastInst("float", BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input85, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input86, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), CastInst("float", BinopInst("+", Int32(1), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input87, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))))), CastInst("float", BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input88, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input89, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input90, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input91, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input92, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR40, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR40, kStruct)[Int32(0)], LoadVarInst(Address(fTemp40, kStack)))
			StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp40, kStack)))))
			DeclareVarInst("float", fTemp41, kStack, BinopInst("+", CastInst("float", BinopInst(">=", BinopInst("<=", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input93, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input94, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))), BinopInst("|", BinopInst("-", BinopInst("+", BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input96, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input95, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input97, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input98, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR41, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR41, kStruct)[Int32(0)], LoadVarInst(Address(fTemp41, kStack)))
			StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp41, kStack)))))
			DeclareVarInst("float", fTemp42, kStack, BinopInst("+", CastInst("float", BinopInst("|", BinopInst("-", BinopInst("+", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input99, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input100, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input101, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))), BinopInst(">>", BinopInst("<<", BinopInst("^", BinopInst("&", CastInst("int", FunCallInst("fmodf", BinopInst("/", CastInst("float", BinopInst("*", CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input102, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f)))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input103, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f))))))), CastInst("float", BinopInst("+", Int32(1), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input104, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))))), CastInst("float", BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input105, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input106, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input107, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", BinopInst("*", Float(3.5f), CastInst("float", LoadVarInst(Address(input108, kStack)[LoadVarInst(Address(i0, kLoop))]))), Float(-2.1474836e+09f))))), BinopInst("+", Int32(3), CastInst("int", FunCallInst("min_f", Float(2.1474835e+09f), FunCallInst("max_f", CastInst("float", LoadVarInst(Address(input109, kStack)[LoadVarInst(Address(i0, kLoop))])), Float(-2.1474836e+09f)))))))), BinopInst("*", Float(0.9f), LoadVarInst(Address(fIIR42, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR42, kStruct)[Int32(0)], LoadVarInst(Address(fTemp42, kStack)))
			StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", Float(0.1f), LoadVarInst(Address(fTemp42, kStack)))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR8, kStruct)[Int32(1)], LoadVarInst(Address(fIIR8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR9, kStruct)[Int32(1)], LoadVarInst(Address(fIIR9, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR10, kStruct)[Int32(1)], LoadVarInst(Address(fIIR10, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR11, kStruct)[Int32(1)], LoadVarInst(Address(fIIR11, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR12, kStruct)[Int32(1)], LoadVarInst(Address(fIIR12, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR13, kStruct)[Int32(1)], LoadVarInst(Address(fIIR13, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR14, kStruct)[Int32(1)], LoadVarInst(Address(fIIR14, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR15, kStruct)[Int32(1)], LoadVarInst(Address(fIIR15, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR16, kStruct)[Int32(1)], LoadVarInst(Address(fIIR16, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR17, kStruct)[Int32(1)], LoadVarInst(Address(fIIR17, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR18, kStruct)[Int32(1)], LoadVarInst(Address(fIIR18, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR19, kStruct)[Int32(1)], LoadVarInst(Address(fIIR19, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR20, kStruct)[Int32(1)], LoadVarInst(Address(fIIR20, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR21, kStruct)[Int32(1)], LoadVarInst(Address(fIIR21, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR22, kStruct)[Int32(1)], LoadVarInst(Address(fIIR22, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR23, kStruct)[Int32(1)], LoadVarInst(Address(fIIR23, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR24, kStruct)[Int32(1)], LoadVarInst(Address(fIIR24, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR25, kStruct)[Int32(1)], LoadVarInst(Address(fIIR25, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR26, kStruct)[Int32(1)], LoadVarInst(Address(fIIR26, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR27, kStruct)[Int32(1)], LoadVarInst(Address(fIIR27, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR28, kStruct)[Int32(1)], LoadVarInst(Address(fIIR28, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR29, kStruct)[Int32(1)], LoadVarInst(Address(fIIR29, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR30, kStruct)[Int32(1)], LoadVarInst(Address(fIIR30, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR31, kStruct)[Int32(1)], LoadVarInst(Address(fIIR31, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR32, kStruct)[Int32(1)], LoadVarInst(Address(fIIR32, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR33, kStruct)[Int32(1)], LoadVarInst(Address(fIIR33, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR34, kStruct)[Int32(1)], LoadVarInst(Address(fIIR34, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR35, kStruct)[Int32(1)], LoadVarInst(Address(fIIR35, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR36, kStruct)[Int32(1)], LoadVarInst(Address(fIIR36, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR37, kStruct)[Int32(1)], LoadVarInst(Address(fIIR37, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR38, kStruct)[Int32(1)], LoadVarInst(Address(fIIR38, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR39, kStruct)[Int32(1)], LoadVarInst(Address(fIIR39, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR40, kStruct)[Int32(1)], LoadVarInst(Address(fIIR40, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR41, kStruct)[Int32(1)], LoadVarInst(Address(fIIR41, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR42, kStruct)[Int32(1)], LoadVarInst(Address(fIIR42, kStruct)[Int32(0)]))
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

Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR27 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR33 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR34 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR35 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR36 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR37 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR38 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR39 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR41 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR42 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR9 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR10 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR11 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR12 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR13 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR14 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR15 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR16 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR17 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR18 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR19 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR20 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR21 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR22 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR23 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR24 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR25 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR26 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR27 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR28 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR29 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR30 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR31 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR32 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR33 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR34 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR35 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR36 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR37 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR38 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR39 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR40 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR41 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR42 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR4 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR5 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR6 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR7 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR8 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR9 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR10 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR11 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR12 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR13 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR14 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR15 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR16 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR17 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR18 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR19 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR20 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR21 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR22 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR23 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR24 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR25 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR26 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR27 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR28 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR29 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR30 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR31 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR32 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR33 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR34 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR35 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR36 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR37 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR38 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR39 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR40 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR41 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR42 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            370
  eval() cache hits:       118 (31.8919%)
  eval() cache misses:     252
  Loop detector calls:     252
  Stack detector calls:    252

--- Phase 3: Propagation ---
  propagate() calls:       1784
  propagate() cache hits:  108 (6.05381%)
  propagate() cache misses:1676

--- Box Type Computation ---
  getBoxType() calls:      1991
  getBoxType() cache hits: 1820 (91.4114%)
  getBoxType() computed:   171

--- Environment Operations ---
  Environment lookups:     4
  Average lookup depth:    0
  Env layers pushed:       8

--- Pattern Matching ---
  build automaton calls:        1
  build total time (ms):        0.009584
  build avg time (ms):          0.009584
  apply calls:                  8
  apply total time (ms):        0.004417
  apply avg time (ms):          0.000552125

--- Tree Operations ---
  Trees created:           7266
  Trees reused (hash):     26247 (78.3189% reuse rate)
  Property set ops:        4463
  Property get ops:        14538

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
