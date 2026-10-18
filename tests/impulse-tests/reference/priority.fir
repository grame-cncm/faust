======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container "mydspSIG0" ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "sinf", "float", dummy0)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydspSIG0",("int[2]", iVec0)("int[2]", iRec0)>)

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
			StoreVarInst(Address(iRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 9 Store = 6 Binop = 5 [ { Int(%) = 1 } { Int(+) = 2 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { sinf = 1 } ] Numbers = 14 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
		StoreVarInst(Address(iRec0, kStruct)[Int32(0)], BinopInst("%", BinopInst("+", LoadVarInst(Address(iVec0, kStruct)[Int32(1)]), LoadVarInst(Address(iRec0, kStruct)[Int32(1)])), Int32(65536)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", LoadVarInst(Address(iRec0, kStruct)[Int32(0)])))))
		StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(iRec0, kStruct)[Int32(1)], LoadVarInst(Address(iRec0, kStruct)[Int32(0)]))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("priority")
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareVarInst("float", ftbl0mydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int[2]", iVec1)("int", fSampleRate)("float", fConst0)("float", fConst1)("int", iConst2)("int[2]", iRec2)("int[2]", iVec2)("int[2]", iIIR0)("int", iConst3)("int[2]", iRec3)("int[2]", iVec3)("int[2]", iIIR1)("float[2]", fRec1)>)

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

======= Static Init begin ==========

BlockInst 
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(iConst2, kStruct), CastInst("int", BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(iConst3, kStruct), CastInst("int", LoadVarInst(Address(fConst0, kStruct))))
EndBlockInst

======= Init end ==========

======= Clear begin ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec2, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l5, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec3, kStruct)[LoadVarInst(Address(l6, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec3, kStruct)[LoadVarInst(Address(l7, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l8, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
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

Instructions complexity : Load = 40 Store = 18 Binop = 22 [ { Int(%) = 4 } { Int(*) = 2 } { Int(+) = 7 } { Int(<) = 1 } { Int(<=) = 2 } { Int(>) = 2 } { Real(*) = 2 } { Real(+) = 1 } { Real(-) = 1 } ] Mathop = 3 [ { floorf = 1 } { max_i = 1 } { min_i = 1 } ] Numbers = 49 Declare = 6 Cast = 3 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec1, kStruct)[Int32(0)], Int32(1))
		StoreVarInst(Address(iRec2, kStruct)[Int32(0)], BinopInst("%", BinopInst("+", LoadVarInst(Address(iVec1, kStruct)[Int32(1)]), LoadVarInst(Address(iRec2, kStruct)[Int32(1)])), LoadVarInst(Address(iConst2, kStruct))))
		DeclareVarInst("int", iTemp0, kStack, BinopInst("<=", LoadVarInst(Address(iRec2, kStruct)[Int32(0)]), LoadVarInst(Address(iRec2, kStruct)[Int32(1)])))
		StoreVarInst(Address(iVec2, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
		DeclareVarInst("int", iTemp1, kStack, BinopInst("+", BinopInst(">", LoadVarInst(Address(iTemp0, kStack)), LoadVarInst(Address(iVec2, kStruct)[Int32(1)])), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp1, kStack)))
		StoreVarInst(Address(iRec3, kStruct)[Int32(0)], BinopInst("%", BinopInst("+", LoadVarInst(Address(iVec1, kStruct)[Int32(1)]), LoadVarInst(Address(iRec3, kStruct)[Int32(1)])), LoadVarInst(Address(iConst3, kStruct))))
		DeclareVarInst("int", iTemp2, kStack, BinopInst("<=", LoadVarInst(Address(iRec3, kStruct)[Int32(0)]), LoadVarInst(Address(iRec3, kStruct)[Int32(1)])))
		StoreVarInst(Address(iVec3, kStruct)[Int32(0)], LoadVarInst(Address(iTemp2, kStack)))
		DeclareVarInst("int", iTemp3, kStack, BinopInst("+", BinopInst(">", LoadVarInst(Address(iTemp2, kStack)), LoadVarInst(Address(iVec3, kStruct)[Int32(1)])), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)])))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp3, kStack)))
		DeclareVarInst("float", fTemp4, kStack, BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), CastInst("float", BinopInst("*", Int32(200), BinopInst("+", BinopInst("+", Int32(1), BinopInst("%", LoadVarInst(Address(iTemp1, kStack)), Int32(2))), BinopInst("*", Int32(2), BinopInst("%", LoadVarInst(Address(iTemp3, kStack)), Int32(2)))))))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp4, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp4, kStack)))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))), Int32(65535)))])))
		StoreVarInst(Address(iVec1, kStruct)[Int32(1)], LoadVarInst(Address(iVec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(iRec2, kStruct)[Int32(1)], LoadVarInst(Address(iRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec2, kStruct)[Int32(1)], LoadVarInst(Address(iVec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
		StoreVarInst(Address(iRec3, kStruct)[Int32(1)], LoadVarInst(Address(iRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(iVec3, kStruct)[Int32(1)], LoadVarInst(Address(iVec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(iIIR1, kStruct)[Int32(1)], LoadVarInst(Address(iIIR1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
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
	DeclareVarInst("float", ftbl0mydspSIG0[65536], kStaticStruct)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("int", iVec1[2], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("float", fConst1, kStruct)
	DeclareVarInst("int", iConst2, kStruct)
	DeclareVarInst("int", iRec2[2], kStruct)
	DeclareVarInst("int", iVec2[2], kStruct)
	DeclareVarInst("int", iIIR0[2], kStruct)
	DeclareVarInst("int", iConst3, kStruct)
	DeclareVarInst("int", iRec3[2], kStruct)
	DeclareVarInst("int", iVec3[2], kStruct)
	DeclareVarInst("int", iIIR1[2], kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(5e+01f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fConst1, kStruct), BinopInst("/", Float(1.0f), LoadVarInst(Address(fConst0, kStruct))))
	StoreVarInst(Address(iConst2, kStruct), CastInst("int", BinopInst("*", Float(0.5f), LoadVarInst(Address(fConst0, kStruct)))))
	StoreVarInst(Address(iConst3, kStruct), CastInst("int", LoadVarInst(Address(fConst0, kStruct))))
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec2, kStruct)[LoadVarInst(Address(l3, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(2))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR0, kStruct)[LoadVarInst(Address(l5, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec3, kStruct)[LoadVarInst(Address(l6, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec3, kStruct)[LoadVarInst(Address(l7, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(2))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iIIR1, kStruct)[LoadVarInst(Address(l8, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65536), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst("int", iVec0[2], kStruct)
	DeclareVarInst("int", iRec0[2], kStruct)
	========== Init method ==========
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
			StoreVarInst(Address(iRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0, kStruct)[Int32(0)], Int32(1))
			StoreVarInst(Address(iRec0, kStruct)[Int32(0)], BinopInst("%", BinopInst("+", LoadVarInst(Address(iVec0, kStruct)[Int32(1)]), LoadVarInst(Address(iRec0, kStruct)[Int32(1)])), Int32(65536)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", LoadVarInst(Address(iRec0, kStruct)[Int32(0)])))))
			StoreVarInst(Address(iVec0, kStruct)[Int32(1)], LoadVarInst(Address(iVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(iRec0, kStruct)[Int32(1)], LoadVarInst(Address(iRec0, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec1, kStruct)[Int32(0)], Int32(1))
			StoreVarInst(Address(iRec2, kStruct)[Int32(0)], BinopInst("%", BinopInst("+", LoadVarInst(Address(iVec1, kStruct)[Int32(1)]), LoadVarInst(Address(iRec2, kStruct)[Int32(1)])), LoadVarInst(Address(iConst2, kStruct))))
			DeclareVarInst("int", iTemp0, kStack, BinopInst("<=", LoadVarInst(Address(iRec2, kStruct)[Int32(0)]), LoadVarInst(Address(iRec2, kStruct)[Int32(1)])))
			StoreVarInst(Address(iVec2, kStruct)[Int32(0)], LoadVarInst(Address(iTemp0, kStack)))
			DeclareVarInst("int", iTemp1, kStack, BinopInst("+", BinopInst(">", LoadVarInst(Address(iTemp0, kStack)), LoadVarInst(Address(iVec2, kStruct)[Int32(1)])), LoadVarInst(Address(iIIR0, kStruct)[Int32(1)])))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(0)], LoadVarInst(Address(iTemp1, kStack)))
			StoreVarInst(Address(iRec3, kStruct)[Int32(0)], BinopInst("%", BinopInst("+", LoadVarInst(Address(iVec1, kStruct)[Int32(1)]), LoadVarInst(Address(iRec3, kStruct)[Int32(1)])), LoadVarInst(Address(iConst3, kStruct))))
			DeclareVarInst("int", iTemp2, kStack, BinopInst("<=", LoadVarInst(Address(iRec3, kStruct)[Int32(0)]), LoadVarInst(Address(iRec3, kStruct)[Int32(1)])))
			StoreVarInst(Address(iVec3, kStruct)[Int32(0)], LoadVarInst(Address(iTemp2, kStack)))
			DeclareVarInst("int", iTemp3, kStack, BinopInst("+", BinopInst(">", LoadVarInst(Address(iTemp2, kStack)), LoadVarInst(Address(iVec3, kStruct)[Int32(1)])), LoadVarInst(Address(iIIR1, kStruct)[Int32(1)])))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(0)], LoadVarInst(Address(iTemp3, kStack)))
			DeclareVarInst("float", fTemp4, kStack, BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), BinopInst("*", LoadVarInst(Address(fConst1, kStruct)), CastInst("float", BinopInst("*", Int32(200), BinopInst("+", BinopInst("+", Int32(1), BinopInst("%", LoadVarInst(Address(iTemp1, kStack)), Int32(2))), BinopInst("*", Int32(2), BinopInst("%", LoadVarInst(Address(iTemp3, kStack)), Int32(2)))))))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], BinopInst("-", LoadVarInst(Address(fTemp4, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp4, kStack)))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", CastInst("int", BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))), Int32(65535)))])))
			StoreVarInst(Address(iVec1, kStruct)[Int32(1)], LoadVarInst(Address(iVec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(iRec2, kStruct)[Int32(1)], LoadVarInst(Address(iRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec2, kStruct)[Int32(1)], LoadVarInst(Address(iVec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(iIIR0, kStruct)[Int32(1)], LoadVarInst(Address(iIIR0, kStruct)[Int32(0)]))
			StoreVarInst(Address(iRec3, kStruct)[Int32(1)], LoadVarInst(Address(iRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(iVec3, kStruct)[Int32(1)], LoadVarInst(Address(iVec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(iIIR1, kStruct)[Int32(1)], LoadVarInst(Address(iIIR1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 12 bytes
Heap size int* = 56 bytes
Heap size real = 16 bytes
Total heap size = 100 bytes
Stack size in compute = 8 bytes

======= Variable access in Control ==========

Field = iVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = iVec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iConst2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iIIR0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iConst3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iVec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iIIR1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = iVec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iConst2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iRec2 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = iVec2 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = iIIR0 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = iConst3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = iRec3 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = iVec3 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = iIIR1 size = 2 size_bytes = 8 read = 2 write = 2 ratio = 2
Field = fRec1 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5

========== COMPILER STATISTICS ==========

--- Phase 1: Parsing ---
  (not instrumented)

--- Phase 2: Box Evaluation ---
  eval() calls:            299
  eval() cache hits:       46 (15.3846%)
  eval() cache misses:     253
  Loop detector calls:     253
  Stack detector calls:    253

--- Phase 3: Propagation ---
  propagate() calls:       193
  propagate() cache hits:  23 (11.9171%)
  propagate() cache misses:170

--- Box Type Computation ---
  getBoxType() calls:      365
  getBoxType() cache hits: 242 (66.3014%)
  getBoxType() computed:   123

--- Environment Operations ---
  Environment lookups:     0
  Env layers pushed:       5

--- Pattern Matching ---
  build automaton calls:        0
  build total time (ms):        0
  apply calls:                  0
  apply total time (ms):        0

--- Tree Operations ---
  Trees created:           3146
  Trees reused (hash):     4775 (60.2828% reuse rate)
  Property set ops:        1144
  Property get ops:        3616

--- Iteration Constructs ---
  par() iterations:        0
  seq() iterations:        0
  sum() iterations:        0
  prod() iterations:       0

==========================================
