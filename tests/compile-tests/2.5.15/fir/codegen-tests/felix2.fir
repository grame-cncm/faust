======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("felix2")
	OpenHorizontalBox("ctrl   0")
	AddVerticalBargraph("ctrl  0", fVbargraph0, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl  1", fVbargraph1, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl  2", fVbargraph2, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl  3", fVbargraph3, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl  4", fVbargraph4, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl  5", fVbargraph5, 0.0f, 1.0f)
	CloseboxInst
	OpenHorizontalBox("ctrl   1")
	AddVerticalBargraph("ctrl 10", fVbargraph6, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 11", fVbargraph7, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 12", fVbargraph8, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 13", fVbargraph9, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 14", fVbargraph10, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 15", fVbargraph11, 0.0f, 1.0f)
	CloseboxInst
	OpenHorizontalBox("ctrl   2")
	AddVerticalBargraph("ctrl 20", fVbargraph12, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 21", fVbargraph13, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 22", fVbargraph14, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 23", fVbargraph15, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 24", fVbargraph16, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 25", fVbargraph17, 0.0f, 1.0f)
	CloseboxInst
	OpenHorizontalBox("ctrl   3")
	AddVerticalBargraph("ctrl 30", fVbargraph18, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 31", fVbargraph19, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 32", fVbargraph20, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 33", fVbargraph21, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 34", fVbargraph22, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 35", fVbargraph23, 0.0f, 1.0f)
	CloseboxInst
	OpenHorizontalBox("ctrl   4")
	AddVerticalBargraph("ctrl 40", fVbargraph24, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 41", fVbargraph25, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 42", fVbargraph26, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 43", fVbargraph27, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 44", fVbargraph28, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 45", fVbargraph29, 0.0f, 1.0f)
	CloseboxInst
	OpenHorizontalBox("ctrl   5")
	AddVerticalBargraph("ctrl 50", fVbargraph30, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 51", fVbargraph31, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 52", fVbargraph32, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 53", fVbargraph33, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 54", fVbargraph34, 0.0f, 1.0f)
	AddVerticalBargraph("ctrl 55", fVbargraph35, 0.0f, 1.0f)
	CloseboxInst
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[512])
	DeclareVarInst(struct, float, fVec1[512])
	DeclareVarInst(struct, float, fVec2[512])
	DeclareVarInst(struct, float, fVec3[512])
	DeclareVarInst(struct, float, fVec4[512])
	DeclareVarInst(struct, float, fVec5[512])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph0)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph1)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph3)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph4)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph5)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph6)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph7)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph8)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph9)
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph10)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph11)
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph12)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph13)
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph14)
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph15)
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph16)
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph17)
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph18)
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph19)
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph20)
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph21)
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph22)
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph23)
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph24)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph25)
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph26)
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph27)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph28)
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph29)
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph30)
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph31)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph32)
	DeclareVarInst(struct, float, fRec33[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph33)
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph34)
	DeclareVarInst(struct, float, fRec35[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph35)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(6))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(36))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getInputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 1
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 2
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 3
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 4
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 5
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Default 
				BlockInst 
					StoreVarInst(stack, rate, Int32(-1))
					EndBlock
				EndCase
			EndSWitch
		RetInst(LoadVarInst(stack, rate))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getOutputRate", "int", channel)
	BlockInst 
		DeclareVarInst(stack, "int", rate)
		SwitchInst LoadVarInst(kFunArgs, channel)
			Case 0
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 1
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 2
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 3
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 4
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 5
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 6
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 7
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 8
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 9
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 10
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 11
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 12
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 13
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 14
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 15
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 16
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 17
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 18
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 19
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 20
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 21
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 22
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 23
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 24
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 25
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 26
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 27
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 28
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 29
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 30
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 31
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 32
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 33
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 34
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Case 35
				BlockInst 
					StoreVarInst(stack, rate, Int32(1))
					EndBlock
				EndCase
			Default 
				BlockInst 
					StoreVarInst(stack, rate, Int32(-1))
					EndBlock
				EndCase
			EndSWitch
		RetInst(LoadVarInst(stack, rate))
		EndBlock
	EndDeclare

======= Init ==========

BlockInst 
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(96.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	EndBlock

======= Clear ==========

BlockInst 
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(512))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(512))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(512))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(512))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(512))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(512))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(2))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(2))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 42
Store = 0
Binop = 0
Numbers = 0
Declare = 42
Cast = 0
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output8, LoadVarInst(kFunArgs, outputs[Int32(8)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output9, LoadVarInst(kFunArgs, outputs[Int32(9)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output10, LoadVarInst(kFunArgs, outputs[Int32(10)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output11, LoadVarInst(kFunArgs, outputs[Int32(11)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output12, LoadVarInst(kFunArgs, outputs[Int32(12)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output13, LoadVarInst(kFunArgs, outputs[Int32(13)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output14, LoadVarInst(kFunArgs, outputs[Int32(14)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output15, LoadVarInst(kFunArgs, outputs[Int32(15)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output16, LoadVarInst(kFunArgs, outputs[Int32(16)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output17, LoadVarInst(kFunArgs, outputs[Int32(17)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output18, LoadVarInst(kFunArgs, outputs[Int32(18)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output19, LoadVarInst(kFunArgs, outputs[Int32(19)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output20, LoadVarInst(kFunArgs, outputs[Int32(20)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output21, LoadVarInst(kFunArgs, outputs[Int32(21)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output22, LoadVarInst(kFunArgs, outputs[Int32(22)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output23, LoadVarInst(kFunArgs, outputs[Int32(23)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output24, LoadVarInst(kFunArgs, outputs[Int32(24)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output25, LoadVarInst(kFunArgs, outputs[Int32(25)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output26, LoadVarInst(kFunArgs, outputs[Int32(26)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output27, LoadVarInst(kFunArgs, outputs[Int32(27)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output28, LoadVarInst(kFunArgs, outputs[Int32(28)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output29, LoadVarInst(kFunArgs, outputs[Int32(29)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output30, LoadVarInst(kFunArgs, outputs[Int32(30)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output31, LoadVarInst(kFunArgs, outputs[Int32(31)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output32, LoadVarInst(kFunArgs, outputs[Int32(32)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output33, LoadVarInst(kFunArgs, outputs[Int32(33)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output34, LoadVarInst(kFunArgs, outputs[Int32(34)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output35, LoadVarInst(kFunArgs, outputs[Int32(35)]))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 442
Store = 152
Binop = 204
Numbers = 81
Declare = 16
Cast = 78
Select = 0
Loop = 1
Funcall = 72

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fTemp0))
		DeclareVarInst(stack, "float", fTemp1, CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fTemp1))
		DeclareVarInst(stack, "float", fTemp2, CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fTemp2))
		DeclareVarInst(stack, "float", fTemp3, CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fTemp3))
		DeclareVarInst(stack, "float", fTemp4, CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)])))
		StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fTemp4))
		StoreVarInst(struct, fRec0[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(244)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(233)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(221)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(209)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(197)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph0, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec0[Int32(0)])))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph0)))
		DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(246)), Int32(511))])))
		StoreVarInst(struct, fRec1[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp5), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(236)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(225)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(215)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(204)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph1, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec1[Int32(0)])))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph1)))
		StoreVarInst(struct, fRec2[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(247)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(230)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(220)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(211)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph2, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec2[Int32(0)])))
		StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph2)))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(249)), Int32(511))])))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(241)), Int32(511))])))
		StoreVarInst(struct, fRec3[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(233)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(225)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(217)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph3, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec3[Int32(0)])))
		StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph3)))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(250)), Int32(511))])))
		StoreVarInst(struct, fRec4[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(243)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(236)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(229)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(222)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph4, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec4[Int32(0)])))
		StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph4)))
		StoreVarInst(struct, fRec5[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(245)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(232)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(225)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph5, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec5[Int32(0)])))
		StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph5)))
		StoreVarInst(struct, fRec6[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp5), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(235)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(224)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(213)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(201)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph6, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec6[Int32(0)])))
		StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph6)))
		StoreVarInst(struct, fRec7[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(221)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(248)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(211)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(230)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))])))))))))
		StoreVarInst(struct, fVbargraph7, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec7[Int32(0)])))
		StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph7)))
		StoreVarInst(struct, fRec8[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(243)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(235)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(227)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(219)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph8, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec8[Int32(0)])))
		StoreVarInst(stack, output8[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph8)))
		StoreVarInst(struct, fRec9[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(225)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(232)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(245)), Int32(511))])))))))))
		StoreVarInst(struct, fVbargraph9, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec9[Int32(0)])))
		StoreVarInst(stack, output9[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph9)))
		StoreVarInst(struct, fRec10[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(247)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(241)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(236)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(230)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph10, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec10[Int32(0)])))
		StoreVarInst(stack, output10[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph10)))
		DeclareVarInst(stack, "float", fTemp9, BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(252)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(248)), Int32(511))])))
		StoreVarInst(struct, fRec11[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(243)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(238)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(233)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph11, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec11[Int32(0)])))
		StoreVarInst(stack, output11[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph11)))
		StoreVarInst(struct, fRec12[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec12[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(232)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(223)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(212)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph12, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec12[Int32(0)])))
		StoreVarInst(stack, output12[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph12)))
		StoreVarInst(struct, fRec13[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec13[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(224)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(240)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(246)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(232)), Int32(511))])))))))))
		StoreVarInst(struct, fVbargraph13, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec13[Int32(0)])))
		StoreVarInst(stack, output13[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph13)))
		StoreVarInst(struct, fRec14[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(231)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(244)), Int32(511))]), BinopInst("+", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(238)), Int32(511))])))))))
		StoreVarInst(struct, fVbargraph14, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec14[Int32(0)])))
		StoreVarInst(stack, output14[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph14)))
		StoreVarInst(struct, fRec15[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec15[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(253)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(250)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(246)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(241)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(236)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph15, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec15[Int32(0)])))
		StoreVarInst(stack, output15[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph15)))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(254)), Int32(511))])))
		StoreVarInst(struct, fRec16[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp10), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(248)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(244)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph16, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec16[Int32(0)])))
		StoreVarInst(stack, output16[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph16)))
		StoreVarInst(struct, fRec17[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec17[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp10), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(252)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(249)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(245)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(242)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph17, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec17[Int32(0)])))
		StoreVarInst(stack, output17[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph17)))
		StoreVarInst(struct, fRec18[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec18[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(246)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(252)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(257)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))])))))))))
		StoreVarInst(struct, fVbargraph18, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec18[Int32(0)])))
		StoreVarInst(stack, output18[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph18)))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]))))
		StoreVarInst(struct, fRec19[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec19[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(245)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(250)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(253)), Int32(511))]), LoadVarInst(stack, fTemp11)))))))
		StoreVarInst(struct, fVbargraph19, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec19[Int32(0)])))
		StoreVarInst(stack, output19[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph19)))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(stack, fTemp11), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(254)), Int32(511))])))
		StoreVarInst(struct, fRec20[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec20[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp12), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(247)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph20, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec20[Int32(0)])))
		StoreVarInst(stack, output20[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph20)))
		StoreVarInst(struct, fRec21[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec21[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp12), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(252)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(249)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph21, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec21[Int32(0)])))
		StoreVarInst(stack, output21[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph21)))
		StoreVarInst(struct, fRec22[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp12), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(253)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(250)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph22, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec22[Int32(0)])))
		StoreVarInst(stack, output22[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph22)))
		StoreVarInst(struct, fRec23[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec23[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(255)), Int32(511))]), BinopInst("+", LoadVarInst(stack, fTemp11), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(253)), Int32(511))])))))))
		StoreVarInst(struct, fVbargraph23, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec23[Int32(0)])))
		StoreVarInst(stack, output23[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph23)))
		StoreVarInst(struct, fRec24[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec24[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(263)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(270)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(274)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(276)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(276)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph24, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec24[Int32(0)])))
		StoreVarInst(stack, output24[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph24)))
		StoreVarInst(struct, fRec25[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec25[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(265)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(268)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(269)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(269)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph25, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec25[Int32(0)])))
		StoreVarInst(stack, output25[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph25)))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(260)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(263)), Int32(511))])))
		StoreVarInst(struct, fRec26[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec26[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp13), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(265)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(265)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(265)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph26, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec26[Int32(0)])))
		StoreVarInst(stack, output26[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph26)))
		StoreVarInst(struct, fRec27[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec27[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(259)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(263)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(263)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(263)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph27, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec27[Int32(0)])))
		StoreVarInst(stack, output27[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph27)))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(258)), Int32(511))])))
		StoreVarInst(struct, fRec28[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec28[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp14), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(260)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(262)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(262)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph28, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec28[Int32(0)])))
		StoreVarInst(stack, output28[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph28)))
		StoreVarInst(struct, fRec29[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec29[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp14), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(259)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(260)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph29, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec29[Int32(0)])))
		StoreVarInst(stack, output29[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph29)))
		StoreVarInst(struct, fRec30[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec30[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(266)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(276)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(285)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(293)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(300)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph30, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec30[Int32(0)])))
		StoreVarInst(stack, output30[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph30)))
		StoreVarInst(struct, fRec31[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec31[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(264)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(272)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(278)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(284)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(289)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph31, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec31[Int32(0)])))
		StoreVarInst(stack, output31[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph31)))
		StoreVarInst(struct, fRec32[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec32[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(262)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(268)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(273)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(278)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(281)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph32, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec32[Int32(0)])))
		StoreVarInst(stack, output32[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph32)))
		StoreVarInst(struct, fRec33[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec33[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(274)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(270)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(266)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(276)), Int32(511))])))))))))
		StoreVarInst(struct, fVbargraph33, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec33[Int32(0)])))
		StoreVarInst(stack, output33[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph33)))
		StoreVarInst(struct, fRec34[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec34[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(264)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(260)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(268)), Int32(511))])))), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(271)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(273)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph34, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec34[Int32(0)])))
		StoreVarInst(stack, output34[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph34)))
		StoreVarInst(struct, fRec35[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec35[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp13), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(266)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(268)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(270)), Int32(511))])))))
		StoreVarInst(struct, fVbargraph35, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec35[Int32(0)])))
		StoreVarInst(stack, output35[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph35)))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
		StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
		StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
		StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
		StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
		StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
		StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "fabsf", "float", dummy0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec0[512])
	DeclareVarInst(struct, float, fVec1[512])
	DeclareVarInst(struct, float, fVec2[512])
	DeclareVarInst(struct, float, fVec3[512])
	DeclareVarInst(struct, float, fVec4[512])
	DeclareVarInst(struct, float, fVec5[512])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph0)
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph1)
	DeclareVarInst(struct, float, fRec2[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph2)
	DeclareVarInst(struct, float, fRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph3)
	DeclareVarInst(struct, float, fRec4[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph4)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph5)
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph6)
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph7)
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph8)
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph9)
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph10)
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph11)
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph12)
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph13)
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph14)
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph15)
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph16)
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph17)
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph18)
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph19)
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph20)
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph21)
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph22)
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph23)
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph24)
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph25)
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph26)
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph27)
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph28)
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph29)
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph30)
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph31)
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph32)
	DeclareVarInst(struct, float, fRec33[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph33)
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph34)
	DeclareVarInst(struct, float, fRec35[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fVbargraph35)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, BinopInst("/", Float(96.0f), FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq))))))
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(512))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[LoadVarInst(loop, l0)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(512))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec1[LoadVarInst(loop, l1)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(512))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l2)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(512))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec3[LoadVarInst(loop, l3)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(512))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec4[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(512))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec5[LoadVarInst(loop, l5)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l6, Int32(0))
		BinopInst("<", LoadVarInst(loop, l6), Int32(2))
		StoreVarInst(loop, l6, BinopInst("+", LoadVarInst(loop, l6), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec0[LoadVarInst(loop, l6)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l7, Int32(0))
		BinopInst("<", LoadVarInst(loop, l7), Int32(2))
		StoreVarInst(loop, l7, BinopInst("+", LoadVarInst(loop, l7), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l7)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec2[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec3[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec4[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(2))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l12)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l14)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l15, Int32(0))
		BinopInst("<", LoadVarInst(loop, l15), Int32(2))
		StoreVarInst(loop, l15, BinopInst("+", LoadVarInst(loop, l15), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec9[LoadVarInst(loop, l15)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l16, Int32(0))
		BinopInst("<", LoadVarInst(loop, l16), Int32(2))
		StoreVarInst(loop, l16, BinopInst("+", LoadVarInst(loop, l16), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l16)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l20)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l21)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l22, Int32(0))
		BinopInst("<", LoadVarInst(loop, l22), Int32(2))
		StoreVarInst(loop, l22, BinopInst("+", LoadVarInst(loop, l22), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec16[LoadVarInst(loop, l22)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l23, Int32(0))
		BinopInst("<", LoadVarInst(loop, l23), Int32(2))
		StoreVarInst(loop, l23, BinopInst("+", LoadVarInst(loop, l23), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l24)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l28)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l29, Int32(0))
		BinopInst("<", LoadVarInst(loop, l29), Int32(2))
		StoreVarInst(loop, l29, BinopInst("+", LoadVarInst(loop, l29), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec23[LoadVarInst(loop, l29)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l30, Int32(0))
		BinopInst("<", LoadVarInst(loop, l30), Int32(2))
		StoreVarInst(loop, l30, BinopInst("+", LoadVarInst(loop, l30), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l32)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l36)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(2))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(2))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l40)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output8, LoadVarInst(kFunArgs, outputs[Int32(8)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output9, LoadVarInst(kFunArgs, outputs[Int32(9)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output10, LoadVarInst(kFunArgs, outputs[Int32(10)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output11, LoadVarInst(kFunArgs, outputs[Int32(11)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output12, LoadVarInst(kFunArgs, outputs[Int32(12)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output13, LoadVarInst(kFunArgs, outputs[Int32(13)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output14, LoadVarInst(kFunArgs, outputs[Int32(14)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output15, LoadVarInst(kFunArgs, outputs[Int32(15)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output16, LoadVarInst(kFunArgs, outputs[Int32(16)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output17, LoadVarInst(kFunArgs, outputs[Int32(17)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output18, LoadVarInst(kFunArgs, outputs[Int32(18)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output19, LoadVarInst(kFunArgs, outputs[Int32(19)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output20, LoadVarInst(kFunArgs, outputs[Int32(20)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output21, LoadVarInst(kFunArgs, outputs[Int32(21)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output22, LoadVarInst(kFunArgs, outputs[Int32(22)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output23, LoadVarInst(kFunArgs, outputs[Int32(23)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output24, LoadVarInst(kFunArgs, outputs[Int32(24)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output25, LoadVarInst(kFunArgs, outputs[Int32(25)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output26, LoadVarInst(kFunArgs, outputs[Int32(26)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output27, LoadVarInst(kFunArgs, outputs[Int32(27)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output28, LoadVarInst(kFunArgs, outputs[Int32(28)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output29, LoadVarInst(kFunArgs, outputs[Int32(29)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output30, LoadVarInst(kFunArgs, outputs[Int32(30)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output31, LoadVarInst(kFunArgs, outputs[Int32(31)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output32, LoadVarInst(kFunArgs, outputs[Int32(32)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output33, LoadVarInst(kFunArgs, outputs[Int32(33)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output34, LoadVarInst(kFunArgs, outputs[Int32(34)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output35, LoadVarInst(kFunArgs, outputs[Int32(35)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec0[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fVec1[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fTemp0))
			DeclareVarInst(stack, "float", fTemp1, CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fTemp1))
			DeclareVarInst(stack, "float", fTemp2, CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fVec3[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fTemp2))
			DeclareVarInst(stack, "float", fTemp3, CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fVec4[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fTemp3))
			DeclareVarInst(stack, "float", fTemp4, CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)])))
			StoreVarInst(struct, fVec5[BinopInst("&", LoadVarInst(struct, IOTA), Int32(511))], LoadVarInst(stack, fTemp4))
			StoreVarInst(struct, fRec0[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec0[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(244)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(233)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(221)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(209)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(197)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph0, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec0[Int32(0)])))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph0)))
			DeclareVarInst(stack, "float", fTemp5, BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(246)), Int32(511))])))
			StoreVarInst(struct, fRec1[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp5), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(236)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(225)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(215)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(204)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph1, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec1[Int32(0)])))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph1)))
			StoreVarInst(struct, fRec2[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec2[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(247)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(230)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(220)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(211)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph2, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec2[Int32(0)])))
			StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph2)))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(249)), Int32(511))])))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(241)), Int32(511))])))
			StoreVarInst(struct, fRec3[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec3[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(233)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(225)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(217)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph3, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec3[Int32(0)])))
			StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph3)))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(250)), Int32(511))])))
			StoreVarInst(struct, fRec4[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec4[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(243)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(236)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(229)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(222)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph4, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec4[Int32(0)])))
			StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph4)))
			StoreVarInst(struct, fRec5[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp8), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(245)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(232)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(225)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph5, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec5[Int32(0)])))
			StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph5)))
			StoreVarInst(struct, fRec6[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec6[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp5), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(235)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(224)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(213)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(201)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph6, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec6[Int32(0)])))
			StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph6)))
			StoreVarInst(struct, fRec7[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(221)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(248)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(211)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(230)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))])))))))))
			StoreVarInst(struct, fVbargraph7, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec7[Int32(0)])))
			StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph7)))
			StoreVarInst(struct, fRec8[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp6), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(243)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(235)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(227)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(219)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph8, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec8[Int32(0)])))
			StoreVarInst(stack, output8[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph8)))
			StoreVarInst(struct, fRec9[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec9[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(225)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(232)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(245)), Int32(511))])))))))))
			StoreVarInst(struct, fVbargraph9, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec9[Int32(0)])))
			StoreVarInst(stack, output9[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph9)))
			StoreVarInst(struct, fRec10[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(247)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(241)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(236)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(230)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph10, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec10[Int32(0)])))
			StoreVarInst(stack, output10[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph10)))
			DeclareVarInst(stack, "float", fTemp9, BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(252)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(248)), Int32(511))])))
			StoreVarInst(struct, fRec11[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(243)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(238)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(233)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph11, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec11[Int32(0)])))
			StoreVarInst(stack, output11[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph11)))
			StoreVarInst(struct, fRec12[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec12[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp7), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(232)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(223)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(212)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph12, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec12[Int32(0)])))
			StoreVarInst(stack, output12[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph12)))
			StoreVarInst(struct, fRec13[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec13[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(224)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(240)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(246)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(232)), Int32(511))])))))))))
			StoreVarInst(struct, fVbargraph13, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec13[Int32(0)])))
			StoreVarInst(stack, output13[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph13)))
			StoreVarInst(struct, fRec14[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(231)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(244)), Int32(511))]), BinopInst("+", LoadVarInst(stack, fTemp9), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(238)), Int32(511))])))))))
			StoreVarInst(struct, fVbargraph14, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec14[Int32(0)])))
			StoreVarInst(stack, output14[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph14)))
			StoreVarInst(struct, fRec15[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec15[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(253)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(250)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(246)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(241)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(236)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph15, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec15[Int32(0)])))
			StoreVarInst(stack, output15[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph15)))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(254)), Int32(511))])))
			StoreVarInst(struct, fRec16[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp10), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(248)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(244)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph16, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec16[Int32(0)])))
			StoreVarInst(stack, output16[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph16)))
			StoreVarInst(struct, fRec17[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec17[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp10), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(252)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(249)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(245)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(242)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph17, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec17[Int32(0)])))
			StoreVarInst(stack, output17[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph17)))
			StoreVarInst(struct, fRec18[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec18[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(246)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(252)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(257)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(239)), Int32(511))])))))))))
			StoreVarInst(struct, fVbargraph18, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec18[Int32(0)])))
			StoreVarInst(stack, output18[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph18)))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]))))
			StoreVarInst(struct, fRec19[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec19[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(245)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(250)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(253)), Int32(511))]), LoadVarInst(stack, fTemp11)))))))
			StoreVarInst(struct, fVbargraph19, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec19[Int32(0)])))
			StoreVarInst(stack, output19[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph19)))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("+", LoadVarInst(stack, fTemp11), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(254)), Int32(511))])))
			StoreVarInst(struct, fRec20[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec20[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp12), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(247)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph20, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec20[Int32(0)])))
			StoreVarInst(stack, output20[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph20)))
			StoreVarInst(struct, fRec21[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec21[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp12), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(252)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(249)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph21, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec21[Int32(0)])))
			StoreVarInst(stack, output21[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph21)))
			StoreVarInst(struct, fRec22[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp12), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(253)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(250)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph22, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec22[Int32(0)])))
			StoreVarInst(stack, output22[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph22)))
			StoreVarInst(struct, fRec23[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec23[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(251)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(255)), Int32(511))]), BinopInst("+", LoadVarInst(stack, fTemp11), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(253)), Int32(511))])))))))
			StoreVarInst(struct, fVbargraph23, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec23[Int32(0)])))
			StoreVarInst(stack, output23[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph23)))
			StoreVarInst(struct, fRec24[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec24[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(263)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(270)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(274)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(276)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(276)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph24, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec24[Int32(0)])))
			StoreVarInst(stack, output24[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph24)))
			StoreVarInst(struct, fRec25[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec25[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(265)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(268)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(269)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(269)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph25, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec25[Int32(0)])))
			StoreVarInst(stack, output25[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph25)))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(260)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(263)), Int32(511))])))
			StoreVarInst(struct, fRec26[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec26[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp13), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(265)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(265)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(265)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph26, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec26[Int32(0)])))
			StoreVarInst(stack, output26[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph26)))
			StoreVarInst(struct, fRec27[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec27[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(259)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(263)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(263)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(263)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph27, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec27[Int32(0)])))
			StoreVarInst(stack, output27[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph27)))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(258)), Int32(511))])))
			StoreVarInst(struct, fRec28[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec28[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp14), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(260)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(262)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(262)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph28, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec28[Int32(0)])))
			StoreVarInst(stack, output28[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph28)))
			StoreVarInst(struct, fRec29[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec29[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp14), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(259)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(260)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph29, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec29[Int32(0)])))
			StoreVarInst(stack, output29[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph29)))
			StoreVarInst(struct, fRec30[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec30[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(266)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(276)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(285)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(293)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(300)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph30, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec30[Int32(0)])))
			StoreVarInst(stack, output30[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph30)))
			StoreVarInst(struct, fRec31[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec31[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(264)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(272)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(278)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(284)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(289)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph31, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec31[Int32(0)])))
			StoreVarInst(stack, output31[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph31)))
			StoreVarInst(struct, fRec32[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec32[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(262)), Int32(511))])), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(268)), Int32(511))])), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(273)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(278)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(281)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph32, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec32[Int32(0)])))
			StoreVarInst(stack, output32[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph32)))
			StoreVarInst(struct, fRec33[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec33[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(274)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(270)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(266)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(261)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(276)), Int32(511))])))))))))
			StoreVarInst(struct, fVbargraph33, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec33[Int32(0)])))
			StoreVarInst(stack, output33[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph33)))
			StoreVarInst(struct, fRec34[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec34[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(264)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec1[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(260)), Int32(511))]), BinopInst("+", LoadVarInst(struct, fVec0[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(256)), Int32(511))]), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(268)), Int32(511))])))), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(271)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(273)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph34, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec34[Int32(0)])))
			StoreVarInst(stack, output34[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph34)))
			StoreVarInst(struct, fRec35[Int32(0)], FunCallInst("max_f", BinopInst("-", LoadVarInst(struct, fRec35[Int32(1)]), LoadVarInst(struct, fConst0)), FunCallInst("fabsf", BinopInst("+", BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp13), LoadVarInst(struct, fVec3[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(266)), Int32(511))])), LoadVarInst(struct, fVec4[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(268)), Int32(511))])), LoadVarInst(struct, fVec5[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), Int32(270)), Int32(511))])))))
			StoreVarInst(struct, fVbargraph35, CastInst("FAUSTFLOAT", LoadVarInst(struct, fRec35[Int32(0)])))
			StoreVarInst(stack, output35[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", LoadVarInst(struct, fVbargraph35)))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec2[Int32(1)], LoadVarInst(struct, fRec2[Int32(0)]))
			StoreVarInst(struct, fRec3[Int32(1)], LoadVarInst(struct, fRec3[Int32(0)]))
			StoreVarInst(struct, fRec4[Int32(1)], LoadVarInst(struct, fRec4[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
			StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
			StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
			StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
			StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 8 bytes
Heap size int* = 0 bytes
Heap size real = 12724 bytes
Heap size = 12732 bytes
Stack size in compute = 336 bytes

