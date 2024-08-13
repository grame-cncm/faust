======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenTabBox("Matrix 8 x 8")
	OpenHorizontalBox("Output 0")
	AddVerticalSlider("Input 0", fVslider0, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 1", fVslider1, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 2", fVslider2, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 3", fVslider3, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 4", fVslider4, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 5", fVslider5, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 6", fVslider6, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 7", fVslider7, -1e+01f, -96.0f, 4.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Output 1")
	AddVerticalSlider("Input 0", fVslider8, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 1", fVslider9, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 2", fVslider10, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 3", fVslider11, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 4", fVslider12, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 5", fVslider13, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 6", fVslider14, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 7", fVslider15, -1e+01f, -96.0f, 4.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Output 2")
	AddVerticalSlider("Input 0", fVslider16, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 1", fVslider17, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 2", fVslider18, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 3", fVslider19, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 4", fVslider20, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 5", fVslider21, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 6", fVslider22, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 7", fVslider23, -1e+01f, -96.0f, 4.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Output 3")
	AddVerticalSlider("Input 0", fVslider24, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 1", fVslider25, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 2", fVslider26, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 3", fVslider27, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 4", fVslider28, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 5", fVslider29, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 6", fVslider30, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 7", fVslider31, -1e+01f, -96.0f, 4.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Output 4")
	AddVerticalSlider("Input 0", fVslider32, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 1", fVslider33, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 2", fVslider34, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 3", fVslider35, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 4", fVslider36, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 5", fVslider37, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 6", fVslider38, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 7", fVslider39, -1e+01f, -96.0f, 4.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Output 5")
	AddVerticalSlider("Input 0", fVslider40, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 1", fVslider41, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 2", fVslider42, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 3", fVslider43, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 4", fVslider44, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 5", fVslider45, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 6", fVslider46, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 7", fVslider47, -1e+01f, -96.0f, 4.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Output 6")
	AddVerticalSlider("Input 0", fVslider48, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 1", fVslider49, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 2", fVslider50, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 3", fVslider51, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 4", fVslider52, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 5", fVslider53, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 6", fVslider54, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 7", fVslider55, -1e+01f, -96.0f, 4.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Output 7")
	AddVerticalSlider("Input 0", fVslider56, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 1", fVslider57, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 2", fVslider58, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 3", fVslider59, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 4", fVslider60, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 5", fVslider61, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 6", fVslider62, -1e+01f, -96.0f, 4.0f, 0.1f)
	AddVerticalSlider("Input 7", fVslider63, -1e+01f, -96.0f, 4.0f, 0.1f)
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "powf", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fVslider0)("FAUSTFLOAT", fVslider1)("FAUSTFLOAT", fVslider2)("FAUSTFLOAT", fVslider3)("FAUSTFLOAT", fVslider4)("FAUSTFLOAT", fVslider5)("FAUSTFLOAT", fVslider6)("FAUSTFLOAT", fVslider7)("FAUSTFLOAT", fVslider8)("FAUSTFLOAT", fVslider9)("FAUSTFLOAT", fVslider10)("FAUSTFLOAT", fVslider11)("FAUSTFLOAT", fVslider12)("FAUSTFLOAT", fVslider13)("FAUSTFLOAT", fVslider14)("FAUSTFLOAT", fVslider15)("FAUSTFLOAT", fVslider16)("FAUSTFLOAT", fVslider17)("FAUSTFLOAT", fVslider18)("FAUSTFLOAT", fVslider19)("FAUSTFLOAT", fVslider20)("FAUSTFLOAT", fVslider21)("FAUSTFLOAT", fVslider22)("FAUSTFLOAT", fVslider23)("FAUSTFLOAT", fVslider24)("FAUSTFLOAT", fVslider25)("FAUSTFLOAT", fVslider26)("FAUSTFLOAT", fVslider27)("FAUSTFLOAT", fVslider28)("FAUSTFLOAT", fVslider29)("FAUSTFLOAT", fVslider30)("FAUSTFLOAT", fVslider31)("FAUSTFLOAT", fVslider32)("FAUSTFLOAT", fVslider33)("FAUSTFLOAT", fVslider34)("FAUSTFLOAT", fVslider35)("FAUSTFLOAT", fVslider36)("FAUSTFLOAT", fVslider37)("FAUSTFLOAT", fVslider38)("FAUSTFLOAT", fVslider39)("FAUSTFLOAT", fVslider40)("FAUSTFLOAT", fVslider41)("FAUSTFLOAT", fVslider42)("FAUSTFLOAT", fVslider43)("FAUSTFLOAT", fVslider44)("FAUSTFLOAT", fVslider45)("FAUSTFLOAT", fVslider46)("FAUSTFLOAT", fVslider47)("FAUSTFLOAT", fVslider48)("FAUSTFLOAT", fVslider49)("FAUSTFLOAT", fVslider50)("FAUSTFLOAT", fVslider51)("FAUSTFLOAT", fVslider52)("FAUSTFLOAT", fVslider53)("FAUSTFLOAT", fVslider54)("FAUSTFLOAT", fVslider55)("FAUSTFLOAT", fVslider56)("FAUSTFLOAT", fVslider57)("FAUSTFLOAT", fVslider58)("FAUSTFLOAT", fVslider59)("FAUSTFLOAT", fVslider60)("FAUSTFLOAT", fVslider61)("FAUSTFLOAT", fVslider62)("FAUSTFLOAT", fVslider63)("int", fSampleRate)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(8))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(8))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider11, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider12, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider13, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider14, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider15, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider16, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider17, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider18, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider19, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider20, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider21, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider22, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider23, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider24, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider25, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider26, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider27, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider28, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider29, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider30, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider31, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider32, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider33, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider34, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider35, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider36, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider37, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider38, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider39, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider40, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider41, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider42, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider43, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider44, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider45, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider46, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider47, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider48, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider49, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider50, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider51, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider52, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider53, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider54, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider55, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider56, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider57, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider58, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider59, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider60, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider61, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider62, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider63, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
EndBlockInst

======= ResetUI end ==========

======= Compute control begin ==========

Instructions complexity : Load = 80 Store = 0 Binop = 64 [ { Real(*) = 64 } ] Mathop = 64 [ { powf = 64 } ] Numbers = 144 Declare = 80 Cast = 64 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", input2, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", input3, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", input4, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", input5, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", input6, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", input7, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))))
	DeclareVarInst("float", fSlow5, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))))
	DeclareVarInst("float", fSlow8, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))
	DeclareVarInst("float", fSlow9, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))))
	DeclareVarInst("float", fSlow11, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider11, kStruct))))))
	DeclareVarInst("float", fSlow12, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider12, kStruct))))))
	DeclareVarInst("float", fSlow13, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider13, kStruct))))))
	DeclareVarInst("float", fSlow14, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider14, kStruct))))))
	DeclareVarInst("float", fSlow15, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider15, kStruct))))))
	DeclareVarInst("float", fSlow16, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider16, kStruct))))))
	DeclareVarInst("float", fSlow17, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider17, kStruct))))))
	DeclareVarInst("float", fSlow18, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider18, kStruct))))))
	DeclareVarInst("float", fSlow19, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider19, kStruct))))))
	DeclareVarInst("float", fSlow20, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider20, kStruct))))))
	DeclareVarInst("float", fSlow21, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider21, kStruct))))))
	DeclareVarInst("float", fSlow22, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider22, kStruct))))))
	DeclareVarInst("float", fSlow23, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider23, kStruct))))))
	DeclareVarInst("float", fSlow24, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider24, kStruct))))))
	DeclareVarInst("float", fSlow25, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider25, kStruct))))))
	DeclareVarInst("float", fSlow26, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider26, kStruct))))))
	DeclareVarInst("float", fSlow27, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider27, kStruct))))))
	DeclareVarInst("float", fSlow28, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider28, kStruct))))))
	DeclareVarInst("float", fSlow29, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider29, kStruct))))))
	DeclareVarInst("float", fSlow30, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider30, kStruct))))))
	DeclareVarInst("float", fSlow31, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider31, kStruct))))))
	DeclareVarInst("float", fSlow32, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider32, kStruct))))))
	DeclareVarInst("float", fSlow33, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider33, kStruct))))))
	DeclareVarInst("float", fSlow34, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider34, kStruct))))))
	DeclareVarInst("float", fSlow35, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider35, kStruct))))))
	DeclareVarInst("float", fSlow36, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider36, kStruct))))))
	DeclareVarInst("float", fSlow37, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider37, kStruct))))))
	DeclareVarInst("float", fSlow38, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider38, kStruct))))))
	DeclareVarInst("float", fSlow39, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider39, kStruct))))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider40, kStruct))))))
	DeclareVarInst("float", fSlow41, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider41, kStruct))))))
	DeclareVarInst("float", fSlow42, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider42, kStruct))))))
	DeclareVarInst("float", fSlow43, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider43, kStruct))))))
	DeclareVarInst("float", fSlow44, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider44, kStruct))))))
	DeclareVarInst("float", fSlow45, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider45, kStruct))))))
	DeclareVarInst("float", fSlow46, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider46, kStruct))))))
	DeclareVarInst("float", fSlow47, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider47, kStruct))))))
	DeclareVarInst("float", fSlow48, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider48, kStruct))))))
	DeclareVarInst("float", fSlow49, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider49, kStruct))))))
	DeclareVarInst("float", fSlow50, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider50, kStruct))))))
	DeclareVarInst("float", fSlow51, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider51, kStruct))))))
	DeclareVarInst("float", fSlow52, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider52, kStruct))))))
	DeclareVarInst("float", fSlow53, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider53, kStruct))))))
	DeclareVarInst("float", fSlow54, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider54, kStruct))))))
	DeclareVarInst("float", fSlow55, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider55, kStruct))))))
	DeclareVarInst("float", fSlow56, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider56, kStruct))))))
	DeclareVarInst("float", fSlow57, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider57, kStruct))))))
	DeclareVarInst("float", fSlow58, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider58, kStruct))))))
	DeclareVarInst("float", fSlow59, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider59, kStruct))))))
	DeclareVarInst("float", fSlow60, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider60, kStruct))))))
	DeclareVarInst("float", fSlow61, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider61, kStruct))))))
	DeclareVarInst("float", fSlow62, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider62, kStruct))))))
	DeclareVarInst("float", fSlow63, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider63, kStruct))))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 155 Store = 9 Binop = 122 [ { Int(+) = 1 } { Int(<) = 1 } { Real(*) = 64 } { Real(+) = 56 } ] Mathop = 0 Numbers = 2 Declare = 9 Cast = 16 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp2, kStack, CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp3, kStack, CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp4, kStack, CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp5, kStack, CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp6, kStack, CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp7, kStack, CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
		StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
		StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow31, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
		StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
		StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
		StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow49, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow51, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow53, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow55, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
		StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow57, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow58, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow60, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow63, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
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
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider10, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider11, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider12, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider13, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider14, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider15, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider16, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider17, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider18, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider19, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider20, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider21, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider22, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider23, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider24, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider25, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider26, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider27, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider28, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider29, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider30, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider31, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider32, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider33, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider34, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider35, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider36, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider37, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider38, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider39, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider40, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider41, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider42, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider43, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider44, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider45, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider46, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider47, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider48, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider49, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider50, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider51, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider52, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider53, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider54, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider55, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider56, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider57, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider58, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider59, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider60, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider61, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider62, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider63, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider11, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider12, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider13, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider14, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider15, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider16, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider17, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider18, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider19, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider20, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider21, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider22, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider23, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider24, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider25, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider26, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider27, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider28, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider29, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider30, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider31, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider32, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider33, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider34, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider35, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider36, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider37, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider38, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider39, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider40, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider41, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider42, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider43, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider44, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider45, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider46, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider47, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider48, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider49, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider50, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider51, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider52, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider53, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider54, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider55, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider56, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider57, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider58, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider59, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider60, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider61, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider62, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
	StoreVarInst(Address(fVslider63, kStruct), CastInst("FAUSTFLOAT", Double(-1e+01f)))
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
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output2, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(2)]))
	DeclareVarInst("FAUSTFLOAT*", output3, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(3)]))
	DeclareVarInst("FAUSTFLOAT*", output4, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(4)]))
	DeclareVarInst("FAUSTFLOAT*", output5, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(5)]))
	DeclareVarInst("FAUSTFLOAT*", output6, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(6)]))
	DeclareVarInst("FAUSTFLOAT*", output7, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(7)]))
	DeclareVarInst("float", fSlow0, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))))
	DeclareVarInst("float", fSlow1, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))))
	DeclareVarInst("float", fSlow2, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))))
	DeclareVarInst("float", fSlow3, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))))
	DeclareVarInst("float", fSlow4, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))))
	DeclareVarInst("float", fSlow5, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))))
	DeclareVarInst("float", fSlow6, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))))
	DeclareVarInst("float", fSlow7, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))))
	DeclareVarInst("float", fSlow8, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))))
	DeclareVarInst("float", fSlow9, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))))
	DeclareVarInst("float", fSlow10, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))))
	DeclareVarInst("float", fSlow11, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider11, kStruct))))))
	DeclareVarInst("float", fSlow12, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider12, kStruct))))))
	DeclareVarInst("float", fSlow13, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider13, kStruct))))))
	DeclareVarInst("float", fSlow14, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider14, kStruct))))))
	DeclareVarInst("float", fSlow15, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider15, kStruct))))))
	DeclareVarInst("float", fSlow16, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider16, kStruct))))))
	DeclareVarInst("float", fSlow17, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider17, kStruct))))))
	DeclareVarInst("float", fSlow18, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider18, kStruct))))))
	DeclareVarInst("float", fSlow19, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider19, kStruct))))))
	DeclareVarInst("float", fSlow20, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider20, kStruct))))))
	DeclareVarInst("float", fSlow21, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider21, kStruct))))))
	DeclareVarInst("float", fSlow22, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider22, kStruct))))))
	DeclareVarInst("float", fSlow23, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider23, kStruct))))))
	DeclareVarInst("float", fSlow24, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider24, kStruct))))))
	DeclareVarInst("float", fSlow25, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider25, kStruct))))))
	DeclareVarInst("float", fSlow26, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider26, kStruct))))))
	DeclareVarInst("float", fSlow27, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider27, kStruct))))))
	DeclareVarInst("float", fSlow28, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider28, kStruct))))))
	DeclareVarInst("float", fSlow29, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider29, kStruct))))))
	DeclareVarInst("float", fSlow30, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider30, kStruct))))))
	DeclareVarInst("float", fSlow31, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider31, kStruct))))))
	DeclareVarInst("float", fSlow32, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider32, kStruct))))))
	DeclareVarInst("float", fSlow33, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider33, kStruct))))))
	DeclareVarInst("float", fSlow34, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider34, kStruct))))))
	DeclareVarInst("float", fSlow35, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider35, kStruct))))))
	DeclareVarInst("float", fSlow36, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider36, kStruct))))))
	DeclareVarInst("float", fSlow37, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider37, kStruct))))))
	DeclareVarInst("float", fSlow38, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider38, kStruct))))))
	DeclareVarInst("float", fSlow39, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider39, kStruct))))))
	DeclareVarInst("float", fSlow40, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider40, kStruct))))))
	DeclareVarInst("float", fSlow41, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider41, kStruct))))))
	DeclareVarInst("float", fSlow42, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider42, kStruct))))))
	DeclareVarInst("float", fSlow43, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider43, kStruct))))))
	DeclareVarInst("float", fSlow44, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider44, kStruct))))))
	DeclareVarInst("float", fSlow45, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider45, kStruct))))))
	DeclareVarInst("float", fSlow46, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider46, kStruct))))))
	DeclareVarInst("float", fSlow47, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider47, kStruct))))))
	DeclareVarInst("float", fSlow48, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider48, kStruct))))))
	DeclareVarInst("float", fSlow49, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider49, kStruct))))))
	DeclareVarInst("float", fSlow50, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider50, kStruct))))))
	DeclareVarInst("float", fSlow51, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider51, kStruct))))))
	DeclareVarInst("float", fSlow52, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider52, kStruct))))))
	DeclareVarInst("float", fSlow53, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider53, kStruct))))))
	DeclareVarInst("float", fSlow54, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider54, kStruct))))))
	DeclareVarInst("float", fSlow55, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider55, kStruct))))))
	DeclareVarInst("float", fSlow56, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider56, kStruct))))))
	DeclareVarInst("float", fSlow57, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider57, kStruct))))))
	DeclareVarInst("float", fSlow58, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider58, kStruct))))))
	DeclareVarInst("float", fSlow59, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider59, kStruct))))))
	DeclareVarInst("float", fSlow60, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider60, kStruct))))))
	DeclareVarInst("float", fSlow61, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider61, kStruct))))))
	DeclareVarInst("float", fSlow62, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider62, kStruct))))))
	DeclareVarInst("float", fSlow63, kStack, FunCallInst("powf", Float(1e+01f), BinopInst("*", Float(0.05f), CastInst("float", LoadVarInst(Address(fVslider63, kStruct))))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp2, kStack, CastInst("float", LoadVarInst(Address(input2, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp3, kStack, CastInst("float", LoadVarInst(Address(input3, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp4, kStack, CastInst("float", LoadVarInst(Address(input4, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp5, kStack, CastInst("float", LoadVarInst(Address(input5, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp6, kStack, CastInst("float", LoadVarInst(Address(input6, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp7, kStack, CastInst("float", LoadVarInst(Address(input7, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow11, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
			StoreVarInst(Address(output2, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow21, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
			StoreVarInst(Address(output3, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow31, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
			StoreVarInst(Address(output4, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
			StoreVarInst(Address(output5, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow41, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
			StoreVarInst(Address(output6, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow49, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow51, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow52, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow53, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow55, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
			StoreVarInst(Address(output7, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), LoadVarInst(Address(fTemp0, kStack))), BinopInst("*", LoadVarInst(Address(fSlow57, kStack)), LoadVarInst(Address(fTemp1, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow58, kStack)), LoadVarInst(Address(fTemp2, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fTemp3, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow60, kStack)), LoadVarInst(Address(fTemp4, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow61, kStack)), LoadVarInst(Address(fTemp5, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), LoadVarInst(Address(fTemp6, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow63, kStack)), LoadVarInst(Address(fTemp7, kStack))))))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 256 bytes
Total heap size = 260 bytes
Stack size in compute = 384 bytes

======= Variable access in Control ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider54 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider55 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute control ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider1 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider2 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider3 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider4 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider11 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider14 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider15 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider16 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider18 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider19 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider20 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider21 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider22 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider23 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider24 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider25 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider26 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider27 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider28 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider29 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider30 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider31 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider32 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider33 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider34 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider35 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider36 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider37 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider38 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider39 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider40 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider41 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider42 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider43 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider44 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider45 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider46 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider47 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider48 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider49 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider50 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider51 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider52 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider53 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider54 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider55 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider56 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider57 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider58 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider59 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider60 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider61 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider62 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider63 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

======= Variable access in compute DSP ==========

Field = fVslider0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider1 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider2 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider3 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider4 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider54 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider55 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
