======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("granulator1")
	AddHorizontalSlider("lim1", fHslider1, 0.0f, 0.0f, 10000.0f, 1.0f)
	AddHorizontalSlider("lim2", fHslider2, 0.0f, 0.0f, 10000.0f, 1.0f)
	AddHorizontalSlider("vol", fHslider0, 0.0f, 0.0f, 1.0f, 0.00999999978f)
	CloseboxInst
	EndBlock

======= Global declarations ==========

BlockInst 
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "int", iConst1)
	DeclareVarInst(struct, int, iRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, int, iRec4[2])
	DeclareVarInst(struct, int, iRec2[2])
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, int, iVec1[2])
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec2[524288])
	DeclareVarInst(struct, "int", iConst4)
	DeclareVarInst(struct, int, iVec3[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "int", iConst5)
	DeclareVarInst(struct, int, iVec4[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "int", iConst6)
	DeclareVarInst(struct, int, iVec5[2])
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, int, iVec6[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, "int", iConst8)
	DeclareVarInst(struct, int, iVec7[2])
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, "int", iConst9)
	DeclareVarInst(struct, int, iVec8[2])
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, "int", iConst10)
	DeclareVarInst(struct, int, iVec9[2])
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, "int", iConst11)
	DeclareVarInst(struct, int, iVec10[2])
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, "int", iConst12)
	DeclareVarInst(struct, int, iVec11[2])
	DeclareVarInst(struct, float, fRec35[2])
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, float, fRec33[2])
	DeclareVarInst(struct, "int", iConst13)
	DeclareVarInst(struct, int, iVec12[2])
	DeclareVarInst(struct, float, fRec38[2])
	DeclareVarInst(struct, float, fRec37[2])
	DeclareVarInst(struct, float, fRec36[2])
	DeclareVarInst(struct, "int", iConst14)
	DeclareVarInst(struct, int, iVec13[2])
	DeclareVarInst(struct, float, fRec41[2])
	DeclareVarInst(struct, float, fRec40[2])
	DeclareVarInst(struct, float, fRec39[2])
	DeclareVarInst(struct, "int", iConst15)
	DeclareVarInst(struct, int, iVec14[2])
	DeclareVarInst(struct, float, fRec44[2])
	DeclareVarInst(struct, float, fRec43[2])
	DeclareVarInst(struct, float, fRec42[2])
	DeclareVarInst(struct, "int", iConst16)
	DeclareVarInst(struct, int, iVec15[2])
	DeclareVarInst(struct, float, fRec47[2])
	DeclareVarInst(struct, float, fRec46[2])
	DeclareVarInst(struct, float, fRec45[2])
	DeclareVarInst(struct, "int", iConst17)
	DeclareVarInst(struct, int, iVec16[2])
	DeclareVarInst(struct, float, fRec50[2])
	DeclareVarInst(struct, float, fRec49[2])
	DeclareVarInst(struct, float, fRec48[2])
	DeclareVarInst(struct, "int", iConst18)
	DeclareVarInst(struct, int, iVec17[2])
	DeclareVarInst(struct, float, fRec53[2])
	DeclareVarInst(struct, float, fRec52[2])
	DeclareVarInst(struct, float, fRec51[2])
	DeclareVarInst(struct, "int", iConst19)
	DeclareVarInst(struct, int, iVec18[2])
	DeclareVarInst(struct, float, fRec56[2])
	DeclareVarInst(struct, float, fRec55[2])
	DeclareVarInst(struct, float, fRec54[2])
	DeclareVarInst(struct, "int", iConst20)
	DeclareVarInst(struct, int, iVec19[2])
	DeclareVarInst(struct, float, fRec59[2])
	DeclareVarInst(struct, float, fRec58[2])
	DeclareVarInst(struct, float, fRec57[2])
	DeclareVarInst(struct, "int", iConst21)
	DeclareVarInst(struct, int, iVec20[2])
	DeclareVarInst(struct, float, fRec62[2])
	DeclareVarInst(struct, float, fRec61[2])
	DeclareVarInst(struct, float, fRec60[2])
	DeclareVarInst(struct, "int", iConst22)
	DeclareVarInst(struct, int, iVec21[2])
	DeclareVarInst(struct, float, fRec65[2])
	DeclareVarInst(struct, float, fRec64[2])
	DeclareVarInst(struct, float, fRec63[2])
	DeclareVarInst(struct, "int", iConst23)
	DeclareVarInst(struct, int, iVec22[2])
	DeclareVarInst(struct, float, fRec68[2])
	DeclareVarInst(struct, float, fRec67[2])
	DeclareVarInst(struct, float, fRec66[2])
	DeclareVarInst(struct, "int", iConst24)
	DeclareVarInst(struct, int, iVec23[2])
	DeclareVarInst(struct, float, fRec71[2])
	DeclareVarInst(struct, float, fRec70[2])
	DeclareVarInst(struct, float, fRec69[2])
	DeclareVarInst(struct, "int", iConst25)
	DeclareVarInst(struct, int, iVec24[2])
	DeclareVarInst(struct, float, fRec74[2])
	DeclareVarInst(struct, float, fRec73[2])
	DeclareVarInst(struct, float, fRec72[2])
	DeclareVarInst(struct, "int", iConst26)
	DeclareVarInst(struct, int, iVec25[2])
	DeclareVarInst(struct, float, fRec77[2])
	DeclareVarInst(struct, float, fRec76[2])
	DeclareVarInst(struct, float, fRec75[2])
	DeclareVarInst(struct, "int", iConst27)
	DeclareVarInst(struct, int, iVec26[2])
	DeclareVarInst(struct, float, fRec80[2])
	DeclareVarInst(struct, float, fRec79[2])
	DeclareVarInst(struct, float, fRec78[2])
	DeclareVarInst(struct, "int", iConst28)
	DeclareVarInst(struct, int, iVec27[2])
	DeclareVarInst(struct, float, fRec83[2])
	DeclareVarInst(struct, float, fRec82[2])
	DeclareVarInst(struct, float, fRec81[2])
	DeclareVarInst(struct, "int", iConst29)
	DeclareVarInst(struct, int, iVec28[2])
	DeclareVarInst(struct, float, fRec86[2])
	DeclareVarInst(struct, float, fRec85[2])
	DeclareVarInst(struct, float, fRec84[2])
	DeclareVarInst(struct, "int", iConst30)
	DeclareVarInst(struct, int, iVec29[2])
	DeclareVarInst(struct, float, fRec89[2])
	DeclareVarInst(struct, float, fRec88[2])
	DeclareVarInst(struct, float, fRec87[2])
	DeclareVarInst(struct, "int", iConst31)
	DeclareVarInst(struct, int, iVec30[2])
	DeclareVarInst(struct, float, fRec92[2])
	DeclareVarInst(struct, float, fRec91[2])
	DeclareVarInst(struct, float, fRec90[2])
	DeclareVarInst(struct, "int", iConst32)
	DeclareVarInst(struct, int, iVec31[2])
	DeclareVarInst(struct, float, fRec95[2])
	DeclareVarInst(struct, float, fRec94[2])
	DeclareVarInst(struct, float, fRec93[2])
	DeclareVarInst(struct, "int", iConst33)
	DeclareVarInst(struct, int, iVec32[2])
	DeclareVarInst(struct, float, fRec98[2])
	DeclareVarInst(struct, float, fRec97[2])
	DeclareVarInst(struct, float, fRec96[2])
	DeclareVarInst(struct, "int", iConst34)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(1))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(2))
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
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, iConst1, CastInst("int", BinopInst("*", Float(0.00729927002f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(4.0f), BinopInst("/", BinopInst("-", Float(20.0f), BinopInst("/", Float(400.0f), LoadVarInst(struct, fConst0))), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(3200.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst4, BinopInst("&", CastInst("int", BinopInst("*", Float(0.3125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst5, BinopInst("&", CastInst("int", BinopInst("*", Float(0.625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst6, BinopInst("&", CastInst("int", BinopInst("*", Float(0.9375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst7, BinopInst("&", CastInst("int", BinopInst("*", Float(1.25f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst8, BinopInst("&", CastInst("int", BinopInst("*", Float(1.5625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst9, BinopInst("&", CastInst("int", BinopInst("*", Float(1.875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst10, BinopInst("&", CastInst("int", BinopInst("*", Float(2.1875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst11, BinopInst("&", CastInst("int", BinopInst("*", Float(2.5f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst12, BinopInst("&", CastInst("int", BinopInst("*", Float(2.8125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst13, BinopInst("&", CastInst("int", BinopInst("*", Float(3.125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst14, BinopInst("&", CastInst("int", BinopInst("*", Float(3.4375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst15, BinopInst("&", CastInst("int", BinopInst("*", Float(3.75f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst16, BinopInst("&", CastInst("int", BinopInst("*", Float(4.0625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst17, BinopInst("&", CastInst("int", BinopInst("*", Float(4.375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst18, BinopInst("&", CastInst("int", BinopInst("*", Float(4.6875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst19, BinopInst("&", CastInst("int", BinopInst("*", Float(0.15625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst20, BinopInst("&", CastInst("int", BinopInst("*", Float(0.46875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst21, BinopInst("&", CastInst("int", BinopInst("*", Float(0.78125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst22, BinopInst("&", CastInst("int", BinopInst("*", Float(1.09375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst23, BinopInst("&", CastInst("int", BinopInst("*", Float(1.40625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst24, BinopInst("&", CastInst("int", BinopInst("*", Float(1.71875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst25, BinopInst("&", CastInst("int", BinopInst("*", Float(2.03125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst26, BinopInst("&", CastInst("int", BinopInst("*", Float(2.34375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst27, BinopInst("&", CastInst("int", BinopInst("*", Float(2.65625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst28, BinopInst("&", CastInst("int", BinopInst("*", Float(2.96875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst29, BinopInst("&", CastInst("int", BinopInst("*", Float(3.28125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst30, BinopInst("&", CastInst("int", BinopInst("*", Float(3.59375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst31, BinopInst("&", CastInst("int", BinopInst("*", Float(3.90625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst32, BinopInst("&", CastInst("int", BinopInst("*", Float(4.21875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst33, BinopInst("&", CastInst("int", BinopInst("*", Float(4.53125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst34, BinopInst("&", CastInst("int", BinopInst("*", Float(4.84375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	EndBlock

======= ResetUI ==========

BlockInst 
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	EndBlock

======= Clear ==========

BlockInst 
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec3[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec4[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec2[LoadVarInst(loop, l2)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l3)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l5)], Float(0.0f))
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
			StoreVarInst(struct, iVec1[LoadVarInst(loop, l7)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(524288))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec3[LoadVarInst(loop, l12)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l14)], Float(0.0f))
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
			StoreVarInst(struct, iVec4[LoadVarInst(loop, l16)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec5[LoadVarInst(loop, l20)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l21)], Float(0.0f))
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
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec6[LoadVarInst(loop, l24)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec7[LoadVarInst(loop, l28)], Int32(0))
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
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec8[LoadVarInst(loop, l32)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec9[LoadVarInst(loop, l36)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(2))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(2))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec10[LoadVarInst(loop, l40)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(2))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(2))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec11[LoadVarInst(loop, l44)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(2))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(2))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(2))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec12[LoadVarInst(loop, l48)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(2))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec13[LoadVarInst(loop, l52)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(2))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(2))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(2))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(2))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec14[LoadVarInst(loop, l56)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(2))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(2))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l59, Int32(0))
		BinopInst("<", LoadVarInst(loop, l59), Int32(2))
		StoreVarInst(loop, l59, BinopInst("+", LoadVarInst(loop, l59), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l59)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l60, Int32(0))
		BinopInst("<", LoadVarInst(loop, l60), Int32(2))
		StoreVarInst(loop, l60, BinopInst("+", LoadVarInst(loop, l60), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec15[LoadVarInst(loop, l60)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l61, Int32(0))
		BinopInst("<", LoadVarInst(loop, l61), Int32(2))
		StoreVarInst(loop, l61, BinopInst("+", LoadVarInst(loop, l61), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l61)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l62, Int32(0))
		BinopInst("<", LoadVarInst(loop, l62), Int32(2))
		StoreVarInst(loop, l62, BinopInst("+", LoadVarInst(loop, l62), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l62)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l63, Int32(0))
		BinopInst("<", LoadVarInst(loop, l63), Int32(2))
		StoreVarInst(loop, l63, BinopInst("+", LoadVarInst(loop, l63), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l63)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l64, Int32(0))
		BinopInst("<", LoadVarInst(loop, l64), Int32(2))
		StoreVarInst(loop, l64, BinopInst("+", LoadVarInst(loop, l64), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec16[LoadVarInst(loop, l64)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l65, Int32(0))
		BinopInst("<", LoadVarInst(loop, l65), Int32(2))
		StoreVarInst(loop, l65, BinopInst("+", LoadVarInst(loop, l65), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l65)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l66, Int32(0))
		BinopInst("<", LoadVarInst(loop, l66), Int32(2))
		StoreVarInst(loop, l66, BinopInst("+", LoadVarInst(loop, l66), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l66)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l67, Int32(0))
		BinopInst("<", LoadVarInst(loop, l67), Int32(2))
		StoreVarInst(loop, l67, BinopInst("+", LoadVarInst(loop, l67), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l67)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l68, Int32(0))
		BinopInst("<", LoadVarInst(loop, l68), Int32(2))
		StoreVarInst(loop, l68, BinopInst("+", LoadVarInst(loop, l68), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec17[LoadVarInst(loop, l68)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l69, Int32(0))
		BinopInst("<", LoadVarInst(loop, l69), Int32(2))
		StoreVarInst(loop, l69, BinopInst("+", LoadVarInst(loop, l69), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec53[LoadVarInst(loop, l69)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l70, Int32(0))
		BinopInst("<", LoadVarInst(loop, l70), Int32(2))
		StoreVarInst(loop, l70, BinopInst("+", LoadVarInst(loop, l70), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec52[LoadVarInst(loop, l70)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l71, Int32(0))
		BinopInst("<", LoadVarInst(loop, l71), Int32(2))
		StoreVarInst(loop, l71, BinopInst("+", LoadVarInst(loop, l71), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l71)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l72, Int32(0))
		BinopInst("<", LoadVarInst(loop, l72), Int32(2))
		StoreVarInst(loop, l72, BinopInst("+", LoadVarInst(loop, l72), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec18[LoadVarInst(loop, l72)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l73, Int32(0))
		BinopInst("<", LoadVarInst(loop, l73), Int32(2))
		StoreVarInst(loop, l73, BinopInst("+", LoadVarInst(loop, l73), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec56[LoadVarInst(loop, l73)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l74, Int32(0))
		BinopInst("<", LoadVarInst(loop, l74), Int32(2))
		StoreVarInst(loop, l74, BinopInst("+", LoadVarInst(loop, l74), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec55[LoadVarInst(loop, l74)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l75, Int32(0))
		BinopInst("<", LoadVarInst(loop, l75), Int32(2))
		StoreVarInst(loop, l75, BinopInst("+", LoadVarInst(loop, l75), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec54[LoadVarInst(loop, l75)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l76, Int32(0))
		BinopInst("<", LoadVarInst(loop, l76), Int32(2))
		StoreVarInst(loop, l76, BinopInst("+", LoadVarInst(loop, l76), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec19[LoadVarInst(loop, l76)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l77, Int32(0))
		BinopInst("<", LoadVarInst(loop, l77), Int32(2))
		StoreVarInst(loop, l77, BinopInst("+", LoadVarInst(loop, l77), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l77)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l78, Int32(0))
		BinopInst("<", LoadVarInst(loop, l78), Int32(2))
		StoreVarInst(loop, l78, BinopInst("+", LoadVarInst(loop, l78), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec58[LoadVarInst(loop, l78)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l79, Int32(0))
		BinopInst("<", LoadVarInst(loop, l79), Int32(2))
		StoreVarInst(loop, l79, BinopInst("+", LoadVarInst(loop, l79), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec57[LoadVarInst(loop, l79)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l80, Int32(0))
		BinopInst("<", LoadVarInst(loop, l80), Int32(2))
		StoreVarInst(loop, l80, BinopInst("+", LoadVarInst(loop, l80), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec20[LoadVarInst(loop, l80)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l81, Int32(0))
		BinopInst("<", LoadVarInst(loop, l81), Int32(2))
		StoreVarInst(loop, l81, BinopInst("+", LoadVarInst(loop, l81), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec62[LoadVarInst(loop, l81)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l82, Int32(0))
		BinopInst("<", LoadVarInst(loop, l82), Int32(2))
		StoreVarInst(loop, l82, BinopInst("+", LoadVarInst(loop, l82), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec61[LoadVarInst(loop, l82)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l83, Int32(0))
		BinopInst("<", LoadVarInst(loop, l83), Int32(2))
		StoreVarInst(loop, l83, BinopInst("+", LoadVarInst(loop, l83), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l83)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l84, Int32(0))
		BinopInst("<", LoadVarInst(loop, l84), Int32(2))
		StoreVarInst(loop, l84, BinopInst("+", LoadVarInst(loop, l84), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec21[LoadVarInst(loop, l84)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l85, Int32(0))
		BinopInst("<", LoadVarInst(loop, l85), Int32(2))
		StoreVarInst(loop, l85, BinopInst("+", LoadVarInst(loop, l85), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec65[LoadVarInst(loop, l85)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l86, Int32(0))
		BinopInst("<", LoadVarInst(loop, l86), Int32(2))
		StoreVarInst(loop, l86, BinopInst("+", LoadVarInst(loop, l86), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec64[LoadVarInst(loop, l86)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l87, Int32(0))
		BinopInst("<", LoadVarInst(loop, l87), Int32(2))
		StoreVarInst(loop, l87, BinopInst("+", LoadVarInst(loop, l87), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec63[LoadVarInst(loop, l87)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l88, Int32(0))
		BinopInst("<", LoadVarInst(loop, l88), Int32(2))
		StoreVarInst(loop, l88, BinopInst("+", LoadVarInst(loop, l88), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec22[LoadVarInst(loop, l88)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l89, Int32(0))
		BinopInst("<", LoadVarInst(loop, l89), Int32(2))
		StoreVarInst(loop, l89, BinopInst("+", LoadVarInst(loop, l89), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec68[LoadVarInst(loop, l89)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l90, Int32(0))
		BinopInst("<", LoadVarInst(loop, l90), Int32(2))
		StoreVarInst(loop, l90, BinopInst("+", LoadVarInst(loop, l90), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec67[LoadVarInst(loop, l90)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l91, Int32(0))
		BinopInst("<", LoadVarInst(loop, l91), Int32(2))
		StoreVarInst(loop, l91, BinopInst("+", LoadVarInst(loop, l91), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec66[LoadVarInst(loop, l91)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l92, Int32(0))
		BinopInst("<", LoadVarInst(loop, l92), Int32(2))
		StoreVarInst(loop, l92, BinopInst("+", LoadVarInst(loop, l92), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec23[LoadVarInst(loop, l92)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l93, Int32(0))
		BinopInst("<", LoadVarInst(loop, l93), Int32(2))
		StoreVarInst(loop, l93, BinopInst("+", LoadVarInst(loop, l93), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec71[LoadVarInst(loop, l93)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l94, Int32(0))
		BinopInst("<", LoadVarInst(loop, l94), Int32(2))
		StoreVarInst(loop, l94, BinopInst("+", LoadVarInst(loop, l94), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec70[LoadVarInst(loop, l94)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l95, Int32(0))
		BinopInst("<", LoadVarInst(loop, l95), Int32(2))
		StoreVarInst(loop, l95, BinopInst("+", LoadVarInst(loop, l95), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec69[LoadVarInst(loop, l95)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l96, Int32(0))
		BinopInst("<", LoadVarInst(loop, l96), Int32(2))
		StoreVarInst(loop, l96, BinopInst("+", LoadVarInst(loop, l96), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec24[LoadVarInst(loop, l96)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l97, Int32(0))
		BinopInst("<", LoadVarInst(loop, l97), Int32(2))
		StoreVarInst(loop, l97, BinopInst("+", LoadVarInst(loop, l97), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec74[LoadVarInst(loop, l97)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l98, Int32(0))
		BinopInst("<", LoadVarInst(loop, l98), Int32(2))
		StoreVarInst(loop, l98, BinopInst("+", LoadVarInst(loop, l98), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec73[LoadVarInst(loop, l98)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l99, Int32(0))
		BinopInst("<", LoadVarInst(loop, l99), Int32(2))
		StoreVarInst(loop, l99, BinopInst("+", LoadVarInst(loop, l99), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec72[LoadVarInst(loop, l99)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l100, Int32(0))
		BinopInst("<", LoadVarInst(loop, l100), Int32(2))
		StoreVarInst(loop, l100, BinopInst("+", LoadVarInst(loop, l100), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec25[LoadVarInst(loop, l100)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l101, Int32(0))
		BinopInst("<", LoadVarInst(loop, l101), Int32(2))
		StoreVarInst(loop, l101, BinopInst("+", LoadVarInst(loop, l101), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec77[LoadVarInst(loop, l101)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l102, Int32(0))
		BinopInst("<", LoadVarInst(loop, l102), Int32(2))
		StoreVarInst(loop, l102, BinopInst("+", LoadVarInst(loop, l102), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec76[LoadVarInst(loop, l102)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l103, Int32(0))
		BinopInst("<", LoadVarInst(loop, l103), Int32(2))
		StoreVarInst(loop, l103, BinopInst("+", LoadVarInst(loop, l103), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec75[LoadVarInst(loop, l103)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l104, Int32(0))
		BinopInst("<", LoadVarInst(loop, l104), Int32(2))
		StoreVarInst(loop, l104, BinopInst("+", LoadVarInst(loop, l104), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec26[LoadVarInst(loop, l104)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l105, Int32(0))
		BinopInst("<", LoadVarInst(loop, l105), Int32(2))
		StoreVarInst(loop, l105, BinopInst("+", LoadVarInst(loop, l105), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec80[LoadVarInst(loop, l105)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l106, Int32(0))
		BinopInst("<", LoadVarInst(loop, l106), Int32(2))
		StoreVarInst(loop, l106, BinopInst("+", LoadVarInst(loop, l106), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec79[LoadVarInst(loop, l106)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l107, Int32(0))
		BinopInst("<", LoadVarInst(loop, l107), Int32(2))
		StoreVarInst(loop, l107, BinopInst("+", LoadVarInst(loop, l107), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec78[LoadVarInst(loop, l107)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l108, Int32(0))
		BinopInst("<", LoadVarInst(loop, l108), Int32(2))
		StoreVarInst(loop, l108, BinopInst("+", LoadVarInst(loop, l108), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec27[LoadVarInst(loop, l108)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l109, Int32(0))
		BinopInst("<", LoadVarInst(loop, l109), Int32(2))
		StoreVarInst(loop, l109, BinopInst("+", LoadVarInst(loop, l109), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec83[LoadVarInst(loop, l109)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l110, Int32(0))
		BinopInst("<", LoadVarInst(loop, l110), Int32(2))
		StoreVarInst(loop, l110, BinopInst("+", LoadVarInst(loop, l110), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec82[LoadVarInst(loop, l110)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l111, Int32(0))
		BinopInst("<", LoadVarInst(loop, l111), Int32(2))
		StoreVarInst(loop, l111, BinopInst("+", LoadVarInst(loop, l111), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec81[LoadVarInst(loop, l111)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l112, Int32(0))
		BinopInst("<", LoadVarInst(loop, l112), Int32(2))
		StoreVarInst(loop, l112, BinopInst("+", LoadVarInst(loop, l112), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec28[LoadVarInst(loop, l112)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l113, Int32(0))
		BinopInst("<", LoadVarInst(loop, l113), Int32(2))
		StoreVarInst(loop, l113, BinopInst("+", LoadVarInst(loop, l113), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec86[LoadVarInst(loop, l113)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l114, Int32(0))
		BinopInst("<", LoadVarInst(loop, l114), Int32(2))
		StoreVarInst(loop, l114, BinopInst("+", LoadVarInst(loop, l114), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec85[LoadVarInst(loop, l114)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l115, Int32(0))
		BinopInst("<", LoadVarInst(loop, l115), Int32(2))
		StoreVarInst(loop, l115, BinopInst("+", LoadVarInst(loop, l115), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec84[LoadVarInst(loop, l115)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l116, Int32(0))
		BinopInst("<", LoadVarInst(loop, l116), Int32(2))
		StoreVarInst(loop, l116, BinopInst("+", LoadVarInst(loop, l116), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec29[LoadVarInst(loop, l116)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l117, Int32(0))
		BinopInst("<", LoadVarInst(loop, l117), Int32(2))
		StoreVarInst(loop, l117, BinopInst("+", LoadVarInst(loop, l117), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec89[LoadVarInst(loop, l117)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l118, Int32(0))
		BinopInst("<", LoadVarInst(loop, l118), Int32(2))
		StoreVarInst(loop, l118, BinopInst("+", LoadVarInst(loop, l118), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec88[LoadVarInst(loop, l118)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l119, Int32(0))
		BinopInst("<", LoadVarInst(loop, l119), Int32(2))
		StoreVarInst(loop, l119, BinopInst("+", LoadVarInst(loop, l119), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec87[LoadVarInst(loop, l119)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l120, Int32(0))
		BinopInst("<", LoadVarInst(loop, l120), Int32(2))
		StoreVarInst(loop, l120, BinopInst("+", LoadVarInst(loop, l120), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec30[LoadVarInst(loop, l120)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l121, Int32(0))
		BinopInst("<", LoadVarInst(loop, l121), Int32(2))
		StoreVarInst(loop, l121, BinopInst("+", LoadVarInst(loop, l121), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec92[LoadVarInst(loop, l121)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l122, Int32(0))
		BinopInst("<", LoadVarInst(loop, l122), Int32(2))
		StoreVarInst(loop, l122, BinopInst("+", LoadVarInst(loop, l122), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec91[LoadVarInst(loop, l122)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l123, Int32(0))
		BinopInst("<", LoadVarInst(loop, l123), Int32(2))
		StoreVarInst(loop, l123, BinopInst("+", LoadVarInst(loop, l123), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec90[LoadVarInst(loop, l123)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l124, Int32(0))
		BinopInst("<", LoadVarInst(loop, l124), Int32(2))
		StoreVarInst(loop, l124, BinopInst("+", LoadVarInst(loop, l124), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec31[LoadVarInst(loop, l124)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l125, Int32(0))
		BinopInst("<", LoadVarInst(loop, l125), Int32(2))
		StoreVarInst(loop, l125, BinopInst("+", LoadVarInst(loop, l125), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec95[LoadVarInst(loop, l125)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l126, Int32(0))
		BinopInst("<", LoadVarInst(loop, l126), Int32(2))
		StoreVarInst(loop, l126, BinopInst("+", LoadVarInst(loop, l126), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec94[LoadVarInst(loop, l126)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l127, Int32(0))
		BinopInst("<", LoadVarInst(loop, l127), Int32(2))
		StoreVarInst(loop, l127, BinopInst("+", LoadVarInst(loop, l127), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec93[LoadVarInst(loop, l127)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l128, Int32(0))
		BinopInst("<", LoadVarInst(loop, l128), Int32(2))
		StoreVarInst(loop, l128, BinopInst("+", LoadVarInst(loop, l128), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec32[LoadVarInst(loop, l128)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l129, Int32(0))
		BinopInst("<", LoadVarInst(loop, l129), Int32(2))
		StoreVarInst(loop, l129, BinopInst("+", LoadVarInst(loop, l129), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec98[LoadVarInst(loop, l129)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l130, Int32(0))
		BinopInst("<", LoadVarInst(loop, l130), Int32(2))
		StoreVarInst(loop, l130, BinopInst("+", LoadVarInst(loop, l130), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec97[LoadVarInst(loop, l130)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l131, Int32(0))
		BinopInst("<", LoadVarInst(loop, l131), Int32(2))
		StoreVarInst(loop, l131, BinopInst("+", LoadVarInst(loop, l131), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec96[LoadVarInst(loop, l131)], Float(0.0f))
			EndBlock
		EndForLoop
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 10
Store = 0
Binop = 4
Numbers = 2
Declare = 8
Cast = 3
Select = 0
Loop = 0
Funcall = 0

BlockInst 
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fSlow2))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(2.32830644e-10f), BinopInst("-", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow1))))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 633
Store = 267
Binop = 367
Numbers = 367
Declare = 68
Cast = 69
Select = 0
Loop = 1
Funcall = 32

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		StoreVarInst(struct, iRec3[Int32(0)], BinopInst("%", BinopInst("+", LoadVarInst(struct, iRec3[Int32(1)]), Int32(1)), LoadVarInst(struct, iConst1)))
		DeclareVarInst(stack, "int", iTemp1, BinopInst("==", LoadVarInst(struct, iRec3[Int32(0)]), Int32(0)))
		StoreVarInst(struct, iRec4[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec4[Int32(1)])), Int32(12345)))
		StoreVarInst(struct, iRec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("-", Int32(1), LoadVarInst(stack, iTemp1)), LoadVarInst(struct, iRec2[Int32(1)])), BinopInst("*", LoadVarInst(stack, iTemp1), CastInst("int", BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(stack, fSlow4), CastInst("float", LoadVarInst(struct, iRec4[Int32(0)]))))))))
		DeclareVarInst(stack, "int", iTemp2, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(0)))
		StoreVarInst(struct, iVec0[Int32(0)], LoadVarInst(stack, iTemp2))
		DeclareVarInst(stack, "int", iTemp3, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec0[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp2)), LoadVarInst(struct, iVec0[Int32(1)])))
		StoreVarInst(struct, fRec5[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp3))))
		StoreVarInst(struct, fRec1[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp3)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fRec5[Int32(1)])))))
		StoreVarInst(struct, fRec0[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec1[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp4, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(2)))
		StoreVarInst(struct, iVec1[Int32(0)], LoadVarInst(stack, iTemp4))
		DeclareVarInst(stack, "int", iTemp5, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec6[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp4)), LoadVarInst(struct, iVec1[Int32(1)])))
		StoreVarInst(struct, fRec8[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp5))))
		StoreVarInst(struct, fRec7[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp5)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(struct, fRec8[Int32(1)])))))
		StoreVarInst(struct, fRec6[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec7[Int32(1)])))
		DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fTemp0)))
		StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(524287))], LoadVarInst(stack, fTemp6))
		DeclareVarInst(stack, "int", iTemp7, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(4)))
		StoreVarInst(struct, iVec3[Int32(0)], LoadVarInst(stack, iTemp7))
		DeclareVarInst(stack, "int", iTemp8, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec9[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp7)), LoadVarInst(struct, iVec3[Int32(1)])))
		StoreVarInst(struct, fRec11[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp8))))
		StoreVarInst(struct, fRec10[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp8)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(struct, fRec11[Int32(1)])))))
		StoreVarInst(struct, fRec9[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec10[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp9, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(6)))
		StoreVarInst(struct, iVec4[Int32(0)], LoadVarInst(stack, iTemp9))
		DeclareVarInst(stack, "int", iTemp10, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec12[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp9)), LoadVarInst(struct, iVec4[Int32(1)])))
		StoreVarInst(struct, fRec14[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp10))))
		StoreVarInst(struct, fRec13[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp10)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec13[Int32(1)]), LoadVarInst(struct, fRec14[Int32(1)])))))
		StoreVarInst(struct, fRec12[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec13[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp11, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(8)))
		StoreVarInst(struct, iVec5[Int32(0)], LoadVarInst(stack, iTemp11))
		DeclareVarInst(stack, "int", iTemp12, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec15[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp11)), LoadVarInst(struct, iVec5[Int32(1)])))
		StoreVarInst(struct, fRec17[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec17[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp12))))
		StoreVarInst(struct, fRec16[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp12)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fRec17[Int32(1)])))))
		StoreVarInst(struct, fRec15[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec16[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp13, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(10)))
		StoreVarInst(struct, iVec6[Int32(0)], LoadVarInst(stack, iTemp13))
		DeclareVarInst(stack, "int", iTemp14, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec18[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp13)), LoadVarInst(struct, iVec6[Int32(1)])))
		StoreVarInst(struct, fRec20[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec20[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp14))))
		StoreVarInst(struct, fRec19[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp14)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec19[Int32(1)]), LoadVarInst(struct, fRec20[Int32(1)])))))
		StoreVarInst(struct, fRec18[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec19[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp15, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(12)))
		StoreVarInst(struct, iVec7[Int32(0)], LoadVarInst(stack, iTemp15))
		DeclareVarInst(stack, "int", iTemp16, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec21[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp15)), LoadVarInst(struct, iVec7[Int32(1)])))
		StoreVarInst(struct, fRec23[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec23[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp16))))
		StoreVarInst(struct, fRec22[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp16)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fRec23[Int32(1)])))))
		StoreVarInst(struct, fRec21[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec22[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp17, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(14)))
		StoreVarInst(struct, iVec8[Int32(0)], LoadVarInst(stack, iTemp17))
		DeclareVarInst(stack, "int", iTemp18, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec24[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp17)), LoadVarInst(struct, iVec8[Int32(1)])))
		StoreVarInst(struct, fRec26[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec26[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp18))))
		StoreVarInst(struct, fRec25[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp18)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec25[Int32(1)]), LoadVarInst(struct, fRec26[Int32(1)])))))
		StoreVarInst(struct, fRec24[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec25[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp19, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(16)))
		StoreVarInst(struct, iVec9[Int32(0)], LoadVarInst(stack, iTemp19))
		DeclareVarInst(stack, "int", iTemp20, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec27[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp19)), LoadVarInst(struct, iVec9[Int32(1)])))
		StoreVarInst(struct, fRec29[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec29[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp20))))
		StoreVarInst(struct, fRec28[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp20)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), LoadVarInst(struct, fRec29[Int32(1)])))))
		StoreVarInst(struct, fRec27[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec28[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp21, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(18)))
		StoreVarInst(struct, iVec10[Int32(0)], LoadVarInst(stack, iTemp21))
		DeclareVarInst(stack, "int", iTemp22, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec30[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp21)), LoadVarInst(struct, iVec10[Int32(1)])))
		StoreVarInst(struct, fRec32[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec32[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp22))))
		StoreVarInst(struct, fRec31[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp22)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec31[Int32(1)]), LoadVarInst(struct, fRec32[Int32(1)])))))
		StoreVarInst(struct, fRec30[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec31[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp23, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(20)))
		StoreVarInst(struct, iVec11[Int32(0)], LoadVarInst(stack, iTemp23))
		DeclareVarInst(stack, "int", iTemp24, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec33[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp23)), LoadVarInst(struct, iVec11[Int32(1)])))
		StoreVarInst(struct, fRec35[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec35[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp24))))
		StoreVarInst(struct, fRec34[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp24)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec34[Int32(1)]), LoadVarInst(struct, fRec35[Int32(1)])))))
		StoreVarInst(struct, fRec33[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec34[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp25, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(22)))
		StoreVarInst(struct, iVec12[Int32(0)], LoadVarInst(stack, iTemp25))
		DeclareVarInst(stack, "int", iTemp26, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec36[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp25)), LoadVarInst(struct, iVec12[Int32(1)])))
		StoreVarInst(struct, fRec38[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec38[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp26))))
		StoreVarInst(struct, fRec37[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp26)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec37[Int32(1)]), LoadVarInst(struct, fRec38[Int32(1)])))))
		StoreVarInst(struct, fRec36[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec37[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp27, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(24)))
		StoreVarInst(struct, iVec13[Int32(0)], LoadVarInst(stack, iTemp27))
		DeclareVarInst(stack, "int", iTemp28, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec39[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp27)), LoadVarInst(struct, iVec13[Int32(1)])))
		StoreVarInst(struct, fRec41[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec41[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp28))))
		StoreVarInst(struct, fRec40[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp28)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec40[Int32(1)]), LoadVarInst(struct, fRec41[Int32(1)])))))
		StoreVarInst(struct, fRec39[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec40[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp29, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(26)))
		StoreVarInst(struct, iVec14[Int32(0)], LoadVarInst(stack, iTemp29))
		DeclareVarInst(stack, "int", iTemp30, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec42[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp29)), LoadVarInst(struct, iVec14[Int32(1)])))
		StoreVarInst(struct, fRec44[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec44[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp30))))
		StoreVarInst(struct, fRec43[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp30)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec43[Int32(1)]), LoadVarInst(struct, fRec44[Int32(1)])))))
		StoreVarInst(struct, fRec42[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec43[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp31, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(28)))
		StoreVarInst(struct, iVec15[Int32(0)], LoadVarInst(stack, iTemp31))
		DeclareVarInst(stack, "int", iTemp32, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec45[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp31)), LoadVarInst(struct, iVec15[Int32(1)])))
		StoreVarInst(struct, fRec47[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec47[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp32))))
		StoreVarInst(struct, fRec46[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp32)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec46[Int32(1)]), LoadVarInst(struct, fRec47[Int32(1)])))))
		StoreVarInst(struct, fRec45[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec46[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp33, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(30)))
		StoreVarInst(struct, iVec16[Int32(0)], LoadVarInst(stack, iTemp33))
		DeclareVarInst(stack, "int", iTemp34, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec48[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp33)), LoadVarInst(struct, iVec16[Int32(1)])))
		StoreVarInst(struct, fRec50[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec50[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp34))))
		StoreVarInst(struct, fRec49[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp34)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec49[Int32(1)]), LoadVarInst(struct, fRec50[Int32(1)])))))
		StoreVarInst(struct, fRec48[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec49[Int32(1)])))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(stack, fTemp0), LoadVarInst(struct, fRec0[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst4)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst5)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst6)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst7)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst8)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec21[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst9)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec24[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst10)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec27[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst11)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec30[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst12)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec33[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst13)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec36[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst14)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec39[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst15)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec42[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst16)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec45[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst17)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec48[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst18)), Int32(524287))])))))
		DeclareVarInst(stack, "int", iTemp35, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(1)))
		StoreVarInst(struct, iVec17[Int32(0)], LoadVarInst(stack, iTemp35))
		DeclareVarInst(stack, "int", iTemp36, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec51[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp35)), LoadVarInst(struct, iVec17[Int32(1)])))
		StoreVarInst(struct, fRec53[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec53[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp36))))
		StoreVarInst(struct, fRec52[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp36)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec52[Int32(1)]), LoadVarInst(struct, fRec53[Int32(1)])))))
		StoreVarInst(struct, fRec51[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec52[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp37, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(3)))
		StoreVarInst(struct, iVec18[Int32(0)], LoadVarInst(stack, iTemp37))
		DeclareVarInst(stack, "int", iTemp38, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec54[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp37)), LoadVarInst(struct, iVec18[Int32(1)])))
		StoreVarInst(struct, fRec56[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec56[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp38))))
		StoreVarInst(struct, fRec55[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp38)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec55[Int32(1)]), LoadVarInst(struct, fRec56[Int32(1)])))))
		StoreVarInst(struct, fRec54[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec55[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp39, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(5)))
		StoreVarInst(struct, iVec19[Int32(0)], LoadVarInst(stack, iTemp39))
		DeclareVarInst(stack, "int", iTemp40, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec57[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp39)), LoadVarInst(struct, iVec19[Int32(1)])))
		StoreVarInst(struct, fRec59[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec59[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp40))))
		StoreVarInst(struct, fRec58[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp40)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec58[Int32(1)]), LoadVarInst(struct, fRec59[Int32(1)])))))
		StoreVarInst(struct, fRec57[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec58[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp41, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(7)))
		StoreVarInst(struct, iVec20[Int32(0)], LoadVarInst(stack, iTemp41))
		DeclareVarInst(stack, "int", iTemp42, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec60[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp41)), LoadVarInst(struct, iVec20[Int32(1)])))
		StoreVarInst(struct, fRec62[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec62[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp42))))
		StoreVarInst(struct, fRec61[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp42)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec61[Int32(1)]), LoadVarInst(struct, fRec62[Int32(1)])))))
		StoreVarInst(struct, fRec60[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec61[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp43, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(9)))
		StoreVarInst(struct, iVec21[Int32(0)], LoadVarInst(stack, iTemp43))
		DeclareVarInst(stack, "int", iTemp44, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec63[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp43)), LoadVarInst(struct, iVec21[Int32(1)])))
		StoreVarInst(struct, fRec65[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec65[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp44))))
		StoreVarInst(struct, fRec64[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp44)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec64[Int32(1)]), LoadVarInst(struct, fRec65[Int32(1)])))))
		StoreVarInst(struct, fRec63[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec64[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp45, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(11)))
		StoreVarInst(struct, iVec22[Int32(0)], LoadVarInst(stack, iTemp45))
		DeclareVarInst(stack, "int", iTemp46, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec66[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp45)), LoadVarInst(struct, iVec22[Int32(1)])))
		StoreVarInst(struct, fRec68[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec68[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp46))))
		StoreVarInst(struct, fRec67[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp46)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec67[Int32(1)]), LoadVarInst(struct, fRec68[Int32(1)])))))
		StoreVarInst(struct, fRec66[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec67[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp47, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(13)))
		StoreVarInst(struct, iVec23[Int32(0)], LoadVarInst(stack, iTemp47))
		DeclareVarInst(stack, "int", iTemp48, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec69[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp47)), LoadVarInst(struct, iVec23[Int32(1)])))
		StoreVarInst(struct, fRec71[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec71[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp48))))
		StoreVarInst(struct, fRec70[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp48)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec70[Int32(1)]), LoadVarInst(struct, fRec71[Int32(1)])))))
		StoreVarInst(struct, fRec69[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec70[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp49, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(15)))
		StoreVarInst(struct, iVec24[Int32(0)], LoadVarInst(stack, iTemp49))
		DeclareVarInst(stack, "int", iTemp50, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec72[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp49)), LoadVarInst(struct, iVec24[Int32(1)])))
		StoreVarInst(struct, fRec74[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec74[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp50))))
		StoreVarInst(struct, fRec73[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp50)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec73[Int32(1)]), LoadVarInst(struct, fRec74[Int32(1)])))))
		StoreVarInst(struct, fRec72[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec73[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp51, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(17)))
		StoreVarInst(struct, iVec25[Int32(0)], LoadVarInst(stack, iTemp51))
		DeclareVarInst(stack, "int", iTemp52, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec75[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp51)), LoadVarInst(struct, iVec25[Int32(1)])))
		StoreVarInst(struct, fRec77[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec77[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp52))))
		StoreVarInst(struct, fRec76[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp52)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec76[Int32(1)]), LoadVarInst(struct, fRec77[Int32(1)])))))
		StoreVarInst(struct, fRec75[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec76[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp53, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(19)))
		StoreVarInst(struct, iVec26[Int32(0)], LoadVarInst(stack, iTemp53))
		DeclareVarInst(stack, "int", iTemp54, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec78[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp53)), LoadVarInst(struct, iVec26[Int32(1)])))
		StoreVarInst(struct, fRec80[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec80[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp54))))
		StoreVarInst(struct, fRec79[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp54)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec79[Int32(1)]), LoadVarInst(struct, fRec80[Int32(1)])))))
		StoreVarInst(struct, fRec78[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec79[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp55, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(21)))
		StoreVarInst(struct, iVec27[Int32(0)], LoadVarInst(stack, iTemp55))
		DeclareVarInst(stack, "int", iTemp56, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec81[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp55)), LoadVarInst(struct, iVec27[Int32(1)])))
		StoreVarInst(struct, fRec83[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec83[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp56))))
		StoreVarInst(struct, fRec82[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp56)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec82[Int32(1)]), LoadVarInst(struct, fRec83[Int32(1)])))))
		StoreVarInst(struct, fRec81[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec82[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp57, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(23)))
		StoreVarInst(struct, iVec28[Int32(0)], LoadVarInst(stack, iTemp57))
		DeclareVarInst(stack, "int", iTemp58, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec84[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp57)), LoadVarInst(struct, iVec28[Int32(1)])))
		StoreVarInst(struct, fRec86[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec86[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp58))))
		StoreVarInst(struct, fRec85[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp58)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec85[Int32(1)]), LoadVarInst(struct, fRec86[Int32(1)])))))
		StoreVarInst(struct, fRec84[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec85[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp59, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(25)))
		StoreVarInst(struct, iVec29[Int32(0)], LoadVarInst(stack, iTemp59))
		DeclareVarInst(stack, "int", iTemp60, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec87[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp59)), LoadVarInst(struct, iVec29[Int32(1)])))
		StoreVarInst(struct, fRec89[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec89[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp60))))
		StoreVarInst(struct, fRec88[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp60)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec88[Int32(1)]), LoadVarInst(struct, fRec89[Int32(1)])))))
		StoreVarInst(struct, fRec87[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec88[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp61, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(27)))
		StoreVarInst(struct, iVec30[Int32(0)], LoadVarInst(stack, iTemp61))
		DeclareVarInst(stack, "int", iTemp62, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec90[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp61)), LoadVarInst(struct, iVec30[Int32(1)])))
		StoreVarInst(struct, fRec92[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec92[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp62))))
		StoreVarInst(struct, fRec91[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp62)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec91[Int32(1)]), LoadVarInst(struct, fRec92[Int32(1)])))))
		StoreVarInst(struct, fRec90[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec91[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp63, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(29)))
		StoreVarInst(struct, iVec31[Int32(0)], LoadVarInst(stack, iTemp63))
		DeclareVarInst(stack, "int", iTemp64, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec93[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp63)), LoadVarInst(struct, iVec31[Int32(1)])))
		StoreVarInst(struct, fRec95[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec95[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp64))))
		StoreVarInst(struct, fRec94[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp64)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec94[Int32(1)]), LoadVarInst(struct, fRec95[Int32(1)])))))
		StoreVarInst(struct, fRec93[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec94[Int32(1)])))
		DeclareVarInst(stack, "int", iTemp65, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(31)))
		StoreVarInst(struct, iVec32[Int32(0)], LoadVarInst(stack, iTemp65))
		DeclareVarInst(stack, "int", iTemp66, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec96[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp65)), LoadVarInst(struct, iVec32[Int32(1)])))
		StoreVarInst(struct, fRec98[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec98[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp66))))
		StoreVarInst(struct, fRec97[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp66)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec97[Int32(1)]), LoadVarInst(struct, fRec98[Int32(1)])))))
		StoreVarInst(struct, fRec96[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec97[Int32(1)])))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec51[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst19)), Int32(524287))])), BinopInst("*", LoadVarInst(struct, fRec54[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst20)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec57[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst21)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec60[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst22)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec63[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst23)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec66[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst24)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec69[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst25)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec72[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst26)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec75[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst27)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec78[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst28)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec81[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst29)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec84[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst30)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec87[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst31)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec90[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst32)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec93[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst33)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec96[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst34)), Int32(524287))])))))
		StoreVarInst(struct, iRec3[Int32(1)], LoadVarInst(struct, iRec3[Int32(0)]))
		StoreVarInst(struct, iRec4[Int32(1)], LoadVarInst(struct, iRec4[Int32(0)]))
		StoreVarInst(struct, iRec2[Int32(1)], LoadVarInst(struct, iRec2[Int32(0)]))
		StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
		StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
		StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
		StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
		StoreVarInst(struct, iVec1[Int32(1)], LoadVarInst(struct, iVec1[Int32(0)]))
		StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
		StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
		StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
		StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
		StoreVarInst(struct, iVec3[Int32(1)], LoadVarInst(struct, iVec3[Int32(0)]))
		StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
		StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
		StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
		StoreVarInst(struct, iVec4[Int32(1)], LoadVarInst(struct, iVec4[Int32(0)]))
		StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
		StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
		StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
		StoreVarInst(struct, iVec5[Int32(1)], LoadVarInst(struct, iVec5[Int32(0)]))
		StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
		StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
		StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
		StoreVarInst(struct, iVec6[Int32(1)], LoadVarInst(struct, iVec6[Int32(0)]))
		StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
		StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
		StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
		StoreVarInst(struct, iVec7[Int32(1)], LoadVarInst(struct, iVec7[Int32(0)]))
		StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
		StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
		StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
		StoreVarInst(struct, iVec8[Int32(1)], LoadVarInst(struct, iVec8[Int32(0)]))
		StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
		StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
		StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
		StoreVarInst(struct, iVec9[Int32(1)], LoadVarInst(struct, iVec9[Int32(0)]))
		StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
		StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
		StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
		StoreVarInst(struct, iVec10[Int32(1)], LoadVarInst(struct, iVec10[Int32(0)]))
		StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
		StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
		StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
		StoreVarInst(struct, iVec11[Int32(1)], LoadVarInst(struct, iVec11[Int32(0)]))
		StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
		StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
		StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
		StoreVarInst(struct, iVec12[Int32(1)], LoadVarInst(struct, iVec12[Int32(0)]))
		StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
		StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
		StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
		StoreVarInst(struct, iVec13[Int32(1)], LoadVarInst(struct, iVec13[Int32(0)]))
		StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
		StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
		StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
		StoreVarInst(struct, iVec14[Int32(1)], LoadVarInst(struct, iVec14[Int32(0)]))
		StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
		StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
		StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
		StoreVarInst(struct, iVec15[Int32(1)], LoadVarInst(struct, iVec15[Int32(0)]))
		StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
		StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
		StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
		StoreVarInst(struct, iVec16[Int32(1)], LoadVarInst(struct, iVec16[Int32(0)]))
		StoreVarInst(struct, fRec50[Int32(1)], LoadVarInst(struct, fRec50[Int32(0)]))
		StoreVarInst(struct, fRec49[Int32(1)], LoadVarInst(struct, fRec49[Int32(0)]))
		StoreVarInst(struct, fRec48[Int32(1)], LoadVarInst(struct, fRec48[Int32(0)]))
		StoreVarInst(struct, iVec17[Int32(1)], LoadVarInst(struct, iVec17[Int32(0)]))
		StoreVarInst(struct, fRec53[Int32(1)], LoadVarInst(struct, fRec53[Int32(0)]))
		StoreVarInst(struct, fRec52[Int32(1)], LoadVarInst(struct, fRec52[Int32(0)]))
		StoreVarInst(struct, fRec51[Int32(1)], LoadVarInst(struct, fRec51[Int32(0)]))
		StoreVarInst(struct, iVec18[Int32(1)], LoadVarInst(struct, iVec18[Int32(0)]))
		StoreVarInst(struct, fRec56[Int32(1)], LoadVarInst(struct, fRec56[Int32(0)]))
		StoreVarInst(struct, fRec55[Int32(1)], LoadVarInst(struct, fRec55[Int32(0)]))
		StoreVarInst(struct, fRec54[Int32(1)], LoadVarInst(struct, fRec54[Int32(0)]))
		StoreVarInst(struct, iVec19[Int32(1)], LoadVarInst(struct, iVec19[Int32(0)]))
		StoreVarInst(struct, fRec59[Int32(1)], LoadVarInst(struct, fRec59[Int32(0)]))
		StoreVarInst(struct, fRec58[Int32(1)], LoadVarInst(struct, fRec58[Int32(0)]))
		StoreVarInst(struct, fRec57[Int32(1)], LoadVarInst(struct, fRec57[Int32(0)]))
		StoreVarInst(struct, iVec20[Int32(1)], LoadVarInst(struct, iVec20[Int32(0)]))
		StoreVarInst(struct, fRec62[Int32(1)], LoadVarInst(struct, fRec62[Int32(0)]))
		StoreVarInst(struct, fRec61[Int32(1)], LoadVarInst(struct, fRec61[Int32(0)]))
		StoreVarInst(struct, fRec60[Int32(1)], LoadVarInst(struct, fRec60[Int32(0)]))
		StoreVarInst(struct, iVec21[Int32(1)], LoadVarInst(struct, iVec21[Int32(0)]))
		StoreVarInst(struct, fRec65[Int32(1)], LoadVarInst(struct, fRec65[Int32(0)]))
		StoreVarInst(struct, fRec64[Int32(1)], LoadVarInst(struct, fRec64[Int32(0)]))
		StoreVarInst(struct, fRec63[Int32(1)], LoadVarInst(struct, fRec63[Int32(0)]))
		StoreVarInst(struct, iVec22[Int32(1)], LoadVarInst(struct, iVec22[Int32(0)]))
		StoreVarInst(struct, fRec68[Int32(1)], LoadVarInst(struct, fRec68[Int32(0)]))
		StoreVarInst(struct, fRec67[Int32(1)], LoadVarInst(struct, fRec67[Int32(0)]))
		StoreVarInst(struct, fRec66[Int32(1)], LoadVarInst(struct, fRec66[Int32(0)]))
		StoreVarInst(struct, iVec23[Int32(1)], LoadVarInst(struct, iVec23[Int32(0)]))
		StoreVarInst(struct, fRec71[Int32(1)], LoadVarInst(struct, fRec71[Int32(0)]))
		StoreVarInst(struct, fRec70[Int32(1)], LoadVarInst(struct, fRec70[Int32(0)]))
		StoreVarInst(struct, fRec69[Int32(1)], LoadVarInst(struct, fRec69[Int32(0)]))
		StoreVarInst(struct, iVec24[Int32(1)], LoadVarInst(struct, iVec24[Int32(0)]))
		StoreVarInst(struct, fRec74[Int32(1)], LoadVarInst(struct, fRec74[Int32(0)]))
		StoreVarInst(struct, fRec73[Int32(1)], LoadVarInst(struct, fRec73[Int32(0)]))
		StoreVarInst(struct, fRec72[Int32(1)], LoadVarInst(struct, fRec72[Int32(0)]))
		StoreVarInst(struct, iVec25[Int32(1)], LoadVarInst(struct, iVec25[Int32(0)]))
		StoreVarInst(struct, fRec77[Int32(1)], LoadVarInst(struct, fRec77[Int32(0)]))
		StoreVarInst(struct, fRec76[Int32(1)], LoadVarInst(struct, fRec76[Int32(0)]))
		StoreVarInst(struct, fRec75[Int32(1)], LoadVarInst(struct, fRec75[Int32(0)]))
		StoreVarInst(struct, iVec26[Int32(1)], LoadVarInst(struct, iVec26[Int32(0)]))
		StoreVarInst(struct, fRec80[Int32(1)], LoadVarInst(struct, fRec80[Int32(0)]))
		StoreVarInst(struct, fRec79[Int32(1)], LoadVarInst(struct, fRec79[Int32(0)]))
		StoreVarInst(struct, fRec78[Int32(1)], LoadVarInst(struct, fRec78[Int32(0)]))
		StoreVarInst(struct, iVec27[Int32(1)], LoadVarInst(struct, iVec27[Int32(0)]))
		StoreVarInst(struct, fRec83[Int32(1)], LoadVarInst(struct, fRec83[Int32(0)]))
		StoreVarInst(struct, fRec82[Int32(1)], LoadVarInst(struct, fRec82[Int32(0)]))
		StoreVarInst(struct, fRec81[Int32(1)], LoadVarInst(struct, fRec81[Int32(0)]))
		StoreVarInst(struct, iVec28[Int32(1)], LoadVarInst(struct, iVec28[Int32(0)]))
		StoreVarInst(struct, fRec86[Int32(1)], LoadVarInst(struct, fRec86[Int32(0)]))
		StoreVarInst(struct, fRec85[Int32(1)], LoadVarInst(struct, fRec85[Int32(0)]))
		StoreVarInst(struct, fRec84[Int32(1)], LoadVarInst(struct, fRec84[Int32(0)]))
		StoreVarInst(struct, iVec29[Int32(1)], LoadVarInst(struct, iVec29[Int32(0)]))
		StoreVarInst(struct, fRec89[Int32(1)], LoadVarInst(struct, fRec89[Int32(0)]))
		StoreVarInst(struct, fRec88[Int32(1)], LoadVarInst(struct, fRec88[Int32(0)]))
		StoreVarInst(struct, fRec87[Int32(1)], LoadVarInst(struct, fRec87[Int32(0)]))
		StoreVarInst(struct, iVec30[Int32(1)], LoadVarInst(struct, iVec30[Int32(0)]))
		StoreVarInst(struct, fRec92[Int32(1)], LoadVarInst(struct, fRec92[Int32(0)]))
		StoreVarInst(struct, fRec91[Int32(1)], LoadVarInst(struct, fRec91[Int32(0)]))
		StoreVarInst(struct, fRec90[Int32(1)], LoadVarInst(struct, fRec90[Int32(0)]))
		StoreVarInst(struct, iVec31[Int32(1)], LoadVarInst(struct, iVec31[Int32(0)]))
		StoreVarInst(struct, fRec95[Int32(1)], LoadVarInst(struct, fRec95[Int32(0)]))
		StoreVarInst(struct, fRec94[Int32(1)], LoadVarInst(struct, fRec94[Int32(0)]))
		StoreVarInst(struct, fRec93[Int32(1)], LoadVarInst(struct, fRec93[Int32(0)]))
		StoreVarInst(struct, iVec32[Int32(1)], LoadVarInst(struct, iVec32[Int32(0)]))
		StoreVarInst(struct, fRec98[Int32(1)], LoadVarInst(struct, fRec98[Int32(0)]))
		StoreVarInst(struct, fRec97[Int32(1)], LoadVarInst(struct, fRec97[Int32(0)]))
		StoreVarInst(struct, fRec96[Int32(1)], LoadVarInst(struct, fRec96[Int32(0)]))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareFunInst("float", "max_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "min_f", "float", dummy0, "float", dummy1)
	DeclareFunInst("float", "mydsp_faustpower2_f", "float", value)
		BlockInst 
			RetInst(BinopInst("*", LoadVarInst(kFunArgs, value), LoadVarInst(kFunArgs, value)))
			EndBlock
		EndDeclare
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider0)
	DeclareVarInst(struct, "int", fSamplingFreq)
	DeclareVarInst(struct, "float", fConst0)
	DeclareVarInst(struct, "int", iConst1)
	DeclareVarInst(struct, int, iRec3[2])
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider1)
	DeclareVarInst(struct, "FAUSTFLOAT", fHslider2)
	DeclareVarInst(struct, int, iRec4[2])
	DeclareVarInst(struct, int, iRec2[2])
	DeclareVarInst(struct, int, iVec0[2])
	DeclareVarInst(struct, "float", fConst2)
	DeclareVarInst(struct, "float", fConst3)
	DeclareVarInst(struct, float, fRec5[2])
	DeclareVarInst(struct, float, fRec1[2])
	DeclareVarInst(struct, float, fRec0[2])
	DeclareVarInst(struct, int, iVec1[2])
	DeclareVarInst(struct, float, fRec8[2])
	DeclareVarInst(struct, float, fRec7[2])
	DeclareVarInst(struct, float, fRec6[2])
	DeclareVarInst(struct, "int", IOTA)
	DeclareVarInst(struct, float, fVec2[524288])
	DeclareVarInst(struct, "int", iConst4)
	DeclareVarInst(struct, int, iVec3[2])
	DeclareVarInst(struct, float, fRec11[2])
	DeclareVarInst(struct, float, fRec10[2])
	DeclareVarInst(struct, float, fRec9[2])
	DeclareVarInst(struct, "int", iConst5)
	DeclareVarInst(struct, int, iVec4[2])
	DeclareVarInst(struct, float, fRec14[2])
	DeclareVarInst(struct, float, fRec13[2])
	DeclareVarInst(struct, float, fRec12[2])
	DeclareVarInst(struct, "int", iConst6)
	DeclareVarInst(struct, int, iVec5[2])
	DeclareVarInst(struct, float, fRec17[2])
	DeclareVarInst(struct, float, fRec16[2])
	DeclareVarInst(struct, float, fRec15[2])
	DeclareVarInst(struct, "int", iConst7)
	DeclareVarInst(struct, int, iVec6[2])
	DeclareVarInst(struct, float, fRec20[2])
	DeclareVarInst(struct, float, fRec19[2])
	DeclareVarInst(struct, float, fRec18[2])
	DeclareVarInst(struct, "int", iConst8)
	DeclareVarInst(struct, int, iVec7[2])
	DeclareVarInst(struct, float, fRec23[2])
	DeclareVarInst(struct, float, fRec22[2])
	DeclareVarInst(struct, float, fRec21[2])
	DeclareVarInst(struct, "int", iConst9)
	DeclareVarInst(struct, int, iVec8[2])
	DeclareVarInst(struct, float, fRec26[2])
	DeclareVarInst(struct, float, fRec25[2])
	DeclareVarInst(struct, float, fRec24[2])
	DeclareVarInst(struct, "int", iConst10)
	DeclareVarInst(struct, int, iVec9[2])
	DeclareVarInst(struct, float, fRec29[2])
	DeclareVarInst(struct, float, fRec28[2])
	DeclareVarInst(struct, float, fRec27[2])
	DeclareVarInst(struct, "int", iConst11)
	DeclareVarInst(struct, int, iVec10[2])
	DeclareVarInst(struct, float, fRec32[2])
	DeclareVarInst(struct, float, fRec31[2])
	DeclareVarInst(struct, float, fRec30[2])
	DeclareVarInst(struct, "int", iConst12)
	DeclareVarInst(struct, int, iVec11[2])
	DeclareVarInst(struct, float, fRec35[2])
	DeclareVarInst(struct, float, fRec34[2])
	DeclareVarInst(struct, float, fRec33[2])
	DeclareVarInst(struct, "int", iConst13)
	DeclareVarInst(struct, int, iVec12[2])
	DeclareVarInst(struct, float, fRec38[2])
	DeclareVarInst(struct, float, fRec37[2])
	DeclareVarInst(struct, float, fRec36[2])
	DeclareVarInst(struct, "int", iConst14)
	DeclareVarInst(struct, int, iVec13[2])
	DeclareVarInst(struct, float, fRec41[2])
	DeclareVarInst(struct, float, fRec40[2])
	DeclareVarInst(struct, float, fRec39[2])
	DeclareVarInst(struct, "int", iConst15)
	DeclareVarInst(struct, int, iVec14[2])
	DeclareVarInst(struct, float, fRec44[2])
	DeclareVarInst(struct, float, fRec43[2])
	DeclareVarInst(struct, float, fRec42[2])
	DeclareVarInst(struct, "int", iConst16)
	DeclareVarInst(struct, int, iVec15[2])
	DeclareVarInst(struct, float, fRec47[2])
	DeclareVarInst(struct, float, fRec46[2])
	DeclareVarInst(struct, float, fRec45[2])
	DeclareVarInst(struct, "int", iConst17)
	DeclareVarInst(struct, int, iVec16[2])
	DeclareVarInst(struct, float, fRec50[2])
	DeclareVarInst(struct, float, fRec49[2])
	DeclareVarInst(struct, float, fRec48[2])
	DeclareVarInst(struct, "int", iConst18)
	DeclareVarInst(struct, int, iVec17[2])
	DeclareVarInst(struct, float, fRec53[2])
	DeclareVarInst(struct, float, fRec52[2])
	DeclareVarInst(struct, float, fRec51[2])
	DeclareVarInst(struct, "int", iConst19)
	DeclareVarInst(struct, int, iVec18[2])
	DeclareVarInst(struct, float, fRec56[2])
	DeclareVarInst(struct, float, fRec55[2])
	DeclareVarInst(struct, float, fRec54[2])
	DeclareVarInst(struct, "int", iConst20)
	DeclareVarInst(struct, int, iVec19[2])
	DeclareVarInst(struct, float, fRec59[2])
	DeclareVarInst(struct, float, fRec58[2])
	DeclareVarInst(struct, float, fRec57[2])
	DeclareVarInst(struct, "int", iConst21)
	DeclareVarInst(struct, int, iVec20[2])
	DeclareVarInst(struct, float, fRec62[2])
	DeclareVarInst(struct, float, fRec61[2])
	DeclareVarInst(struct, float, fRec60[2])
	DeclareVarInst(struct, "int", iConst22)
	DeclareVarInst(struct, int, iVec21[2])
	DeclareVarInst(struct, float, fRec65[2])
	DeclareVarInst(struct, float, fRec64[2])
	DeclareVarInst(struct, float, fRec63[2])
	DeclareVarInst(struct, "int", iConst23)
	DeclareVarInst(struct, int, iVec22[2])
	DeclareVarInst(struct, float, fRec68[2])
	DeclareVarInst(struct, float, fRec67[2])
	DeclareVarInst(struct, float, fRec66[2])
	DeclareVarInst(struct, "int", iConst24)
	DeclareVarInst(struct, int, iVec23[2])
	DeclareVarInst(struct, float, fRec71[2])
	DeclareVarInst(struct, float, fRec70[2])
	DeclareVarInst(struct, float, fRec69[2])
	DeclareVarInst(struct, "int", iConst25)
	DeclareVarInst(struct, int, iVec24[2])
	DeclareVarInst(struct, float, fRec74[2])
	DeclareVarInst(struct, float, fRec73[2])
	DeclareVarInst(struct, float, fRec72[2])
	DeclareVarInst(struct, "int", iConst26)
	DeclareVarInst(struct, int, iVec25[2])
	DeclareVarInst(struct, float, fRec77[2])
	DeclareVarInst(struct, float, fRec76[2])
	DeclareVarInst(struct, float, fRec75[2])
	DeclareVarInst(struct, "int", iConst27)
	DeclareVarInst(struct, int, iVec26[2])
	DeclareVarInst(struct, float, fRec80[2])
	DeclareVarInst(struct, float, fRec79[2])
	DeclareVarInst(struct, float, fRec78[2])
	DeclareVarInst(struct, "int", iConst28)
	DeclareVarInst(struct, int, iVec27[2])
	DeclareVarInst(struct, float, fRec83[2])
	DeclareVarInst(struct, float, fRec82[2])
	DeclareVarInst(struct, float, fRec81[2])
	DeclareVarInst(struct, "int", iConst29)
	DeclareVarInst(struct, int, iVec28[2])
	DeclareVarInst(struct, float, fRec86[2])
	DeclareVarInst(struct, float, fRec85[2])
	DeclareVarInst(struct, float, fRec84[2])
	DeclareVarInst(struct, "int", iConst30)
	DeclareVarInst(struct, int, iVec29[2])
	DeclareVarInst(struct, float, fRec89[2])
	DeclareVarInst(struct, float, fRec88[2])
	DeclareVarInst(struct, float, fRec87[2])
	DeclareVarInst(struct, "int", iConst31)
	DeclareVarInst(struct, int, iVec30[2])
	DeclareVarInst(struct, float, fRec92[2])
	DeclareVarInst(struct, float, fRec91[2])
	DeclareVarInst(struct, float, fRec90[2])
	DeclareVarInst(struct, "int", iConst32)
	DeclareVarInst(struct, int, iVec31[2])
	DeclareVarInst(struct, float, fRec95[2])
	DeclareVarInst(struct, float, fRec94[2])
	DeclareVarInst(struct, float, fRec93[2])
	DeclareVarInst(struct, "int", iConst33)
	DeclareVarInst(struct, int, iVec32[2])
	DeclareVarInst(struct, float, fRec98[2])
	DeclareVarInst(struct, float, fRec97[2])
	DeclareVarInst(struct, float, fRec96[2])
	DeclareVarInst(struct, "int", iConst34)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	StoreVarInst(struct, fConst0, FunCallInst("min_f", Float(192000.0f), FunCallInst("max_f", Float(1.0f), CastInst("float", LoadVarInst(struct, fSamplingFreq)))))
	StoreVarInst(struct, iConst1, CastInst("int", BinopInst("*", Float(0.00729927002f), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst2, BinopInst("*", Float(4.0f), BinopInst("/", BinopInst("-", Float(20.0f), BinopInst("/", Float(400.0f), LoadVarInst(struct, fConst0))), LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, fConst3, BinopInst("/", Float(3200.0f), FunCallInst("mydsp_faustpower2_f", LoadVarInst(struct, fConst0))))
	StoreVarInst(struct, iConst4, BinopInst("&", CastInst("int", BinopInst("*", Float(0.3125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst5, BinopInst("&", CastInst("int", BinopInst("*", Float(0.625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst6, BinopInst("&", CastInst("int", BinopInst("*", Float(0.9375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst7, BinopInst("&", CastInst("int", BinopInst("*", Float(1.25f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst8, BinopInst("&", CastInst("int", BinopInst("*", Float(1.5625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst9, BinopInst("&", CastInst("int", BinopInst("*", Float(1.875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst10, BinopInst("&", CastInst("int", BinopInst("*", Float(2.1875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst11, BinopInst("&", CastInst("int", BinopInst("*", Float(2.5f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst12, BinopInst("&", CastInst("int", BinopInst("*", Float(2.8125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst13, BinopInst("&", CastInst("int", BinopInst("*", Float(3.125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst14, BinopInst("&", CastInst("int", BinopInst("*", Float(3.4375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst15, BinopInst("&", CastInst("int", BinopInst("*", Float(3.75f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst16, BinopInst("&", CastInst("int", BinopInst("*", Float(4.0625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst17, BinopInst("&", CastInst("int", BinopInst("*", Float(4.375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst18, BinopInst("&", CastInst("int", BinopInst("*", Float(4.6875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst19, BinopInst("&", CastInst("int", BinopInst("*", Float(0.15625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst20, BinopInst("&", CastInst("int", BinopInst("*", Float(0.46875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst21, BinopInst("&", CastInst("int", BinopInst("*", Float(0.78125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst22, BinopInst("&", CastInst("int", BinopInst("*", Float(1.09375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst23, BinopInst("&", CastInst("int", BinopInst("*", Float(1.40625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst24, BinopInst("&", CastInst("int", BinopInst("*", Float(1.71875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst25, BinopInst("&", CastInst("int", BinopInst("*", Float(2.03125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst26, BinopInst("&", CastInst("int", BinopInst("*", Float(2.34375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst27, BinopInst("&", CastInst("int", BinopInst("*", Float(2.65625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst28, BinopInst("&", CastInst("int", BinopInst("*", Float(2.96875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst29, BinopInst("&", CastInst("int", BinopInst("*", Float(3.28125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst30, BinopInst("&", CastInst("int", BinopInst("*", Float(3.59375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst31, BinopInst("&", CastInst("int", BinopInst("*", Float(3.90625f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst32, BinopInst("&", CastInst("int", BinopInst("*", Float(4.21875f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst33, BinopInst("&", CastInst("int", BinopInst("*", Float(4.53125f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, iConst34, BinopInst("&", CastInst("int", BinopInst("*", Float(4.84375f), LoadVarInst(struct, fConst0))), Int32(524287)))
	StoreVarInst(struct, fHslider0, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider1, CastInst("FAUSTFLOAT", Double(0.0f)))
	StoreVarInst(struct, fHslider2, CastInst("FAUSTFLOAT", Double(0.0f)))
	ForLoopInst 
		DeclareVarInst(loop, "int", l0, Int32(0))
		BinopInst("<", LoadVarInst(loop, l0), Int32(2))
		StoreVarInst(loop, l0, BinopInst("+", LoadVarInst(loop, l0), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec3[LoadVarInst(loop, l0)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l1, Int32(0))
		BinopInst("<", LoadVarInst(loop, l1), Int32(2))
		StoreVarInst(loop, l1, BinopInst("+", LoadVarInst(loop, l1), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec4[LoadVarInst(loop, l1)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l2, Int32(0))
		BinopInst("<", LoadVarInst(loop, l2), Int32(2))
		StoreVarInst(loop, l2, BinopInst("+", LoadVarInst(loop, l2), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iRec2[LoadVarInst(loop, l2)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l3, Int32(0))
		BinopInst("<", LoadVarInst(loop, l3), Int32(2))
		StoreVarInst(loop, l3, BinopInst("+", LoadVarInst(loop, l3), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec0[LoadVarInst(loop, l3)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l4, Int32(0))
		BinopInst("<", LoadVarInst(loop, l4), Int32(2))
		StoreVarInst(loop, l4, BinopInst("+", LoadVarInst(loop, l4), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec5[LoadVarInst(loop, l4)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l5, Int32(0))
		BinopInst("<", LoadVarInst(loop, l5), Int32(2))
		StoreVarInst(loop, l5, BinopInst("+", LoadVarInst(loop, l5), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec1[LoadVarInst(loop, l5)], Float(0.0f))
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
			StoreVarInst(struct, iVec1[LoadVarInst(loop, l7)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l8, Int32(0))
		BinopInst("<", LoadVarInst(loop, l8), Int32(2))
		StoreVarInst(loop, l8, BinopInst("+", LoadVarInst(loop, l8), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec8[LoadVarInst(loop, l8)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l9, Int32(0))
		BinopInst("<", LoadVarInst(loop, l9), Int32(2))
		StoreVarInst(loop, l9, BinopInst("+", LoadVarInst(loop, l9), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec7[LoadVarInst(loop, l9)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l10, Int32(0))
		BinopInst("<", LoadVarInst(loop, l10), Int32(2))
		StoreVarInst(loop, l10, BinopInst("+", LoadVarInst(loop, l10), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec6[LoadVarInst(loop, l10)], Float(0.0f))
			EndBlock
		EndForLoop
	StoreVarInst(struct, IOTA, Int32(0))
	ForLoopInst 
		DeclareVarInst(loop, "int", l11, Int32(0))
		BinopInst("<", LoadVarInst(loop, l11), Int32(524288))
		StoreVarInst(loop, l11, BinopInst("+", LoadVarInst(loop, l11), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fVec2[LoadVarInst(loop, l11)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l12, Int32(0))
		BinopInst("<", LoadVarInst(loop, l12), Int32(2))
		StoreVarInst(loop, l12, BinopInst("+", LoadVarInst(loop, l12), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec3[LoadVarInst(loop, l12)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l13, Int32(0))
		BinopInst("<", LoadVarInst(loop, l13), Int32(2))
		StoreVarInst(loop, l13, BinopInst("+", LoadVarInst(loop, l13), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec11[LoadVarInst(loop, l13)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l14, Int32(0))
		BinopInst("<", LoadVarInst(loop, l14), Int32(2))
		StoreVarInst(loop, l14, BinopInst("+", LoadVarInst(loop, l14), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec10[LoadVarInst(loop, l14)], Float(0.0f))
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
			StoreVarInst(struct, iVec4[LoadVarInst(loop, l16)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l17, Int32(0))
		BinopInst("<", LoadVarInst(loop, l17), Int32(2))
		StoreVarInst(loop, l17, BinopInst("+", LoadVarInst(loop, l17), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec14[LoadVarInst(loop, l17)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l18, Int32(0))
		BinopInst("<", LoadVarInst(loop, l18), Int32(2))
		StoreVarInst(loop, l18, BinopInst("+", LoadVarInst(loop, l18), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec13[LoadVarInst(loop, l18)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l19, Int32(0))
		BinopInst("<", LoadVarInst(loop, l19), Int32(2))
		StoreVarInst(loop, l19, BinopInst("+", LoadVarInst(loop, l19), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec12[LoadVarInst(loop, l19)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l20, Int32(0))
		BinopInst("<", LoadVarInst(loop, l20), Int32(2))
		StoreVarInst(loop, l20, BinopInst("+", LoadVarInst(loop, l20), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec5[LoadVarInst(loop, l20)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l21, Int32(0))
		BinopInst("<", LoadVarInst(loop, l21), Int32(2))
		StoreVarInst(loop, l21, BinopInst("+", LoadVarInst(loop, l21), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec17[LoadVarInst(loop, l21)], Float(0.0f))
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
			StoreVarInst(struct, fRec15[LoadVarInst(loop, l23)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l24, Int32(0))
		BinopInst("<", LoadVarInst(loop, l24), Int32(2))
		StoreVarInst(loop, l24, BinopInst("+", LoadVarInst(loop, l24), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec6[LoadVarInst(loop, l24)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l25, Int32(0))
		BinopInst("<", LoadVarInst(loop, l25), Int32(2))
		StoreVarInst(loop, l25, BinopInst("+", LoadVarInst(loop, l25), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec20[LoadVarInst(loop, l25)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l26, Int32(0))
		BinopInst("<", LoadVarInst(loop, l26), Int32(2))
		StoreVarInst(loop, l26, BinopInst("+", LoadVarInst(loop, l26), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec19[LoadVarInst(loop, l26)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l27, Int32(0))
		BinopInst("<", LoadVarInst(loop, l27), Int32(2))
		StoreVarInst(loop, l27, BinopInst("+", LoadVarInst(loop, l27), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec18[LoadVarInst(loop, l27)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l28, Int32(0))
		BinopInst("<", LoadVarInst(loop, l28), Int32(2))
		StoreVarInst(loop, l28, BinopInst("+", LoadVarInst(loop, l28), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec7[LoadVarInst(loop, l28)], Int32(0))
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
			StoreVarInst(struct, fRec22[LoadVarInst(loop, l30)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l31, Int32(0))
		BinopInst("<", LoadVarInst(loop, l31), Int32(2))
		StoreVarInst(loop, l31, BinopInst("+", LoadVarInst(loop, l31), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec21[LoadVarInst(loop, l31)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l32, Int32(0))
		BinopInst("<", LoadVarInst(loop, l32), Int32(2))
		StoreVarInst(loop, l32, BinopInst("+", LoadVarInst(loop, l32), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec8[LoadVarInst(loop, l32)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l33, Int32(0))
		BinopInst("<", LoadVarInst(loop, l33), Int32(2))
		StoreVarInst(loop, l33, BinopInst("+", LoadVarInst(loop, l33), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec26[LoadVarInst(loop, l33)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l34, Int32(0))
		BinopInst("<", LoadVarInst(loop, l34), Int32(2))
		StoreVarInst(loop, l34, BinopInst("+", LoadVarInst(loop, l34), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec25[LoadVarInst(loop, l34)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l35, Int32(0))
		BinopInst("<", LoadVarInst(loop, l35), Int32(2))
		StoreVarInst(loop, l35, BinopInst("+", LoadVarInst(loop, l35), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec24[LoadVarInst(loop, l35)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l36, Int32(0))
		BinopInst("<", LoadVarInst(loop, l36), Int32(2))
		StoreVarInst(loop, l36, BinopInst("+", LoadVarInst(loop, l36), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec9[LoadVarInst(loop, l36)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l37, Int32(0))
		BinopInst("<", LoadVarInst(loop, l37), Int32(2))
		StoreVarInst(loop, l37, BinopInst("+", LoadVarInst(loop, l37), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec29[LoadVarInst(loop, l37)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l38, Int32(0))
		BinopInst("<", LoadVarInst(loop, l38), Int32(2))
		StoreVarInst(loop, l38, BinopInst("+", LoadVarInst(loop, l38), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec28[LoadVarInst(loop, l38)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l39, Int32(0))
		BinopInst("<", LoadVarInst(loop, l39), Int32(2))
		StoreVarInst(loop, l39, BinopInst("+", LoadVarInst(loop, l39), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec27[LoadVarInst(loop, l39)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l40, Int32(0))
		BinopInst("<", LoadVarInst(loop, l40), Int32(2))
		StoreVarInst(loop, l40, BinopInst("+", LoadVarInst(loop, l40), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec10[LoadVarInst(loop, l40)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l41, Int32(0))
		BinopInst("<", LoadVarInst(loop, l41), Int32(2))
		StoreVarInst(loop, l41, BinopInst("+", LoadVarInst(loop, l41), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec32[LoadVarInst(loop, l41)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l42, Int32(0))
		BinopInst("<", LoadVarInst(loop, l42), Int32(2))
		StoreVarInst(loop, l42, BinopInst("+", LoadVarInst(loop, l42), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec31[LoadVarInst(loop, l42)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l43, Int32(0))
		BinopInst("<", LoadVarInst(loop, l43), Int32(2))
		StoreVarInst(loop, l43, BinopInst("+", LoadVarInst(loop, l43), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec30[LoadVarInst(loop, l43)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l44, Int32(0))
		BinopInst("<", LoadVarInst(loop, l44), Int32(2))
		StoreVarInst(loop, l44, BinopInst("+", LoadVarInst(loop, l44), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec11[LoadVarInst(loop, l44)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l45, Int32(0))
		BinopInst("<", LoadVarInst(loop, l45), Int32(2))
		StoreVarInst(loop, l45, BinopInst("+", LoadVarInst(loop, l45), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec35[LoadVarInst(loop, l45)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l46, Int32(0))
		BinopInst("<", LoadVarInst(loop, l46), Int32(2))
		StoreVarInst(loop, l46, BinopInst("+", LoadVarInst(loop, l46), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec34[LoadVarInst(loop, l46)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l47, Int32(0))
		BinopInst("<", LoadVarInst(loop, l47), Int32(2))
		StoreVarInst(loop, l47, BinopInst("+", LoadVarInst(loop, l47), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec33[LoadVarInst(loop, l47)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l48, Int32(0))
		BinopInst("<", LoadVarInst(loop, l48), Int32(2))
		StoreVarInst(loop, l48, BinopInst("+", LoadVarInst(loop, l48), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec12[LoadVarInst(loop, l48)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l49, Int32(0))
		BinopInst("<", LoadVarInst(loop, l49), Int32(2))
		StoreVarInst(loop, l49, BinopInst("+", LoadVarInst(loop, l49), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec38[LoadVarInst(loop, l49)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l50, Int32(0))
		BinopInst("<", LoadVarInst(loop, l50), Int32(2))
		StoreVarInst(loop, l50, BinopInst("+", LoadVarInst(loop, l50), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec37[LoadVarInst(loop, l50)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l51, Int32(0))
		BinopInst("<", LoadVarInst(loop, l51), Int32(2))
		StoreVarInst(loop, l51, BinopInst("+", LoadVarInst(loop, l51), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec36[LoadVarInst(loop, l51)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l52, Int32(0))
		BinopInst("<", LoadVarInst(loop, l52), Int32(2))
		StoreVarInst(loop, l52, BinopInst("+", LoadVarInst(loop, l52), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec13[LoadVarInst(loop, l52)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l53, Int32(0))
		BinopInst("<", LoadVarInst(loop, l53), Int32(2))
		StoreVarInst(loop, l53, BinopInst("+", LoadVarInst(loop, l53), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec41[LoadVarInst(loop, l53)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l54, Int32(0))
		BinopInst("<", LoadVarInst(loop, l54), Int32(2))
		StoreVarInst(loop, l54, BinopInst("+", LoadVarInst(loop, l54), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec40[LoadVarInst(loop, l54)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l55, Int32(0))
		BinopInst("<", LoadVarInst(loop, l55), Int32(2))
		StoreVarInst(loop, l55, BinopInst("+", LoadVarInst(loop, l55), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec39[LoadVarInst(loop, l55)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l56, Int32(0))
		BinopInst("<", LoadVarInst(loop, l56), Int32(2))
		StoreVarInst(loop, l56, BinopInst("+", LoadVarInst(loop, l56), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec14[LoadVarInst(loop, l56)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l57, Int32(0))
		BinopInst("<", LoadVarInst(loop, l57), Int32(2))
		StoreVarInst(loop, l57, BinopInst("+", LoadVarInst(loop, l57), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec44[LoadVarInst(loop, l57)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l58, Int32(0))
		BinopInst("<", LoadVarInst(loop, l58), Int32(2))
		StoreVarInst(loop, l58, BinopInst("+", LoadVarInst(loop, l58), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec43[LoadVarInst(loop, l58)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l59, Int32(0))
		BinopInst("<", LoadVarInst(loop, l59), Int32(2))
		StoreVarInst(loop, l59, BinopInst("+", LoadVarInst(loop, l59), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec42[LoadVarInst(loop, l59)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l60, Int32(0))
		BinopInst("<", LoadVarInst(loop, l60), Int32(2))
		StoreVarInst(loop, l60, BinopInst("+", LoadVarInst(loop, l60), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec15[LoadVarInst(loop, l60)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l61, Int32(0))
		BinopInst("<", LoadVarInst(loop, l61), Int32(2))
		StoreVarInst(loop, l61, BinopInst("+", LoadVarInst(loop, l61), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec47[LoadVarInst(loop, l61)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l62, Int32(0))
		BinopInst("<", LoadVarInst(loop, l62), Int32(2))
		StoreVarInst(loop, l62, BinopInst("+", LoadVarInst(loop, l62), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec46[LoadVarInst(loop, l62)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l63, Int32(0))
		BinopInst("<", LoadVarInst(loop, l63), Int32(2))
		StoreVarInst(loop, l63, BinopInst("+", LoadVarInst(loop, l63), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec45[LoadVarInst(loop, l63)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l64, Int32(0))
		BinopInst("<", LoadVarInst(loop, l64), Int32(2))
		StoreVarInst(loop, l64, BinopInst("+", LoadVarInst(loop, l64), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec16[LoadVarInst(loop, l64)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l65, Int32(0))
		BinopInst("<", LoadVarInst(loop, l65), Int32(2))
		StoreVarInst(loop, l65, BinopInst("+", LoadVarInst(loop, l65), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec50[LoadVarInst(loop, l65)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l66, Int32(0))
		BinopInst("<", LoadVarInst(loop, l66), Int32(2))
		StoreVarInst(loop, l66, BinopInst("+", LoadVarInst(loop, l66), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec49[LoadVarInst(loop, l66)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l67, Int32(0))
		BinopInst("<", LoadVarInst(loop, l67), Int32(2))
		StoreVarInst(loop, l67, BinopInst("+", LoadVarInst(loop, l67), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec48[LoadVarInst(loop, l67)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l68, Int32(0))
		BinopInst("<", LoadVarInst(loop, l68), Int32(2))
		StoreVarInst(loop, l68, BinopInst("+", LoadVarInst(loop, l68), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec17[LoadVarInst(loop, l68)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l69, Int32(0))
		BinopInst("<", LoadVarInst(loop, l69), Int32(2))
		StoreVarInst(loop, l69, BinopInst("+", LoadVarInst(loop, l69), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec53[LoadVarInst(loop, l69)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l70, Int32(0))
		BinopInst("<", LoadVarInst(loop, l70), Int32(2))
		StoreVarInst(loop, l70, BinopInst("+", LoadVarInst(loop, l70), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec52[LoadVarInst(loop, l70)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l71, Int32(0))
		BinopInst("<", LoadVarInst(loop, l71), Int32(2))
		StoreVarInst(loop, l71, BinopInst("+", LoadVarInst(loop, l71), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec51[LoadVarInst(loop, l71)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l72, Int32(0))
		BinopInst("<", LoadVarInst(loop, l72), Int32(2))
		StoreVarInst(loop, l72, BinopInst("+", LoadVarInst(loop, l72), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec18[LoadVarInst(loop, l72)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l73, Int32(0))
		BinopInst("<", LoadVarInst(loop, l73), Int32(2))
		StoreVarInst(loop, l73, BinopInst("+", LoadVarInst(loop, l73), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec56[LoadVarInst(loop, l73)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l74, Int32(0))
		BinopInst("<", LoadVarInst(loop, l74), Int32(2))
		StoreVarInst(loop, l74, BinopInst("+", LoadVarInst(loop, l74), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec55[LoadVarInst(loop, l74)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l75, Int32(0))
		BinopInst("<", LoadVarInst(loop, l75), Int32(2))
		StoreVarInst(loop, l75, BinopInst("+", LoadVarInst(loop, l75), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec54[LoadVarInst(loop, l75)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l76, Int32(0))
		BinopInst("<", LoadVarInst(loop, l76), Int32(2))
		StoreVarInst(loop, l76, BinopInst("+", LoadVarInst(loop, l76), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec19[LoadVarInst(loop, l76)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l77, Int32(0))
		BinopInst("<", LoadVarInst(loop, l77), Int32(2))
		StoreVarInst(loop, l77, BinopInst("+", LoadVarInst(loop, l77), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec59[LoadVarInst(loop, l77)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l78, Int32(0))
		BinopInst("<", LoadVarInst(loop, l78), Int32(2))
		StoreVarInst(loop, l78, BinopInst("+", LoadVarInst(loop, l78), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec58[LoadVarInst(loop, l78)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l79, Int32(0))
		BinopInst("<", LoadVarInst(loop, l79), Int32(2))
		StoreVarInst(loop, l79, BinopInst("+", LoadVarInst(loop, l79), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec57[LoadVarInst(loop, l79)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l80, Int32(0))
		BinopInst("<", LoadVarInst(loop, l80), Int32(2))
		StoreVarInst(loop, l80, BinopInst("+", LoadVarInst(loop, l80), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec20[LoadVarInst(loop, l80)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l81, Int32(0))
		BinopInst("<", LoadVarInst(loop, l81), Int32(2))
		StoreVarInst(loop, l81, BinopInst("+", LoadVarInst(loop, l81), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec62[LoadVarInst(loop, l81)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l82, Int32(0))
		BinopInst("<", LoadVarInst(loop, l82), Int32(2))
		StoreVarInst(loop, l82, BinopInst("+", LoadVarInst(loop, l82), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec61[LoadVarInst(loop, l82)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l83, Int32(0))
		BinopInst("<", LoadVarInst(loop, l83), Int32(2))
		StoreVarInst(loop, l83, BinopInst("+", LoadVarInst(loop, l83), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec60[LoadVarInst(loop, l83)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l84, Int32(0))
		BinopInst("<", LoadVarInst(loop, l84), Int32(2))
		StoreVarInst(loop, l84, BinopInst("+", LoadVarInst(loop, l84), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec21[LoadVarInst(loop, l84)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l85, Int32(0))
		BinopInst("<", LoadVarInst(loop, l85), Int32(2))
		StoreVarInst(loop, l85, BinopInst("+", LoadVarInst(loop, l85), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec65[LoadVarInst(loop, l85)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l86, Int32(0))
		BinopInst("<", LoadVarInst(loop, l86), Int32(2))
		StoreVarInst(loop, l86, BinopInst("+", LoadVarInst(loop, l86), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec64[LoadVarInst(loop, l86)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l87, Int32(0))
		BinopInst("<", LoadVarInst(loop, l87), Int32(2))
		StoreVarInst(loop, l87, BinopInst("+", LoadVarInst(loop, l87), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec63[LoadVarInst(loop, l87)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l88, Int32(0))
		BinopInst("<", LoadVarInst(loop, l88), Int32(2))
		StoreVarInst(loop, l88, BinopInst("+", LoadVarInst(loop, l88), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec22[LoadVarInst(loop, l88)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l89, Int32(0))
		BinopInst("<", LoadVarInst(loop, l89), Int32(2))
		StoreVarInst(loop, l89, BinopInst("+", LoadVarInst(loop, l89), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec68[LoadVarInst(loop, l89)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l90, Int32(0))
		BinopInst("<", LoadVarInst(loop, l90), Int32(2))
		StoreVarInst(loop, l90, BinopInst("+", LoadVarInst(loop, l90), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec67[LoadVarInst(loop, l90)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l91, Int32(0))
		BinopInst("<", LoadVarInst(loop, l91), Int32(2))
		StoreVarInst(loop, l91, BinopInst("+", LoadVarInst(loop, l91), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec66[LoadVarInst(loop, l91)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l92, Int32(0))
		BinopInst("<", LoadVarInst(loop, l92), Int32(2))
		StoreVarInst(loop, l92, BinopInst("+", LoadVarInst(loop, l92), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec23[LoadVarInst(loop, l92)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l93, Int32(0))
		BinopInst("<", LoadVarInst(loop, l93), Int32(2))
		StoreVarInst(loop, l93, BinopInst("+", LoadVarInst(loop, l93), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec71[LoadVarInst(loop, l93)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l94, Int32(0))
		BinopInst("<", LoadVarInst(loop, l94), Int32(2))
		StoreVarInst(loop, l94, BinopInst("+", LoadVarInst(loop, l94), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec70[LoadVarInst(loop, l94)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l95, Int32(0))
		BinopInst("<", LoadVarInst(loop, l95), Int32(2))
		StoreVarInst(loop, l95, BinopInst("+", LoadVarInst(loop, l95), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec69[LoadVarInst(loop, l95)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l96, Int32(0))
		BinopInst("<", LoadVarInst(loop, l96), Int32(2))
		StoreVarInst(loop, l96, BinopInst("+", LoadVarInst(loop, l96), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec24[LoadVarInst(loop, l96)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l97, Int32(0))
		BinopInst("<", LoadVarInst(loop, l97), Int32(2))
		StoreVarInst(loop, l97, BinopInst("+", LoadVarInst(loop, l97), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec74[LoadVarInst(loop, l97)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l98, Int32(0))
		BinopInst("<", LoadVarInst(loop, l98), Int32(2))
		StoreVarInst(loop, l98, BinopInst("+", LoadVarInst(loop, l98), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec73[LoadVarInst(loop, l98)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l99, Int32(0))
		BinopInst("<", LoadVarInst(loop, l99), Int32(2))
		StoreVarInst(loop, l99, BinopInst("+", LoadVarInst(loop, l99), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec72[LoadVarInst(loop, l99)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l100, Int32(0))
		BinopInst("<", LoadVarInst(loop, l100), Int32(2))
		StoreVarInst(loop, l100, BinopInst("+", LoadVarInst(loop, l100), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec25[LoadVarInst(loop, l100)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l101, Int32(0))
		BinopInst("<", LoadVarInst(loop, l101), Int32(2))
		StoreVarInst(loop, l101, BinopInst("+", LoadVarInst(loop, l101), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec77[LoadVarInst(loop, l101)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l102, Int32(0))
		BinopInst("<", LoadVarInst(loop, l102), Int32(2))
		StoreVarInst(loop, l102, BinopInst("+", LoadVarInst(loop, l102), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec76[LoadVarInst(loop, l102)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l103, Int32(0))
		BinopInst("<", LoadVarInst(loop, l103), Int32(2))
		StoreVarInst(loop, l103, BinopInst("+", LoadVarInst(loop, l103), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec75[LoadVarInst(loop, l103)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l104, Int32(0))
		BinopInst("<", LoadVarInst(loop, l104), Int32(2))
		StoreVarInst(loop, l104, BinopInst("+", LoadVarInst(loop, l104), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec26[LoadVarInst(loop, l104)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l105, Int32(0))
		BinopInst("<", LoadVarInst(loop, l105), Int32(2))
		StoreVarInst(loop, l105, BinopInst("+", LoadVarInst(loop, l105), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec80[LoadVarInst(loop, l105)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l106, Int32(0))
		BinopInst("<", LoadVarInst(loop, l106), Int32(2))
		StoreVarInst(loop, l106, BinopInst("+", LoadVarInst(loop, l106), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec79[LoadVarInst(loop, l106)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l107, Int32(0))
		BinopInst("<", LoadVarInst(loop, l107), Int32(2))
		StoreVarInst(loop, l107, BinopInst("+", LoadVarInst(loop, l107), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec78[LoadVarInst(loop, l107)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l108, Int32(0))
		BinopInst("<", LoadVarInst(loop, l108), Int32(2))
		StoreVarInst(loop, l108, BinopInst("+", LoadVarInst(loop, l108), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec27[LoadVarInst(loop, l108)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l109, Int32(0))
		BinopInst("<", LoadVarInst(loop, l109), Int32(2))
		StoreVarInst(loop, l109, BinopInst("+", LoadVarInst(loop, l109), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec83[LoadVarInst(loop, l109)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l110, Int32(0))
		BinopInst("<", LoadVarInst(loop, l110), Int32(2))
		StoreVarInst(loop, l110, BinopInst("+", LoadVarInst(loop, l110), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec82[LoadVarInst(loop, l110)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l111, Int32(0))
		BinopInst("<", LoadVarInst(loop, l111), Int32(2))
		StoreVarInst(loop, l111, BinopInst("+", LoadVarInst(loop, l111), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec81[LoadVarInst(loop, l111)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l112, Int32(0))
		BinopInst("<", LoadVarInst(loop, l112), Int32(2))
		StoreVarInst(loop, l112, BinopInst("+", LoadVarInst(loop, l112), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec28[LoadVarInst(loop, l112)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l113, Int32(0))
		BinopInst("<", LoadVarInst(loop, l113), Int32(2))
		StoreVarInst(loop, l113, BinopInst("+", LoadVarInst(loop, l113), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec86[LoadVarInst(loop, l113)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l114, Int32(0))
		BinopInst("<", LoadVarInst(loop, l114), Int32(2))
		StoreVarInst(loop, l114, BinopInst("+", LoadVarInst(loop, l114), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec85[LoadVarInst(loop, l114)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l115, Int32(0))
		BinopInst("<", LoadVarInst(loop, l115), Int32(2))
		StoreVarInst(loop, l115, BinopInst("+", LoadVarInst(loop, l115), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec84[LoadVarInst(loop, l115)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l116, Int32(0))
		BinopInst("<", LoadVarInst(loop, l116), Int32(2))
		StoreVarInst(loop, l116, BinopInst("+", LoadVarInst(loop, l116), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec29[LoadVarInst(loop, l116)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l117, Int32(0))
		BinopInst("<", LoadVarInst(loop, l117), Int32(2))
		StoreVarInst(loop, l117, BinopInst("+", LoadVarInst(loop, l117), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec89[LoadVarInst(loop, l117)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l118, Int32(0))
		BinopInst("<", LoadVarInst(loop, l118), Int32(2))
		StoreVarInst(loop, l118, BinopInst("+", LoadVarInst(loop, l118), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec88[LoadVarInst(loop, l118)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l119, Int32(0))
		BinopInst("<", LoadVarInst(loop, l119), Int32(2))
		StoreVarInst(loop, l119, BinopInst("+", LoadVarInst(loop, l119), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec87[LoadVarInst(loop, l119)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l120, Int32(0))
		BinopInst("<", LoadVarInst(loop, l120), Int32(2))
		StoreVarInst(loop, l120, BinopInst("+", LoadVarInst(loop, l120), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec30[LoadVarInst(loop, l120)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l121, Int32(0))
		BinopInst("<", LoadVarInst(loop, l121), Int32(2))
		StoreVarInst(loop, l121, BinopInst("+", LoadVarInst(loop, l121), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec92[LoadVarInst(loop, l121)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l122, Int32(0))
		BinopInst("<", LoadVarInst(loop, l122), Int32(2))
		StoreVarInst(loop, l122, BinopInst("+", LoadVarInst(loop, l122), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec91[LoadVarInst(loop, l122)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l123, Int32(0))
		BinopInst("<", LoadVarInst(loop, l123), Int32(2))
		StoreVarInst(loop, l123, BinopInst("+", LoadVarInst(loop, l123), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec90[LoadVarInst(loop, l123)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l124, Int32(0))
		BinopInst("<", LoadVarInst(loop, l124), Int32(2))
		StoreVarInst(loop, l124, BinopInst("+", LoadVarInst(loop, l124), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec31[LoadVarInst(loop, l124)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l125, Int32(0))
		BinopInst("<", LoadVarInst(loop, l125), Int32(2))
		StoreVarInst(loop, l125, BinopInst("+", LoadVarInst(loop, l125), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec95[LoadVarInst(loop, l125)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l126, Int32(0))
		BinopInst("<", LoadVarInst(loop, l126), Int32(2))
		StoreVarInst(loop, l126, BinopInst("+", LoadVarInst(loop, l126), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec94[LoadVarInst(loop, l126)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l127, Int32(0))
		BinopInst("<", LoadVarInst(loop, l127), Int32(2))
		StoreVarInst(loop, l127, BinopInst("+", LoadVarInst(loop, l127), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec93[LoadVarInst(loop, l127)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l128, Int32(0))
		BinopInst("<", LoadVarInst(loop, l128), Int32(2))
		StoreVarInst(loop, l128, BinopInst("+", LoadVarInst(loop, l128), Int32(1)))
		BlockInst 
			StoreVarInst(struct, iVec32[LoadVarInst(loop, l128)], Int32(0))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l129, Int32(0))
		BinopInst("<", LoadVarInst(loop, l129), Int32(2))
		StoreVarInst(loop, l129, BinopInst("+", LoadVarInst(loop, l129), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec98[LoadVarInst(loop, l129)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l130, Int32(0))
		BinopInst("<", LoadVarInst(loop, l130), Int32(2))
		StoreVarInst(loop, l130, BinopInst("+", LoadVarInst(loop, l130), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec97[LoadVarInst(loop, l130)], Float(0.0f))
			EndBlock
		EndForLoop
	ForLoopInst 
		DeclareVarInst(loop, "int", l131, Int32(0))
		BinopInst("<", LoadVarInst(loop, l131), Int32(2))
		StoreVarInst(loop, l131, BinopInst("+", LoadVarInst(loop, l131), Int32(1)))
		BlockInst 
			StoreVarInst(struct, fRec96[LoadVarInst(loop, l131)], Float(0.0f))
			EndBlock
		EndForLoop
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, "float", fSlow0, CastInst("float", LoadVarInst(struct, fHslider0)))
	DeclareVarInst(stack, "float", fSlow1, CastInst("float", LoadVarInst(struct, fHslider1)))
	DeclareVarInst(stack, "float", fSlow2, CastInst("float", LoadVarInst(struct, fHslider2)))
	DeclareVarInst(stack, "float", fSlow3, BinopInst("*", Float(0.5f), BinopInst("+", LoadVarInst(stack, fSlow1), LoadVarInst(stack, fSlow2))))
	DeclareVarInst(stack, "float", fSlow4, BinopInst("*", Float(2.32830644e-10f), BinopInst("-", LoadVarInst(stack, fSlow2), LoadVarInst(stack, fSlow1))))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			StoreVarInst(struct, iRec3[Int32(0)], BinopInst("%", BinopInst("+", LoadVarInst(struct, iRec3[Int32(1)]), Int32(1)), LoadVarInst(struct, iConst1)))
			DeclareVarInst(stack, "int", iTemp1, BinopInst("==", LoadVarInst(struct, iRec3[Int32(0)]), Int32(0)))
			StoreVarInst(struct, iRec4[Int32(0)], BinopInst("+", BinopInst("*", Int32(1103515245), LoadVarInst(struct, iRec4[Int32(1)])), Int32(12345)))
			StoreVarInst(struct, iRec2[Int32(0)], BinopInst("+", BinopInst("*", BinopInst("-", Int32(1), LoadVarInst(stack, iTemp1)), LoadVarInst(struct, iRec2[Int32(1)])), BinopInst("*", LoadVarInst(stack, iTemp1), CastInst("int", BinopInst("+", LoadVarInst(stack, fSlow3), BinopInst("*", LoadVarInst(stack, fSlow4), CastInst("float", LoadVarInst(struct, iRec4[Int32(0)]))))))))
			DeclareVarInst(stack, "int", iTemp2, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(0)))
			StoreVarInst(struct, iVec0[Int32(0)], LoadVarInst(stack, iTemp2))
			DeclareVarInst(stack, "int", iTemp3, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec0[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp2)), LoadVarInst(struct, iVec0[Int32(1)])))
			StoreVarInst(struct, fRec5[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec5[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp3))))
			StoreVarInst(struct, fRec1[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp3)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec1[Int32(1)]), LoadVarInst(struct, fRec5[Int32(1)])))))
			StoreVarInst(struct, fRec0[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec1[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp4, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(2)))
			StoreVarInst(struct, iVec1[Int32(0)], LoadVarInst(stack, iTemp4))
			DeclareVarInst(stack, "int", iTemp5, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec6[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp4)), LoadVarInst(struct, iVec1[Int32(1)])))
			StoreVarInst(struct, fRec8[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec8[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp5))))
			StoreVarInst(struct, fRec7[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp5)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec7[Int32(1)]), LoadVarInst(struct, fRec8[Int32(1)])))))
			StoreVarInst(struct, fRec6[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec7[Int32(1)])))
			DeclareVarInst(stack, "float", fTemp6, BinopInst("*", LoadVarInst(stack, fSlow0), LoadVarInst(stack, fTemp0)))
			StoreVarInst(struct, fVec2[BinopInst("&", LoadVarInst(struct, IOTA), Int32(524287))], LoadVarInst(stack, fTemp6))
			DeclareVarInst(stack, "int", iTemp7, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(4)))
			StoreVarInst(struct, iVec3[Int32(0)], LoadVarInst(stack, iTemp7))
			DeclareVarInst(stack, "int", iTemp8, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec9[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp7)), LoadVarInst(struct, iVec3[Int32(1)])))
			StoreVarInst(struct, fRec11[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec11[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp8))))
			StoreVarInst(struct, fRec10[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp8)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec10[Int32(1)]), LoadVarInst(struct, fRec11[Int32(1)])))))
			StoreVarInst(struct, fRec9[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec10[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp9, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(6)))
			StoreVarInst(struct, iVec4[Int32(0)], LoadVarInst(stack, iTemp9))
			DeclareVarInst(stack, "int", iTemp10, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec12[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp9)), LoadVarInst(struct, iVec4[Int32(1)])))
			StoreVarInst(struct, fRec14[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec14[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp10))))
			StoreVarInst(struct, fRec13[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp10)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec13[Int32(1)]), LoadVarInst(struct, fRec14[Int32(1)])))))
			StoreVarInst(struct, fRec12[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec13[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp11, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(8)))
			StoreVarInst(struct, iVec5[Int32(0)], LoadVarInst(stack, iTemp11))
			DeclareVarInst(stack, "int", iTemp12, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec15[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp11)), LoadVarInst(struct, iVec5[Int32(1)])))
			StoreVarInst(struct, fRec17[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec17[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp12))))
			StoreVarInst(struct, fRec16[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp12)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec16[Int32(1)]), LoadVarInst(struct, fRec17[Int32(1)])))))
			StoreVarInst(struct, fRec15[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec16[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp13, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(10)))
			StoreVarInst(struct, iVec6[Int32(0)], LoadVarInst(stack, iTemp13))
			DeclareVarInst(stack, "int", iTemp14, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec18[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp13)), LoadVarInst(struct, iVec6[Int32(1)])))
			StoreVarInst(struct, fRec20[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec20[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp14))))
			StoreVarInst(struct, fRec19[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp14)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec19[Int32(1)]), LoadVarInst(struct, fRec20[Int32(1)])))))
			StoreVarInst(struct, fRec18[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec19[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp15, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(12)))
			StoreVarInst(struct, iVec7[Int32(0)], LoadVarInst(stack, iTemp15))
			DeclareVarInst(stack, "int", iTemp16, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec21[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp15)), LoadVarInst(struct, iVec7[Int32(1)])))
			StoreVarInst(struct, fRec23[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec23[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp16))))
			StoreVarInst(struct, fRec22[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp16)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec22[Int32(1)]), LoadVarInst(struct, fRec23[Int32(1)])))))
			StoreVarInst(struct, fRec21[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec22[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp17, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(14)))
			StoreVarInst(struct, iVec8[Int32(0)], LoadVarInst(stack, iTemp17))
			DeclareVarInst(stack, "int", iTemp18, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec24[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp17)), LoadVarInst(struct, iVec8[Int32(1)])))
			StoreVarInst(struct, fRec26[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec26[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp18))))
			StoreVarInst(struct, fRec25[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp18)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec25[Int32(1)]), LoadVarInst(struct, fRec26[Int32(1)])))))
			StoreVarInst(struct, fRec24[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec25[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp19, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(16)))
			StoreVarInst(struct, iVec9[Int32(0)], LoadVarInst(stack, iTemp19))
			DeclareVarInst(stack, "int", iTemp20, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec27[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp19)), LoadVarInst(struct, iVec9[Int32(1)])))
			StoreVarInst(struct, fRec29[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec29[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp20))))
			StoreVarInst(struct, fRec28[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp20)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec28[Int32(1)]), LoadVarInst(struct, fRec29[Int32(1)])))))
			StoreVarInst(struct, fRec27[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec28[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp21, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(18)))
			StoreVarInst(struct, iVec10[Int32(0)], LoadVarInst(stack, iTemp21))
			DeclareVarInst(stack, "int", iTemp22, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec30[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp21)), LoadVarInst(struct, iVec10[Int32(1)])))
			StoreVarInst(struct, fRec32[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec32[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp22))))
			StoreVarInst(struct, fRec31[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp22)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec31[Int32(1)]), LoadVarInst(struct, fRec32[Int32(1)])))))
			StoreVarInst(struct, fRec30[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec31[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp23, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(20)))
			StoreVarInst(struct, iVec11[Int32(0)], LoadVarInst(stack, iTemp23))
			DeclareVarInst(stack, "int", iTemp24, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec33[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp23)), LoadVarInst(struct, iVec11[Int32(1)])))
			StoreVarInst(struct, fRec35[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec35[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp24))))
			StoreVarInst(struct, fRec34[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp24)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec34[Int32(1)]), LoadVarInst(struct, fRec35[Int32(1)])))))
			StoreVarInst(struct, fRec33[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec34[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp25, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(22)))
			StoreVarInst(struct, iVec12[Int32(0)], LoadVarInst(stack, iTemp25))
			DeclareVarInst(stack, "int", iTemp26, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec36[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp25)), LoadVarInst(struct, iVec12[Int32(1)])))
			StoreVarInst(struct, fRec38[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec38[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp26))))
			StoreVarInst(struct, fRec37[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp26)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec37[Int32(1)]), LoadVarInst(struct, fRec38[Int32(1)])))))
			StoreVarInst(struct, fRec36[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec37[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp27, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(24)))
			StoreVarInst(struct, iVec13[Int32(0)], LoadVarInst(stack, iTemp27))
			DeclareVarInst(stack, "int", iTemp28, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec39[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp27)), LoadVarInst(struct, iVec13[Int32(1)])))
			StoreVarInst(struct, fRec41[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec41[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp28))))
			StoreVarInst(struct, fRec40[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp28)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec40[Int32(1)]), LoadVarInst(struct, fRec41[Int32(1)])))))
			StoreVarInst(struct, fRec39[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec40[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp29, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(26)))
			StoreVarInst(struct, iVec14[Int32(0)], LoadVarInst(stack, iTemp29))
			DeclareVarInst(stack, "int", iTemp30, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec42[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp29)), LoadVarInst(struct, iVec14[Int32(1)])))
			StoreVarInst(struct, fRec44[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec44[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp30))))
			StoreVarInst(struct, fRec43[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp30)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec43[Int32(1)]), LoadVarInst(struct, fRec44[Int32(1)])))))
			StoreVarInst(struct, fRec42[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec43[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp31, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(28)))
			StoreVarInst(struct, iVec15[Int32(0)], LoadVarInst(stack, iTemp31))
			DeclareVarInst(stack, "int", iTemp32, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec45[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp31)), LoadVarInst(struct, iVec15[Int32(1)])))
			StoreVarInst(struct, fRec47[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec47[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp32))))
			StoreVarInst(struct, fRec46[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp32)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec46[Int32(1)]), LoadVarInst(struct, fRec47[Int32(1)])))))
			StoreVarInst(struct, fRec45[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec46[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp33, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(30)))
			StoreVarInst(struct, iVec16[Int32(0)], LoadVarInst(stack, iTemp33))
			DeclareVarInst(stack, "int", iTemp34, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec48[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp33)), LoadVarInst(struct, iVec16[Int32(1)])))
			StoreVarInst(struct, fRec50[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec50[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp34))))
			StoreVarInst(struct, fRec49[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp34)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec49[Int32(1)]), LoadVarInst(struct, fRec50[Int32(1)])))))
			StoreVarInst(struct, fRec48[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec49[Int32(1)])))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(stack, fSlow0), BinopInst("*", LoadVarInst(stack, fTemp0), LoadVarInst(struct, fRec0[Int32(0)]))), BinopInst("*", LoadVarInst(struct, fRec6[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst4)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec9[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst5)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec12[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst6)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec15[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst7)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec18[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst8)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec21[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst9)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec24[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst10)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec27[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst11)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec30[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst12)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec33[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst13)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec36[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst14)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec39[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst15)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec42[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst16)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec45[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst17)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec48[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst18)), Int32(524287))])))))
			DeclareVarInst(stack, "int", iTemp35, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(1)))
			StoreVarInst(struct, iVec17[Int32(0)], LoadVarInst(stack, iTemp35))
			DeclareVarInst(stack, "int", iTemp36, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec51[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp35)), LoadVarInst(struct, iVec17[Int32(1)])))
			StoreVarInst(struct, fRec53[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec53[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp36))))
			StoreVarInst(struct, fRec52[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp36)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec52[Int32(1)]), LoadVarInst(struct, fRec53[Int32(1)])))))
			StoreVarInst(struct, fRec51[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec52[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp37, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(3)))
			StoreVarInst(struct, iVec18[Int32(0)], LoadVarInst(stack, iTemp37))
			DeclareVarInst(stack, "int", iTemp38, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec54[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp37)), LoadVarInst(struct, iVec18[Int32(1)])))
			StoreVarInst(struct, fRec56[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec56[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp38))))
			StoreVarInst(struct, fRec55[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp38)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec55[Int32(1)]), LoadVarInst(struct, fRec56[Int32(1)])))))
			StoreVarInst(struct, fRec54[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec55[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp39, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(5)))
			StoreVarInst(struct, iVec19[Int32(0)], LoadVarInst(stack, iTemp39))
			DeclareVarInst(stack, "int", iTemp40, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec57[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp39)), LoadVarInst(struct, iVec19[Int32(1)])))
			StoreVarInst(struct, fRec59[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec59[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp40))))
			StoreVarInst(struct, fRec58[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp40)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec58[Int32(1)]), LoadVarInst(struct, fRec59[Int32(1)])))))
			StoreVarInst(struct, fRec57[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec58[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp41, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(7)))
			StoreVarInst(struct, iVec20[Int32(0)], LoadVarInst(stack, iTemp41))
			DeclareVarInst(stack, "int", iTemp42, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec60[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp41)), LoadVarInst(struct, iVec20[Int32(1)])))
			StoreVarInst(struct, fRec62[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec62[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp42))))
			StoreVarInst(struct, fRec61[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp42)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec61[Int32(1)]), LoadVarInst(struct, fRec62[Int32(1)])))))
			StoreVarInst(struct, fRec60[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec61[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp43, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(9)))
			StoreVarInst(struct, iVec21[Int32(0)], LoadVarInst(stack, iTemp43))
			DeclareVarInst(stack, "int", iTemp44, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec63[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp43)), LoadVarInst(struct, iVec21[Int32(1)])))
			StoreVarInst(struct, fRec65[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec65[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp44))))
			StoreVarInst(struct, fRec64[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp44)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec64[Int32(1)]), LoadVarInst(struct, fRec65[Int32(1)])))))
			StoreVarInst(struct, fRec63[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec64[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp45, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(11)))
			StoreVarInst(struct, iVec22[Int32(0)], LoadVarInst(stack, iTemp45))
			DeclareVarInst(stack, "int", iTemp46, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec66[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp45)), LoadVarInst(struct, iVec22[Int32(1)])))
			StoreVarInst(struct, fRec68[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec68[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp46))))
			StoreVarInst(struct, fRec67[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp46)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec67[Int32(1)]), LoadVarInst(struct, fRec68[Int32(1)])))))
			StoreVarInst(struct, fRec66[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec67[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp47, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(13)))
			StoreVarInst(struct, iVec23[Int32(0)], LoadVarInst(stack, iTemp47))
			DeclareVarInst(stack, "int", iTemp48, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec69[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp47)), LoadVarInst(struct, iVec23[Int32(1)])))
			StoreVarInst(struct, fRec71[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec71[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp48))))
			StoreVarInst(struct, fRec70[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp48)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec70[Int32(1)]), LoadVarInst(struct, fRec71[Int32(1)])))))
			StoreVarInst(struct, fRec69[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec70[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp49, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(15)))
			StoreVarInst(struct, iVec24[Int32(0)], LoadVarInst(stack, iTemp49))
			DeclareVarInst(stack, "int", iTemp50, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec72[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp49)), LoadVarInst(struct, iVec24[Int32(1)])))
			StoreVarInst(struct, fRec74[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec74[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp50))))
			StoreVarInst(struct, fRec73[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp50)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec73[Int32(1)]), LoadVarInst(struct, fRec74[Int32(1)])))))
			StoreVarInst(struct, fRec72[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec73[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp51, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(17)))
			StoreVarInst(struct, iVec25[Int32(0)], LoadVarInst(stack, iTemp51))
			DeclareVarInst(stack, "int", iTemp52, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec75[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp51)), LoadVarInst(struct, iVec25[Int32(1)])))
			StoreVarInst(struct, fRec77[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec77[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp52))))
			StoreVarInst(struct, fRec76[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp52)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec76[Int32(1)]), LoadVarInst(struct, fRec77[Int32(1)])))))
			StoreVarInst(struct, fRec75[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec76[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp53, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(19)))
			StoreVarInst(struct, iVec26[Int32(0)], LoadVarInst(stack, iTemp53))
			DeclareVarInst(stack, "int", iTemp54, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec78[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp53)), LoadVarInst(struct, iVec26[Int32(1)])))
			StoreVarInst(struct, fRec80[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec80[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp54))))
			StoreVarInst(struct, fRec79[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp54)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec79[Int32(1)]), LoadVarInst(struct, fRec80[Int32(1)])))))
			StoreVarInst(struct, fRec78[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec79[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp55, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(21)))
			StoreVarInst(struct, iVec27[Int32(0)], LoadVarInst(stack, iTemp55))
			DeclareVarInst(stack, "int", iTemp56, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec81[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp55)), LoadVarInst(struct, iVec27[Int32(1)])))
			StoreVarInst(struct, fRec83[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec83[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp56))))
			StoreVarInst(struct, fRec82[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp56)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec82[Int32(1)]), LoadVarInst(struct, fRec83[Int32(1)])))))
			StoreVarInst(struct, fRec81[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec82[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp57, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(23)))
			StoreVarInst(struct, iVec28[Int32(0)], LoadVarInst(stack, iTemp57))
			DeclareVarInst(stack, "int", iTemp58, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec84[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp57)), LoadVarInst(struct, iVec28[Int32(1)])))
			StoreVarInst(struct, fRec86[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec86[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp58))))
			StoreVarInst(struct, fRec85[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp58)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec85[Int32(1)]), LoadVarInst(struct, fRec86[Int32(1)])))))
			StoreVarInst(struct, fRec84[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec85[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp59, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(25)))
			StoreVarInst(struct, iVec29[Int32(0)], LoadVarInst(stack, iTemp59))
			DeclareVarInst(stack, "int", iTemp60, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec87[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp59)), LoadVarInst(struct, iVec29[Int32(1)])))
			StoreVarInst(struct, fRec89[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec89[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp60))))
			StoreVarInst(struct, fRec88[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp60)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec88[Int32(1)]), LoadVarInst(struct, fRec89[Int32(1)])))))
			StoreVarInst(struct, fRec87[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec88[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp61, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(27)))
			StoreVarInst(struct, iVec30[Int32(0)], LoadVarInst(stack, iTemp61))
			DeclareVarInst(stack, "int", iTemp62, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec90[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp61)), LoadVarInst(struct, iVec30[Int32(1)])))
			StoreVarInst(struct, fRec92[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec92[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp62))))
			StoreVarInst(struct, fRec91[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp62)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec91[Int32(1)]), LoadVarInst(struct, fRec92[Int32(1)])))))
			StoreVarInst(struct, fRec90[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec91[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp63, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(29)))
			StoreVarInst(struct, iVec31[Int32(0)], LoadVarInst(stack, iTemp63))
			DeclareVarInst(stack, "int", iTemp64, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec93[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp63)), LoadVarInst(struct, iVec31[Int32(1)])))
			StoreVarInst(struct, fRec95[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec95[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp64))))
			StoreVarInst(struct, fRec94[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp64)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec94[Int32(1)]), LoadVarInst(struct, fRec95[Int32(1)])))))
			StoreVarInst(struct, fRec93[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec94[Int32(1)])))
			DeclareVarInst(stack, "int", iTemp65, BinopInst("==", LoadVarInst(struct, iRec2[Int32(0)]), Int32(31)))
			StoreVarInst(struct, iVec32[Int32(0)], LoadVarInst(stack, iTemp65))
			DeclareVarInst(stack, "int", iTemp66, BinopInst("|", BinopInst("|", BinopInst(">", LoadVarInst(struct, fRec96[Int32(1)]), Float(0.0f)), LoadVarInst(stack, iTemp65)), LoadVarInst(struct, iVec32[Int32(1)])))
			StoreVarInst(struct, fRec98[Int32(0)], BinopInst("*", BinopInst("-", LoadVarInst(struct, fRec98[Int32(1)]), LoadVarInst(struct, fConst3)), CastInst("float", LoadVarInst(stack, iTemp66))))
			StoreVarInst(struct, fRec97[Int32(0)], BinopInst("*", CastInst("float", LoadVarInst(stack, iTemp66)), BinopInst("+", LoadVarInst(struct, fConst2), BinopInst("+", LoadVarInst(struct, fRec97[Int32(1)]), LoadVarInst(struct, fRec98[Int32(1)])))))
			StoreVarInst(struct, fRec96[Int32(0)], FunCallInst("max_f", Float(0.0f), LoadVarInst(struct, fRec97[Int32(1)])))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", LoadVarInst(struct, fRec51[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst19)), Int32(524287))])), BinopInst("*", LoadVarInst(struct, fRec54[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst20)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec57[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst21)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec60[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst22)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec63[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst23)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec66[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst24)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec69[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst25)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec72[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst26)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec75[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst27)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec78[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst28)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec81[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst29)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec84[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst30)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec87[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst31)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec90[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst32)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec93[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst33)), Int32(524287))]))), BinopInst("*", LoadVarInst(struct, fRec96[Int32(0)]), LoadVarInst(struct, fVec2[BinopInst("&", BinopInst("-", LoadVarInst(struct, IOTA), LoadVarInst(struct, iConst34)), Int32(524287))])))))
			StoreVarInst(struct, iRec3[Int32(1)], LoadVarInst(struct, iRec3[Int32(0)]))
			StoreVarInst(struct, iRec4[Int32(1)], LoadVarInst(struct, iRec4[Int32(0)]))
			StoreVarInst(struct, iRec2[Int32(1)], LoadVarInst(struct, iRec2[Int32(0)]))
			StoreVarInst(struct, iVec0[Int32(1)], LoadVarInst(struct, iVec0[Int32(0)]))
			StoreVarInst(struct, fRec5[Int32(1)], LoadVarInst(struct, fRec5[Int32(0)]))
			StoreVarInst(struct, fRec1[Int32(1)], LoadVarInst(struct, fRec1[Int32(0)]))
			StoreVarInst(struct, fRec0[Int32(1)], LoadVarInst(struct, fRec0[Int32(0)]))
			StoreVarInst(struct, iVec1[Int32(1)], LoadVarInst(struct, iVec1[Int32(0)]))
			StoreVarInst(struct, fRec8[Int32(1)], LoadVarInst(struct, fRec8[Int32(0)]))
			StoreVarInst(struct, fRec7[Int32(1)], LoadVarInst(struct, fRec7[Int32(0)]))
			StoreVarInst(struct, fRec6[Int32(1)], LoadVarInst(struct, fRec6[Int32(0)]))
			StoreVarInst(struct, IOTA, BinopInst("+", LoadVarInst(struct, IOTA), Int32(1)))
			StoreVarInst(struct, iVec3[Int32(1)], LoadVarInst(struct, iVec3[Int32(0)]))
			StoreVarInst(struct, fRec11[Int32(1)], LoadVarInst(struct, fRec11[Int32(0)]))
			StoreVarInst(struct, fRec10[Int32(1)], LoadVarInst(struct, fRec10[Int32(0)]))
			StoreVarInst(struct, fRec9[Int32(1)], LoadVarInst(struct, fRec9[Int32(0)]))
			StoreVarInst(struct, iVec4[Int32(1)], LoadVarInst(struct, iVec4[Int32(0)]))
			StoreVarInst(struct, fRec14[Int32(1)], LoadVarInst(struct, fRec14[Int32(0)]))
			StoreVarInst(struct, fRec13[Int32(1)], LoadVarInst(struct, fRec13[Int32(0)]))
			StoreVarInst(struct, fRec12[Int32(1)], LoadVarInst(struct, fRec12[Int32(0)]))
			StoreVarInst(struct, iVec5[Int32(1)], LoadVarInst(struct, iVec5[Int32(0)]))
			StoreVarInst(struct, fRec17[Int32(1)], LoadVarInst(struct, fRec17[Int32(0)]))
			StoreVarInst(struct, fRec16[Int32(1)], LoadVarInst(struct, fRec16[Int32(0)]))
			StoreVarInst(struct, fRec15[Int32(1)], LoadVarInst(struct, fRec15[Int32(0)]))
			StoreVarInst(struct, iVec6[Int32(1)], LoadVarInst(struct, iVec6[Int32(0)]))
			StoreVarInst(struct, fRec20[Int32(1)], LoadVarInst(struct, fRec20[Int32(0)]))
			StoreVarInst(struct, fRec19[Int32(1)], LoadVarInst(struct, fRec19[Int32(0)]))
			StoreVarInst(struct, fRec18[Int32(1)], LoadVarInst(struct, fRec18[Int32(0)]))
			StoreVarInst(struct, iVec7[Int32(1)], LoadVarInst(struct, iVec7[Int32(0)]))
			StoreVarInst(struct, fRec23[Int32(1)], LoadVarInst(struct, fRec23[Int32(0)]))
			StoreVarInst(struct, fRec22[Int32(1)], LoadVarInst(struct, fRec22[Int32(0)]))
			StoreVarInst(struct, fRec21[Int32(1)], LoadVarInst(struct, fRec21[Int32(0)]))
			StoreVarInst(struct, iVec8[Int32(1)], LoadVarInst(struct, iVec8[Int32(0)]))
			StoreVarInst(struct, fRec26[Int32(1)], LoadVarInst(struct, fRec26[Int32(0)]))
			StoreVarInst(struct, fRec25[Int32(1)], LoadVarInst(struct, fRec25[Int32(0)]))
			StoreVarInst(struct, fRec24[Int32(1)], LoadVarInst(struct, fRec24[Int32(0)]))
			StoreVarInst(struct, iVec9[Int32(1)], LoadVarInst(struct, iVec9[Int32(0)]))
			StoreVarInst(struct, fRec29[Int32(1)], LoadVarInst(struct, fRec29[Int32(0)]))
			StoreVarInst(struct, fRec28[Int32(1)], LoadVarInst(struct, fRec28[Int32(0)]))
			StoreVarInst(struct, fRec27[Int32(1)], LoadVarInst(struct, fRec27[Int32(0)]))
			StoreVarInst(struct, iVec10[Int32(1)], LoadVarInst(struct, iVec10[Int32(0)]))
			StoreVarInst(struct, fRec32[Int32(1)], LoadVarInst(struct, fRec32[Int32(0)]))
			StoreVarInst(struct, fRec31[Int32(1)], LoadVarInst(struct, fRec31[Int32(0)]))
			StoreVarInst(struct, fRec30[Int32(1)], LoadVarInst(struct, fRec30[Int32(0)]))
			StoreVarInst(struct, iVec11[Int32(1)], LoadVarInst(struct, iVec11[Int32(0)]))
			StoreVarInst(struct, fRec35[Int32(1)], LoadVarInst(struct, fRec35[Int32(0)]))
			StoreVarInst(struct, fRec34[Int32(1)], LoadVarInst(struct, fRec34[Int32(0)]))
			StoreVarInst(struct, fRec33[Int32(1)], LoadVarInst(struct, fRec33[Int32(0)]))
			StoreVarInst(struct, iVec12[Int32(1)], LoadVarInst(struct, iVec12[Int32(0)]))
			StoreVarInst(struct, fRec38[Int32(1)], LoadVarInst(struct, fRec38[Int32(0)]))
			StoreVarInst(struct, fRec37[Int32(1)], LoadVarInst(struct, fRec37[Int32(0)]))
			StoreVarInst(struct, fRec36[Int32(1)], LoadVarInst(struct, fRec36[Int32(0)]))
			StoreVarInst(struct, iVec13[Int32(1)], LoadVarInst(struct, iVec13[Int32(0)]))
			StoreVarInst(struct, fRec41[Int32(1)], LoadVarInst(struct, fRec41[Int32(0)]))
			StoreVarInst(struct, fRec40[Int32(1)], LoadVarInst(struct, fRec40[Int32(0)]))
			StoreVarInst(struct, fRec39[Int32(1)], LoadVarInst(struct, fRec39[Int32(0)]))
			StoreVarInst(struct, iVec14[Int32(1)], LoadVarInst(struct, iVec14[Int32(0)]))
			StoreVarInst(struct, fRec44[Int32(1)], LoadVarInst(struct, fRec44[Int32(0)]))
			StoreVarInst(struct, fRec43[Int32(1)], LoadVarInst(struct, fRec43[Int32(0)]))
			StoreVarInst(struct, fRec42[Int32(1)], LoadVarInst(struct, fRec42[Int32(0)]))
			StoreVarInst(struct, iVec15[Int32(1)], LoadVarInst(struct, iVec15[Int32(0)]))
			StoreVarInst(struct, fRec47[Int32(1)], LoadVarInst(struct, fRec47[Int32(0)]))
			StoreVarInst(struct, fRec46[Int32(1)], LoadVarInst(struct, fRec46[Int32(0)]))
			StoreVarInst(struct, fRec45[Int32(1)], LoadVarInst(struct, fRec45[Int32(0)]))
			StoreVarInst(struct, iVec16[Int32(1)], LoadVarInst(struct, iVec16[Int32(0)]))
			StoreVarInst(struct, fRec50[Int32(1)], LoadVarInst(struct, fRec50[Int32(0)]))
			StoreVarInst(struct, fRec49[Int32(1)], LoadVarInst(struct, fRec49[Int32(0)]))
			StoreVarInst(struct, fRec48[Int32(1)], LoadVarInst(struct, fRec48[Int32(0)]))
			StoreVarInst(struct, iVec17[Int32(1)], LoadVarInst(struct, iVec17[Int32(0)]))
			StoreVarInst(struct, fRec53[Int32(1)], LoadVarInst(struct, fRec53[Int32(0)]))
			StoreVarInst(struct, fRec52[Int32(1)], LoadVarInst(struct, fRec52[Int32(0)]))
			StoreVarInst(struct, fRec51[Int32(1)], LoadVarInst(struct, fRec51[Int32(0)]))
			StoreVarInst(struct, iVec18[Int32(1)], LoadVarInst(struct, iVec18[Int32(0)]))
			StoreVarInst(struct, fRec56[Int32(1)], LoadVarInst(struct, fRec56[Int32(0)]))
			StoreVarInst(struct, fRec55[Int32(1)], LoadVarInst(struct, fRec55[Int32(0)]))
			StoreVarInst(struct, fRec54[Int32(1)], LoadVarInst(struct, fRec54[Int32(0)]))
			StoreVarInst(struct, iVec19[Int32(1)], LoadVarInst(struct, iVec19[Int32(0)]))
			StoreVarInst(struct, fRec59[Int32(1)], LoadVarInst(struct, fRec59[Int32(0)]))
			StoreVarInst(struct, fRec58[Int32(1)], LoadVarInst(struct, fRec58[Int32(0)]))
			StoreVarInst(struct, fRec57[Int32(1)], LoadVarInst(struct, fRec57[Int32(0)]))
			StoreVarInst(struct, iVec20[Int32(1)], LoadVarInst(struct, iVec20[Int32(0)]))
			StoreVarInst(struct, fRec62[Int32(1)], LoadVarInst(struct, fRec62[Int32(0)]))
			StoreVarInst(struct, fRec61[Int32(1)], LoadVarInst(struct, fRec61[Int32(0)]))
			StoreVarInst(struct, fRec60[Int32(1)], LoadVarInst(struct, fRec60[Int32(0)]))
			StoreVarInst(struct, iVec21[Int32(1)], LoadVarInst(struct, iVec21[Int32(0)]))
			StoreVarInst(struct, fRec65[Int32(1)], LoadVarInst(struct, fRec65[Int32(0)]))
			StoreVarInst(struct, fRec64[Int32(1)], LoadVarInst(struct, fRec64[Int32(0)]))
			StoreVarInst(struct, fRec63[Int32(1)], LoadVarInst(struct, fRec63[Int32(0)]))
			StoreVarInst(struct, iVec22[Int32(1)], LoadVarInst(struct, iVec22[Int32(0)]))
			StoreVarInst(struct, fRec68[Int32(1)], LoadVarInst(struct, fRec68[Int32(0)]))
			StoreVarInst(struct, fRec67[Int32(1)], LoadVarInst(struct, fRec67[Int32(0)]))
			StoreVarInst(struct, fRec66[Int32(1)], LoadVarInst(struct, fRec66[Int32(0)]))
			StoreVarInst(struct, iVec23[Int32(1)], LoadVarInst(struct, iVec23[Int32(0)]))
			StoreVarInst(struct, fRec71[Int32(1)], LoadVarInst(struct, fRec71[Int32(0)]))
			StoreVarInst(struct, fRec70[Int32(1)], LoadVarInst(struct, fRec70[Int32(0)]))
			StoreVarInst(struct, fRec69[Int32(1)], LoadVarInst(struct, fRec69[Int32(0)]))
			StoreVarInst(struct, iVec24[Int32(1)], LoadVarInst(struct, iVec24[Int32(0)]))
			StoreVarInst(struct, fRec74[Int32(1)], LoadVarInst(struct, fRec74[Int32(0)]))
			StoreVarInst(struct, fRec73[Int32(1)], LoadVarInst(struct, fRec73[Int32(0)]))
			StoreVarInst(struct, fRec72[Int32(1)], LoadVarInst(struct, fRec72[Int32(0)]))
			StoreVarInst(struct, iVec25[Int32(1)], LoadVarInst(struct, iVec25[Int32(0)]))
			StoreVarInst(struct, fRec77[Int32(1)], LoadVarInst(struct, fRec77[Int32(0)]))
			StoreVarInst(struct, fRec76[Int32(1)], LoadVarInst(struct, fRec76[Int32(0)]))
			StoreVarInst(struct, fRec75[Int32(1)], LoadVarInst(struct, fRec75[Int32(0)]))
			StoreVarInst(struct, iVec26[Int32(1)], LoadVarInst(struct, iVec26[Int32(0)]))
			StoreVarInst(struct, fRec80[Int32(1)], LoadVarInst(struct, fRec80[Int32(0)]))
			StoreVarInst(struct, fRec79[Int32(1)], LoadVarInst(struct, fRec79[Int32(0)]))
			StoreVarInst(struct, fRec78[Int32(1)], LoadVarInst(struct, fRec78[Int32(0)]))
			StoreVarInst(struct, iVec27[Int32(1)], LoadVarInst(struct, iVec27[Int32(0)]))
			StoreVarInst(struct, fRec83[Int32(1)], LoadVarInst(struct, fRec83[Int32(0)]))
			StoreVarInst(struct, fRec82[Int32(1)], LoadVarInst(struct, fRec82[Int32(0)]))
			StoreVarInst(struct, fRec81[Int32(1)], LoadVarInst(struct, fRec81[Int32(0)]))
			StoreVarInst(struct, iVec28[Int32(1)], LoadVarInst(struct, iVec28[Int32(0)]))
			StoreVarInst(struct, fRec86[Int32(1)], LoadVarInst(struct, fRec86[Int32(0)]))
			StoreVarInst(struct, fRec85[Int32(1)], LoadVarInst(struct, fRec85[Int32(0)]))
			StoreVarInst(struct, fRec84[Int32(1)], LoadVarInst(struct, fRec84[Int32(0)]))
			StoreVarInst(struct, iVec29[Int32(1)], LoadVarInst(struct, iVec29[Int32(0)]))
			StoreVarInst(struct, fRec89[Int32(1)], LoadVarInst(struct, fRec89[Int32(0)]))
			StoreVarInst(struct, fRec88[Int32(1)], LoadVarInst(struct, fRec88[Int32(0)]))
			StoreVarInst(struct, fRec87[Int32(1)], LoadVarInst(struct, fRec87[Int32(0)]))
			StoreVarInst(struct, iVec30[Int32(1)], LoadVarInst(struct, iVec30[Int32(0)]))
			StoreVarInst(struct, fRec92[Int32(1)], LoadVarInst(struct, fRec92[Int32(0)]))
			StoreVarInst(struct, fRec91[Int32(1)], LoadVarInst(struct, fRec91[Int32(0)]))
			StoreVarInst(struct, fRec90[Int32(1)], LoadVarInst(struct, fRec90[Int32(0)]))
			StoreVarInst(struct, iVec31[Int32(1)], LoadVarInst(struct, iVec31[Int32(0)]))
			StoreVarInst(struct, fRec95[Int32(1)], LoadVarInst(struct, fRec95[Int32(0)]))
			StoreVarInst(struct, fRec94[Int32(1)], LoadVarInst(struct, fRec94[Int32(0)]))
			StoreVarInst(struct, fRec93[Int32(1)], LoadVarInst(struct, fRec93[Int32(0)]))
			StoreVarInst(struct, iVec32[Int32(1)], LoadVarInst(struct, iVec32[Int32(0)]))
			StoreVarInst(struct, fRec98[Int32(1)], LoadVarInst(struct, fRec98[Int32(0)]))
			StoreVarInst(struct, fRec97[Int32(1)], LoadVarInst(struct, fRec97[Int32(0)]))
			StoreVarInst(struct, fRec96[Int32(1)], LoadVarInst(struct, fRec96[Int32(0)]))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 136 bytes
Heap size int* = 280 bytes
Heap size real = 2097944 bytes
Heap size = 2098360 bytes
Stack size in compute = 44 bytes

