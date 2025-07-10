======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("norm1")
	AddHorizontalSlider("1.1_x", fHslider0, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("1.2_x", fHslider2, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("1.2_y", fHslider1, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("1.3_x", fHslider3, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("1.4_x", fHslider4, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("1.5_y", fHslider5, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("1.6_x", fHslider6, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.1_x", fHslider7, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.1_y", fHslider8, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.2_x", fHslider9, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.2_y", fHslider10, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.3_x", fHslider11, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.3_y", fHslider12, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.3_z", fHslider13, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.4_x", fHslider15, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.4_y", fHslider16, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.4_z", fHslider14, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.5_x", fHslider18, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("2.5_y", fHslider17, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("3.1_x", fHslider19, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("3.2_x", fHslider20, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("3.3_x", fHslider21, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("3.6_z", fHslider22, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("3.7_y", fHslider23, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.1_x", fHslider24, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.1_y", fHslider25, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.2_x", fHslider26, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.2_y", fHslider28, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.2_z", fHslider27, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.3_x", fHslider29, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.3_y", fHslider30, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.3_z", fHslider31, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.4_y", fHslider32, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.5_x", fHslider33, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("4.5_y", fHslider34, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("5.1_x", fHslider35, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("5.2_x", fHslider36, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("5.3_x", fHslider37, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("5.3_y", fHslider38, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("5.4_x", fHslider39, 1.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("5.5_x", fHslider40, 1.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.1_x", fHslider41, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.1_y", fHslider42, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.1_z", fHslider43, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.2_x", fHslider44, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.2_y", fHslider45, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.3_x", fHslider46, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.3_y", fHslider47, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.4_x", fHslider48, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.5_a", fHslider51, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.5_b", fHslider52, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.5_x", fHslider49, 0.0f, -1e+01f, 1e+01f, 0.1f)
	AddHorizontalSlider("6.5_y", fHslider50, 0.0f, -1e+01f, 1e+01f, 0.1f)
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower5_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fHslider0)("FAUSTFLOAT", fHslider1)("FAUSTFLOAT", fHslider2)("FAUSTFLOAT", fHslider3)("FAUSTFLOAT", fHslider4)("FAUSTFLOAT", fHslider5)("FAUSTFLOAT", fHslider6)("FAUSTFLOAT", fHslider7)("FAUSTFLOAT", fHslider8)("FAUSTFLOAT", fHslider9)("FAUSTFLOAT", fHslider10)("FAUSTFLOAT", fHslider11)("FAUSTFLOAT", fHslider12)("FAUSTFLOAT", fHslider13)("FAUSTFLOAT", fHslider14)("FAUSTFLOAT", fHslider15)("FAUSTFLOAT", fHslider16)("FAUSTFLOAT", fHslider17)("FAUSTFLOAT", fHslider18)("FAUSTFLOAT", fHslider19)("FAUSTFLOAT", fHslider20)("FAUSTFLOAT", fHslider21)("FAUSTFLOAT", fHslider22)("FAUSTFLOAT", fHslider23)("FAUSTFLOAT", fHslider24)("FAUSTFLOAT", fHslider25)("FAUSTFLOAT", fHslider26)("FAUSTFLOAT", fHslider27)("FAUSTFLOAT", fHslider28)("FAUSTFLOAT", fHslider29)("FAUSTFLOAT", fHslider30)("FAUSTFLOAT", fHslider31)("FAUSTFLOAT", fHslider32)("FAUSTFLOAT", fHslider33)("FAUSTFLOAT", fHslider34)("FAUSTFLOAT", fHslider35)("FAUSTFLOAT", fHslider36)("FAUSTFLOAT", fHslider37)("FAUSTFLOAT", fHslider38)("FAUSTFLOAT", fHslider39)("FAUSTFLOAT", fHslider40)("FAUSTFLOAT", fHslider41)("FAUSTFLOAT", fHslider42)("FAUSTFLOAT", fHslider43)("FAUSTFLOAT", fHslider44)("FAUSTFLOAT", fHslider45)("FAUSTFLOAT", fHslider46)("FAUSTFLOAT", fHslider47)("FAUSTFLOAT", fHslider48)("FAUSTFLOAT", fHslider49)("FAUSTFLOAT", fHslider50)("FAUSTFLOAT", fHslider51)("FAUSTFLOAT", fHslider52)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(0))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(35))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider10, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider11, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider12, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider13, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider14, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider15, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider16, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider17, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider18, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider19, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider20, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider21, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider22, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider23, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider24, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider25, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider26, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider27, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider28, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider29, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider30, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider31, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider32, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider33, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider34, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider35, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider36, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider37, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider38, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider39, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider40, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider41, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider42, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider43, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider44, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider45, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider46, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider47, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider48, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider49, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider50, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider51, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider52, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
EndBlockInst

======= ResetUI end ==========

======= Compute control begin ==========

Instructions complexity : Load = 97 Store = 0 Binop = 38 [ { Real(*) = 19 } { Real(+) = 16 } { Real(-) = 1 } { Real(/) = 2 } ] Mathop = 8 [ { mydsp_faustpower2_f = 5 } { mydsp_faustpower3_f = 2 } { mydsp_faustpower5_f = 1 } ] Numbers = 46 Declare = 70 Cast = 52 Select = 0 Loop = 0

BlockInst 
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
	DeclareVarInst("FAUSTFLOAT*", output31, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(31)]))
	DeclareVarInst("FAUSTFLOAT*", output32, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(32)]))
	DeclareVarInst("FAUSTFLOAT*", output33, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(33)]))
	DeclareVarInst("FAUSTFLOAT*", output34, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(34)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider1, kStruct))), BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(3.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	DeclareVarInst("float", fSlow3, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(3.7f), CastInst("float", LoadVarInst(Address(fHslider6, kStruct)))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider7, kStruct))), CastInst("float", LoadVarInst(Address(fHslider8, kStruct)))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", CastInst("float", LoadVarInst(Address(fHslider9, kStruct))), CastInst("float", LoadVarInst(Address(fHslider10, kStruct)))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider11, kStruct))), CastInst("float", LoadVarInst(Address(fHslider12, kStruct)))), CastInst("float", LoadVarInst(Address(fHslider13, kStruct)))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider14, kStruct))), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider15, kStruct))), CastInst("float", LoadVarInst(Address(fHslider16, kStruct))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(2.0f), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider17, kStruct))), CastInst("float", LoadVarInst(Address(fHslider18, kStruct))))))
	DeclareVarInst("float", fSlow10, kStack, CastInst("float", LoadVarInst(Address(fHslider19, kStruct))))
	DeclareVarInst("float", fSlow11, kStack, CastInst("float", LoadVarInst(Address(fHslider20, kStruct))))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", LoadVarInst(Address(fHslider21, kStruct))))
	DeclareVarInst("float", fSlow13, kStack, CastInst("float", LoadVarInst(Address(fHslider22, kStruct))))
	DeclareVarInst("float", fSlow14, kStack, CastInst("float", LoadVarInst(Address(fHslider23, kStruct))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", Float(2.0f), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider24, kStruct))), CastInst("float", LoadVarInst(Address(fHslider25, kStruct))))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("-", BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider26, kStruct))), CastInst("float", LoadVarInst(Address(fHslider27, kStruct)))), CastInst("float", LoadVarInst(Address(fHslider28, kStruct)))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", BinopInst("*", FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider29, kStruct)))), CastInst("float", LoadVarInst(Address(fHslider30, kStruct)))), CastInst("float", LoadVarInst(Address(fHslider31, kStruct)))))
	DeclareVarInst("float", fSlow18, kStack, CastInst("float", LoadVarInst(Address(fHslider32, kStruct))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("*", Float(0.5f), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider33, kStruct))), CastInst("float", LoadVarInst(Address(fHslider34, kStruct))))))
	DeclareVarInst("float", fSlow20, kStack, FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider35, kStruct)))))
	DeclareVarInst("float", fSlow21, kStack, FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider36, kStruct)))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("*", FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider37, kStruct)))), FunCallInst("mydsp_faustpower3_f", CastInst("float", LoadVarInst(Address(fHslider38, kStruct))))))
	DeclareVarInst("float", fSlow23, kStack, CastInst("float", LoadVarInst(Address(fHslider39, kStruct))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("/", FunCallInst("mydsp_faustpower5_f", LoadVarInst(Address(fSlow23, kStack))), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fSlow23, kStack)))))
	DeclareVarInst("float", fSlow25, kStack, FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider40, kStruct)))))
	DeclareVarInst("float", fSlow26, kStack, BinopInst("/", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fSlow25, kStack))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("*", CastInst("float", LoadVarInst(Address(fHslider41, kStruct))), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider42, kStruct))), CastInst("float", LoadVarInst(Address(fHslider43, kStruct))))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("+", BinopInst("*", Float(4.0f), CastInst("float", LoadVarInst(Address(fHslider44, kStruct)))), BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider45, kStruct))))))
	DeclareVarInst("float", fSlow29, kStack, CastInst("float", LoadVarInst(Address(fHslider46, kStruct))))
	DeclareVarInst("float", fSlow30, kStack, CastInst("float", LoadVarInst(Address(fHslider47, kStruct))))
	DeclareVarInst("float", fSlow31, kStack, BinopInst("*", BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fSlow30, kStack))), BinopInst("+", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fSlow30, kStack)))))
	DeclareVarInst("float", fSlow32, kStack, CastInst("float", LoadVarInst(Address(fHslider48, kStruct))))
	DeclareVarInst("float", fSlow33, kStack, BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), BinopInst("+", BinopInst("*", Float(3.0f), LoadVarInst(Address(fSlow32, kStack))), Float(-6.0f))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("*", BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider49, kStruct))), CastInst("float", LoadVarInst(Address(fHslider50, kStruct)))), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider51, kStruct))), CastInst("float", LoadVarInst(Address(fHslider52, kStruct))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 71 Store = 36 Binop = 3 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 1 } ] Mathop = 0 Numbers = 5 Declare = 1 Cast = 36 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow0, kStack))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow1, kStack))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow2, kStack))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", MinusInst(BinopInst("*", Float(3.0f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow3, kStack))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow4, kStack))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow5, kStack))))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow5, kStack))))
		StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow6, kStack))))
		StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow6, kStack))))
		StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow7, kStack))))
		StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow8, kStack))))
		StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow9, kStack))))
		StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow10, kStack))))
		StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow11, kStack))))
		StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow12, kStack))))
		StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(0.0f)))
		StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(0)))
		StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow13, kStack))))
		StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow14, kStack))))
		StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow15, kStack))))
		StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow16, kStack))))
		StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow17, kStack))))
		StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow18, kStack))))
		StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow19, kStack))))
		StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow20, kStack))))
		StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow21, kStack))))
		StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow22, kStack))))
		StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow24, kStack))))
		StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow26, kStack))))
		StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow27, kStack))))
		StoreVarInst(Address(output31, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow28, kStack))))
		StoreVarInst(Address(output32, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow31, kStack))))
		StoreVarInst(Address(output33, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow33, kStack))))
		StoreVarInst(Address(output34, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow34, kStack))))
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
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower3_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareFunInst("float", "mydsp_faustpower5_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", BinopInst("*", BinopInst("*", BinopInst("*", LoadVarInst(Address(value, kFunArgs)), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))), LoadVarInst(Address(value, kFunArgs))))
		EndBlockInst
	EndDeclare
	DeclareVarInst("FAUSTFLOAT", fHslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider9, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider10, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider11, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider12, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider13, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider14, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider15, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider16, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider17, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider18, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider19, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider20, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider21, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider22, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider23, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider24, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider25, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider26, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider27, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider28, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider29, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider30, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider31, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider32, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider33, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider34, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider35, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider36, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider37, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider38, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider39, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider40, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider41, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider42, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider43, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider44, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider45, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider46, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider47, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider48, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider49, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider50, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider51, kStruct)
	DeclareVarInst("FAUSTFLOAT", fHslider52, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fHslider0, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider2, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider10, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider11, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider12, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider13, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider14, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider15, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider16, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider17, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider18, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider19, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider20, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider21, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider22, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider23, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider24, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider25, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider26, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider27, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider28, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider29, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider30, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider31, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider32, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider33, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider34, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider35, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider36, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider37, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider38, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider39, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider40, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fHslider41, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider42, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider43, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider44, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider45, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider46, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider47, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider48, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider49, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider50, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider51, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fHslider52, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	========== Static init method ==========
	========== Subcontainers ==========
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
	DeclareVarInst("FAUSTFLOAT*", output31, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(31)]))
	DeclareVarInst("FAUSTFLOAT*", output32, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(32)]))
	DeclareVarInst("FAUSTFLOAT*", output33, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(33)]))
	DeclareVarInst("FAUSTFLOAT*", output34, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(34)]))
	DeclareVarInst("float", fSlow0, kStack, BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider0, kStruct)))))
	DeclareVarInst("float", fSlow1, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider1, kStruct))), BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider2, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, BinopInst("*", Float(3.0f), CastInst("float", LoadVarInst(Address(fHslider3, kStruct)))))
	DeclareVarInst("float", fSlow3, kStack, CastInst("float", LoadVarInst(Address(fHslider5, kStruct))))
	DeclareVarInst("float", fSlow4, kStack, BinopInst("*", Float(3.7f), CastInst("float", LoadVarInst(Address(fHslider6, kStruct)))))
	DeclareVarInst("float", fSlow5, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider7, kStruct))), CastInst("float", LoadVarInst(Address(fHslider8, kStruct)))))
	DeclareVarInst("float", fSlow6, kStack, BinopInst("*", CastInst("float", LoadVarInst(Address(fHslider9, kStruct))), CastInst("float", LoadVarInst(Address(fHslider10, kStruct)))))
	DeclareVarInst("float", fSlow7, kStack, BinopInst("+", BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider11, kStruct))), CastInst("float", LoadVarInst(Address(fHslider12, kStruct)))), CastInst("float", LoadVarInst(Address(fHslider13, kStruct)))))
	DeclareVarInst("float", fSlow8, kStack, BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider14, kStruct))), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider15, kStruct))), CastInst("float", LoadVarInst(Address(fHslider16, kStruct))))))
	DeclareVarInst("float", fSlow9, kStack, BinopInst("*", Float(2.0f), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider17, kStruct))), CastInst("float", LoadVarInst(Address(fHslider18, kStruct))))))
	DeclareVarInst("float", fSlow10, kStack, CastInst("float", LoadVarInst(Address(fHslider19, kStruct))))
	DeclareVarInst("float", fSlow11, kStack, CastInst("float", LoadVarInst(Address(fHslider20, kStruct))))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", LoadVarInst(Address(fHslider21, kStruct))))
	DeclareVarInst("float", fSlow13, kStack, CastInst("float", LoadVarInst(Address(fHslider22, kStruct))))
	DeclareVarInst("float", fSlow14, kStack, CastInst("float", LoadVarInst(Address(fHslider23, kStruct))))
	DeclareVarInst("float", fSlow15, kStack, BinopInst("*", Float(2.0f), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider24, kStruct))), CastInst("float", LoadVarInst(Address(fHslider25, kStruct))))))
	DeclareVarInst("float", fSlow16, kStack, BinopInst("-", BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider26, kStruct))), CastInst("float", LoadVarInst(Address(fHslider27, kStruct)))), CastInst("float", LoadVarInst(Address(fHslider28, kStruct)))))
	DeclareVarInst("float", fSlow17, kStack, BinopInst("*", BinopInst("*", FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider29, kStruct)))), CastInst("float", LoadVarInst(Address(fHslider30, kStruct)))), CastInst("float", LoadVarInst(Address(fHslider31, kStruct)))))
	DeclareVarInst("float", fSlow18, kStack, CastInst("float", LoadVarInst(Address(fHslider32, kStruct))))
	DeclareVarInst("float", fSlow19, kStack, BinopInst("*", Float(0.5f), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider33, kStruct))), CastInst("float", LoadVarInst(Address(fHslider34, kStruct))))))
	DeclareVarInst("float", fSlow20, kStack, FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider35, kStruct)))))
	DeclareVarInst("float", fSlow21, kStack, FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider36, kStruct)))))
	DeclareVarInst("float", fSlow22, kStack, BinopInst("*", FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider37, kStruct)))), FunCallInst("mydsp_faustpower3_f", CastInst("float", LoadVarInst(Address(fHslider38, kStruct))))))
	DeclareVarInst("float", fSlow23, kStack, CastInst("float", LoadVarInst(Address(fHslider39, kStruct))))
	DeclareVarInst("float", fSlow24, kStack, BinopInst("/", FunCallInst("mydsp_faustpower5_f", LoadVarInst(Address(fSlow23, kStack))), FunCallInst("mydsp_faustpower3_f", LoadVarInst(Address(fSlow23, kStack)))))
	DeclareVarInst("float", fSlow25, kStack, FunCallInst("mydsp_faustpower2_f", CastInst("float", LoadVarInst(Address(fHslider40, kStruct)))))
	DeclareVarInst("float", fSlow26, kStack, BinopInst("/", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fSlow25, kStack))))
	DeclareVarInst("float", fSlow27, kStack, BinopInst("*", CastInst("float", LoadVarInst(Address(fHslider41, kStruct))), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider42, kStruct))), CastInst("float", LoadVarInst(Address(fHslider43, kStruct))))))
	DeclareVarInst("float", fSlow28, kStack, BinopInst("+", BinopInst("*", Float(4.0f), CastInst("float", LoadVarInst(Address(fHslider44, kStruct)))), BinopInst("*", Float(2.0f), CastInst("float", LoadVarInst(Address(fHslider45, kStruct))))))
	DeclareVarInst("float", fSlow29, kStack, CastInst("float", LoadVarInst(Address(fHslider46, kStruct))))
	DeclareVarInst("float", fSlow30, kStack, CastInst("float", LoadVarInst(Address(fHslider47, kStruct))))
	DeclareVarInst("float", fSlow31, kStack, BinopInst("*", BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fSlow30, kStack))), BinopInst("+", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fSlow30, kStack)))))
	DeclareVarInst("float", fSlow32, kStack, CastInst("float", LoadVarInst(Address(fHslider48, kStruct))))
	DeclareVarInst("float", fSlow33, kStack, BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), BinopInst("+", BinopInst("*", Float(3.0f), LoadVarInst(Address(fSlow32, kStack))), Float(-6.0f))))
	DeclareVarInst("float", fSlow34, kStack, BinopInst("*", BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider49, kStruct))), CastInst("float", LoadVarInst(Address(fHslider50, kStruct)))), BinopInst("+", CastInst("float", LoadVarInst(Address(fHslider51, kStruct))), CastInst("float", LoadVarInst(Address(fHslider52, kStruct))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow0, kStack))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow1, kStack))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow2, kStack))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", MinusInst(BinopInst("*", Float(3.0f), CastInst("float", LoadVarInst(Address(fHslider4, kStruct)))))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow3, kStack))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow4, kStack))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow5, kStack))))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow5, kStack))))
			StoreVarInst(Address(output8, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow6, kStack))))
			StoreVarInst(Address(output9, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow6, kStack))))
			StoreVarInst(Address(output10, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow7, kStack))))
			StoreVarInst(Address(output11, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow8, kStack))))
			StoreVarInst(Address(output12, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow9, kStack))))
			StoreVarInst(Address(output13, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow10, kStack))))
			StoreVarInst(Address(output14, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow11, kStack))))
			StoreVarInst(Address(output15, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow12, kStack))))
			StoreVarInst(Address(output16, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Float(0.0f)))
			StoreVarInst(Address(output17, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", Int32(0)))
			StoreVarInst(Address(output18, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow13, kStack))))
			StoreVarInst(Address(output19, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow14, kStack))))
			StoreVarInst(Address(output20, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow15, kStack))))
			StoreVarInst(Address(output21, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow16, kStack))))
			StoreVarInst(Address(output22, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow17, kStack))))
			StoreVarInst(Address(output23, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow18, kStack))))
			StoreVarInst(Address(output24, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow19, kStack))))
			StoreVarInst(Address(output25, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow20, kStack))))
			StoreVarInst(Address(output26, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow21, kStack))))
			StoreVarInst(Address(output27, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow22, kStack))))
			StoreVarInst(Address(output28, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow24, kStack))))
			StoreVarInst(Address(output29, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow26, kStack))))
			StoreVarInst(Address(output30, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow27, kStack))))
			StoreVarInst(Address(output31, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow28, kStack))))
			StoreVarInst(Address(output32, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow31, kStack))))
			StoreVarInst(Address(output33, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow33, kStack))))
			StoreVarInst(Address(output34, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", LoadVarInst(Address(fSlow34, kStack))))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 212 bytes
Total heap size = 216 bytes
Stack size in compute = 420 bytes

======= Variable access in Control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider11 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider14 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider15 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider16 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider18 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider19 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider20 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider21 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider22 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider23 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider24 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider25 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider26 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider27 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider28 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider29 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider30 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider31 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider32 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider33 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider34 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider35 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider36 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider37 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider38 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider39 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider40 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider41 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider42 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider43 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider44 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider45 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider46 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider47 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider48 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider49 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider50 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider51 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider52 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fHslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fHslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fHslider52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
