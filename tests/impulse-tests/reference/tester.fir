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

DeclareStructTypeInst(StructType<"mydspSIG0",("int", IOTA1)("int[2]", iVec12SI)>)

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
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec12SI, kStruct)[LoadVarInst(Address(l6, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 10 Store = 4 Binop = 10 [ { Int(&) = 3 } { Int(+) = 4 } { Int(-) = 1 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 1 [ { sinf = 1 } ] Numbers = 10 Declare = 1 Cast = 1 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i1, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i1, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i1, kLoop), BinopInst("+", LoadVarInst(Address(i1, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec12SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
		StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))]), Int32(-1))))))
		StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
	EndBlockInst
EndForLoopInst

======= Compute DSP end ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Audio Tester")
	AddMetaDeclareInst(fHslider2, "1", "")
	AddMetaDeclareInst(fHslider2, "unit", "Hz")
	AddHorizontalSlider("freq", fHslider2, 1e+03f, 1e+01f, 2e+04f, 1.0f)
	AddMetaDeclareInst(fHslider1, "2", "")
	AddMetaDeclareInst(fHslider1, "unit", "dB")
	AddHorizontalSlider("volume", fHslider1, -24.9984f, -96.0f, 0.0f, 1.0f)
	AddMetaDeclareInst(fHslider0, "3", "")
	AddHorizontalSlider("destination", fHslider0, 0.0f, 0.0f, 8.0f, 1.0f)
	AddCheckButtonInst("pink noise"fCheckbox1)
	AddCheckButtonInst("white noise"fCheckbox0)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0SImydspSIG0[65537], kStaticStruct)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("int", IOTA0)("int[2]", iVec0SI)("float[4]", fVec2SI)("float[2]", fVec4SI)("float[4]", fVec5SI)("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("float[2]", fVec8SE)("FAUSTFLOAT", fHslider2)("int", fSampleRate)("float", fConst0KI)("float[2]", fVec10SE)("FAUSTFLOAT", fCheckbox0)("FAUSTFLOAT", fCheckbox1)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(8))
	EndBlockInst
EndDeclare

======= Static Init begin ==========

BlockInst 
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65537), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct|kReference|kMutable))))
EndBlockInst
BlockInst 
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
EndBlockInst

======= Static Init end ==========

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(-24.9984f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(Address(iVec0SI, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SI, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SI, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(4))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
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
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 22 Store = 0 Binop = 13 [ { Real(*) = 5 } { Real(==) = 8 } ] Mathop = 1 [ { powf = 1 } ] Numbers = 21 Declare = 21 Cast = 13 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(0.0f))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("*", Float(1e+01f), CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct)))))
	DeclareVarInst("float", fSlow6BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow7BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(2.0f))))
	DeclareVarInst("float", fSlow8BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(3.0f))))
	DeclareVarInst("float", fSlow9BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(4.0f))))
	DeclareVarInst("float", fSlow10BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(5.0f))))
	DeclareVarInst("float", fSlow11BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(6.0f))))
	DeclareVarInst("float", fSlow12BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(7.0f))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 78 Store = 16 Binop = 63 [ { Int(&) = 18 } { Int(*) = 1 } { Int(+) = 4 } { Int(-) = 7 } { Int(<) = 1 } { Real(*) = 19 } { Real(+) = 13 } ] Mathop = 6 [ { floorf = 2 } { max_i = 2 } { min_i = 2 } ] Numbers = 42 Declare = 8 Cast = 10 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
		DeclareVarInst("float", fTemp0SI, kStack, CastInst("float", LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		DeclareVarInst("float", fTemp1SI, kStack, LoadVarInst(Address(fTemp0SI, kStack)))
		StoreVarInst(Address(fVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp1SI, kStack)))
		StoreVarInst(Address(fVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(6.906783e-12f), LoadVarInst(Address(fVec2SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])), BinopInst("*", Float(1.8011608f), LoadVarInst(Address(fVec4SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), BinopInst("*", Float(2.308528e-11f), LoadVarInst(Address(fTemp0SI, kStack)))), BinopInst("*", Float(-0.8025774f), LoadVarInst(Address(fVec5SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", Float(-2.936265e-11f), LoadVarInst(Address(fVec2SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))))
		StoreVarInst(Address(fVec5SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
		DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack)))))))
		DeclareVarInst("float", fTemp3SE, kStack, BinopInst("*", Float(65536.0f), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
		DeclareVarInst("int", iTemp4SE, kStack, CastInst("int", LoadVarInst(Address(fTemp3SE, kStack))))
		DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp4SE, kStack)), Int32(65536)))]))
		DeclareVarInst("float", fTemp6SE, kStack, BinopInst("*", LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp5SE, kStack)), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp3SE, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp3SE, kStack))))), BinopInst("+", LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp4SE, kStack)), Int32(1)), Int32(65536)))]), MinusInst(LoadVarInst(Address(fTemp5SE, kStack)))))), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fTemp0SI, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow7BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
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
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "floorf", "float", dummy0)
	DeclareFunInst("int", "min_i", "int", dummy0, "int", dummy1)
	DeclareFunInst("int", "max_i", "int", dummy0, "int", dummy1)
	DeclareVarInst("float", ftbl0SImydspSIG0[65537], kStaticStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	// Recursion delay iVec0SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec0SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec2SI[4], kStruct)
	// Recursion delay fVec4SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec4SI[2], kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec5SI[4], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	// Recursion delay fVec8SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec8SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	// Recursion delay fVec10SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec10SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fCheckbox1, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0KI, kStruct), BinopInst("/", Float(1.0f), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct)))))))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(-24.9984f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(1e+03f)))
	StoreVarInst(Address(fCheckbox0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fCheckbox1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(2))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0SI, kStruct)[LoadVarInst(Address(l0, kLoop))], Int32(0))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(4))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SI, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(2))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SI, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(4))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SI, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
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
	========== Static init method ==========
	DeclareVarInst("mydspSIG0", sig0, kStack, FunCallInst("newmydspSIG0"))
	DropInst(MethodFunCallInst("instanceInitmydspSIG0", LoadVarInst(Address(sig0, kStack)), LoadVarInst(Address(sample_rate, kFunArgs))))
	DropInst(MethodFunCallInst("fillmydspSIG0", LoadVarInst(Address(sig0, kStack)), Int32(65537), LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct|kReference|kMutable))))
	DropInst(FunCallInst("deletemydspSIG0", LoadVarInst(Address(sig0, kStack))))
	========== Subcontainers ==========
	========== Declaration part ==========
	DeclareFunInst("float", "sinf", "float", dummy0)
	DeclareVarInst("int", IOTA1, kStruct)
	// Recursion delay iVec12SI is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("int", iVec12SI[2], kStruct)
	========== Init method ==========
	StoreVarInst(Address(IOTA1, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(2))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec12SI, kStruct)[LoadVarInst(Address(l6, kLoop))], Int32(0))
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
			StoreVarInst(Address(iVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(iVec12SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)), Int32(1))]), Int32(1)))
			StoreVarInst(Address(table, kFunArgs)[LoadVarInst(Address(i1, kLoop))], FunCallInst("sinf", BinopInst("*", Float(9.58738e-05f), CastInst("float", BinopInst("+", LoadVarInst(Address(iVec12SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA1, kStruct)), Int32(1))]), Int32(-1))))))
			StoreVarInst(Address(IOTA1, kStruct), BinopInst("+", LoadVarInst(Address(IOTA1, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fHslider0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(0.0f))))
	DeclareVarInst("float", fSlow2BE, kStack, BinopInst("*", Float(0.001f), FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fHslider1, kStruct)))))))
	DeclareVarInst("float", fSlow3BE, kStack, BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fHslider2, kStruct)))))
	DeclareVarInst("float", fSlow4BE, kStack, BinopInst("*", Float(4.656613e-10f), CastInst("float", LoadVarInst(Address(fCheckbox0, kStruct)))))
	DeclareVarInst("float", fSlow5BE, kStack, BinopInst("*", Float(1e+01f), CastInst("float", LoadVarInst(Address(fCheckbox1, kStruct)))))
	DeclareVarInst("float", fSlow6BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(1.0f))))
	DeclareVarInst("float", fSlow7BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(2.0f))))
	DeclareVarInst("float", fSlow8BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(3.0f))))
	DeclareVarInst("float", fSlow9BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(4.0f))))
	DeclareVarInst("float", fSlow10BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(5.0f))))
	DeclareVarInst("float", fSlow11BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(6.0f))))
	DeclareVarInst("float", fSlow12BE, kStack, CastInst("float", BinopInst("==", LoadVarInst(Address(fSlow0BE, kStack)), Float(7.0f))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))])), Int32(12345)))
			DeclareVarInst("float", fTemp0SI, kStack, CastInst("float", LoadVarInst(Address(iVec0SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			DeclareVarInst("float", fTemp1SI, kStack, LoadVarInst(Address(fTemp0SI, kStack)))
			StoreVarInst(Address(fVec2SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fTemp1SI, kStack)))
			StoreVarInst(Address(fVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(6.906783e-12f), LoadVarInst(Address(fVec2SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))])), BinopInst("*", Float(1.8011608f), LoadVarInst(Address(fVec4SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))), BinopInst("*", Float(2.308528e-11f), LoadVarInst(Address(fTemp0SI, kStack)))), BinopInst("*", Float(-0.8025774f), LoadVarInst(Address(fVec5SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(2)), Int32(3))]))), BinopInst("*", Float(-2.936265e-11f), LoadVarInst(Address(fVec2SI, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(3))]))))
			StoreVarInst(Address(fVec5SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(3))], LoadVarInst(Address(fVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", LoadVarInst(Address(fSlow2BE, kStack)), BinopInst("*", Float(0.999f), LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))))
			DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], BinopInst("+", BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), MinusInst(FunCallInst("floorf", BinopInst("+", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack)))))))
			DeclareVarInst("float", fTemp3SE, kStack, BinopInst("*", Float(65536.0f), LoadVarInst(Address(fVec10SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))
			DeclareVarInst("int", iTemp4SE, kStack, CastInst("int", LoadVarInst(Address(fTemp3SE, kStack))))
			DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", LoadVarInst(Address(iTemp4SE, kStack)), Int32(65536)))]))
			DeclareVarInst("float", fTemp6SE, kStack, BinopInst("*", LoadVarInst(Address(fVec8SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]), BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(Address(fTemp5SE, kStack)), BinopInst("*", BinopInst("+", LoadVarInst(Address(fTemp3SE, kStack)), MinusInst(FunCallInst("floorf", LoadVarInst(Address(fTemp3SE, kStack))))), BinopInst("+", LoadVarInst(Address(ftbl0SImydspSIG0, kStaticStruct)[FunCallInst("max_i", Int32(0), FunCallInst("min_i", BinopInst("+", LoadVarInst(Address(iTemp4SE, kStack)), Int32(1)), Int32(65536)))]), MinusInst(LoadVarInst(Address(fTemp5SE, kStack)))))), BinopInst("*", LoadVarInst(Address(fSlow4BE, kStack)), LoadVarInst(Address(fTemp0SI, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow5BE, kStack)), LoadVarInst(Address(fVec4SI, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))])))))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow7BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 8 bytes
Heap size real = 80 bytes
Total heap size = 108 bytes
Stack size in compute = 116 bytes

======= Variable access in Control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec4SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = iVec0SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec2SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fVec4SI size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVec5SI size = 4 size_bytes = 16 read = 0 write = 0 ratio = 0
Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec8SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec10SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fCheckbox0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fCheckbox1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1

======= Variable access in compute DSP ==========

Field = IOTA0 size = 1 size_bytes = 4 read = 19 write = 1 ratio = 20
Field = iVec0SI size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVec2SI size = 4 size_bytes = 16 read = 2 write = 1 ratio = 0.75
Field = fVec4SI size = 2 size_bytes = 8 read = 3 write = 1 ratio = 2
Field = fVec5SI size = 4 size_bytes = 16 read = 1 write = 1 ratio = 0.5
Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec8SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec10SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fCheckbox0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fCheckbox1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
