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
	AddVerticalSlider("delay (sec)", fVslider4, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider5, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider6, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider7, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider8, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider9, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider10, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider11, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider12, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider13, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Tap 1")
	AddVerticalSlider("delay (sec)", fVslider15, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider16, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider17, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider18, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider19, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider20, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider21, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider22, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider23, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider24, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Tap 2")
	AddVerticalSlider("delay (sec)", fVslider26, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider27, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider28, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider29, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider30, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider31, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider32, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider33, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider34, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider35, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Tap 3")
	AddVerticalSlider("delay (sec)", fVslider37, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider38, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider39, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider40, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider41, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider42, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider43, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider44, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider45, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider46, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Tap 4")
	AddVerticalSlider("delay (sec)", fVslider48, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider49, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider50, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider51, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider52, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider53, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider54, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider55, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider56, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider57, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("Tap 5")
	AddVerticalSlider("delay (sec)", fVslider59, 0.0f, 0.0f, 5.0f, 0.01f)
	AddVerticalSlider("gain", fVslider60, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider61, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider62, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider63, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider64, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider65, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider66, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider67, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider68, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	CloseboxInst
	OpenVerticalBox("outputs")
	OpenHorizontalBox("output 0")
	AddVerticalSlider("gain", fVslider0, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider1, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider2, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider3, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider14, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider25, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider36, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider47, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider58, 0.0f, 0.0f, 1.0f, 0.1f)
	CloseboxInst
	OpenHorizontalBox("output 1")
	AddVerticalSlider("gain", fVslider69, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 0", fVslider70, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("input 1", fVslider71, 1.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 0", fVslider72, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 1", fVslider73, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 2", fVslider74, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 3", fVslider75, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 4", fVslider76, 0.0f, 0.0f, 1.0f, 0.1f)
	AddVerticalSlider("tap 5", fVslider77, 0.0f, 0.0f, 1.0f, 0.1f)
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

DeclareStructTypeInst(StructType<"mydsp",("FAUSTFLOAT", fVslider0)("FAUSTFLOAT", fVslider1)("FAUSTFLOAT", fVslider2)("FAUSTFLOAT", fVslider3)("FAUSTFLOAT", fVslider4)("int", fSampleRate)("float", fConst0KI)("FAUSTFLOAT", fVslider5)("FAUSTFLOAT", fVslider6)("FAUSTFLOAT", fVslider7)("FAUSTFLOAT", fVslider8)("int", IOTA0)("FAUSTFLOAT", fVslider9)("FAUSTFLOAT", fVslider10)("FAUSTFLOAT", fVslider11)("FAUSTFLOAT", fVslider12)("FAUSTFLOAT", fVslider13)("float[524288]", fVec6SE)("float[2]", fVec0SE)("FAUSTFLOAT", fVslider14)("FAUSTFLOAT", fVslider15)("FAUSTFLOAT", fVslider16)("FAUSTFLOAT", fVslider17)("FAUSTFLOAT", fVslider18)("FAUSTFLOAT", fVslider19)("FAUSTFLOAT", fVslider20)("FAUSTFLOAT", fVslider21)("FAUSTFLOAT", fVslider22)("FAUSTFLOAT", fVslider23)("FAUSTFLOAT", fVslider24)("float[524288]", fVec9SE)("float[2]", fVec1SE)("FAUSTFLOAT", fVslider25)("FAUSTFLOAT", fVslider26)("FAUSTFLOAT", fVslider27)("FAUSTFLOAT", fVslider28)("FAUSTFLOAT", fVslider29)("FAUSTFLOAT", fVslider30)("FAUSTFLOAT", fVslider31)("FAUSTFLOAT", fVslider32)("FAUSTFLOAT", fVslider33)("FAUSTFLOAT", fVslider34)("FAUSTFLOAT", fVslider35)("float[524288]", fVec12SE)("float[2]", fVec2SE)("FAUSTFLOAT", fVslider36)("FAUSTFLOAT", fVslider37)("FAUSTFLOAT", fVslider38)("FAUSTFLOAT", fVslider39)("FAUSTFLOAT", fVslider40)("FAUSTFLOAT", fVslider41)("FAUSTFLOAT", fVslider42)("FAUSTFLOAT", fVslider43)("FAUSTFLOAT", fVslider44)("FAUSTFLOAT", fVslider45)("FAUSTFLOAT", fVslider46)("float[524288]", fVec15SE)("float[2]", fVec3SE)("FAUSTFLOAT", fVslider47)("FAUSTFLOAT", fVslider48)("FAUSTFLOAT", fVslider49)("FAUSTFLOAT", fVslider50)("FAUSTFLOAT", fVslider51)("FAUSTFLOAT", fVslider52)("FAUSTFLOAT", fVslider53)("FAUSTFLOAT", fVslider54)("FAUSTFLOAT", fVslider55)("FAUSTFLOAT", fVslider56)("FAUSTFLOAT", fVslider57)("float[524288]", fVec18SE)("float[2]", fVec4SE)("FAUSTFLOAT", fVslider58)("FAUSTFLOAT", fVslider59)("FAUSTFLOAT", fVslider60)("FAUSTFLOAT", fVslider61)("FAUSTFLOAT", fVslider62)("FAUSTFLOAT", fVslider63)("FAUSTFLOAT", fVslider64)("FAUSTFLOAT", fVslider65)("FAUSTFLOAT", fVslider66)("FAUSTFLOAT", fVslider67)("FAUSTFLOAT", fVslider68)("float[524288]", fVec21SE)("float[2]", fVec5SE)("FAUSTFLOAT", fVslider69)("FAUSTFLOAT", fVslider70)("FAUSTFLOAT", fVslider71)("FAUSTFLOAT", fVslider72)("FAUSTFLOAT", fVslider73)("FAUSTFLOAT", fVslider74)("FAUSTFLOAT", fVslider75)("FAUSTFLOAT", fVslider76)("FAUSTFLOAT", fVslider77)>)

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
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
EndBlockInst

======= Init end ==========

======= ResetUI begin ==========

BlockInst 
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider11, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider12, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider13, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider14, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider15, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider16, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider17, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider18, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider19, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider20, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider21, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider22, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider23, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider24, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider25, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider26, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider27, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider28, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider29, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider30, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider31, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider32, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider33, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider34, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider35, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider36, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider37, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider38, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider39, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider40, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider41, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider42, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider43, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider44, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider45, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider46, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider47, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider48, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider49, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider50, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider51, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider52, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider53, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider54, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider55, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider56, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider57, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider58, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider59, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider60, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider61, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider62, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider63, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider64, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider65, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider66, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider67, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider68, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider69, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider70, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider71, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider72, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider73, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider74, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider75, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider76, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider77, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
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
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(524288))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(524288))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(524288))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(524288))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(524288))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))
	DeclareVarInst("float", fSlow2BE, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow3BE, kStack, CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))
	DeclareVarInst("int", iSlow4BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow5BE, kStack, CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))
	DeclareVarInst("float", fSlow6BE, kStack, CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))
	DeclareVarInst("float", fSlow7BE, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow8BE, kStack, CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))
	DeclareVarInst("float", fSlow9BE, kStack, CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))
	DeclareVarInst("float", fSlow10BE, kStack, CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))
	DeclareVarInst("float", fSlow11BE, kStack, CastInst("float", LoadVarInst(Address(fVslider11, kStruct))))
	DeclareVarInst("float", fSlow12BE, kStack, CastInst("float", LoadVarInst(Address(fVslider12, kStruct))))
	DeclareVarInst("float", fSlow13BE, kStack, CastInst("float", LoadVarInst(Address(fVslider13, kStruct))))
	DeclareVarInst("float", fSlow14BE, kStack, CastInst("float", LoadVarInst(Address(fVslider14, kStruct))))
	DeclareVarInst("int", iSlow15BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider15, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow16BE, kStack, CastInst("float", LoadVarInst(Address(fVslider16, kStruct))))
	DeclareVarInst("float", fSlow17BE, kStack, CastInst("float", LoadVarInst(Address(fVslider17, kStruct))))
	DeclareVarInst("float", fSlow18BE, kStack, CastInst("float", LoadVarInst(Address(fVslider18, kStruct))))
	DeclareVarInst("float", fSlow19BE, kStack, CastInst("float", LoadVarInst(Address(fVslider19, kStruct))))
	DeclareVarInst("float", fSlow20BE, kStack, CastInst("float", LoadVarInst(Address(fVslider20, kStruct))))
	DeclareVarInst("float", fSlow21BE, kStack, CastInst("float", LoadVarInst(Address(fVslider21, kStruct))))
	DeclareVarInst("float", fSlow22BE, kStack, CastInst("float", LoadVarInst(Address(fVslider22, kStruct))))
	DeclareVarInst("float", fSlow23BE, kStack, CastInst("float", LoadVarInst(Address(fVslider23, kStruct))))
	DeclareVarInst("float", fSlow24BE, kStack, CastInst("float", LoadVarInst(Address(fVslider24, kStruct))))
	DeclareVarInst("float", fSlow25BE, kStack, CastInst("float", LoadVarInst(Address(fVslider25, kStruct))))
	DeclareVarInst("int", iSlow26BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider26, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow27BE, kStack, CastInst("float", LoadVarInst(Address(fVslider27, kStruct))))
	DeclareVarInst("float", fSlow28BE, kStack, CastInst("float", LoadVarInst(Address(fVslider28, kStruct))))
	DeclareVarInst("float", fSlow29BE, kStack, CastInst("float", LoadVarInst(Address(fVslider29, kStruct))))
	DeclareVarInst("float", fSlow30BE, kStack, CastInst("float", LoadVarInst(Address(fVslider30, kStruct))))
	DeclareVarInst("float", fSlow31BE, kStack, CastInst("float", LoadVarInst(Address(fVslider31, kStruct))))
	DeclareVarInst("float", fSlow32BE, kStack, CastInst("float", LoadVarInst(Address(fVslider32, kStruct))))
	DeclareVarInst("float", fSlow33BE, kStack, CastInst("float", LoadVarInst(Address(fVslider33, kStruct))))
	DeclareVarInst("float", fSlow34BE, kStack, CastInst("float", LoadVarInst(Address(fVslider34, kStruct))))
	DeclareVarInst("float", fSlow35BE, kStack, CastInst("float", LoadVarInst(Address(fVslider35, kStruct))))
	DeclareVarInst("float", fSlow36BE, kStack, CastInst("float", LoadVarInst(Address(fVslider36, kStruct))))
	DeclareVarInst("int", iSlow37BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider37, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow38BE, kStack, CastInst("float", LoadVarInst(Address(fVslider38, kStruct))))
	DeclareVarInst("float", fSlow39BE, kStack, CastInst("float", LoadVarInst(Address(fVslider39, kStruct))))
	DeclareVarInst("float", fSlow40BE, kStack, CastInst("float", LoadVarInst(Address(fVslider40, kStruct))))
	DeclareVarInst("float", fSlow41BE, kStack, CastInst("float", LoadVarInst(Address(fVslider41, kStruct))))
	DeclareVarInst("float", fSlow42BE, kStack, CastInst("float", LoadVarInst(Address(fVslider42, kStruct))))
	DeclareVarInst("float", fSlow43BE, kStack, CastInst("float", LoadVarInst(Address(fVslider43, kStruct))))
	DeclareVarInst("float", fSlow44BE, kStack, CastInst("float", LoadVarInst(Address(fVslider44, kStruct))))
	DeclareVarInst("float", fSlow45BE, kStack, CastInst("float", LoadVarInst(Address(fVslider45, kStruct))))
	DeclareVarInst("float", fSlow46BE, kStack, CastInst("float", LoadVarInst(Address(fVslider46, kStruct))))
	DeclareVarInst("float", fSlow47BE, kStack, CastInst("float", LoadVarInst(Address(fVslider47, kStruct))))
	DeclareVarInst("int", iSlow48BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider48, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow49BE, kStack, CastInst("float", LoadVarInst(Address(fVslider49, kStruct))))
	DeclareVarInst("float", fSlow50BE, kStack, CastInst("float", LoadVarInst(Address(fVslider50, kStruct))))
	DeclareVarInst("float", fSlow51BE, kStack, CastInst("float", LoadVarInst(Address(fVslider51, kStruct))))
	DeclareVarInst("float", fSlow52BE, kStack, CastInst("float", LoadVarInst(Address(fVslider52, kStruct))))
	DeclareVarInst("float", fSlow53BE, kStack, CastInst("float", LoadVarInst(Address(fVslider53, kStruct))))
	DeclareVarInst("float", fSlow54BE, kStack, CastInst("float", LoadVarInst(Address(fVslider54, kStruct))))
	DeclareVarInst("float", fSlow55BE, kStack, CastInst("float", LoadVarInst(Address(fVslider55, kStruct))))
	DeclareVarInst("float", fSlow56BE, kStack, CastInst("float", LoadVarInst(Address(fVslider56, kStruct))))
	DeclareVarInst("float", fSlow57BE, kStack, CastInst("float", LoadVarInst(Address(fVslider57, kStruct))))
	DeclareVarInst("float", fSlow58BE, kStack, CastInst("float", LoadVarInst(Address(fVslider58, kStruct))))
	DeclareVarInst("int", iSlow59BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider59, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow60BE, kStack, CastInst("float", LoadVarInst(Address(fVslider60, kStruct))))
	DeclareVarInst("float", fSlow61BE, kStack, CastInst("float", LoadVarInst(Address(fVslider61, kStruct))))
	DeclareVarInst("float", fSlow62BE, kStack, CastInst("float", LoadVarInst(Address(fVslider62, kStruct))))
	DeclareVarInst("float", fSlow63BE, kStack, CastInst("float", LoadVarInst(Address(fVslider63, kStruct))))
	DeclareVarInst("float", fSlow64BE, kStack, CastInst("float", LoadVarInst(Address(fVslider64, kStruct))))
	DeclareVarInst("float", fSlow65BE, kStack, CastInst("float", LoadVarInst(Address(fVslider65, kStruct))))
	DeclareVarInst("float", fSlow66BE, kStack, CastInst("float", LoadVarInst(Address(fVslider66, kStruct))))
	DeclareVarInst("float", fSlow67BE, kStack, CastInst("float", LoadVarInst(Address(fVslider67, kStruct))))
	DeclareVarInst("float", fSlow68BE, kStack, CastInst("float", LoadVarInst(Address(fVslider68, kStruct))))
	DeclareVarInst("float", fSlow69BE, kStack, CastInst("float", LoadVarInst(Address(fVslider69, kStruct))))
	DeclareVarInst("float", fSlow70BE, kStack, CastInst("float", LoadVarInst(Address(fVslider70, kStruct))))
	DeclareVarInst("float", fSlow71BE, kStack, CastInst("float", LoadVarInst(Address(fVslider71, kStruct))))
	DeclareVarInst("float", fSlow72BE, kStack, CastInst("float", LoadVarInst(Address(fVslider72, kStruct))))
	DeclareVarInst("float", fSlow73BE, kStack, CastInst("float", LoadVarInst(Address(fVslider73, kStruct))))
	DeclareVarInst("float", fSlow74BE, kStack, CastInst("float", LoadVarInst(Address(fVslider74, kStruct))))
	DeclareVarInst("float", fSlow75BE, kStack, CastInst("float", LoadVarInst(Address(fVslider75, kStruct))))
	DeclareVarInst("float", fSlow76BE, kStack, CastInst("float", LoadVarInst(Address(fVslider76, kStruct))))
	DeclareVarInst("float", fSlow77BE, kStack, CastInst("float", LoadVarInst(Address(fVslider77, kStruct))))
EndBlockInst

======= Compute control end ==========

======= Compute DSP begin ==========

Instructions complexity : Load = 200 Store = 16 Binop = 173 [ { Int(&) = 30 } { Int(+) = 2 } { Int(-) = 12 } { Int(<) = 1 } { Real(*) = 72 } { Real(+) = 56 } ] Mathop = 0 Numbers = 39 Declare = 15 Cast = 4 Select = 0 Loop = 1

ForLoopInst 
	DeclareVarInst("int", i0, kLoop, Int32(0))
	BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
	StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
	BlockInst 
		DeclareVarInst("float", fTemp0SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp1SE, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
		DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp4SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp6SE, kStack, LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		DeclareVarInst("float", fTemp7SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
		StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow7BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
		StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow4BE, kStack))), Int32(524287))]))
		DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow16BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow19BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow20BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow21BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow24BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow17BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow18BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
		StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow15BE, kStack))), Int32(524287))]))
		DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow27BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow30BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow31BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow32BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow34BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow35BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow28BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow29BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
		StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow26BE, kStack))), Int32(524287))]))
		DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow38BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow41BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow42BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow43BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow45BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow46BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow39BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow40BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
		StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow37BE, kStack))), Int32(524287))]))
		DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow49BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow52BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow53BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow54BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow56BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow57BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow50BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow51BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
		StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow48BE, kStack))), Int32(524287))]))
		DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow60BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow63BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow64BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow65BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow67BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow68BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow61BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow62BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
		StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow59BE, kStack))), Int32(524287))]))
		DeclareVarInst("float", fTemp13SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
		StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow14BE, kStack)), LoadVarInst(Address(fTemp9SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow25BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow36BE, kStack)), LoadVarInst(Address(fTemp11SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow47BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow58BE, kStack)), LoadVarInst(Address(fTemp13SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack)))))))
		StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow69BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow72BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow73BE, kStack)), LoadVarInst(Address(fTemp9SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow74BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow75BE, kStack)), LoadVarInst(Address(fTemp11SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow76BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), LoadVarInst(Address(fTemp13SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow70BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow71BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack)))))))
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
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareVarInst("FAUSTFLOAT", fVslider0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider1, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider2, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider3, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider4, kStruct)
	DeclareVarInst("int", fSampleRate, kStruct)
	DeclareVarInst("float", fConst0KI, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider5, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider6, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider7, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider8, kStruct)
	DeclareVarInst("int", IOTA0, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider9, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider10, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider11, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider12, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider13, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec6SE[524288], kStruct)
	// Recursion delay fVec0SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec0SE[2], kStruct)
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
	// Ring Delay
	DeclareVarInst("float", fVec9SE[524288], kStruct)
	// Recursion delay fVec1SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec1SE[2], kStruct)
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
	// Ring Delay
	DeclareVarInst("float", fVec12SE[524288], kStruct)
	// Recursion delay fVec2SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec2SE[2], kStruct)
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
	// Ring Delay
	DeclareVarInst("float", fVec15SE[524288], kStruct)
	// Recursion delay fVec3SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec3SE[2], kStruct)
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
	// Ring Delay
	DeclareVarInst("float", fVec18SE[524288], kStruct)
	// Recursion delay fVec4SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec4SE[2], kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider58, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider59, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider60, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider61, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider62, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider63, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider64, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider65, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider66, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider67, kStruct)
	DeclareVarInst("FAUSTFLOAT", fVslider68, kStruct)
	// Ring Delay
	DeclareVarInst("float", fVec21SE[524288], kStruct)
	// Recursion delay fVec5SE is of type kSingleDelay
	// While its definition is of type kZeroDelay
	// Ring Delay
	DeclareVarInst("float", fVec5SE[2], kStruct)
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
	StoreVarInst(Address(fConst0KI, kStruct), FunCallInst("min_f", Float(1.92e+05f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(Address(fSampleRate, kStruct))))))
	StoreVarInst(Address(fVslider0, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider1, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider2, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider3, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider4, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider5, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider6, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider7, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider8, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider9, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider10, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider11, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider12, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider13, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider14, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider15, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider16, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider17, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider18, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider19, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider20, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider21, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider22, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider23, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider24, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider25, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider26, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider27, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider28, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider29, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider30, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider31, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider32, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider33, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider34, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider35, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider36, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider37, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider38, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider39, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider40, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider41, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider42, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider43, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider44, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider45, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider46, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider47, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider48, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider49, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider50, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider51, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider52, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider53, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider54, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider55, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider56, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider57, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider58, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider59, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider60, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider61, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider62, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider63, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider64, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider65, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider66, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider67, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider68, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider69, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider70, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider71, kStruct), CastInst("FAUSTFLOAT", Double(1.0f)))
	StoreVarInst(Address(fVslider72, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider73, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider74, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider75, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider76, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(fVslider77, kStruct), CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(Address(IOTA0, kStruct), Int32(0))
	ForLoopInst 
		DeclareVarInst("int", l0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l0, kLoop)), Int32(524288))
		StoreVarInst(Address(l0, kLoop), BinopInst("+", LoadVarInst(Address(l0, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec6SE, kStruct)[LoadVarInst(Address(l0, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l1, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l1, kLoop)), Int32(2))
		StoreVarInst(Address(l1, kLoop), BinopInst("+", LoadVarInst(Address(l1, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec0SE, kStruct)[LoadVarInst(Address(l1, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l2, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l2, kLoop)), Int32(524288))
		StoreVarInst(Address(l2, kLoop), BinopInst("+", LoadVarInst(Address(l2, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec9SE, kStruct)[LoadVarInst(Address(l2, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l3, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l3, kLoop)), Int32(2))
		StoreVarInst(Address(l3, kLoop), BinopInst("+", LoadVarInst(Address(l3, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec1SE, kStruct)[LoadVarInst(Address(l3, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l4, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l4, kLoop)), Int32(524288))
		StoreVarInst(Address(l4, kLoop), BinopInst("+", LoadVarInst(Address(l4, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec12SE, kStruct)[LoadVarInst(Address(l4, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l5, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l5, kLoop)), Int32(2))
		StoreVarInst(Address(l5, kLoop), BinopInst("+", LoadVarInst(Address(l5, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec2SE, kStruct)[LoadVarInst(Address(l5, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l6, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l6, kLoop)), Int32(524288))
		StoreVarInst(Address(l6, kLoop), BinopInst("+", LoadVarInst(Address(l6, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec15SE, kStruct)[LoadVarInst(Address(l6, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l7, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l7, kLoop)), Int32(2))
		StoreVarInst(Address(l7, kLoop), BinopInst("+", LoadVarInst(Address(l7, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec3SE, kStruct)[LoadVarInst(Address(l7, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l8, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l8, kLoop)), Int32(524288))
		StoreVarInst(Address(l8, kLoop), BinopInst("+", LoadVarInst(Address(l8, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec18SE, kStruct)[LoadVarInst(Address(l8, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l9, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l9, kLoop)), Int32(2))
		StoreVarInst(Address(l9, kLoop), BinopInst("+", LoadVarInst(Address(l9, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec4SE, kStruct)[LoadVarInst(Address(l9, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l10, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l10, kLoop)), Int32(524288))
		StoreVarInst(Address(l10, kLoop), BinopInst("+", LoadVarInst(Address(l10, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec21SE, kStruct)[LoadVarInst(Address(l10, kLoop))], Float(0.0f))
		EndBlockInst
	EndForLoopInst
	ForLoopInst 
		DeclareVarInst("int", l11, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(l11, kLoop)), Int32(2))
		StoreVarInst(Address(l11, kLoop), BinopInst("+", LoadVarInst(Address(l11, kLoop)), Int32(1)))
		BlockInst 
			StoreVarInst(Address(fVec5SE, kStruct)[LoadVarInst(Address(l11, kLoop))], Float(0.0f))
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
	DeclareVarInst("float", fSlow0BE, kStack, CastInst("float", LoadVarInst(Address(fVslider0, kStruct))))
	DeclareVarInst("float", fSlow1BE, kStack, CastInst("float", LoadVarInst(Address(fVslider1, kStruct))))
	DeclareVarInst("float", fSlow2BE, kStack, CastInst("float", LoadVarInst(Address(fVslider2, kStruct))))
	DeclareVarInst("float", fSlow3BE, kStack, CastInst("float", LoadVarInst(Address(fVslider3, kStruct))))
	DeclareVarInst("int", iSlow4BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider4, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow5BE, kStack, CastInst("float", LoadVarInst(Address(fVslider5, kStruct))))
	DeclareVarInst("float", fSlow6BE, kStack, CastInst("float", LoadVarInst(Address(fVslider6, kStruct))))
	DeclareVarInst("float", fSlow7BE, kStack, CastInst("float", LoadVarInst(Address(fVslider7, kStruct))))
	DeclareVarInst("float", fSlow8BE, kStack, CastInst("float", LoadVarInst(Address(fVslider8, kStruct))))
	DeclareVarInst("float", fSlow9BE, kStack, CastInst("float", LoadVarInst(Address(fVslider9, kStruct))))
	DeclareVarInst("float", fSlow10BE, kStack, CastInst("float", LoadVarInst(Address(fVslider10, kStruct))))
	DeclareVarInst("float", fSlow11BE, kStack, CastInst("float", LoadVarInst(Address(fVslider11, kStruct))))
	DeclareVarInst("float", fSlow12BE, kStack, CastInst("float", LoadVarInst(Address(fVslider12, kStruct))))
	DeclareVarInst("float", fSlow13BE, kStack, CastInst("float", LoadVarInst(Address(fVslider13, kStruct))))
	DeclareVarInst("float", fSlow14BE, kStack, CastInst("float", LoadVarInst(Address(fVslider14, kStruct))))
	DeclareVarInst("int", iSlow15BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider15, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow16BE, kStack, CastInst("float", LoadVarInst(Address(fVslider16, kStruct))))
	DeclareVarInst("float", fSlow17BE, kStack, CastInst("float", LoadVarInst(Address(fVslider17, kStruct))))
	DeclareVarInst("float", fSlow18BE, kStack, CastInst("float", LoadVarInst(Address(fVslider18, kStruct))))
	DeclareVarInst("float", fSlow19BE, kStack, CastInst("float", LoadVarInst(Address(fVslider19, kStruct))))
	DeclareVarInst("float", fSlow20BE, kStack, CastInst("float", LoadVarInst(Address(fVslider20, kStruct))))
	DeclareVarInst("float", fSlow21BE, kStack, CastInst("float", LoadVarInst(Address(fVslider21, kStruct))))
	DeclareVarInst("float", fSlow22BE, kStack, CastInst("float", LoadVarInst(Address(fVslider22, kStruct))))
	DeclareVarInst("float", fSlow23BE, kStack, CastInst("float", LoadVarInst(Address(fVslider23, kStruct))))
	DeclareVarInst("float", fSlow24BE, kStack, CastInst("float", LoadVarInst(Address(fVslider24, kStruct))))
	DeclareVarInst("float", fSlow25BE, kStack, CastInst("float", LoadVarInst(Address(fVslider25, kStruct))))
	DeclareVarInst("int", iSlow26BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider26, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow27BE, kStack, CastInst("float", LoadVarInst(Address(fVslider27, kStruct))))
	DeclareVarInst("float", fSlow28BE, kStack, CastInst("float", LoadVarInst(Address(fVslider28, kStruct))))
	DeclareVarInst("float", fSlow29BE, kStack, CastInst("float", LoadVarInst(Address(fVslider29, kStruct))))
	DeclareVarInst("float", fSlow30BE, kStack, CastInst("float", LoadVarInst(Address(fVslider30, kStruct))))
	DeclareVarInst("float", fSlow31BE, kStack, CastInst("float", LoadVarInst(Address(fVslider31, kStruct))))
	DeclareVarInst("float", fSlow32BE, kStack, CastInst("float", LoadVarInst(Address(fVslider32, kStruct))))
	DeclareVarInst("float", fSlow33BE, kStack, CastInst("float", LoadVarInst(Address(fVslider33, kStruct))))
	DeclareVarInst("float", fSlow34BE, kStack, CastInst("float", LoadVarInst(Address(fVslider34, kStruct))))
	DeclareVarInst("float", fSlow35BE, kStack, CastInst("float", LoadVarInst(Address(fVslider35, kStruct))))
	DeclareVarInst("float", fSlow36BE, kStack, CastInst("float", LoadVarInst(Address(fVslider36, kStruct))))
	DeclareVarInst("int", iSlow37BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider37, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow38BE, kStack, CastInst("float", LoadVarInst(Address(fVslider38, kStruct))))
	DeclareVarInst("float", fSlow39BE, kStack, CastInst("float", LoadVarInst(Address(fVslider39, kStruct))))
	DeclareVarInst("float", fSlow40BE, kStack, CastInst("float", LoadVarInst(Address(fVslider40, kStruct))))
	DeclareVarInst("float", fSlow41BE, kStack, CastInst("float", LoadVarInst(Address(fVslider41, kStruct))))
	DeclareVarInst("float", fSlow42BE, kStack, CastInst("float", LoadVarInst(Address(fVslider42, kStruct))))
	DeclareVarInst("float", fSlow43BE, kStack, CastInst("float", LoadVarInst(Address(fVslider43, kStruct))))
	DeclareVarInst("float", fSlow44BE, kStack, CastInst("float", LoadVarInst(Address(fVslider44, kStruct))))
	DeclareVarInst("float", fSlow45BE, kStack, CastInst("float", LoadVarInst(Address(fVslider45, kStruct))))
	DeclareVarInst("float", fSlow46BE, kStack, CastInst("float", LoadVarInst(Address(fVslider46, kStruct))))
	DeclareVarInst("float", fSlow47BE, kStack, CastInst("float", LoadVarInst(Address(fVslider47, kStruct))))
	DeclareVarInst("int", iSlow48BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider48, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow49BE, kStack, CastInst("float", LoadVarInst(Address(fVslider49, kStruct))))
	DeclareVarInst("float", fSlow50BE, kStack, CastInst("float", LoadVarInst(Address(fVslider50, kStruct))))
	DeclareVarInst("float", fSlow51BE, kStack, CastInst("float", LoadVarInst(Address(fVslider51, kStruct))))
	DeclareVarInst("float", fSlow52BE, kStack, CastInst("float", LoadVarInst(Address(fVslider52, kStruct))))
	DeclareVarInst("float", fSlow53BE, kStack, CastInst("float", LoadVarInst(Address(fVslider53, kStruct))))
	DeclareVarInst("float", fSlow54BE, kStack, CastInst("float", LoadVarInst(Address(fVslider54, kStruct))))
	DeclareVarInst("float", fSlow55BE, kStack, CastInst("float", LoadVarInst(Address(fVslider55, kStruct))))
	DeclareVarInst("float", fSlow56BE, kStack, CastInst("float", LoadVarInst(Address(fVslider56, kStruct))))
	DeclareVarInst("float", fSlow57BE, kStack, CastInst("float", LoadVarInst(Address(fVslider57, kStruct))))
	DeclareVarInst("float", fSlow58BE, kStack, CastInst("float", LoadVarInst(Address(fVslider58, kStruct))))
	DeclareVarInst("int", iSlow59BE, kStack, BinopInst("&", CastInst("int", BinopInst("*", LoadVarInst(Address(fConst0KI, kStruct)), CastInst("float", LoadVarInst(Address(fVslider59, kStruct))))), Int32(524287)))
	DeclareVarInst("float", fSlow60BE, kStack, CastInst("float", LoadVarInst(Address(fVslider60, kStruct))))
	DeclareVarInst("float", fSlow61BE, kStack, CastInst("float", LoadVarInst(Address(fVslider61, kStruct))))
	DeclareVarInst("float", fSlow62BE, kStack, CastInst("float", LoadVarInst(Address(fVslider62, kStruct))))
	DeclareVarInst("float", fSlow63BE, kStack, CastInst("float", LoadVarInst(Address(fVslider63, kStruct))))
	DeclareVarInst("float", fSlow64BE, kStack, CastInst("float", LoadVarInst(Address(fVslider64, kStruct))))
	DeclareVarInst("float", fSlow65BE, kStack, CastInst("float", LoadVarInst(Address(fVslider65, kStruct))))
	DeclareVarInst("float", fSlow66BE, kStack, CastInst("float", LoadVarInst(Address(fVslider66, kStruct))))
	DeclareVarInst("float", fSlow67BE, kStack, CastInst("float", LoadVarInst(Address(fVslider67, kStruct))))
	DeclareVarInst("float", fSlow68BE, kStack, CastInst("float", LoadVarInst(Address(fVslider68, kStruct))))
	DeclareVarInst("float", fSlow69BE, kStack, CastInst("float", LoadVarInst(Address(fVslider69, kStruct))))
	DeclareVarInst("float", fSlow70BE, kStack, CastInst("float", LoadVarInst(Address(fVslider70, kStruct))))
	DeclareVarInst("float", fSlow71BE, kStack, CastInst("float", LoadVarInst(Address(fVslider71, kStruct))))
	DeclareVarInst("float", fSlow72BE, kStack, CastInst("float", LoadVarInst(Address(fVslider72, kStruct))))
	DeclareVarInst("float", fSlow73BE, kStack, CastInst("float", LoadVarInst(Address(fVslider73, kStruct))))
	DeclareVarInst("float", fSlow74BE, kStack, CastInst("float", LoadVarInst(Address(fVslider74, kStruct))))
	DeclareVarInst("float", fSlow75BE, kStack, CastInst("float", LoadVarInst(Address(fVslider75, kStruct))))
	DeclareVarInst("float", fSlow76BE, kStack, CastInst("float", LoadVarInst(Address(fVslider76, kStruct))))
	DeclareVarInst("float", fSlow77BE, kStack, CastInst("float", LoadVarInst(Address(fVslider77, kStruct))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst("int", i0, kLoop, Int32(0))
		BinopInst("<", LoadVarInst(Address(i0, kLoop)), LoadVarInst(Address(count, kFunArgs)))
		StoreVarInst(Address(i0, kLoop), BinopInst("+", LoadVarInst(Address(i0, kLoop)), Int32(1)))
		BlockInst 
			DeclareVarInst("float", fTemp0SE, kStack, CastInst("float", LoadVarInst(Address(input0, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp1SE, kStack, CastInst("float", LoadVarInst(Address(input1, kStack)[LoadVarInst(Address(i0, kLoop))])))
			DeclareVarInst("float", fTemp2SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp3SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp4SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp5SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp6SE, kStack, LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			DeclareVarInst("float", fTemp7SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)), Int32(1))]))
			StoreVarInst(Address(fVec6SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow5BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow8BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow9BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow10BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow11BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow12BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow13BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow6BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow7BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
			StoreVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec6SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow4BE, kStack))), Int32(524287))]))
			DeclareVarInst("float", fTemp8SE, kStack, LoadVarInst(Address(fVec0SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec9SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow16BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow19BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow20BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow21BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow22BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow23BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow24BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow17BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow18BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
			StoreVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec9SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow15BE, kStack))), Int32(524287))]))
			DeclareVarInst("float", fTemp9SE, kStack, LoadVarInst(Address(fVec1SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec12SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow27BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow30BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow31BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow32BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow33BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow34BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow35BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow28BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow29BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
			StoreVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec12SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow26BE, kStack))), Int32(524287))]))
			DeclareVarInst("float", fTemp10SE, kStack, LoadVarInst(Address(fVec2SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec15SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow38BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow41BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow42BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow43BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow44BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow45BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow46BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow39BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow40BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
			StoreVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec15SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow37BE, kStack))), Int32(524287))]))
			DeclareVarInst("float", fTemp11SE, kStack, LoadVarInst(Address(fVec3SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec18SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow49BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow52BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow53BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow54BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow55BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow56BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow57BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow50BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow51BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
			StoreVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec18SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow48BE, kStack))), Int32(524287))]))
			DeclareVarInst("float", fTemp12SE, kStack, LoadVarInst(Address(fVec4SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(fVec21SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(524287))], BinopInst("*", LoadVarInst(Address(fSlow60BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow63BE, kStack)), LoadVarInst(Address(fTemp2SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow64BE, kStack)), LoadVarInst(Address(fTemp3SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow65BE, kStack)), LoadVarInst(Address(fTemp4SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow66BE, kStack)), LoadVarInst(Address(fTemp5SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow67BE, kStack)), LoadVarInst(Address(fTemp6SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow68BE, kStack)), LoadVarInst(Address(fTemp7SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow61BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow62BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack))))))
			StoreVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))], LoadVarInst(Address(fVec21SE, kStruct)[BinopInst("&", BinopInst("-", LoadVarInst(Address(IOTA0, kStruct)), LoadVarInst(Address(iSlow59BE, kStack))), Int32(524287))]))
			DeclareVarInst("float", fTemp13SE, kStack, LoadVarInst(Address(fVec5SE, kStruct)[BinopInst("&", LoadVarInst(Address(IOTA0, kStruct)), Int32(1))]))
			StoreVarInst(Address(output0, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow0BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow3BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow14BE, kStack)), LoadVarInst(Address(fTemp9SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow25BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow36BE, kStack)), LoadVarInst(Address(fTemp11SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow47BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow58BE, kStack)), LoadVarInst(Address(fTemp13SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow1BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow2BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack)))))))
			StoreVarInst(Address(output1, kStack)[LoadVarInst(Address(i0, kLoop))], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(Address(fSlow69BE, kStack)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(Address(fSlow72BE, kStack)), LoadVarInst(Address(fTemp8SE, kStack))), BinopInst("*", LoadVarInst(Address(fSlow73BE, kStack)), LoadVarInst(Address(fTemp9SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow74BE, kStack)), LoadVarInst(Address(fTemp10SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow75BE, kStack)), LoadVarInst(Address(fTemp11SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow76BE, kStack)), LoadVarInst(Address(fTemp12SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow77BE, kStack)), LoadVarInst(Address(fTemp13SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow70BE, kStack)), LoadVarInst(Address(fTemp0SE, kStack)))), BinopInst("*", LoadVarInst(Address(fSlow71BE, kStack)), LoadVarInst(Address(fTemp1SE, kStack)))))))
			StoreVarInst(Address(IOTA0, kStruct), BinopInst("+", LoadVarInst(Address(IOTA0, kStruct)), Int32(1)))
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
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
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
Field = fVec9SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
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
Field = fVec12SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
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
Field = fVec15SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
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
Field = fVec18SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider65 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec21SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
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
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 6 write = 0 ratio = 6
Field = fVslider5 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider6 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider7 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider8 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = IOTA0 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider9 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider10 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider11 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider12 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider13 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec6SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec0SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
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
Field = fVec9SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec1SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
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
Field = fVec12SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec2SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
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
Field = fVec15SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec3SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
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
Field = fVec18SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec4SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
Field = fVslider58 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider59 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider60 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider61 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider62 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider63 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider64 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider65 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider66 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider67 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVslider68 size = 1 size_bytes = 4 read = 1 write = 0 ratio = 1
Field = fVec21SE size = 524288 size_bytes = 2097152 read = 0 write = 0 ratio = 0
Field = fVec5SE size = 2 size_bytes = 8 read = 0 write = 0 ratio = 0
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
Field = fSampleRate size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fConst0KI size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider5 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider6 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider7 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider8 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = IOTA0 size = 1 size_bytes = 4 read = 31 write = 1 ratio = 32
Field = fVslider9 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider10 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider11 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider12 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider13 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec6SE size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVec0SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
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
Field = fVec9SE size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVec1SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
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
Field = fVec12SE size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVec2SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
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
Field = fVec15SE size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVec3SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
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
Field = fVec18SE size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVec4SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVslider58 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider59 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider60 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider61 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider62 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider63 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider64 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider65 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider66 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider67 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider68 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVec21SE size = 524288 size_bytes = 2097152 read = 1 write = 1 ratio = 3.8147e-06
Field = fVec5SE size = 2 size_bytes = 8 read = 2 write = 1 ratio = 1.5
Field = fVslider69 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider70 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider71 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider72 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider73 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider74 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider75 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider76 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
Field = fVslider77 size = 1 size_bytes = 4 read = 0 write = 0 ratio = 0
