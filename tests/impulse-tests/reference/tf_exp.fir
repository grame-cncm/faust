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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", fSampleRate)("float", fConst0)("float", fConst1)("float", fConst2)("float", fConst3)("float", fConst4)("float", fConst5)("float", fConst6)("float", fConst7)("float", fConst8)("int[2]", iVec0)("float", fConst9)("float", fConst10)("float", fConst11)("float", fConst12)("float", fConst13)("float", fConst14)("float", fConst15)("float", fConst16)("float", fConst17)("float", fConst18)("float", fConst19)("float[2]", fVec1)("float", fConst20)("float[2]", fIIR1)("float", fConst21)("float", fConst22)("float[3]", fIIR0)("float[3]", fVec2)("float", fConst23)("float[3]", fRec0)("float", fConst24)("float", fConst25)("float", fConst26)("float[2]", fIIR5)("float[3]", fIIR4)("float[3]", fVec3)("float", fConst27)("float", fConst28)("float[2]", fVec4)("float", fConst29)("float[2]", fIIR3)("float", fConst30)("float[3]", fIIR2)("float[3]", fVec5)("float", fConst31)("float", fConst32)("float", fConst33)("float", fConst34)("float[2]", fIIR7)("float[3]", fIIR6)("float[3]", fVec6)("float", fConst35)("float", fConst36)("float", fConst37)>)

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
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), FunCallInst("tanf", BinopInst("/", Float(1776.5707f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst1, kStruct))))
	StoreVarInst(Address(fConst3, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst1, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst3, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("+", Float(1.0f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("+", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst5, kStruct)), LoadVarInst(Address(fConst2, kStruct))), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("/", Float(2.0f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst9, kStruct), FunCallInst("tanf", BinopInst("/", Float(3553.1414f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst10, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst9, kStruct))))
	StoreVarInst(Address(fConst11, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst9, kStruct))))
	StoreVarInst(Address(fConst12, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst10, kStruct))))
	StoreVarInst(Address(fConst13, kStruct), BinopInst("+", Float(1.0f), LoadVarInst(Address(fConst12, kStruct))))
	StoreVarInst(Address(fConst14, kStruct), BinopInst("+", LoadVarInst(Address(fConst11, kStruct)), LoadVarInst(Address(fConst13, kStruct))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fConst14, kStruct))))
	StoreVarInst(Address(fConst16, kStruct), BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fConst15, kStruct))))
	StoreVarInst(Address(fConst17, kStruct), BinopInst("*", Float(2.0f), LoadVarInst(Address(fConst16, kStruct))))
	StoreVarInst(Address(fConst18, kStruct), BinopInst("+", Float(1.0f), LoadVarInst(Address(fConst11, kStruct))))
	StoreVarInst(Address(fConst19, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fConst18, kStruct)))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst11, kStruct))), LoadVarInst(Address(fConst18, kStruct))))
	StoreVarInst(Address(fConst21, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst12, kStruct))), LoadVarInst(Address(fConst14, kStruct)))))
	StoreVarInst(Address(fConst22, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst13, kStruct)), LoadVarInst(Address(fConst11, kStruct))), LoadVarInst(Address(fConst14, kStruct))))
	StoreVarInst(Address(fConst23, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst15, kStruct))))
	StoreVarInst(Address(fConst24, kStruct), BinopInst("+", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))))
	StoreVarInst(Address(fConst25, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fConst24, kStruct)))))
	StoreVarInst(Address(fConst26, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst18, kStruct))))
	StoreVarInst(Address(fConst27, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst14, kStruct))))
	StoreVarInst(Address(fConst28, kStruct), BinopInst("/", Float(2.0f), LoadVarInst(Address(fConst14, kStruct))))
	StoreVarInst(Address(fConst29, kStruct), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst4, kStruct))), LoadVarInst(Address(fConst6, kStruct)))))
	StoreVarInst(Address(fConst31, kStruct), BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst32, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst31, kStruct))))
	StoreVarInst(Address(fConst33, kStruct), BinopInst("/", Float(2.0f), LoadVarInst(Address(fConst31, kStruct))))
	StoreVarInst(Address(fConst34, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst35, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst36, kStruct), BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst37, kStruct), BinopInst("*", Float(2.0f), LoadVarInst(Address(fConst36, kStruct))))
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
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(3))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(3))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(3))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(3))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(3))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(3))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(3))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(3))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
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

Instructions complexity : Load = 125 Store = 43 Binop = 68 [ { Int(+) = 1 } { Int(-) = 1 } { Int(<) = 1 } { Real(*) = 33 } { Real(+) = 14 } { Real(-) = 18 } ] Mathop = 0 Numbers = 105 Declare = 16 Cast = 2 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
		DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
		DeclareVarInst("float", fTemp1, kStack, CastInst("float", BinopInst("-", Int32(1), LoadVarInst(Address(iVec0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
		DeclareVarInst("float", fTemp2, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fVec1, kStruct)[Int32(0)]), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
		DeclareVarInst("float", fTemp3, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fTemp3, kStack))))
		StoreVarInst(Address(fVec2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
		DeclareVarInst("float", fTemp5, kStack, BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst23, kStruct)), LoadVarInst(Address(fVec2, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst23, kStruct)), LoadVarInst(Address(fVec2, kStruct)[Int32(2)]))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("-", LoadVarInst(Address(fTemp5, kStack)), LoadVarInst(Address(fTemp0, kStack))))))))
		DeclareVarInst("float", fTemp6, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fVec1, kStruct)[Int32(0)]), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
		DeclareVarInst("float", fTemp7, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp6, kStack)), BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), LoadVarInst(Address(fIIR4, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp7, kStack)))
		StoreVarInst(Address(fVec3, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fConst26, kStruct)), LoadVarInst(Address(fTemp7, kStack))))
		DeclareVarInst("float", fTemp8, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst27, kStruct)), LoadVarInst(Address(fVec3, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst28, kStruct)), LoadVarInst(Address(fVec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst27, kStruct)), LoadVarInst(Address(fVec3, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fVec4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp8, kStack)))
		DeclareVarInst("float", fTemp9, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp8, kStack)), LoadVarInst(Address(fVec4, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp9, kStack)))
		DeclareVarInst("float", fTemp10, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp9, kStack)), BinopInst("*", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
		StoreVarInst(Address(fVec5, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fConst25, kStruct)), LoadVarInst(Address(fTemp10, kStack))))
		DeclareVarInst("float", fTemp11, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), LoadVarInst(Address(fVec4, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp11, kStack)))
		DeclareVarInst("float", fTemp12, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp11, kStack)), BinopInst("*", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fIIR6, kStruct)[Int32(2)]))))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
		DeclareVarInst("float", fTemp13, kStack, BinopInst("*", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fTemp12, kStack))))
		StoreVarInst(Address(fVec6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp13, kStack)))
		DeclareVarInst("float", fTemp14, kStack, BinopInst("*", LoadVarInst(Address(fConst37, kStruct)), LoadVarInst(Address(fVec6, kStruct)[Int32(1)])))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst32, kStruct)), LoadVarInst(Address(fVec5, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst33, kStruct)), LoadVarInst(Address(fVec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst32, kStruct)), LoadVarInst(Address(fVec5, kStruct)[Int32(2)])))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fVec6, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fVec6, kStruct)[Int32(2)])))), BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("-", LoadVarInst(Address(fTemp14, kStack)), LoadVarInst(Address(fTemp0, kStack))))))))
		StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(2)], LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec2, kStruct)[Int32(2)], LoadVarInst(Address(fVec2, kStruct)[Int32(1)]))
		StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(2)], LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec3, kStruct)[Int32(2)], LoadVarInst(Address(fVec3, kStruct)[Int32(1)]))
		StoreVarInst(Address(fVec3, kStruct)[Int32(1)], LoadVarInst(Address(fVec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec4, kStruct)[Int32(1)], LoadVarInst(Address(fVec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(2)], LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec5, kStruct)[Int32(2)], LoadVarInst(Address(fVec5, kStruct)[Int32(1)]))
		StoreVarInst(Address(fVec5, kStruct)[Int32(1)], LoadVarInst(Address(fVec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(2)], LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))
		StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec6, kStruct)[Int32(2)], LoadVarInst(Address(fVec6, kStruct)[Int32(1)]))
		StoreVarInst(Address(fVec6, kStruct)[Int32(1)], LoadVarInst(Address(fVec6, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value_f)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value_f, kFunArgs)), LoadVarInst(Address(value_f, kFunArgs))))
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
	DeclareVarInst("float", fConst8, kStruct)
	DeclareVarInst("int", iVec0[2], kStruct)
	DeclareVarInst("float", fConst9, kStruct)
	DeclareVarInst("float", fConst10, kStruct)
	DeclareVarInst("float", fConst11, kStruct)
	DeclareVarInst("float", fConst12, kStruct)
	DeclareVarInst("float", fConst13, kStruct)
	DeclareVarInst("float", fConst14, kStruct)
	DeclareVarInst("float", fConst15, kStruct)
	DeclareVarInst("float", fConst16, kStruct)
	DeclareVarInst("float", fConst17, kStruct)
	DeclareVarInst("float", fConst18, kStruct)
	DeclareVarInst("float", fConst19, kStruct)
	DeclareVarInst("float", fVec1[2], kStruct)
	DeclareVarInst("float", fConst20, kStruct)
	DeclareVarInst("float", fIIR1[2], kStruct)
	DeclareVarInst("float", fConst21, kStruct)
	DeclareVarInst("float", fConst22, kStruct)
	DeclareVarInst("float", fIIR0[3], kStruct)
	DeclareVarInst("float", fVec2[3], kStruct)
	DeclareVarInst("float", fConst23, kStruct)
	DeclareVarInst("float", fRec0[3], kStruct)
	DeclareVarInst("float", fConst24, kStruct)
	DeclareVarInst("float", fConst25, kStruct)
	DeclareVarInst("float", fConst26, kStruct)
	DeclareVarInst("float", fIIR5[2], kStruct)
	DeclareVarInst("float", fIIR4[3], kStruct)
	DeclareVarInst("float", fVec3[3], kStruct)
	DeclareVarInst("float", fConst27, kStruct)
	DeclareVarInst("float", fConst28, kStruct)
	DeclareVarInst("float", fVec4[2], kStruct)
	DeclareVarInst("float", fConst29, kStruct)
	DeclareVarInst("float", fIIR3[2], kStruct)
	DeclareVarInst("float", fConst30, kStruct)
	DeclareVarInst("float", fIIR2[3], kStruct)
	DeclareVarInst("float", fVec5[3], kStruct)
	DeclareVarInst("float", fConst31, kStruct)
	DeclareVarInst("float", fConst32, kStruct)
	DeclareVarInst("float", fConst33, kStruct)
	DeclareVarInst("float", fConst34, kStruct)
	DeclareVarInst("float", fIIR7[2], kStruct)
	DeclareVarInst("float", fIIR6[3], kStruct)
	DeclareVarInst("float", fVec6[3], kStruct)
	DeclareVarInst("float", fConst35, kStruct)
	DeclareVarInst("float", fConst36, kStruct)
	DeclareVarInst("float", fConst37, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), FunCallInst("tanf", BinopInst("/", Float(1776.5707f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst2, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst1, kStruct))))
	StoreVarInst(Address(fConst3, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst1, kStruct))))
	StoreVarInst(Address(fConst4, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst3, kStruct))))
	StoreVarInst(Address(fConst5, kStruct), BinopInst("+", Float(1.0f), LoadVarInst(Address(fConst4, kStruct))))
	StoreVarInst(Address(fConst6, kStruct), BinopInst("+", LoadVarInst(Address(fConst2, kStruct)), LoadVarInst(Address(fConst5, kStruct))))
	StoreVarInst(Address(fConst7, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst5, kStruct)), LoadVarInst(Address(fConst2, kStruct))), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst8, kStruct), BinopInst("/", Float(2.0f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst9, kStruct), FunCallInst("tanf", BinopInst("/", Float(3553.1414f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(fConst10, kStruct), FunCallInst("mydsp_faustpower2_f", LoadVarInst(Address(fConst9, kStruct))))
	StoreVarInst(Address(fConst11, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst9, kStruct))))
	StoreVarInst(Address(fConst12, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst10, kStruct))))
	StoreVarInst(Address(fConst13, kStruct), BinopInst("+", Float(1.0f), LoadVarInst(Address(fConst12, kStruct))))
	StoreVarInst(Address(fConst14, kStruct), BinopInst("+", LoadVarInst(Address(fConst11, kStruct)), LoadVarInst(Address(fConst13, kStruct))))
	StoreVarInst(Address(fConst15, kStruct), BinopInst("*", LoadVarInst(Address(fConst10, kStruct)), LoadVarInst(Address(fConst14, kStruct))))
	StoreVarInst(Address(fConst16, kStruct), BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fConst15, kStruct))))
	StoreVarInst(Address(fConst17, kStruct), BinopInst("*", Float(2.0f), LoadVarInst(Address(fConst16, kStruct))))
	StoreVarInst(Address(fConst18, kStruct), BinopInst("+", Float(1.0f), LoadVarInst(Address(fConst11, kStruct))))
	StoreVarInst(Address(fConst19, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst9, kStruct)), LoadVarInst(Address(fConst18, kStruct)))))
	StoreVarInst(Address(fConst20, kStruct), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst11, kStruct))), LoadVarInst(Address(fConst18, kStruct))))
	StoreVarInst(Address(fConst21, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst12, kStruct))), LoadVarInst(Address(fConst14, kStruct)))))
	StoreVarInst(Address(fConst22, kStruct), BinopInst("/", BinopInst("-", LoadVarInst(Address(fConst13, kStruct)), LoadVarInst(Address(fConst11, kStruct))), LoadVarInst(Address(fConst14, kStruct))))
	StoreVarInst(Address(fConst23, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst15, kStruct))))
	StoreVarInst(Address(fConst24, kStruct), BinopInst("+", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))))
	StoreVarInst(Address(fConst25, kStruct), BinopInst("/", Float(1.0f), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), LoadVarInst(Address(fConst24, kStruct)))))
	StoreVarInst(Address(fConst26, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst18, kStruct))))
	StoreVarInst(Address(fConst27, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst14, kStruct))))
	StoreVarInst(Address(fConst28, kStruct), BinopInst("/", Float(2.0f), LoadVarInst(Address(fConst14, kStruct))))
	StoreVarInst(Address(fConst29, kStruct), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst2, kStruct))), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst30, kStruct), BinopInst("*", Float(2.0f), BinopInst("/", BinopInst("-", Float(1.0f), LoadVarInst(Address(fConst4, kStruct))), LoadVarInst(Address(fConst6, kStruct)))))
	StoreVarInst(Address(fConst31, kStruct), BinopInst("*", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst32, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst31, kStruct))))
	StoreVarInst(Address(fConst33, kStruct), BinopInst("/", Float(2.0f), LoadVarInst(Address(fConst31, kStruct))))
	StoreVarInst(Address(fConst34, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst24, kStruct))))
	StoreVarInst(Address(fConst35, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst36, kStruct), BinopInst("/", LoadVarInst(Address(fConst3, kStruct)), LoadVarInst(Address(fConst6, kStruct))))
	StoreVarInst(Address(fConst37, kStruct), BinopInst("*", Float(2.0f), LoadVarInst(Address(fConst36, kStruct))))
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
			StoreVarInst(Address(fIIR1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(3))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR0, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(3))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
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
			StoreVarInst(Address(fIIR5, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(3))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR4, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(3))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(2))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR3, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(3))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR2, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l12, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l12, kLoop)), Int32(3))
		StoreVarInst(Address(l12, kLoop), BinopInst("+", LoadVarInst(Address(l12, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l12, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l13, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l13, kLoop)), Int32(2))
		StoreVarInst(Address(l13, kLoop), BinopInst("+", LoadVarInst(Address(l13, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR7, kStruct)[LoadVarInst(Address(l13, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l14, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l14, kLoop)), Int32(3))
		StoreVarInst(Address(l14, kLoop), BinopInst("+", LoadVarInst(Address(l14, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fIIR6, kStruct)[LoadVarInst(Address(l14, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l15, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l15, kLoop)), Int32(3))
		StoreVarInst(Address(l15, kLoop), BinopInst("+", LoadVarInst(Address(l15, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6, kStruct)[LoadVarInst(Address(l15, kLoop))], Float(0.0f))
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
			DeclareVarInst("float", fTemp0, kStack, BinopInst("*", LoadVarInst(Address(fConst8, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])))
			DeclareVarInst("float", fTemp1, kStack, CastInst("float", BinopInst("-", Int32(1), LoadVarInst(Address(iVec0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fVec1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp1, kStack)))
			DeclareVarInst("float", fTemp2, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fVec1, kStruct)[Int32(0)]), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fIIR1, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(0)], LoadVarInst(Address(fTemp2, kStack)))
			DeclareVarInst("float", fTemp3, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), LoadVarInst(Address(fIIR0, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("*", LoadVarInst(Address(fConst19, kStruct)), LoadVarInst(Address(fTemp3, kStack))))
			StoreVarInst(Address(fVec2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp4, kStack)))
			DeclareVarInst("float", fTemp5, kStack, BinopInst("*", LoadVarInst(Address(fConst17, kStruct)), LoadVarInst(Address(fVec2, kStruct)[Int32(1)])))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst23, kStruct)), LoadVarInst(Address(fVec2, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst23, kStruct)), LoadVarInst(Address(fVec2, kStruct)[Int32(2)]))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("-", LoadVarInst(Address(fTemp5, kStack)), LoadVarInst(Address(fTemp0, kStack))))))))
			DeclareVarInst("float", fTemp6, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fVec1, kStruct)[Int32(0)]), LoadVarInst(Address(fVec1, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst20, kStruct)), LoadVarInst(Address(fIIR5, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(0)], LoadVarInst(Address(fTemp6, kStack)))
			DeclareVarInst("float", fTemp7, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp6, kStack)), BinopInst("*", LoadVarInst(Address(fConst21, kStruct)), LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst22, kStruct)), LoadVarInst(Address(fIIR4, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp7, kStack)))
			StoreVarInst(Address(fVec3, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fConst26, kStruct)), LoadVarInst(Address(fTemp7, kStack))))
			DeclareVarInst("float", fTemp8, kStack, BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst27, kStruct)), LoadVarInst(Address(fVec3, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst28, kStruct)), LoadVarInst(Address(fVec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst27, kStruct)), LoadVarInst(Address(fVec3, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fVec4, kStruct)[Int32(0)], LoadVarInst(Address(fTemp8, kStack)))
			DeclareVarInst("float", fTemp9, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp8, kStack)), LoadVarInst(Address(fVec4, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fIIR3, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(0)], LoadVarInst(Address(fTemp9, kStack)))
			DeclareVarInst("float", fTemp10, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp9, kStack)), BinopInst("*", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fIIR2, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(0)], LoadVarInst(Address(fTemp10, kStack)))
			StoreVarInst(Address(fVec5, kStruct)[Int32(0)], BinopInst("*", LoadVarInst(Address(fConst25, kStruct)), LoadVarInst(Address(fTemp10, kStack))))
			DeclareVarInst("float", fTemp11, kStack, BinopInst("-", BinopInst("+", LoadVarInst(Address(fTemp8, kStack)), LoadVarInst(Address(fVec4, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fConst29, kStruct)), LoadVarInst(Address(fIIR7, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(0)], LoadVarInst(Address(fTemp11, kStack)))
			DeclareVarInst("float", fTemp12, kStack, BinopInst("-", BinopInst("-", LoadVarInst(Address(fTemp11, kStack)), BinopInst("*", LoadVarInst(Address(fConst30, kStruct)), LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fIIR6, kStruct)[Int32(2)]))))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp12, kStack)))
			DeclareVarInst("float", fTemp13, kStack, BinopInst("*", LoadVarInst(Address(fConst34, kStruct)), LoadVarInst(Address(fTemp12, kStack))))
			StoreVarInst(Address(fVec6, kStruct)[Int32(0)], LoadVarInst(Address(fTemp13, kStack)))
			DeclareVarInst("float", fTemp14, kStack, BinopInst("*", LoadVarInst(Address(fConst37, kStruct)), LoadVarInst(Address(fVec6, kStruct)[Int32(1)])))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst7, kStruct)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), LoadVarInst(Address(fRec0, kStruct)[Int32(2)])), BinopInst("+", BinopInst("-", BinopInst("*", LoadVarInst(Address(fConst32, kStruct)), LoadVarInst(Address(fVec5, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst33, kStruct)), LoadVarInst(Address(fVec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fConst32, kStruct)), LoadVarInst(Address(fVec5, kStruct)[Int32(2)])))), BinopInst("+", BinopInst("*", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fVec6, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fConst35, kStruct)), LoadVarInst(Address(fVec6, kStruct)[Int32(2)])))), BinopInst("+", LoadVarInst(Address(fTemp0, kStack)), BinopInst("*", LoadVarInst(Address(fConst4, kStruct)), BinopInst("-", LoadVarInst(Address(fTemp14, kStack)), LoadVarInst(Address(fTemp0, kStack))))))))
			StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec1, kStruct)[Int32(1)], LoadVarInst(Address(fVec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR1, kStruct)[Int32(1)], LoadVarInst(Address(fIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(2)], LoadVarInst(Address(fIIR0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR0, kStruct)[Int32(1)], LoadVarInst(Address(fIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec2, kStruct)[Int32(2)], LoadVarInst(Address(fVec2, kStruct)[Int32(1)]))
			StoreVarInst(Address(fVec2, kStruct)[Int32(1)], LoadVarInst(Address(fVec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(2)], LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR5, kStruct)[Int32(1)], LoadVarInst(Address(fIIR5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(2)], LoadVarInst(Address(fIIR4, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR4, kStruct)[Int32(1)], LoadVarInst(Address(fIIR4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec3, kStruct)[Int32(2)], LoadVarInst(Address(fVec3, kStruct)[Int32(1)]))
			StoreVarInst(Address(fVec3, kStruct)[Int32(1)], LoadVarInst(Address(fVec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec4, kStruct)[Int32(1)], LoadVarInst(Address(fVec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR3, kStruct)[Int32(1)], LoadVarInst(Address(fIIR3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(2)], LoadVarInst(Address(fIIR2, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR2, kStruct)[Int32(1)], LoadVarInst(Address(fIIR2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec5, kStruct)[Int32(2)], LoadVarInst(Address(fVec5, kStruct)[Int32(1)]))
			StoreVarInst(Address(fVec5, kStruct)[Int32(1)], LoadVarInst(Address(fVec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR7, kStruct)[Int32(1)], LoadVarInst(Address(fIIR7, kStruct)[Int32(0)]))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(2)], LoadVarInst(Address(fIIR6, kStruct)[Int32(1)]))
			StoreVarInst(Address(fIIR6, kStruct)[Int32(1)], LoadVarInst(Address(fIIR6, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec6, kStruct)[Int32(2)], LoadVarInst(Address(fVec6, kStruct)[Int32(1)]))
			StoreVarInst(Address(fVec6, kStruct)[Int32(1)], LoadVarInst(Address(fVec6, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 308 bytes
Total heap size = 320 bytes
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
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

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
Field = fConst8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec3 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fConst30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR2 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec5 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fIIR7 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fIIR6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fVec6 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fConst35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst4 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst7 size = 1 size_bytes = 4 read = 4 write = 0 ratio = 4
Field = fConst8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iVec0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst19 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fConst20 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst21 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst22 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fIIR0 size = 3 size_bytes = 12 read = 4 write = 3 ratio = 2.33333
Field = fVec2 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fConst23 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fRec0 size = 3 size_bytes = 12 read = 6 write = 3 ratio = 3
Field = fConst24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst25 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst26 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR5 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR4 size = 3 size_bytes = 12 read = 4 write = 3 ratio = 2.33333
Field = fVec3 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fConst27 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst28 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec4 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fConst29 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fIIR3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fConst30 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fIIR2 size = 3 size_bytes = 12 read = 4 write = 3 ratio = 2.33333
Field = fVec5 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fConst31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst32 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst33 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fConst34 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fIIR7 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fIIR6 size = 3 size_bytes = 12 read = 4 write = 3 ratio = 2.33333
Field = fVec6 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fConst35 size = 1 size_bytes = 4 read = 2 write = 0 ratio = 2
Field = fConst36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst37 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            749
  eval() cache hits:       335 (44.7263%)
  eval() cache misses:     414
  Loop detector calls:     414
  Stack detector calls:    414

--- Phase 3: Propagation ---
  propagate() calls:       804
  propagate() cache hits:  177 (22.0149%)
  propagate() cache misses:627

--- Box Type Computation ---
  getBoxType() calls:      1534
  getBoxType() cache hits: 1131 (73.7288%)
  getBoxType() computed:   403

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       6

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           3080
  Trees reused (hash):     18769 (85.9032% reuse rate)
  Property set ops:        1679
  Property get ops:        5315

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
