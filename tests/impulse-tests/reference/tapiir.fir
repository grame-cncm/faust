======= Container "mydsp" ==========

======= External types declaration ==========

DeclareStructTypeInst(StructType<"Soundfile",("void*", fBuffers)("int*", fLength)("int*", fSR)("int*", fOffset)("int", fChannels)("int", fParts)("int", fIsDouble)>)

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface begin ==========

BlockInst 
	OpenVerticalBox("Tapiir")
	OpenTabBox("0x00")
	OpenHorizontalBox("Tap 0")
	AddVerticalSlider("delay (sec)", fVslider11, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider2, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider9, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider10, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider3, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider4, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider5, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider6, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider7, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider8, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Tap 1")
	AddVerticalSlider("delay (sec)", fVslider21, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider12, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider19, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider20, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider13, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider14, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider15, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider16, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider17, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider18, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Tap 2")
	AddVerticalSlider("delay (sec)", fVslider31, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider22, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider29, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider30, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider23, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider24, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider25, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider26, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider27, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider28, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Tap 3")
	AddVerticalSlider("delay (sec)", fVslider41, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider32, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider39, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider40, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider33, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider34, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider35, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider36, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider37, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider38, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Tap 4")
	AddVerticalSlider("delay (sec)", fVslider51, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider42, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider49, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider50, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider43, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider44, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider45, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider46, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider47, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider48, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Tap 5")
	AddVerticalSlider("delay (sec)", fVslider61, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider52, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider59, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider60, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider53, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider54, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider55, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider56, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider57, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider58, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	CloseboxInst
	OpenVerticalBox("outputs")
	OpenHorizontalBox("output 0")
	AddVerticalSlider("gain", fVslider0, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider67, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider68, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider1, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider62, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider63, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider64, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider65, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider66, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("output 1")
	AddVerticalSlider("gain", fVslider69, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider76, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider77, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider70, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider71, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider72, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider73, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider74, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider75, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	CloseboxInst
	CloseboxInst
EndBlockInst

======= User Interface end ==========

======= Global declarations begin ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
EndBlockInst

======= Global declarations end ==========

======= DSP struct begin ==========

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fVslider0)("FAUSTFLOAT", fVslider1)("FAUSTFLOAT", fVslider2)("FAUSTFLOAT", fVslider3)("FAUSTFLOAT", fVslider4)("FAUSTFLOAT", fVslider5)("FAUSTFLOAT", fVslider6)("FAUSTFLOAT", fVslider7)("FAUSTFLOAT", fVslider8)("FAUSTFLOAT", fVslider9)("FAUSTFLOAT", fVslider10)("int", IOTA0)("float[524288]", fVec0)("int", fSampleRate)("float", fConst0)("FAUSTFLOAT", fVslider11)("float[2]", fRec0)("FAUSTFLOAT", fVslider12)("FAUSTFLOAT", fVslider13)("FAUSTFLOAT", fVslider14)("FAUSTFLOAT", fVslider15)("FAUSTFLOAT", fVslider16)("FAUSTFLOAT", fVslider17)("FAUSTFLOAT", fVslider18)("FAUSTFLOAT", fVslider19)("FAUSTFLOAT", fVslider20)("float[524288]", fVec1)("FAUSTFLOAT", fVslider21)("float[2]", fRec1)("FAUSTFLOAT", fVslider22)("FAUSTFLOAT", fVslider23)("FAUSTFLOAT", fVslider24)("FAUSTFLOAT", fVslider25)("FAUSTFLOAT", fVslider26)("FAUSTFLOAT", fVslider27)("FAUSTFLOAT", fVslider28)("FAUSTFLOAT", fVslider29)("FAUSTFLOAT", fVslider30)("float[524288]", fVec2)("FAUSTFLOAT", fVslider31)("float[2]", fRec2)("FAUSTFLOAT", fVslider32)("FAUSTFLOAT", fVslider33)("FAUSTFLOAT", fVslider34)("FAUSTFLOAT", fVslider35)("FAUSTFLOAT", fVslider36)("FAUSTFLOAT", fVslider37)("FAUSTFLOAT", fVslider38)("FAUSTFLOAT", fVslider39)("FAUSTFLOAT", fVslider40)("float[524288]", fVec3)("FAUSTFLOAT", fVslider41)("float[2]", fRec3)("FAUSTFLOAT", fVslider42)("FAUSTFLOAT", fVslider43)("FAUSTFLOAT", fVslider44)("FAUSTFLOAT", fVslider45)("FAUSTFLOAT", fVslider46)("FAUSTFLOAT", fVslider47)("FAUSTFLOAT", fVslider48)("FAUSTFLOAT", fVslider49)("FAUSTFLOAT", fVslider50)("float[524288]", fVec4)("FAUSTFLOAT", fVslider51)("float[2]", fRec4)("FAUSTFLOAT", fVslider52)("FAUSTFLOAT", fVslider53)("FAUSTFLOAT", fVslider54)("FAUSTFLOAT", fVslider55)("FAUSTFLOAT", fVslider56)("FAUSTFLOAT", fVslider57)("FAUSTFLOAT", fVslider58)("FAUSTFLOAT", fVslider59)("FAUSTFLOAT", fVslider60)("float[524288]", fVec5)("FAUSTFLOAT", fVslider61)("float[2]", fRec5)("FAUSTFLOAT", fVslider62)("FAUSTFLOAT", fVslider63)("FAUSTFLOAT", fVslider64)("FAUSTFLOAT", fVslider65)("FAUSTFLOAT", fVslider66)("FAUSTFLOAT", fVslider67)("FAUSTFLOAT", fVslider68)("FAUSTFLOAT", fVslider69)("FAUSTFLOAT", fVslider70)("FAUSTFLOAT", fVslider71)("FAUSTFLOAT", fVslider72)("FAUSTFLOAT", fVslider73)("FAUSTFLOAT", fVslider74)("FAUSTFLOAT", fVslider75)("FAUSTFLOAT", fVslider76)("FAUSTFLOAT", fVslider77)>)

======= DSP struct end ==========

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(2))
	EndBlockInst
EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
	EndBlockInst
EndDeclare

======= Init begin ==========

BlockInst 
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider11, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider12, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider13, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider14, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider15, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider16, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider17, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider18, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider19, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider20, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider21, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider22, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider23, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider24, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider25, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider26, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider27, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider28, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider29, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider30, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider31, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider32, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider33, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider34, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider35, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider36, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider37, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider38, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider39, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider40, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider41, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider42, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider43, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider44, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider45, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider46, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider47, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider48, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider49, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider50, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider51, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider52, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider53, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider54, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider55, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider56, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider57, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider58, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider59, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider60, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider61, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider62, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider63, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider64, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider65, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider66, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider67, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider68, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider69, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider70, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider71, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider72, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider73, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider74, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider75, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider76, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider77, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
EndBlockInst

======= ResetUI end ==========

======= Clear begin ==========

BlockInst 
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(524288))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(524288))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(524288))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(524288))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(524288))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(524288))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
EndBlockInst

======= Clear end ==========

======= Compute control begin ==========

Instructions complexity : Load = 88 Store = 0 Binop = 12 [ { Int(&) = 6 } { Real(*) = 6 } ] Mathop = 0 Numbers = 10 Declare = 82 Cast = 84 Select = 0 Loop = 0

BlockInst 
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow3, kStack, CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))
	DeclareVarInst("float", fSlow4, kStack, CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow8, kStack, CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))
	DeclareVarInst("float", fSlow9, kStack, CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))
	DeclareVarInst("float", fSlow10, kStack, CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))
	DeclareVarInst("int", iSlow11, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider11, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", LoadVarInst(Address(fVslider12, kStruct))))
	DeclareVarInst("float", fSlow13, kStack, CastInst("float", LoadVarInst(Address(fVslider13, kStruct))))
	DeclareVarInst("float", fSlow14, kStack, CastInst("float", LoadVarInst(Address(fVslider14, kStruct))))
	DeclareVarInst("float", fSlow15, kStack, CastInst("float", LoadVarInst(Address(fVslider15, kStruct))))
	DeclareVarInst("float", fSlow16, kStack, CastInst("float", LoadVarInst(Address(fVslider16, kStruct))))
	DeclareVarInst("float", fSlow17, kStack, CastInst("float", LoadVarInst(Address(fVslider17, kStruct))))
	DeclareVarInst("float", fSlow18, kStack, CastInst("float", LoadVarInst(Address(fVslider18, kStruct))))
	DeclareVarInst("float", fSlow19, kStack, CastInst("float", LoadVarInst(Address(fVslider19, kStruct))))
	DeclareVarInst("float", fSlow20, kStack, CastInst("float", LoadVarInst(Address(fVslider20, kStruct))))
	DeclareVarInst("int", iSlow21, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider21, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", LoadVarInst(Address(fVslider22, kStruct))))
	DeclareVarInst("float", fSlow23, kStack, CastInst("float", LoadVarInst(Address(fVslider23, kStruct))))
	DeclareVarInst("float", fSlow24, kStack, CastInst("float", LoadVarInst(Address(fVslider24, kStruct))))
	DeclareVarInst("float", fSlow25, kStack, CastInst("float", LoadVarInst(Address(fVslider25, kStruct))))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", LoadVarInst(Address(fVslider26, kStruct))))
	DeclareVarInst("float", fSlow27, kStack, CastInst("float", LoadVarInst(Address(fVslider27, kStruct))))
	DeclareVarInst("float", fSlow28, kStack, CastInst("float", LoadVarInst(Address(fVslider28, kStruct))))
	DeclareVarInst("float", fSlow29, kStack, CastInst("float", LoadVarInst(Address(fVslider29, kStruct))))
	DeclareVarInst("float", fSlow30, kStack, CastInst("float", LoadVarInst(Address(fVslider30, kStruct))))
	DeclareVarInst("int", iSlow31, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider31, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow32, kStack, CastInst("float", LoadVarInst(Address(fVslider32, kStruct))))
	DeclareVarInst("float", fSlow33, kStack, CastInst("float", LoadVarInst(Address(fVslider33, kStruct))))
	DeclareVarInst("float", fSlow34, kStack, CastInst("float", LoadVarInst(Address(fVslider34, kStruct))))
	DeclareVarInst("float", fSlow35, kStack, CastInst("float", LoadVarInst(Address(fVslider35, kStruct))))
	DeclareVarInst("float", fSlow36, kStack, CastInst("float", LoadVarInst(Address(fVslider36, kStruct))))
	DeclareVarInst("float", fSlow37, kStack, CastInst("float", LoadVarInst(Address(fVslider37, kStruct))))
	DeclareVarInst("float", fSlow38, kStack, CastInst("float", LoadVarInst(Address(fVslider38, kStruct))))
	DeclareVarInst("float", fSlow39, kStack, CastInst("float", LoadVarInst(Address(fVslider39, kStruct))))
	DeclareVarInst("float", fSlow40, kStack, CastInst("float", LoadVarInst(Address(fVslider40, kStruct))))
	DeclareVarInst("int", iSlow41, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider41, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow42, kStack, CastInst("float", LoadVarInst(Address(fVslider42, kStruct))))
	DeclareVarInst("float", fSlow43, kStack, CastInst("float", LoadVarInst(Address(fVslider43, kStruct))))
	DeclareVarInst("float", fSlow44, kStack, CastInst("float", LoadVarInst(Address(fVslider44, kStruct))))
	DeclareVarInst("float", fSlow45, kStack, CastInst("float", LoadVarInst(Address(fVslider45, kStruct))))
	DeclareVarInst("float", fSlow46, kStack, CastInst("float", LoadVarInst(Address(fVslider46, kStruct))))
	DeclareVarInst("float", fSlow47, kStack, CastInst("float", LoadVarInst(Address(fVslider47, kStruct))))
	DeclareVarInst("float", fSlow48, kStack, CastInst("float", LoadVarInst(Address(fVslider48, kStruct))))
	DeclareVarInst("float", fSlow49, kStack, CastInst("float", LoadVarInst(Address(fVslider49, kStruct))))
	DeclareVarInst("float", fSlow50, kStack, CastInst("float", LoadVarInst(Address(fVslider50, kStruct))))
	DeclareVarInst("int", iSlow51, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider51, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow52, kStack, CastInst("float", LoadVarInst(Address(fVslider52, kStruct))))
	DeclareVarInst("float", fSlow53, kStack, CastInst("float", LoadVarInst(Address(fVslider53, kStruct))))
	DeclareVarInst("float", fSlow54, kStack, CastInst("float", LoadVarInst(Address(fVslider54, kStruct))))
	DeclareVarInst("float", fSlow55, kStack, CastInst("float", LoadVarInst(Address(fVslider55, kStruct))))
	DeclareVarInst("float", fSlow56, kStack, CastInst("float", LoadVarInst(Address(fVslider56, kStruct))))
	DeclareVarInst("float", fSlow57, kStack, CastInst("float", LoadVarInst(Address(fVslider57, kStruct))))
	DeclareVarInst("float", fSlow58, kStack, CastInst("float", LoadVarInst(Address(fVslider58, kStruct))))
	DeclareVarInst("float", fSlow59, kStack, CastInst("float", LoadVarInst(Address(fVslider59, kStruct))))
	DeclareVarInst("float", fSlow60, kStack, CastInst("float", LoadVarInst(Address(fVslider60, kStruct))))
	DeclareVarInst("int", iSlow61, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider61, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow62, kStack, CastInst("float", LoadVarInst(Address(fVslider62, kStruct))))
	DeclareVarInst("float", fSlow63, kStack, CastInst("float", LoadVarInst(Address(fVslider63, kStruct))))
	DeclareVarInst("float", fSlow64, kStack, CastInst("float", LoadVarInst(Address(fVslider64, kStruct))))
	DeclareVarInst("float", fSlow65, kStack, CastInst("float", LoadVarInst(Address(fVslider65, kStruct))))
	DeclareVarInst("float", fSlow66, kStack, CastInst("float", LoadVarInst(Address(fVslider66, kStruct))))
	DeclareVarInst("float", fSlow67, kStack, CastInst("float", LoadVarInst(Address(fVslider67, kStruct))))
	DeclareVarInst("float", fSlow68, kStack, CastInst("float", LoadVarInst(Address(fVslider68, kStruct))))
	DeclareVarInst("float", fSlow69, kStack, CastInst("float", LoadVarInst(Address(fVslider69, kStruct))))
	DeclareVarInst("float", fSlow70, kStack, CastInst("float", LoadVarInst(Address(fVslider70, kStruct))))
	DeclareVarInst("float", fSlow71, kStack, CastInst("float", LoadVarInst(Address(fVslider71, kStruct))))
	DeclareVarInst("float", fSlow72, kStack, CastInst("float", LoadVarInst(Address(fVslider72, kStruct))))
	DeclareVarInst("float", fSlow73, kStack, CastInst("float", LoadVarInst(Address(fVslider73, kStruct))))
	DeclareVarInst("float", fSlow74, kStack, CastInst("float", LoadVarInst(Address(fVslider74, kStruct))))
	DeclareVarInst("float", fSlow75, kStack, CastInst("float", LoadVarInst(Address(fVslider75, kStruct))))
	DeclareVarInst("float", fSlow76, kStack, CastInst("float", LoadVarInst(Address(fVslider76, kStruct))))
	DeclareVarInst("float", fSlow77, kStack, CastInst("float", LoadVarInst(Address(fVslider77, kStruct))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 176 Store = 22 Binop = 149 [ { Int(&) = 12 } { Int(+) = 2 } { Int(-) = 6 } { Int(<) = 1 } { Real(*) = 72 } { Real(+) = 56 } ] Mathop = 0 Numbers = 81 Declare = 3 Cast = 4 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
		StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow11, kStack))), Int32(524287))]))
		StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
		StoreVarInst(Address(fRec1, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow21, kStack))), Int32(524287))]))
		StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
		StoreVarInst(Address(fRec2, kStruct)[Int32(0)], LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow31, kStack))), Int32(524287))]))
		StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
		StoreVarInst(Address(fRec3, kStruct)[Int32(0)], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow41, kStack))), Int32(524287))]))
		StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow49, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
		StoreVarInst(Address(fRec4, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow51, kStack))), Int32(524287))]))
		StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow52, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow53, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow55, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow57, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow58, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow60, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
		StoreVarInst(Address(fRec5, kStruct)[Int32(0)], LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow61, kStack))), Int32(524287))]))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow63, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow65, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow67, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow68, kStack)), LoadVarInst(Address(fTemp1, kStack)))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow69, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow71, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow72, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow73, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow74, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow75, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow76, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fTemp1, kStack)))))))
		StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
		StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
		StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
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
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("float", fVec0[524288], kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider11, kStruct)
	DeclareVarInst("float", fRec0[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider12, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider13, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider14, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider15, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider16, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider17, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider18, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider19, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider20, kStruct)
	DeclareVarInst("float", fVec1[524288], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider21, kStruct)
	DeclareVarInst("float", fRec1[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider22, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider23, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider24, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider25, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider26, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider27, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider28, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider29, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider30, kStruct)
	DeclareVarInst("float", fVec2[524288], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider31, kStruct)
	DeclareVarInst("float", fRec2[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider32, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider33, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider34, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider35, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider36, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider37, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider38, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider39, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider40, kStruct)
	DeclareVarInst("float", fVec3[524288], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider41, kStruct)
	DeclareVarInst("float", fRec3[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider42, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider43, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider44, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider45, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider46, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider47, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider48, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider49, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider50, kStruct)
	DeclareVarInst("float", fVec4[524288], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider51, kStruct)
	DeclareVarInst("float", fRec4[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider52, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider53, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider54, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider55, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider56, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider57, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider58, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider59, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider60, kStruct)
	DeclareVarInst("float", fVec5[524288], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider61, kStruct)
	DeclareVarInst("float", fRec5[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider62, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider63, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider64, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider65, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider66, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider67, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider68, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider69, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider70, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider71, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider72, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider73, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider74, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider75, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider76, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider77, kStruct)
	========== Init method ==========
	StoreVarInst(Address(fSampleRate, kStruct), LoadVarInst(Address(sample_rate, kFunArgs)))
	StoreVarInst(Address(fConst0, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider11, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider12, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider13, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider14, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider15, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider16, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider17, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider18, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider19, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider20, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider21, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider22, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider23, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider24, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider25, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider26, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider27, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider28, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider29, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider30, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider31, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider32, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider33, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider34, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider35, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider36, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider37, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider38, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider39, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider40, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider41, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider42, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider43, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider44, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider45, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider46, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider47, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider48, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider49, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider50, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider51, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider52, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider53, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider54, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider55, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider56, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider57, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider58, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider59, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider60, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider61, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider62, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider63, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider64, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider65, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider66, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider67, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider68, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider69, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider70, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider71, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider72, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider73, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider74, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider75, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider76, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider77, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(524288))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec0, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(524288))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec1, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(524288))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec2, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(524288))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec3, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(524288))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec4, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(524288))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fRec5, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	========== Static init method ==========
	========== Subcontainers ==========
	========== Control ==========
	========== Compute control ==========
	DeclareVarInst("FAUSTFLOAT*", input0, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", input1, kStack, LoadVarInst(Address(inputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("FAUSTFLOAT*", output0, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(0)]))
	DeclareVarInst("FAUSTFLOAT*", output1, kStack, LoadVarInst(Address(outputs, kFunArgs)[Int32(1)]))
	DeclareVarInst("float", fSlow0, kStack, CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))
	DeclareVarInst("float", fSlow1, kStack, CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))
	DeclareVarInst("float", fSlow2, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow3, kStack, CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))
	DeclareVarInst("float", fSlow4, kStack, CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))
	DeclareVarInst("float", fSlow5, kStack, CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))
	DeclareVarInst("float", fSlow6, kStack, CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))
	DeclareVarInst("float", fSlow7, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow8, kStack, CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))
	DeclareVarInst("float", fSlow9, kStack, CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))
	DeclareVarInst("float", fSlow10, kStack, CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))
	DeclareVarInst("int", iSlow11, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider11, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow12, kStack, CastInst("float", LoadVarInst(Address(fVslider12, kStruct))))
	DeclareVarInst("float", fSlow13, kStack, CastInst("float", LoadVarInst(Address(fVslider13, kStruct))))
	DeclareVarInst("float", fSlow14, kStack, CastInst("float", LoadVarInst(Address(fVslider14, kStruct))))
	DeclareVarInst("float", fSlow15, kStack, CastInst("float", LoadVarInst(Address(fVslider15, kStruct))))
	DeclareVarInst("float", fSlow16, kStack, CastInst("float", LoadVarInst(Address(fVslider16, kStruct))))
	DeclareVarInst("float", fSlow17, kStack, CastInst("float", LoadVarInst(Address(fVslider17, kStruct))))
	DeclareVarInst("float", fSlow18, kStack, CastInst("float", LoadVarInst(Address(fVslider18, kStruct))))
	DeclareVarInst("float", fSlow19, kStack, CastInst("float", LoadVarInst(Address(fVslider19, kStruct))))
	DeclareVarInst("float", fSlow20, kStack, CastInst("float", LoadVarInst(Address(fVslider20, kStruct))))
	DeclareVarInst("int", iSlow21, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider21, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow22, kStack, CastInst("float", LoadVarInst(Address(fVslider22, kStruct))))
	DeclareVarInst("float", fSlow23, kStack, CastInst("float", LoadVarInst(Address(fVslider23, kStruct))))
	DeclareVarInst("float", fSlow24, kStack, CastInst("float", LoadVarInst(Address(fVslider24, kStruct))))
	DeclareVarInst("float", fSlow25, kStack, CastInst("float", LoadVarInst(Address(fVslider25, kStruct))))
	DeclareVarInst("float", fSlow26, kStack, CastInst("float", LoadVarInst(Address(fVslider26, kStruct))))
	DeclareVarInst("float", fSlow27, kStack, CastInst("float", LoadVarInst(Address(fVslider27, kStruct))))
	DeclareVarInst("float", fSlow28, kStack, CastInst("float", LoadVarInst(Address(fVslider28, kStruct))))
	DeclareVarInst("float", fSlow29, kStack, CastInst("float", LoadVarInst(Address(fVslider29, kStruct))))
	DeclareVarInst("float", fSlow30, kStack, CastInst("float", LoadVarInst(Address(fVslider30, kStruct))))
	DeclareVarInst("int", iSlow31, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider31, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow32, kStack, CastInst("float", LoadVarInst(Address(fVslider32, kStruct))))
	DeclareVarInst("float", fSlow33, kStack, CastInst("float", LoadVarInst(Address(fVslider33, kStruct))))
	DeclareVarInst("float", fSlow34, kStack, CastInst("float", LoadVarInst(Address(fVslider34, kStruct))))
	DeclareVarInst("float", fSlow35, kStack, CastInst("float", LoadVarInst(Address(fVslider35, kStruct))))
	DeclareVarInst("float", fSlow36, kStack, CastInst("float", LoadVarInst(Address(fVslider36, kStruct))))
	DeclareVarInst("float", fSlow37, kStack, CastInst("float", LoadVarInst(Address(fVslider37, kStruct))))
	DeclareVarInst("float", fSlow38, kStack, CastInst("float", LoadVarInst(Address(fVslider38, kStruct))))
	DeclareVarInst("float", fSlow39, kStack, CastInst("float", LoadVarInst(Address(fVslider39, kStruct))))
	DeclareVarInst("float", fSlow40, kStack, CastInst("float", LoadVarInst(Address(fVslider40, kStruct))))
	DeclareVarInst("int", iSlow41, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider41, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow42, kStack, CastInst("float", LoadVarInst(Address(fVslider42, kStruct))))
	DeclareVarInst("float", fSlow43, kStack, CastInst("float", LoadVarInst(Address(fVslider43, kStruct))))
	DeclareVarInst("float", fSlow44, kStack, CastInst("float", LoadVarInst(Address(fVslider44, kStruct))))
	DeclareVarInst("float", fSlow45, kStack, CastInst("float", LoadVarInst(Address(fVslider45, kStruct))))
	DeclareVarInst("float", fSlow46, kStack, CastInst("float", LoadVarInst(Address(fVslider46, kStruct))))
	DeclareVarInst("float", fSlow47, kStack, CastInst("float", LoadVarInst(Address(fVslider47, kStruct))))
	DeclareVarInst("float", fSlow48, kStack, CastInst("float", LoadVarInst(Address(fVslider48, kStruct))))
	DeclareVarInst("float", fSlow49, kStack, CastInst("float", LoadVarInst(Address(fVslider49, kStruct))))
	DeclareVarInst("float", fSlow50, kStack, CastInst("float", LoadVarInst(Address(fVslider50, kStruct))))
	DeclareVarInst("int", iSlow51, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider51, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow52, kStack, CastInst("float", LoadVarInst(Address(fVslider52, kStruct))))
	DeclareVarInst("float", fSlow53, kStack, CastInst("float", LoadVarInst(Address(fVslider53, kStruct))))
	DeclareVarInst("float", fSlow54, kStack, CastInst("float", LoadVarInst(Address(fVslider54, kStruct))))
	DeclareVarInst("float", fSlow55, kStack, CastInst("float", LoadVarInst(Address(fVslider55, kStruct))))
	DeclareVarInst("float", fSlow56, kStack, CastInst("float", LoadVarInst(Address(fVslider56, kStruct))))
	DeclareVarInst("float", fSlow57, kStack, CastInst("float", LoadVarInst(Address(fVslider57, kStruct))))
	DeclareVarInst("float", fSlow58, kStack, CastInst("float", LoadVarInst(Address(fVslider58, kStruct))))
	DeclareVarInst("float", fSlow59, kStack, CastInst("float", LoadVarInst(Address(fVslider59, kStruct))))
	DeclareVarInst("float", fSlow60, kStack, CastInst("float", LoadVarInst(Address(fVslider60, kStruct))))
	DeclareVarInst("int", iSlow61, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0, kStruct)), CastInst("float", LoadVarInst(Address(fVslider61, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow62, kStack, CastInst("float", LoadVarInst(Address(fVslider62, kStruct))))
	DeclareVarInst("float", fSlow63, kStack, CastInst("float", LoadVarInst(Address(fVslider63, kStruct))))
	DeclareVarInst("float", fSlow64, kStack, CastInst("float", LoadVarInst(Address(fVslider64, kStruct))))
	DeclareVarInst("float", fSlow65, kStack, CastInst("float", LoadVarInst(Address(fVslider65, kStruct))))
	DeclareVarInst("float", fSlow66, kStack, CastInst("float", LoadVarInst(Address(fVslider66, kStruct))))
	DeclareVarInst("float", fSlow67, kStack, CastInst("float", LoadVarInst(Address(fVslider67, kStruct))))
	DeclareVarInst("float", fSlow68, kStack, CastInst("float", LoadVarInst(Address(fVslider68, kStruct))))
	DeclareVarInst("float", fSlow69, kStack, CastInst("float", LoadVarInst(Address(fVslider69, kStruct))))
	DeclareVarInst("float", fSlow70, kStack, CastInst("float", LoadVarInst(Address(fVslider70, kStruct))))
	DeclareVarInst("float", fSlow71, kStack, CastInst("float", LoadVarInst(Address(fVslider71, kStruct))))
	DeclareVarInst("float", fSlow72, kStack, CastInst("float", LoadVarInst(Address(fVslider72, kStruct))))
	DeclareVarInst("float", fSlow73, kStack, CastInst("float", LoadVarInst(Address(fVslider73, kStruct))))
	DeclareVarInst("float", fSlow74, kStack, CastInst("float", LoadVarInst(Address(fVslider74, kStruct))))
	DeclareVarInst("float", fSlow75, kStack, CastInst("float", LoadVarInst(Address(fVslider75, kStruct))))
	DeclareVarInst("float", fSlow76, kStack, CastInst("float", LoadVarInst(Address(fVslider76, kStruct))))
	DeclareVarInst("float", fSlow77, kStack, CastInst("float", LoadVarInst(Address(fVslider77, kStruct))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp1, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			StoreVarInst(Address(fVec0, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow2, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow4, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow5, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow6, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow7, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow8, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow9, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow10, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
			StoreVarInst(Address(fRec0, kStruct)[Int32(0)], LoadVarInst(Address(fVec0, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow11, kStack))), Int32(524287))]))
			StoreVarInst(Address(fVec1, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow12, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow13, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow14, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow15, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow16, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow17, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow18, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow19, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow20, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
			StoreVarInst(Address(fRec1, kStruct)[Int32(0)], LoadVarInst(Address(fVec1, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow21, kStack))), Int32(524287))]))
			StoreVarInst(Address(fVec2, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow22, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow23, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow24, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow25, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow26, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow27, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow28, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow29, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow30, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
			StoreVarInst(Address(fRec2, kStruct)[Int32(0)], LoadVarInst(Address(fVec2, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow31, kStack))), Int32(524287))]))
			StoreVarInst(Address(fVec3, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow32, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow33, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow34, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow35, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow36, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow37, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow38, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow39, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow40, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
			StoreVarInst(Address(fRec3, kStruct)[Int32(0)], LoadVarInst(Address(fVec3, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow41, kStack))), Int32(524287))]))
			StoreVarInst(Address(fVec4, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow42, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow43, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow44, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow45, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow46, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow47, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow48, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow49, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow50, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
			StoreVarInst(Address(fRec4, kStruct)[Int32(0)], LoadVarInst(Address(fVec4, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow51, kStack))), Int32(524287))]))
			StoreVarInst(Address(fVec5, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow52, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow53, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(1)])), BinopInst("*", LoadVarInst(Address(fSlow54, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow55, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow56, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow57, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow58, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(1)]))), BinopInst("*", LoadVarInst(Address(fSlow59, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow60, kStack)), LoadVarInst(Address(fTemp1, kStack))))))
			StoreVarInst(Address(fRec5, kStruct)[Int32(0)], LoadVarInst(Address(fVec5, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow61, kStack))), Int32(524287))]))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow0, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow1, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow62, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow63, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow64, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow65, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow66, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow67, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow68, kStack)), LoadVarInst(Address(fTemp1, kStack)))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow69, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow70, kStack)), LoadVarInst(Address(fRec0, kStruct)[Int32(0)])), BinopInst("*", LoadVarInst(Address(fSlow71, kStack)), LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow72, kStack)), LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow73, kStack)), LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow74, kStack)), LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow75, kStack)), LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))), BinopInst("*", LoadVarInst(Address(fSlow76, kStack)), LoadVarInst(Address(fTemp0, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow77, kStack)), LoadVarInst(Address(fTemp1, kStack)))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
			StoreVarInst(Address(fRec0, kStruct)[Int32(1)], LoadVarInst(Address(fRec0, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec1, kStruct)[Int32(1)], LoadVarInst(Address(fRec1, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec2, kStruct)[Int32(1)], LoadVarInst(Address(fRec2, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec3, kStruct)[Int32(1)], LoadVarInst(Address(fRec3, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec4, kStruct)[Int32(1)], LoadVarInst(Address(fRec4, kStruct)[Int32(0)]))
			StoreVarInst(Address(fRec5, kStruct)[Int32(1)], LoadVarInst(Address(fRec5, kStruct)[Int32(0)]))
		EndBlockInst
	EndForLoopInst
	========== Post compute DSP ==========
EndBlockInst

======= Flatten FIR end ==========

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 12583276 bytes
Total heap size = 12583284 bytes
Stack size in compute = 344 bytes

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
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVslider21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVslider31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec3 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVslider41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVslider51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider54 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider55 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVslider61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider65 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider69 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider70 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider71 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider72 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider73 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider74 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider75 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider76 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider77 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0

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
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec0 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 6 write = 0 ratio = 6
Field = fVslider11 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec0 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider14 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider15 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider16 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider17 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider18 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider19 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider20 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec1 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVslider21 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec1 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider22 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider23 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider24 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider25 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider26 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider27 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider28 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider29 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider30 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec2 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVslider31 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec2 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider32 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider33 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider34 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider35 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider36 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider37 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider38 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider39 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider40 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec3 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVslider41 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec3 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider42 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider43 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider44 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider45 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider46 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider47 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider48 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider49 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider50 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec4 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVslider51 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec4 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider52 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider53 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider54 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider55 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider56 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider57 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider58 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider59 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider60 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec5 size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVslider61 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fRec5 size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider62 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider63 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider64 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider65 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider66 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider67 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider68 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider69 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider70 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider71 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider72 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider73 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider74 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider75 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider76 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider77 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1

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
Field = IOTA0 size = 1 size_bytes = 4 read = 13 write = 1 ratio = 14
Field = fVec0 size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec0 size = 2 size_bytes = 8 read = 9 write = 2 ratio = 5.5
Field = fVslider12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider14 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider15 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider16 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider17 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider18 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider19 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider20 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec1 size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVslider21 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec1 size = 2 size_bytes = 8 read = 9 write = 2 ratio = 5.5
Field = fVslider22 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider23 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider24 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider25 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider26 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider27 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider28 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider29 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider30 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec2 size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVslider31 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec2 size = 2 size_bytes = 8 read = 9 write = 2 ratio = 5.5
Field = fVslider32 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider33 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider34 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider35 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider36 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider37 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider38 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider39 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider40 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec3 size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVslider41 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec3 size = 2 size_bytes = 8 read = 9 write = 2 ratio = 5.5
Field = fVslider42 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider43 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider44 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider45 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider46 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider47 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider48 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider49 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider50 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec4 size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVslider51 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec4 size = 2 size_bytes = 8 read = 9 write = 2 ratio = 5.5
Field = fVslider52 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider53 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider54 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider55 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider56 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider57 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec5 size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVslider61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fRec5 size = 2 size_bytes = 8 read = 9 write = 2 ratio = 5.5
Field = fVslider62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider65 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider69 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider70 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider71 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider72 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider73 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider74 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider75 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider76 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider77 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
