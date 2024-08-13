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

DeclareStructTypeInst(StructType<"mydspSIG0",("int[2]", iRec2)>)

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
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 7 Store = 4 Binop = 5 [ { Int(+) = 3 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { sinf = 1 } ] Numbers = 10 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iRec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(iRec2, kStruct)[Int32(1)]), Int32(1)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iRec2, kStruct)[Int32(0)]), Int32(-1))))))
		StoreVarInst(Address(iRec2, kStruct)[Int32(1)], LoadVarInst(Address(iRec2, kStruct)[Int32(0)]))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Stereo Audio Tester")
	AddMetaDeclareInst(fHslider3, "1", "")
	AddMetaDeclareInst(fHslider3, "scale", "log")
	AddMetaDeclareInst(fHslider3, "unit", "Hz")
	AddHorizontalSlider("freq", fHslider3, 3043.0f, 4e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fHslider0, "2", "")
	AddMetaDeclareInst(fHslider0, "unit", "dB")
	AddHorizontalSlider("volume", fHslider0, -31.9968f, -96.0f, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider2, "3", "")
	AddMetaDeclareInst(fHslider2, "style", "menu{'white noise':0;'pink noise':1;'sine':2}")
	AddHorizontalSlider("signal", fHslider2, 0.0f, 0.0f, 2.0f, 1.0f)
	AddMetaDeclareInst(fHslider1, "4", "")
	AddMetaDeclareInst(fHslider1, "style", "radio{'none':0;'left':1;'right':2;'both':3}")
	AddHorizontalSlider("channel", fHslider1, 1.0f, 0.0f, 3.0f, 1.0f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareVarInst("float", ftbl0mydspSIG0[65537], kStaticStruct)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("float[2]", fRec0)("FAUSTFLOAT", fHslider1)("float[2]", fRec1)("FAUSTFLOAT", fHslider2)("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fHslider3)("float[2]", fRec3)("int[2]", iRec5)("float[3]", fVec0)("float[3]", fRec4)("float[2]", fRec6)>)

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

======= Static Init begin ==========

BlockInst 
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65537), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(-31.9968f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(3043.0f)))
EndBlockInst

======= ResetUI end ==========

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
			StoreVarInst(Address(iRec5, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(3))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 11 Store = 0 Binop = 9 [ { Int(!=) = 2 } { Int(&) = 2 } { Int(==) = 2 } { Real(*) = 3 } ] Mathop = 1 [ { powf = 1 } ] Numbers = 11 Declare = 10 Cast = 8 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))))
	DeclareVarInst("int", iSlow1, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", BinopInst("!=", BinopInst("&", LoadVarInst(Address(iSlow1, kStack)), Int32(1)), Int32(0))))
	DeclareVarInst("int", iSlow3, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("int", iSlow4, kStack, BinopInst("==", LoadVarInst(Address(iSlow3, kStack)), Int32(0)))
	DeclareVarInst("int", iSlow5, kStack, BinopInst("==", LoadVarInst(Address(iSlow3, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", BinopInst("!=", BinopInst("&", LoadVarInst(Address(iSlow1, kStack)), Int32(2)), Int32(0))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 60 Store = 19 Binop = 35 [ { Int(*) = 1 } { Int(+) = 3 } { Int(<) = 1 } { Real(*) = 13 } { Real(+) = 11 } { Real(-) = 4 } { Real(<) = 2 } ] Mathop = 10 [ { floorf = 2 } { max_f = 2 } { max_i = 2 } { min_f = 2 } { min_i = 2 } ] Numbers = 67 Declare = 6 Cast = 4 Select = 4 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], Select2Inst(BinopInst("<", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow2, kStack))) FunCallInst("min_f", BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(0.00022675737f)), LoadVarInst(Address(fSlow2, kStack))) FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(-0.00022675737f)), LoadVarInst(Address(fSlow2, kStack)))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("-", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))))
		DeclareVarInst("float", fTemp0, kStack, BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
		DeclareVarInst("int", iTemp1, kStack, CastInst("int", LoadVarInst(Address(fTemp0, kStack))))
		DeclareVarInst("float", fTemp2, kStack, LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp1, kStack)), Int32(65536)))]))
		StoreVarInst(Address(iRec5, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec5, kStruct)[Int32(1)])), Int32(12345)))
		DeclareVarInst("float", fTemp3, kStack, CastInst("float", LoadVarInst(Address(iRec5, kStruct)[Int32(0)])))
		StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(6.906783e-12f), LoadVarInst(Address(fVec0, kStruct)[Int32(2)])), BinopInst("+", BinopInst("*", Float(1.8011608f), LoadVarInst(Address(fRec4, kStruct)[Int32(1)])), BinopInst("*", Float(2.308528e-11f), LoadVarInst(Address(fTemp3, kStack))))), BinopInst("+", BinopInst("*", Float(0.8025774f), LoadVarInst(Address(fRec4, kStruct)[Int32(2)])), BinopInst("*", Float(2.936265e-11f), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])))))
		DeclareVarInst("float", fTemp4, kStack, Select2Inst(LoadVarInst(Address(iSlow4, kStack)) BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fTemp3, kStack))) Select2Inst(LoadVarInst(Address(iSlow5, kStack)) LoadVarInst(Address(fRec4, kStruct)[Int32(0)]) BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp0, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp0, kStack)))), BinopInst("-", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp1, kStack)), Int32(1)), Int32(65536)))]), LoadVarInst(Address(fTemp2, kStack))))))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])), LoadVarInst(Address(fTemp4, kStack)))))
		StoreVarInst(Address(fRec6, kStruct)[Int32(0)], Select2Inst(BinopInst("<", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow7, kStack))) FunCallInst("min_f", BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), Float(0.00022675737f)), LoadVarInst(Address(fSlow7, kStack))) FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), Float(-0.00022675737f)), LoadVarInst(Address(fSlow7, kStack)))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])), LoadVarInst(Address(fTemp4, kStack)))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(iRec5, kStruct)[Int32(1)], LoadVarInst(Address(iRec5, kStruct)[Int32(0)]))
		StoreVarInst(Address(fVec0, kStruct)[Int32(2)], LoadVarInst(Address(fVec0, kStruct)[Int32(1)]))
		StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(2)], LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
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
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareVarInst("float", ftbl0mydspSIG0[65537], kStaticStruct)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("int", iRec5[2], kStruct)
	DeclareVarInst("float", fVec0[3], kStruct)
	DeclareVarInst("float", fRec4[3], kStruct)
	DeclareVarInst("float", fRec6[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(-31.9968f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(3043.0f)))
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
			StoreVarInst(Address(iRec5, kStruct)[LoadVarInst(Address(l4, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(3))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(3))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec6, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65537), LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst("int", iRec2[2], kStruct)
	========== Init method ==========
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iRec2, kStruct)[LoadVarInst(Address(l2, kLoop))], Int32(0))
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
			StoreVarInst(Address(iRec2, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(iRec2, kStruct)[Int32(1)]), Int32(1)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iRec2, kStruct)[Int32(0)]), Int32(-1))))))
			StoreVarInst(Address(iRec2, kStruct)[Int32(1)], LoadVarInst(Address(iRec2, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))))
	DeclareVarInst("int", iSlow1, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", BinopInst("!=", BinopInst("&", LoadVarInst(Address(iSlow1, kStack)), Int32(1)), Int32(0))))
	DeclareVarInst("int", iSlow3, kStack, CastInst("int", CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("int", iSlow4, kStack, BinopInst("==", LoadVarInst(Address(iSlow3, kStack)), Int32(0)))
	DeclareVarInst("int", iSlow5, kStack, BinopInst("==", LoadVarInst(Address(iSlow3, kStack)), Int32(1)))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", BinopInst("!=", BinopInst("&", LoadVarInst(Address(iSlow1, kStack)), Int32(2)), Int32(0))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow0, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fRec0, kStruct)[Int32(1)]))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], Select2Inst(BinopInst("<", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow2, kStack))) FunCallInst("min_f", BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(0.00022675737f)), LoadVarInst(Address(fSlow2, kStack))) FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fRec1, kStruct)[Int32(1)]), Float(-0.00022675737f)), LoadVarInst(Address(fSlow2, kStack)))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), BinopInst("-", LoadVarInst(Address(fRec3, kStruct)[Int32(1)]), FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))))))
			DeclareVarInst("float", fTemp0, kStack, BinopInst("*", Float(65536.0f), LoadVarInst(Address(fRec3, kStruct)[Int32(0)])))
			DeclareVarInst("int", iTemp1, kStack, CastInst("int", LoadVarInst(Address(fTemp0, kStack))))
			DeclareVarInst("float", fTemp2, kStack, LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp1, kStack)), Int32(65536)))]))
			StoreVarInst(Address(iRec5, kStruct)[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iRec5, kStruct)[Int32(1)])), Int32(12345)))
			DeclareVarInst("float", fTemp3, kStack, CastInst("float", LoadVarInst(Address(iRec5, kStruct)[Int32(0)])))
			StoreVarInst(Address(fVec0, kStruct)[Int32(0)], LoadVarInst(Address(fTemp3, kStack)))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], BinopInst("-", BinopInst("+", BinopInst("*", Float(6.906783e-12f), LoadVarInst(Address(fVec0, kStruct)[Int32(2)])), BinopInst("+", BinopInst("*", Float(1.8011608f), LoadVarInst(Address(fRec4, kStruct)[Int32(1)])), BinopInst("*", Float(2.308528e-11f), LoadVarInst(Address(fTemp3, kStack))))), BinopInst("+", BinopInst("*", Float(0.8025774f), LoadVarInst(Address(fRec4, kStruct)[Int32(2)])), BinopInst("*", Float(2.936265e-11f), LoadVarInst(Address(fVec0, kStruct)[Int32(1)])))))
			DeclareVarInst("float", fTemp4, kStack, Select2Inst(LoadVarInst(Address(iSlow4, kStack)) BinopInst("*", Float(4.656613e-10f), LoadVarInst(Address(fTemp3, kStack))) Select2Inst(LoadVarInst(Address(iSlow5, kStack)) LoadVarInst(Address(fRec4, kStruct)[Int32(0)]) BinopInst("+", LoadVarInst(Address(fTemp2, kStack)), BinopInst("*", BinopInst("-", LoadVarInst(Address(fTemp0, kStack)), FunCallInst("floorf", LoadVarInst(Address(fTemp0, kStack)))), BinopInst("-", LoadVarInst(Address(ftbl0mydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp1, kStack)), Int32(1)), Int32(65536)))]), LoadVarInst(Address(fTemp2, kStack))))))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), LoadVarInst(Address(fRec1, kStruct)[Int32(0)])), LoadVarInst(Address(fTemp4, kStack)))))
			StoreVarInst(Address(fRec6, kStruct)[Int32(0)], Select2Inst(BinopInst("<", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), LoadVarInst(Address(fSlow7, kStack))) FunCallInst("min_f", BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), Float(0.00022675737f)), LoadVarInst(Address(fSlow7, kStack))) FunCallInst("max_f", BinopInst("+", LoadVarInst(Address(fRec6, kStruct)[Int32(1)]), Float(-0.00022675737f)), LoadVarInst(Address(fSlow7, kStack)))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", BinopInst("*", LoadVarInst(Address(fRec0, kStruct)[Int32(0)]), LoadVarInst(Address(fRec6, kStruct)[Int32(0)])), LoadVarInst(Address(fTemp4, kStack)))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(iRec5, kStruct)[Int32(1)], LoadVarInst(Address(iRec5, kStruct)[Int32(0)]))
			StoreVarInst(Address(fVec0, kStruct)[Int32(2)], LoadVarInst(Address(fVec0, kStruct)[Int32(1)]))
			StoreVarInst(Address(fVec0, kStruct)[Int32(1)], LoadVarInst(Address(fVec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(2)], LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec6, kStruct)[Int32(1)], LoadVarInst(Address(fRec6, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 8 bytes
Heap size real = 76 bytes
Total heap size = 96 bytes
Stack size in compute = 48 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = iRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec0 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec4 size = 3 size_bytes = 12 read = 0 write = 0 ratio = 0
Field = fRec6 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 4 write = 2 ratio = 3
Field = iRec5 size = 2 size_bytes = 8 read = 3 write = 2 ratio = 2.5
Field = fVec0 size = 3 size_bytes = 12 read = 4 write = 3 ratio = 2.33333
Field = fRec4 size = 3 size_bytes = 12 read = 5 write = 3 ratio = 2.66667
Field = fRec6 size = 2 size_bytes = 8 read = 5 write = 2 ratio = 3.5
