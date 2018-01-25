======= Container "mydsp" ==========

======= Sub container begin ==========

======= Sub container end ==========

======= User Interface ==========

BlockInst 
	OpenVerticalBox("DNN")
	CloseboxInst
	EndBlock

======= Declarations ==========

BlockInst 
	DeclareVarInst(struct, "int", fSamplingFreq)
	EndBlock

DeclareFunInst("int", "getNumInputs")
	BlockInst 
		RetInst(Int32(8))
		EndBlock
	EndDeclare

DeclareFunInst("int", "getNumOutputs")
	BlockInst 
		RetInst(Int32(8))
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
	EndBlock

======= Compute control ==========

Instructions complexity
Load = 16
Store = 0
Binop = 0
Numbers = 0
Declare = 16
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
	DeclareVarInst(stack, FAUSTFLOAT*, input6, LoadVarInst(kFunArgs, inputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input7, LoadVarInst(kFunArgs, inputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	EndBlock

======= Compute DSP ==========

Instructions complexity
Load = 124
Store = 9
Binop = 172
Numbers = 93
Declare = 27
Cast = 29
Select = 0
Loop = 1
Funcall = 0

ForLoopInst 
	DeclareVarInst(loop, "int", i, Int32(0))
	BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
	StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
	BlockInst 
		DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input7[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp1, CastInst("float", LoadVarInst(stack, input6[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp2, CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp3, CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp4, CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp5, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp6, CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp7, BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp0)), BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp1)), BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp2)), BinopInst("+", BinopInst("*", Float(40.0f), LoadVarInst(stack, fTemp3)), BinopInst("+", BinopInst("+", BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp4)), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp5))), BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp6))))))))
		DeclareVarInst(stack, "float", fTemp8, BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp7), Float(0.0f))), LoadVarInst(stack, fTemp7)))
		DeclareVarInst(stack, "float", fTemp9, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
		DeclareVarInst(stack, "float", fTemp10, BinopInst("+", BinopInst("*", Float(43.0f), LoadVarInst(stack, fTemp0)), BinopInst("+", BinopInst("+", BinopInst("*", Float(23.0f), LoadVarInst(stack, fTemp2)), BinopInst("+", BinopInst("*", Float(53.0f), LoadVarInst(stack, fTemp3)), BinopInst("+", BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp6)), BinopInst("+", BinopInst("*", Float(33.0f), LoadVarInst(stack, fTemp4)), BinopInst("+", BinopInst("*", Float(13.0f), LoadVarInst(stack, fTemp9)), BinopInst("*", Float(63.0f), LoadVarInst(stack, fTemp5))))))), BinopInst("*", Float(73.0f), LoadVarInst(stack, fTemp1)))))
		DeclareVarInst(stack, "float", fTemp11, BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp10), Float(0.0f))), LoadVarInst(stack, fTemp10)))
		DeclareVarInst(stack, "float", fTemp12, BinopInst("+", BinopInst("*", Float(61.0f), LoadVarInst(stack, fTemp0)), BinopInst("+", BinopInst("*", Float(11.0f), LoadVarInst(stack, fTemp1)), BinopInst("+", BinopInst("*", Float(41.0f), LoadVarInst(stack, fTemp2)), BinopInst("+", BinopInst("+", BinopInst("*", Float(21.0f), LoadVarInst(stack, fTemp6)), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("*", Float(31.0f), LoadVarInst(stack, fTemp9))), BinopInst("*", Float(51.0f), LoadVarInst(stack, fTemp4)))), BinopInst("*", Float(71.0f), LoadVarInst(stack, fTemp3)))))))
		DeclareVarInst(stack, "float", fTemp13, BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp12), Float(0.0f))), LoadVarInst(stack, fTemp12)))
		DeclareVarInst(stack, "float", fTemp14, BinopInst("+", BinopInst("+", BinopInst("*", Float(24.0f), LoadVarInst(stack, fTemp1)), BinopInst("+", BinopInst("*", Float(54.0f), LoadVarInst(stack, fTemp2)), BinopInst("+", BinopInst("*", Float(4.0f), LoadVarInst(stack, fTemp3)), BinopInst("+", BinopInst("*", Float(34.0f), LoadVarInst(stack, fTemp6)), BinopInst("+", BinopInst("+", BinopInst("*", Float(14.0f), LoadVarInst(stack, fTemp5)), BinopInst("*", Float(44.0f), LoadVarInst(stack, fTemp9))), BinopInst("*", Float(64.0f), LoadVarInst(stack, fTemp4))))))), BinopInst("*", Float(74.0f), LoadVarInst(stack, fTemp0))))
		DeclareVarInst(stack, "float", fTemp15, BinopInst("*", LoadVarInst(stack, fTemp14), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp14), Float(0.0f)))))
		DeclareVarInst(stack, "float", fTemp16, BinopInst("+", BinopInst("*", Float(12.0f), LoadVarInst(stack, fTemp0)), BinopInst("+", BinopInst("*", Float(42.0f), LoadVarInst(stack, fTemp1)), BinopInst("+", BinopInst("+", BinopInst("*", Float(22.0f), LoadVarInst(stack, fTemp3)), BinopInst("+", BinopInst("*", Float(52.0f), LoadVarInst(stack, fTemp6)), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(stack, fTemp4)), BinopInst("+", BinopInst("*", Float(32.0f), LoadVarInst(stack, fTemp5)), BinopInst("*", Float(62.0f), LoadVarInst(stack, fTemp9)))))), BinopInst("*", Float(72.0f), LoadVarInst(stack, fTemp2))))))
		DeclareVarInst(stack, "float", fTemp17, BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp16), Float(0.0f))), LoadVarInst(stack, fTemp16)))
		DeclareVarInst(stack, "float", fTemp18, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(110.0f), LoadVarInst(stack, fTemp11))), BinopInst("*", Float(120.0f), LoadVarInst(stack, fTemp13))), BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp15))), BinopInst("*", Float(140.0f), LoadVarInst(stack, fTemp17))))
		StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fTemp18), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp18), Float(0.0f))))))
		DeclareVarInst(stack, "float", fTemp19, BinopInst("+", BinopInst("*", Float(121.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("*", Float(111.0f), LoadVarInst(stack, fTemp15)), BinopInst("+", BinopInst("*", Float(101.0f), LoadVarInst(stack, fTemp13)), BinopInst("+", BinopInst("*", Float(131.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(141.0f), LoadVarInst(stack, fTemp11)))))))
		StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp19), Float(0.0f))), LoadVarInst(stack, fTemp19))))
		DeclareVarInst(stack, "float", fTemp20, BinopInst("+", BinopInst("*", Float(102.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(112.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(122.0f), LoadVarInst(stack, fTemp11))), BinopInst("*", Float(132.0f), LoadVarInst(stack, fTemp13))), BinopInst("*", Float(142.0f), LoadVarInst(stack, fTemp15)))))
		StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp20), Float(0.0f))), LoadVarInst(stack, fTemp20))))
		DeclareVarInst(stack, "float", fTemp21, BinopInst("+", BinopInst("*", Float(133.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("*", Float(123.0f), LoadVarInst(stack, fTemp15)), BinopInst("+", BinopInst("*", Float(113.0f), LoadVarInst(stack, fTemp13)), BinopInst("+", BinopInst("*", Float(103.0f), LoadVarInst(stack, fTemp11)), BinopInst("*", Float(143.0f), LoadVarInst(stack, fTemp8)))))))
		StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp21), Float(0.0f))), LoadVarInst(stack, fTemp21))))
		DeclareVarInst(stack, "float", fTemp22, BinopInst("+", BinopInst("*", Float(114.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("*", Float(104.0f), LoadVarInst(stack, fTemp15)), BinopInst("+", BinopInst("+", BinopInst("*", Float(124.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(134.0f), LoadVarInst(stack, fTemp11))), BinopInst("*", Float(144.0f), LoadVarInst(stack, fTemp13))))))
		StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp22), Float(0.0f))), LoadVarInst(stack, fTemp22))))
		DeclareVarInst(stack, "float", fTemp23, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(105.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(115.0f), LoadVarInst(stack, fTemp11))), BinopInst("*", Float(125.0f), LoadVarInst(stack, fTemp13))), BinopInst("*", Float(135.0f), LoadVarInst(stack, fTemp15))), BinopInst("*", Float(145.0f), LoadVarInst(stack, fTemp17))))
		StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fTemp23), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp23), Float(0.0f))))))
		DeclareVarInst(stack, "float", fTemp24, BinopInst("+", BinopInst("*", Float(126.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("*", Float(116.0f), LoadVarInst(stack, fTemp15)), BinopInst("+", BinopInst("*", Float(106.0f), LoadVarInst(stack, fTemp13)), BinopInst("+", BinopInst("*", Float(136.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(146.0f), LoadVarInst(stack, fTemp11)))))))
		StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp24), Float(0.0f))), LoadVarInst(stack, fTemp24))))
		DeclareVarInst(stack, "float", fTemp25, BinopInst("+", BinopInst("*", Float(107.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(117.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(127.0f), LoadVarInst(stack, fTemp11))), BinopInst("*", Float(137.0f), LoadVarInst(stack, fTemp13))), BinopInst("*", Float(147.0f), LoadVarInst(stack, fTemp15)))))
		StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp25), Float(0.0f))), LoadVarInst(stack, fTemp25))))
		EndBlock
	EndForLoop

======= Flatten FIR ==========

BlockInst 
	========== Declaration part ==========
	DeclareVarInst(struct, "int", fSamplingFreq)
	========== Init method ==========
	StoreVarInst(struct, fSamplingFreq, LoadVarInst(kFunArgs, samplingFreq))
	========== Static init method ==========
	========== Subcontainers ==========
	========== Compute control ==========
	DeclareVarInst(stack, FAUSTFLOAT*, input0, LoadVarInst(kFunArgs, inputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input1, LoadVarInst(kFunArgs, inputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input2, LoadVarInst(kFunArgs, inputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input3, LoadVarInst(kFunArgs, inputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input4, LoadVarInst(kFunArgs, inputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input5, LoadVarInst(kFunArgs, inputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input6, LoadVarInst(kFunArgs, inputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, input7, LoadVarInst(kFunArgs, inputs[Int32(7)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output0, LoadVarInst(kFunArgs, outputs[Int32(0)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output1, LoadVarInst(kFunArgs, outputs[Int32(1)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output2, LoadVarInst(kFunArgs, outputs[Int32(2)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output3, LoadVarInst(kFunArgs, outputs[Int32(3)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output4, LoadVarInst(kFunArgs, outputs[Int32(4)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output5, LoadVarInst(kFunArgs, outputs[Int32(5)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output6, LoadVarInst(kFunArgs, outputs[Int32(6)]))
	DeclareVarInst(stack, FAUSTFLOAT*, output7, LoadVarInst(kFunArgs, outputs[Int32(7)]))
	========== Compute DSP ==========
	ForLoopInst 
		DeclareVarInst(loop, "int", i, Int32(0))
		BinopInst("<", LoadVarInst(loop, i), LoadVarInst(kFunArgs, count))
		StoreVarInst(loop, i, BinopInst("+", LoadVarInst(loop, i), Int32(1)))
		BlockInst 
			DeclareVarInst(stack, "float", fTemp0, CastInst("float", LoadVarInst(stack, input7[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp1, CastInst("float", LoadVarInst(stack, input6[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp2, CastInst("float", LoadVarInst(stack, input5[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp3, CastInst("float", LoadVarInst(stack, input4[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp4, CastInst("float", LoadVarInst(stack, input2[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp5, CastInst("float", LoadVarInst(stack, input1[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp6, CastInst("float", LoadVarInst(stack, input3[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp7, BinopInst("+", BinopInst("*", Float(30.0f), LoadVarInst(stack, fTemp0)), BinopInst("+", BinopInst("*", Float(60.0f), LoadVarInst(stack, fTemp1)), BinopInst("+", BinopInst("*", Float(10.0f), LoadVarInst(stack, fTemp2)), BinopInst("+", BinopInst("*", Float(40.0f), LoadVarInst(stack, fTemp3)), BinopInst("+", BinopInst("+", BinopInst("*", Float(20.0f), LoadVarInst(stack, fTemp4)), BinopInst("*", Float(50.0f), LoadVarInst(stack, fTemp5))), BinopInst("*", Float(70.0f), LoadVarInst(stack, fTemp6))))))))
			DeclareVarInst(stack, "float", fTemp8, BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp7), Float(0.0f))), LoadVarInst(stack, fTemp7)))
			DeclareVarInst(stack, "float", fTemp9, CastInst("float", LoadVarInst(stack, input0[LoadVarInst(loop, i)])))
			DeclareVarInst(stack, "float", fTemp10, BinopInst("+", BinopInst("*", Float(43.0f), LoadVarInst(stack, fTemp0)), BinopInst("+", BinopInst("+", BinopInst("*", Float(23.0f), LoadVarInst(stack, fTemp2)), BinopInst("+", BinopInst("*", Float(53.0f), LoadVarInst(stack, fTemp3)), BinopInst("+", BinopInst("*", Float(3.0f), LoadVarInst(stack, fTemp6)), BinopInst("+", BinopInst("*", Float(33.0f), LoadVarInst(stack, fTemp4)), BinopInst("+", BinopInst("*", Float(13.0f), LoadVarInst(stack, fTemp9)), BinopInst("*", Float(63.0f), LoadVarInst(stack, fTemp5))))))), BinopInst("*", Float(73.0f), LoadVarInst(stack, fTemp1)))))
			DeclareVarInst(stack, "float", fTemp11, BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp10), Float(0.0f))), LoadVarInst(stack, fTemp10)))
			DeclareVarInst(stack, "float", fTemp12, BinopInst("+", BinopInst("*", Float(61.0f), LoadVarInst(stack, fTemp0)), BinopInst("+", BinopInst("*", Float(11.0f), LoadVarInst(stack, fTemp1)), BinopInst("+", BinopInst("*", Float(41.0f), LoadVarInst(stack, fTemp2)), BinopInst("+", BinopInst("+", BinopInst("*", Float(21.0f), LoadVarInst(stack, fTemp6)), BinopInst("+", BinopInst("+", LoadVarInst(stack, fTemp5), BinopInst("*", Float(31.0f), LoadVarInst(stack, fTemp9))), BinopInst("*", Float(51.0f), LoadVarInst(stack, fTemp4)))), BinopInst("*", Float(71.0f), LoadVarInst(stack, fTemp3)))))))
			DeclareVarInst(stack, "float", fTemp13, BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp12), Float(0.0f))), LoadVarInst(stack, fTemp12)))
			DeclareVarInst(stack, "float", fTemp14, BinopInst("+", BinopInst("+", BinopInst("*", Float(24.0f), LoadVarInst(stack, fTemp1)), BinopInst("+", BinopInst("*", Float(54.0f), LoadVarInst(stack, fTemp2)), BinopInst("+", BinopInst("*", Float(4.0f), LoadVarInst(stack, fTemp3)), BinopInst("+", BinopInst("*", Float(34.0f), LoadVarInst(stack, fTemp6)), BinopInst("+", BinopInst("+", BinopInst("*", Float(14.0f), LoadVarInst(stack, fTemp5)), BinopInst("*", Float(44.0f), LoadVarInst(stack, fTemp9))), BinopInst("*", Float(64.0f), LoadVarInst(stack, fTemp4))))))), BinopInst("*", Float(74.0f), LoadVarInst(stack, fTemp0))))
			DeclareVarInst(stack, "float", fTemp15, BinopInst("*", LoadVarInst(stack, fTemp14), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp14), Float(0.0f)))))
			DeclareVarInst(stack, "float", fTemp16, BinopInst("+", BinopInst("*", Float(12.0f), LoadVarInst(stack, fTemp0)), BinopInst("+", BinopInst("*", Float(42.0f), LoadVarInst(stack, fTemp1)), BinopInst("+", BinopInst("+", BinopInst("*", Float(22.0f), LoadVarInst(stack, fTemp3)), BinopInst("+", BinopInst("*", Float(52.0f), LoadVarInst(stack, fTemp6)), BinopInst("+", BinopInst("*", Float(2.0f), LoadVarInst(stack, fTemp4)), BinopInst("+", BinopInst("*", Float(32.0f), LoadVarInst(stack, fTemp5)), BinopInst("*", Float(62.0f), LoadVarInst(stack, fTemp9)))))), BinopInst("*", Float(72.0f), LoadVarInst(stack, fTemp2))))))
			DeclareVarInst(stack, "float", fTemp17, BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp16), Float(0.0f))), LoadVarInst(stack, fTemp16)))
			DeclareVarInst(stack, "float", fTemp18, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(100.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(110.0f), LoadVarInst(stack, fTemp11))), BinopInst("*", Float(120.0f), LoadVarInst(stack, fTemp13))), BinopInst("*", Float(130.0f), LoadVarInst(stack, fTemp15))), BinopInst("*", Float(140.0f), LoadVarInst(stack, fTemp17))))
			StoreVarInst(stack, output0[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fTemp18), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp18), Float(0.0f))))))
			DeclareVarInst(stack, "float", fTemp19, BinopInst("+", BinopInst("*", Float(121.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("*", Float(111.0f), LoadVarInst(stack, fTemp15)), BinopInst("+", BinopInst("*", Float(101.0f), LoadVarInst(stack, fTemp13)), BinopInst("+", BinopInst("*", Float(131.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(141.0f), LoadVarInst(stack, fTemp11)))))))
			StoreVarInst(stack, output1[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp19), Float(0.0f))), LoadVarInst(stack, fTemp19))))
			DeclareVarInst(stack, "float", fTemp20, BinopInst("+", BinopInst("*", Float(102.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(112.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(122.0f), LoadVarInst(stack, fTemp11))), BinopInst("*", Float(132.0f), LoadVarInst(stack, fTemp13))), BinopInst("*", Float(142.0f), LoadVarInst(stack, fTemp15)))))
			StoreVarInst(stack, output2[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp20), Float(0.0f))), LoadVarInst(stack, fTemp20))))
			DeclareVarInst(stack, "float", fTemp21, BinopInst("+", BinopInst("*", Float(133.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("*", Float(123.0f), LoadVarInst(stack, fTemp15)), BinopInst("+", BinopInst("*", Float(113.0f), LoadVarInst(stack, fTemp13)), BinopInst("+", BinopInst("*", Float(103.0f), LoadVarInst(stack, fTemp11)), BinopInst("*", Float(143.0f), LoadVarInst(stack, fTemp8)))))))
			StoreVarInst(stack, output3[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp21), Float(0.0f))), LoadVarInst(stack, fTemp21))))
			DeclareVarInst(stack, "float", fTemp22, BinopInst("+", BinopInst("*", Float(114.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("*", Float(104.0f), LoadVarInst(stack, fTemp15)), BinopInst("+", BinopInst("+", BinopInst("*", Float(124.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(134.0f), LoadVarInst(stack, fTemp11))), BinopInst("*", Float(144.0f), LoadVarInst(stack, fTemp13))))))
			StoreVarInst(stack, output4[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp22), Float(0.0f))), LoadVarInst(stack, fTemp22))))
			DeclareVarInst(stack, "float", fTemp23, BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(105.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(115.0f), LoadVarInst(stack, fTemp11))), BinopInst("*", Float(125.0f), LoadVarInst(stack, fTemp13))), BinopInst("*", Float(135.0f), LoadVarInst(stack, fTemp15))), BinopInst("*", Float(145.0f), LoadVarInst(stack, fTemp17))))
			StoreVarInst(stack, output5[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", LoadVarInst(stack, fTemp23), CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp23), Float(0.0f))))))
			DeclareVarInst(stack, "float", fTemp24, BinopInst("+", BinopInst("*", Float(126.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("*", Float(116.0f), LoadVarInst(stack, fTemp15)), BinopInst("+", BinopInst("*", Float(106.0f), LoadVarInst(stack, fTemp13)), BinopInst("+", BinopInst("*", Float(136.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(146.0f), LoadVarInst(stack, fTemp11)))))))
			StoreVarInst(stack, output6[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp24), Float(0.0f))), LoadVarInst(stack, fTemp24))))
			DeclareVarInst(stack, "float", fTemp25, BinopInst("+", BinopInst("*", Float(107.0f), LoadVarInst(stack, fTemp17)), BinopInst("+", BinopInst("+", BinopInst("+", BinopInst("*", Float(117.0f), LoadVarInst(stack, fTemp8)), BinopInst("*", Float(127.0f), LoadVarInst(stack, fTemp11))), BinopInst("*", Float(137.0f), LoadVarInst(stack, fTemp13))), BinopInst("*", Float(147.0f), LoadVarInst(stack, fTemp15)))))
			StoreVarInst(stack, output7[LoadVarInst(loop, i)], CastInst("FAUSTFLOAT", BinopInst("*", CastInst("float", BinopInst(">", LoadVarInst(stack, fTemp25), Float(0.0f))), LoadVarInst(stack, fTemp25))))
			EndBlock
		EndForLoop
	EndBlock

======= Object memory footprint ==========

Heap size int = 4 bytes
Heap size int* = 0 bytes
Heap size real = 0 bytes
Heap size = 4 bytes
Stack size in compute = 128 bytes

