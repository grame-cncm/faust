======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("tf_exp")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("float", fConst1)("float", fConst2)("float", fConst3)("float", fConst4)("float", fConst5)("float", fConst6)("float", fConst7)("int[2]", iVec0)("float[2]", fVec1)("float[2]", fRec2)("float", fConst8)("float", fConst9)("float", fConst10)("float[3]", fRec1)("float", fConst11)("float", fConst12)("float", fConst13)("float", fConst14)("float", fConst15)("float", fConst16)("float", fConst17)("float", fConst18)("float[3]", fRec0)("float", fConst19)("float", fConst20)("float[2]", fRec6)("float[3]", fRec5)("float[2]", fVec2)("float[2]", fRec4)("float", fConst21)("float[3]", fRec3)("float", fConst22)("float[2]", fRec8)("float[3]", fRec7)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(1))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), FunCallInst("tanf", BinopInst("/", Float(3553.1414f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst1, kStruct))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst1, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(1.0f)), LoadVarInst(Address(fConst1, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst4, kStruct)))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst3, kStruct))))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst9, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-1.0f)), LoadVarInst(Address(fConst1, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst10, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))))))
	StoreVarInst(Address(fConst11, kStruct), FunCallInst("tanf", BinopInst("/", Float(1776.5707f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst12, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst11, kStruct))))
	StoreVarInst(Address(fConst13, kStruct), BinopInst("+", LoadVarInst(Address(fConst12, kStruct)), Float(1.0f)))
	StoreVarInst(Address(fConst14, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", LoadVarInst(Address(fConst13, kStruct)), LoadVarInst(Address(fConst11, kStruct))), Float(1.0f))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst12, kStruct))))
	StoreVarInst(Address(fConst16, kStruct), BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fConst11, kStruct)))))
	StoreVarInst(Address(fConst17, kStruct), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst11, kStruct)))))
	StoreVarInst(Address(fConst18, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst17, kStruct)))))
	StoreVarInst(Address(fConst19, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst12, kStruct)), Float(1.0f)), LoadVarInst(Address(fConst11, kStruct))), Float(1.0f))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst13, kStruct))))
	StoreVarInst(Address(fConst21, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst12, kStruct)), Float(-1.0f)), LoadVarInst(Address(fConst11, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst22, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst11, kStruct)), LoadVarInst(Address(fConst4, kStruct)))))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(3))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
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
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(3))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(3))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 1 Store = 0 Binop = 0 Mathop = 0 Numbers = 1 Declare = 1 Cast = 0 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 97 Store = 31 Binop = 68 [ { Int(+) = 1 } { Int(-) = 1 } { Int(<) = 1 } { Real(*) = 35 } { Real(+) = 17 } { Real(-) = 13 } ] Mathop = 0 Numbers = 91 Declare = 4 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", BinopInst("-", Int32(1), LoadVarInst(Address(iVec0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst6, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), BinopInst("-", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])))))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp1, kStack, BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst5, kStruct)), BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(2)]), BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))), BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp1, kStack))))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst6, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec6, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fRec5, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec5, kStruct)[Int32(1)])))))
		StoreVarInst(Address(fVec2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst20, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(fRec8, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst20, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fRec8, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))))))
		StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fRec8, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fRec7, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(2)]), BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), BinopInst("+", LoadVarInst(Address(fTemp1, kStack)), BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))), BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))), BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(2)]), BinopInst("-", LoadVarInst(Address(fRec7, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))))))))
		StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(2)], LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(2)], LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(2)], LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "tanf", "float", dummy0)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("float", fConst2, kStruct)
	DeclareVarInst("float", fConst3, kStruct)
	DeclareVarInst("float", fConst4, kStruct)
	DeclareVarInst("float", fConst5, kStruct)
	DeclareVarInst("float", fConst6, kStruct)
	DeclareVarInst("float", fConst7, kStruct)
	DeclareVarInst("int", iVec0[2], kStruct)
	DeclareVarInst("float", fVec1[2], kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("float", fConst8, kStruct)
	DeclareVarInst("float", fConst9, kStruct)
	DeclareVarInst("float", fConst10, kStruct)
	DeclareVarInst("float", fRec1[3], kStruct)
	DeclareVarInst("float", fConst11, kStruct)
	DeclareVarInst("float", fConst12, kStruct)
	DeclareVarInst("float", fConst13, kStruct)
	DeclareVarInst("float", fConst14, kStruct)
	DeclareVarInst("float", fConst15, kStruct)
	DeclareVarInst("float", fConst16, kStruct)
	DeclareVarInst("float", fConst17, kStruct)
	DeclareVarInst("float", fConst18, kStruct)
	DeclareVarInst("float", fRec0[3], kStruct)
	DeclareVarInst("float", fConst19, kStruct)
	DeclareVarInst("float", fConst20, kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	DeclareVarInst("float", fRec5[3], kStruct)
	DeclareVarInst("float", fVec2[2], kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("float", fConst21, kStruct)
	DeclareVarInst("float", fRec3[3], kStruct)
	DeclareVarInst("float", fConst22, kStruct)
	DeclareVarInst("float", fRec8[2], kStruct)
	DeclareVarInst("float", fRec7[3], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), FunCallInst("tanf", BinopInst("/", Float(3553.1414f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst2, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst1, kStruct))))
	StoreVarInst(Address(fConst3, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst1, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(1.0f)), LoadVarInst(Address(fConst1, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst4, kStruct)))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(1.0f))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst3, kStruct))))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst9, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst3, kStruct)), Float(-1.0f)), LoadVarInst(Address(fConst1, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst10, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))))))
	StoreVarInst(Address(fConst11, kStruct), FunCallInst("tanf", BinopInst("/", Float(1776.5707f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst12, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst11, kStruct))))
	StoreVarInst(Address(fConst13, kStruct), BinopInst("+", LoadVarInst(Address(fConst12, kStruct)), Float(1.0f)))
	StoreVarInst(Address(fConst14, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", LoadVarInst(Address(fConst13, kStruct)), LoadVarInst(Address(fConst11, kStruct))), Float(1.0f))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst12, kStruct))))
	StoreVarInst(Address(fConst16, kStruct), BinopInst("-", Float(1.0f), BinopInst("/", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fConst11, kStruct)))))
	StoreVarInst(Address(fConst17, kStruct), BinopInst("/", Float(1.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst11, kStruct)))))
	StoreVarInst(Address(fConst18, kStruct), BinopInst("*", Float(2.0f), BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst17, kStruct)))))
	StoreVarInst(Address(fConst19, kStruct), BinopInst("/", Float(1.0f), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst12, kStruct)), Float(1.0f)), LoadVarInst(Address(fConst11, kStruct))), Float(1.0f))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst13, kStruct))))
	StoreVarInst(Address(fConst21, kStruct), BinopInst("+", BinopInst("/", BinopInst("+", LoadVarInst(Address(fConst12, kStruct)), Float(-1.0f)), LoadVarInst(Address(fConst11, kStruct))), Float(1.0f)))
	StoreVarInst(Address(fConst22, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst11, kStruct)), LoadVarInst(Address(fConst4, kStruct)))))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(3))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
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
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
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
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(3))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec8, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(3))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec7, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", BinopInst("-", Int32(1), LoadVarInst(Address(iVec0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp0, kStack)))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst6, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), BinopInst("-", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])))))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fRec2, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp1, kStack, BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst5, kStruct)), BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(2)]), BinopInst("-", LoadVarInst(Address(fRec1, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))))), BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), LoadVarInst(Address(fTemp1, kStack))))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst6, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec6, kStruct)[Int32(1)])), BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), LoadVarInst(Address(fVec1, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fRec6, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fRec5, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fRec5, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec5, kStruct)[Int32(1)])))))
			StoreVarInst(Address(fVec2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst20, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fRec4, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(fRec8, kStruct)[Int32(0)], MinusInst(BinopInst("*", LoadVarInst(Address(fConst20, kStruct)), BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst15, kStruct)), LoadVarInst(Address(fRec8, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))))))
			StoreVarInst(Address(fRec7, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fRec8, kStruct)[Int32(0)]), BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fRec7, kStruct)[Int32(2)])), BinopInst("*", LoadVarInst(Address(fConst18, kStruct)), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec0, kStruct)[Int32(2)]), BinopInst("*", LoadVarInst(Address(fConst14, kStruct)), BinopInst("+", LoadVarInst(Address(fTemp1, kStack)), BinopInst("*", LoadVarInst(Address(fConst16, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))))), BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), BinopInst("+", BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(2)]), BinopInst("+", LoadVarInst(Address(fRec3, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec3, kStruct)[Int32(1)])))), BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), BinopInst("+", LoadVarInst(Address(fRec7, kStruct)[Int32(2)]), BinopInst("-", LoadVarInst(Address(fRec7, kStruct)[Int32(0)]), BinopInst("*", Float(2.0f), LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))))))))))
			StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(2)], LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(2)], LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(2)], LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec8, kStruct)[Int32(1)], LoadVarInst(Address(fRec8, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(2)], LoadVarInst(Address(fRec7, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec7, kStruct)[Int32(1)], LoadVarInst(Address(fRec7, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 200 bytes
Total heap size = 212 bytes
Stack size in compute = 8 bytes

======= Variable access in Control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec8 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec7 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst6 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst7 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = iVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fVec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst8 size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fConst9 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst10 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec1 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst15 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst16 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst18 size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fRec0 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fConst19 size = 1 size_bytes = 4 read = 3 write = 0 ratio = 3
Field = fConst20 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec6 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec5 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fVec2 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst21 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec3 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
Field = fConst22 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec8 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fRec7 size = 3 size_bytes = 12 read = 7 write = 3 ratio = 3.33333
