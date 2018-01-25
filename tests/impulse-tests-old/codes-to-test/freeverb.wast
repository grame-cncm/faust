
(module
	(export "getNumInputs" (func $getNumInputs))
	(export "getNumOutputs" (func $getNumOutputs))
	(export "getSampleRate" (func $getSampleRate))
	(export "init" (func $init))
	(export "instanceInit" (func $instanceInit))
	(export "instanceConstants" (func $instanceConstants))
	(export "instanceResetUserInterface" (func $instanceResetUserInterface))
	(export "instanceClear" (func $instanceClear))
	(export "setParamValue" (func $setParamValue))
	(export "getParamValue" (func $getParamValue))
	(export "compute" (func $compute))
	(import "env" "memoryBase" (global $memoryBase i32))
	(import "env" "tableBase" (global $tableBase i32))
	(memory (export "memory") 16)
	(data (i32.const 0) "{\"name\":\"freeverb\",\"version\":\"2.5.15\",\"options\":\"wast-i, -double -ftz 0\",\"size\":\"299688\",\"inputs\":\"2\",\"outputs\":\"2\",\"meta\":[{\"author\":\"Grame\"},{\"copyright\":\"(c) GRAME 2006\"},{\"license\":\"BSD\"},{\"name\":\"freeverb\"},{\"reference\":\"https://ccrma.stanford.edu/~jos/pasp/Freeverb.html\"},{\"version\":\"1.0\"}],\"ui\":[{\"type\":\"vgroup\",\"label\":\"Freeverb\",\"items\":[{\"type\":\"hslider\",\"label\":\"Damp\",\"address\":\"/Freeverb/Damp\",\"index\":\"16\",\"init\":\"1\",\"min\":\"0\",\"max\":\"1\",\"step\":\"0.025\"},{\"type\":\"hslider\",\"label\":\"RoomSize\",\"address\":\"/Freeverb/RoomSize\",\"index\":\"8\",\"init\":\"1\",\"min\":\"0\",\"max\":\"1\",\"step\":\"0.025\"},{\"type\":\"hslider\",\"label\":\"Wet\",\"address\":\"/Freeverb/Wet\",\"index\":\"0\",\"init\":\"0.93\",\"min\":\"0\",\"max\":\"1\",\"step\":\"0.025\"}]}]}")
	
	(func $min_i (param $v10 i32) (param $v20 i32) (result i32)
		(return (select (get_local $v10) (get_local $v20) (i32.lt_s (get_local $v10) (get_local $v20))))
	)
	(func $max_i (param $v11 i32) (param $v21 i32) (result i32)
		(return (select (get_local $v21) (get_local $v11) (i32.lt_s (get_local $v11) (get_local $v21))))
	)
	(func $getNumInputs (param $dsp i32) (result i32)
		(return (i32.const 2))
	)
	(func $getNumOutputs (param $dsp i32) (result i32)
		(return (i32.const 2))
	)
	(func $classInit (param $dsp i32) (param $samplingFreq i32)
		
	)
	(func $instanceConstants (param $dsp i32) (param $samplingFreq i32)
		(i32.store offset=299680 (i32.const 0) (get_local $samplingFreq))
		
	)
	(func $instanceResetUserInterface (param $dsp i32)
		(f64.store (i32.const 0) (f64.const 0.93000000000000005))
		(f64.store offset=8 (i32.const 0) (f64.const 1.))
		(f64.store offset=16 (i32.const 0) (f64.const 1.))
		
	)
	(func $instanceClear (param $dsp i32)
		(local $l0 i32)
		(local $l1 i32)
		(local $l2 i32)
		(local $l3 i32)
		(local $l4 i32)
		(local $l5 i32)
		(local $l6 i32)
		(local $l7 i32)
		(local $l8 i32)
		(local $l9 i32)
		(local $l10 i32)
		(local $l11 i32)
		(local $l12 i32)
		(local $l13 i32)
		(local $l14 i32)
		(local $l15 i32)
		(local $l16 i32)
		(local $l17 i32)
		(local $l18 i32)
		(local $l19 i32)
		(local $l20 i32)
		(local $l21 i32)
		(local $l22 i32)
		(local $l23 i32)
		(local $l24 i32)
		(local $l25 i32)
		(local $l26 i32)
		(local $l27 i32)
		(local $l28 i32)
		(local $l29 i32)
		(local $l30 i32)
		(local $l31 i32)
		(local $l32 i32)
		(local $l33 i32)
		(local $l34 i32)
		(local $l35 i32)
		(local $l36 i32)
		(local $l37 i32)
		(local $l38 i32)
		(local $l39 i32)
		(local $l40 i32)
		(local $l41 i32)
		(local $l42 i32)
		(local $l43 i32)
		(local $l44 i32)
		(local $l45 i32)
		(local $l46 i32)
		(local $l47 i32)
		(local $l48 i32)
		(local $l49 i32)
		(local $l50 i32)
		(local $l51 i32)
		(local $l52 i32)
		(local $l53 i32)
		(local $l54 i32)
		(local $l55 i32)
		(local $l56 i32)
		(local $l57 i32)
		(local $l58 i32)
		(local $l59 i32)
		(local $l60 i32)
		(local $l61 i32)
		(local $l62 i32)
		(local $l63 i32)
		(set_local $l0 (i32.const 0))
		(set_local $l1 (i32.const 0))
		(set_local $l2 (i32.const 0))
		(set_local $l3 (i32.const 0))
		(set_local $l4 (i32.const 0))
		(set_local $l5 (i32.const 0))
		(set_local $l6 (i32.const 0))
		(set_local $l7 (i32.const 0))
		(set_local $l8 (i32.const 0))
		(set_local $l9 (i32.const 0))
		(set_local $l10 (i32.const 0))
		(set_local $l11 (i32.const 0))
		(set_local $l12 (i32.const 0))
		(set_local $l13 (i32.const 0))
		(set_local $l14 (i32.const 0))
		(set_local $l15 (i32.const 0))
		(set_local $l16 (i32.const 0))
		(set_local $l17 (i32.const 0))
		(set_local $l18 (i32.const 0))
		(set_local $l19 (i32.const 0))
		(set_local $l20 (i32.const 0))
		(set_local $l21 (i32.const 0))
		(set_local $l22 (i32.const 0))
		(set_local $l23 (i32.const 0))
		(set_local $l24 (i32.const 0))
		(set_local $l25 (i32.const 0))
		(set_local $l26 (i32.const 0))
		(set_local $l27 (i32.const 0))
		(set_local $l28 (i32.const 0))
		(set_local $l29 (i32.const 0))
		(set_local $l30 (i32.const 0))
		(set_local $l31 (i32.const 0))
		(set_local $l32 (i32.const 0))
		(set_local $l33 (i32.const 0))
		(set_local $l34 (i32.const 0))
		(set_local $l35 (i32.const 0))
		(set_local $l36 (i32.const 0))
		(set_local $l37 (i32.const 0))
		(set_local $l38 (i32.const 0))
		(set_local $l39 (i32.const 0))
		(set_local $l40 (i32.const 0))
		(set_local $l41 (i32.const 0))
		(set_local $l42 (i32.const 0))
		(set_local $l43 (i32.const 0))
		(set_local $l44 (i32.const 0))
		(set_local $l45 (i32.const 0))
		(set_local $l46 (i32.const 0))
		(set_local $l47 (i32.const 0))
		(set_local $l48 (i32.const 0))
		(set_local $l49 (i32.const 0))
		(set_local $l50 (i32.const 0))
		(set_local $l51 (i32.const 0))
		(set_local $l52 (i32.const 0))
		(set_local $l53 (i32.const 0))
		(set_local $l54 (i32.const 0))
		(set_local $l55 (i32.const 0))
		(set_local $l56 (i32.const 0))
		(set_local $l57 (i32.const 0))
		(set_local $l58 (i32.const 0))
		(set_local $l59 (i32.const 0))
		(set_local $l60 (i32.const 0))
		(set_local $l61 (i32.const 0))
		(set_local $l62 (i32.const 0))
		(set_local $l63 (i32.const 0))
		(set_local $l0 (i32.const 0))
		(loop $for-in-l0 
			(block $for-out-l0 
				(f64.store (i32.add (i32.const 24) (i32.shl (get_local $l0) (i32.const 3))) (f64.const 0.))
				(set_local $l0 (i32.add (get_local $l0) (i32.const 1)))
				(if (i32.lt_s (get_local $l0) (i32.const 2)) (br $for-in-l0) (br $for-out-l0))
				
			)
		)
		(i32.store offset=40 (i32.const 0) (i32.const 0))
		(set_local $l1 (i32.const 0))
		(loop $for-in-l1 
			(block $for-out-l1 
				(f64.store (i32.add (i32.const 48) (i32.shl (get_local $l1) (i32.const 3))) (f64.const 0.))
				(set_local $l1 (i32.add (get_local $l1) (i32.const 1)))
				(if (i32.lt_s (get_local $l1) (i32.const 2048)) (br $for-in-l1) (br $for-out-l1))
				
			)
		)
		(set_local $l2 (i32.const 0))
		(loop $for-in-l2 
			(block $for-out-l2 
				(f64.store (i32.add (i32.const 16432) (i32.shl (get_local $l2) (i32.const 3))) (f64.const 0.))
				(set_local $l2 (i32.add (get_local $l2) (i32.const 1)))
				(if (i32.lt_s (get_local $l2) (i32.const 2)) (br $for-in-l2) (br $for-out-l2))
				
			)
		)
		(set_local $l3 (i32.const 0))
		(loop $for-in-l3 
			(block $for-out-l3 
				(f64.store (i32.add (i32.const 16448) (i32.shl (get_local $l3) (i32.const 3))) (f64.const 0.))
				(set_local $l3 (i32.add (get_local $l3) (i32.const 1)))
				(if (i32.lt_s (get_local $l3) (i32.const 2)) (br $for-in-l3) (br $for-out-l3))
				
			)
		)
		(set_local $l4 (i32.const 0))
		(loop $for-in-l4 
			(block $for-out-l4 
				(f64.store (i32.add (i32.const 16464) (i32.shl (get_local $l4) (i32.const 3))) (f64.const 0.))
				(set_local $l4 (i32.add (get_local $l4) (i32.const 1)))
				(if (i32.lt_s (get_local $l4) (i32.const 2048)) (br $for-in-l4) (br $for-out-l4))
				
			)
		)
		(set_local $l5 (i32.const 0))
		(loop $for-in-l5 
			(block $for-out-l5 
				(f64.store (i32.add (i32.const 32848) (i32.shl (get_local $l5) (i32.const 3))) (f64.const 0.))
				(set_local $l5 (i32.add (get_local $l5) (i32.const 1)))
				(if (i32.lt_s (get_local $l5) (i32.const 2)) (br $for-in-l5) (br $for-out-l5))
				
			)
		)
		(set_local $l6 (i32.const 0))
		(loop $for-in-l6 
			(block $for-out-l6 
				(f64.store (i32.add (i32.const 32864) (i32.shl (get_local $l6) (i32.const 3))) (f64.const 0.))
				(set_local $l6 (i32.add (get_local $l6) (i32.const 1)))
				(if (i32.lt_s (get_local $l6) (i32.const 2)) (br $for-in-l6) (br $for-out-l6))
				
			)
		)
		(set_local $l7 (i32.const 0))
		(loop $for-in-l7 
			(block $for-out-l7 
				(f64.store (i32.add (i32.const 32880) (i32.shl (get_local $l7) (i32.const 3))) (f64.const 0.))
				(set_local $l7 (i32.add (get_local $l7) (i32.const 1)))
				(if (i32.lt_s (get_local $l7) (i32.const 2048)) (br $for-in-l7) (br $for-out-l7))
				
			)
		)
		(set_local $l8 (i32.const 0))
		(loop $for-in-l8 
			(block $for-out-l8 
				(f64.store (i32.add (i32.const 49264) (i32.shl (get_local $l8) (i32.const 3))) (f64.const 0.))
				(set_local $l8 (i32.add (get_local $l8) (i32.const 1)))
				(if (i32.lt_s (get_local $l8) (i32.const 2)) (br $for-in-l8) (br $for-out-l8))
				
			)
		)
		(set_local $l9 (i32.const 0))
		(loop $for-in-l9 
			(block $for-out-l9 
				(f64.store (i32.add (i32.const 49280) (i32.shl (get_local $l9) (i32.const 3))) (f64.const 0.))
				(set_local $l9 (i32.add (get_local $l9) (i32.const 1)))
				(if (i32.lt_s (get_local $l9) (i32.const 2)) (br $for-in-l9) (br $for-out-l9))
				
			)
		)
		(set_local $l10 (i32.const 0))
		(loop $for-in-l10 
			(block $for-out-l10 
				(f64.store (i32.add (i32.const 49296) (i32.shl (get_local $l10) (i32.const 3))) (f64.const 0.))
				(set_local $l10 (i32.add (get_local $l10) (i32.const 1)))
				(if (i32.lt_s (get_local $l10) (i32.const 2048)) (br $for-in-l10) (br $for-out-l10))
				
			)
		)
		(set_local $l11 (i32.const 0))
		(loop $for-in-l11 
			(block $for-out-l11 
				(f64.store (i32.add (i32.const 65680) (i32.shl (get_local $l11) (i32.const 3))) (f64.const 0.))
				(set_local $l11 (i32.add (get_local $l11) (i32.const 1)))
				(if (i32.lt_s (get_local $l11) (i32.const 2)) (br $for-in-l11) (br $for-out-l11))
				
			)
		)
		(set_local $l12 (i32.const 0))
		(loop $for-in-l12 
			(block $for-out-l12 
				(f64.store (i32.add (i32.const 65696) (i32.shl (get_local $l12) (i32.const 3))) (f64.const 0.))
				(set_local $l12 (i32.add (get_local $l12) (i32.const 1)))
				(if (i32.lt_s (get_local $l12) (i32.const 2)) (br $for-in-l12) (br $for-out-l12))
				
			)
		)
		(set_local $l13 (i32.const 0))
		(loop $for-in-l13 
			(block $for-out-l13 
				(f64.store (i32.add (i32.const 65712) (i32.shl (get_local $l13) (i32.const 3))) (f64.const 0.))
				(set_local $l13 (i32.add (get_local $l13) (i32.const 1)))
				(if (i32.lt_s (get_local $l13) (i32.const 2048)) (br $for-in-l13) (br $for-out-l13))
				
			)
		)
		(set_local $l14 (i32.const 0))
		(loop $for-in-l14 
			(block $for-out-l14 
				(f64.store (i32.add (i32.const 82096) (i32.shl (get_local $l14) (i32.const 3))) (f64.const 0.))
				(set_local $l14 (i32.add (get_local $l14) (i32.const 1)))
				(if (i32.lt_s (get_local $l14) (i32.const 2)) (br $for-in-l14) (br $for-out-l14))
				
			)
		)
		(set_local $l15 (i32.const 0))
		(loop $for-in-l15 
			(block $for-out-l15 
				(f64.store (i32.add (i32.const 82112) (i32.shl (get_local $l15) (i32.const 3))) (f64.const 0.))
				(set_local $l15 (i32.add (get_local $l15) (i32.const 1)))
				(if (i32.lt_s (get_local $l15) (i32.const 2)) (br $for-in-l15) (br $for-out-l15))
				
			)
		)
		(set_local $l16 (i32.const 0))
		(loop $for-in-l16 
			(block $for-out-l16 
				(f64.store (i32.add (i32.const 82128) (i32.shl (get_local $l16) (i32.const 3))) (f64.const 0.))
				(set_local $l16 (i32.add (get_local $l16) (i32.const 1)))
				(if (i32.lt_s (get_local $l16) (i32.const 2048)) (br $for-in-l16) (br $for-out-l16))
				
			)
		)
		(set_local $l17 (i32.const 0))
		(loop $for-in-l17 
			(block $for-out-l17 
				(f64.store (i32.add (i32.const 98512) (i32.shl (get_local $l17) (i32.const 3))) (f64.const 0.))
				(set_local $l17 (i32.add (get_local $l17) (i32.const 1)))
				(if (i32.lt_s (get_local $l17) (i32.const 2)) (br $for-in-l17) (br $for-out-l17))
				
			)
		)
		(set_local $l18 (i32.const 0))
		(loop $for-in-l18 
			(block $for-out-l18 
				(f64.store (i32.add (i32.const 98528) (i32.shl (get_local $l18) (i32.const 3))) (f64.const 0.))
				(set_local $l18 (i32.add (get_local $l18) (i32.const 1)))
				(if (i32.lt_s (get_local $l18) (i32.const 2)) (br $for-in-l18) (br $for-out-l18))
				
			)
		)
		(set_local $l19 (i32.const 0))
		(loop $for-in-l19 
			(block $for-out-l19 
				(f64.store (i32.add (i32.const 98544) (i32.shl (get_local $l19) (i32.const 3))) (f64.const 0.))
				(set_local $l19 (i32.add (get_local $l19) (i32.const 1)))
				(if (i32.lt_s (get_local $l19) (i32.const 2048)) (br $for-in-l19) (br $for-out-l19))
				
			)
		)
		(set_local $l20 (i32.const 0))
		(loop $for-in-l20 
			(block $for-out-l20 
				(f64.store (i32.add (i32.const 114928) (i32.shl (get_local $l20) (i32.const 3))) (f64.const 0.))
				(set_local $l20 (i32.add (get_local $l20) (i32.const 1)))
				(if (i32.lt_s (get_local $l20) (i32.const 2)) (br $for-in-l20) (br $for-out-l20))
				
			)
		)
		(set_local $l21 (i32.const 0))
		(loop $for-in-l21 
			(block $for-out-l21 
				(f64.store (i32.add (i32.const 114944) (i32.shl (get_local $l21) (i32.const 3))) (f64.const 0.))
				(set_local $l21 (i32.add (get_local $l21) (i32.const 1)))
				(if (i32.lt_s (get_local $l21) (i32.const 2)) (br $for-in-l21) (br $for-out-l21))
				
			)
		)
		(set_local $l22 (i32.const 0))
		(loop $for-in-l22 
			(block $for-out-l22 
				(f64.store (i32.add (i32.const 114960) (i32.shl (get_local $l22) (i32.const 3))) (f64.const 0.))
				(set_local $l22 (i32.add (get_local $l22) (i32.const 1)))
				(if (i32.lt_s (get_local $l22) (i32.const 2048)) (br $for-in-l22) (br $for-out-l22))
				
			)
		)
		(set_local $l23 (i32.const 0))
		(loop $for-in-l23 
			(block $for-out-l23 
				(f64.store (i32.add (i32.const 131344) (i32.shl (get_local $l23) (i32.const 3))) (f64.const 0.))
				(set_local $l23 (i32.add (get_local $l23) (i32.const 1)))
				(if (i32.lt_s (get_local $l23) (i32.const 2)) (br $for-in-l23) (br $for-out-l23))
				
			)
		)
		(set_local $l24 (i32.const 0))
		(loop $for-in-l24 
			(block $for-out-l24 
				(f64.store (i32.add (i32.const 131360) (i32.shl (get_local $l24) (i32.const 3))) (f64.const 0.))
				(set_local $l24 (i32.add (get_local $l24) (i32.const 1)))
				(if (i32.lt_s (get_local $l24) (i32.const 1024)) (br $for-in-l24) (br $for-out-l24))
				
			)
		)
		(set_local $l25 (i32.const 0))
		(loop $for-in-l25 
			(block $for-out-l25 
				(f64.store (i32.add (i32.const 139552) (i32.shl (get_local $l25) (i32.const 3))) (f64.const 0.))
				(set_local $l25 (i32.add (get_local $l25) (i32.const 1)))
				(if (i32.lt_s (get_local $l25) (i32.const 2)) (br $for-in-l25) (br $for-out-l25))
				
			)
		)
		(set_local $l26 (i32.const 0))
		(loop $for-in-l26 
			(block $for-out-l26 
				(f64.store (i32.add (i32.const 139568) (i32.shl (get_local $l26) (i32.const 3))) (f64.const 0.))
				(set_local $l26 (i32.add (get_local $l26) (i32.const 1)))
				(if (i32.lt_s (get_local $l26) (i32.const 512)) (br $for-in-l26) (br $for-out-l26))
				
			)
		)
		(set_local $l27 (i32.const 0))
		(loop $for-in-l27 
			(block $for-out-l27 
				(f64.store (i32.add (i32.const 143664) (i32.shl (get_local $l27) (i32.const 3))) (f64.const 0.))
				(set_local $l27 (i32.add (get_local $l27) (i32.const 1)))
				(if (i32.lt_s (get_local $l27) (i32.const 2)) (br $for-in-l27) (br $for-out-l27))
				
			)
		)
		(set_local $l28 (i32.const 0))
		(loop $for-in-l28 
			(block $for-out-l28 
				(f64.store (i32.add (i32.const 143680) (i32.shl (get_local $l28) (i32.const 3))) (f64.const 0.))
				(set_local $l28 (i32.add (get_local $l28) (i32.const 1)))
				(if (i32.lt_s (get_local $l28) (i32.const 512)) (br $for-in-l28) (br $for-out-l28))
				
			)
		)
		(set_local $l29 (i32.const 0))
		(loop $for-in-l29 
			(block $for-out-l29 
				(f64.store (i32.add (i32.const 147776) (i32.shl (get_local $l29) (i32.const 3))) (f64.const 0.))
				(set_local $l29 (i32.add (get_local $l29) (i32.const 1)))
				(if (i32.lt_s (get_local $l29) (i32.const 2)) (br $for-in-l29) (br $for-out-l29))
				
			)
		)
		(set_local $l30 (i32.const 0))
		(loop $for-in-l30 
			(block $for-out-l30 
				(f64.store (i32.add (i32.const 147792) (i32.shl (get_local $l30) (i32.const 3))) (f64.const 0.))
				(set_local $l30 (i32.add (get_local $l30) (i32.const 1)))
				(if (i32.lt_s (get_local $l30) (i32.const 256)) (br $for-in-l30) (br $for-out-l30))
				
			)
		)
		(set_local $l31 (i32.const 0))
		(loop $for-in-l31 
			(block $for-out-l31 
				(f64.store (i32.add (i32.const 149840) (i32.shl (get_local $l31) (i32.const 3))) (f64.const 0.))
				(set_local $l31 (i32.add (get_local $l31) (i32.const 1)))
				(if (i32.lt_s (get_local $l31) (i32.const 2)) (br $for-in-l31) (br $for-out-l31))
				
			)
		)
		(set_local $l32 (i32.const 0))
		(loop $for-in-l32 
			(block $for-out-l32 
				(f64.store (i32.add (i32.const 149856) (i32.shl (get_local $l32) (i32.const 3))) (f64.const 0.))
				(set_local $l32 (i32.add (get_local $l32) (i32.const 1)))
				(if (i32.lt_s (get_local $l32) (i32.const 2)) (br $for-in-l32) (br $for-out-l32))
				
			)
		)
		(set_local $l33 (i32.const 0))
		(loop $for-in-l33 
			(block $for-out-l33 
				(f64.store (i32.add (i32.const 149872) (i32.shl (get_local $l33) (i32.const 3))) (f64.const 0.))
				(set_local $l33 (i32.add (get_local $l33) (i32.const 1)))
				(if (i32.lt_s (get_local $l33) (i32.const 2048)) (br $for-in-l33) (br $for-out-l33))
				
			)
		)
		(set_local $l34 (i32.const 0))
		(loop $for-in-l34 
			(block $for-out-l34 
				(f64.store (i32.add (i32.const 166256) (i32.shl (get_local $l34) (i32.const 3))) (f64.const 0.))
				(set_local $l34 (i32.add (get_local $l34) (i32.const 1)))
				(if (i32.lt_s (get_local $l34) (i32.const 2)) (br $for-in-l34) (br $for-out-l34))
				
			)
		)
		(set_local $l35 (i32.const 0))
		(loop $for-in-l35 
			(block $for-out-l35 
				(f64.store (i32.add (i32.const 166272) (i32.shl (get_local $l35) (i32.const 3))) (f64.const 0.))
				(set_local $l35 (i32.add (get_local $l35) (i32.const 1)))
				(if (i32.lt_s (get_local $l35) (i32.const 2)) (br $for-in-l35) (br $for-out-l35))
				
			)
		)
		(set_local $l36 (i32.const 0))
		(loop $for-in-l36 
			(block $for-out-l36 
				(f64.store (i32.add (i32.const 166288) (i32.shl (get_local $l36) (i32.const 3))) (f64.const 0.))
				(set_local $l36 (i32.add (get_local $l36) (i32.const 1)))
				(if (i32.lt_s (get_local $l36) (i32.const 2048)) (br $for-in-l36) (br $for-out-l36))
				
			)
		)
		(set_local $l37 (i32.const 0))
		(loop $for-in-l37 
			(block $for-out-l37 
				(f64.store (i32.add (i32.const 182672) (i32.shl (get_local $l37) (i32.const 3))) (f64.const 0.))
				(set_local $l37 (i32.add (get_local $l37) (i32.const 1)))
				(if (i32.lt_s (get_local $l37) (i32.const 2)) (br $for-in-l37) (br $for-out-l37))
				
			)
		)
		(set_local $l38 (i32.const 0))
		(loop $for-in-l38 
			(block $for-out-l38 
				(f64.store (i32.add (i32.const 182688) (i32.shl (get_local $l38) (i32.const 3))) (f64.const 0.))
				(set_local $l38 (i32.add (get_local $l38) (i32.const 1)))
				(if (i32.lt_s (get_local $l38) (i32.const 2)) (br $for-in-l38) (br $for-out-l38))
				
			)
		)
		(set_local $l39 (i32.const 0))
		(loop $for-in-l39 
			(block $for-out-l39 
				(f64.store (i32.add (i32.const 182704) (i32.shl (get_local $l39) (i32.const 3))) (f64.const 0.))
				(set_local $l39 (i32.add (get_local $l39) (i32.const 1)))
				(if (i32.lt_s (get_local $l39) (i32.const 2048)) (br $for-in-l39) (br $for-out-l39))
				
			)
		)
		(set_local $l40 (i32.const 0))
		(loop $for-in-l40 
			(block $for-out-l40 
				(f64.store (i32.add (i32.const 199088) (i32.shl (get_local $l40) (i32.const 3))) (f64.const 0.))
				(set_local $l40 (i32.add (get_local $l40) (i32.const 1)))
				(if (i32.lt_s (get_local $l40) (i32.const 2)) (br $for-in-l40) (br $for-out-l40))
				
			)
		)
		(set_local $l41 (i32.const 0))
		(loop $for-in-l41 
			(block $for-out-l41 
				(f64.store (i32.add (i32.const 199104) (i32.shl (get_local $l41) (i32.const 3))) (f64.const 0.))
				(set_local $l41 (i32.add (get_local $l41) (i32.const 1)))
				(if (i32.lt_s (get_local $l41) (i32.const 2)) (br $for-in-l41) (br $for-out-l41))
				
			)
		)
		(set_local $l42 (i32.const 0))
		(loop $for-in-l42 
			(block $for-out-l42 
				(f64.store (i32.add (i32.const 199120) (i32.shl (get_local $l42) (i32.const 3))) (f64.const 0.))
				(set_local $l42 (i32.add (get_local $l42) (i32.const 1)))
				(if (i32.lt_s (get_local $l42) (i32.const 2048)) (br $for-in-l42) (br $for-out-l42))
				
			)
		)
		(set_local $l43 (i32.const 0))
		(loop $for-in-l43 
			(block $for-out-l43 
				(f64.store (i32.add (i32.const 215504) (i32.shl (get_local $l43) (i32.const 3))) (f64.const 0.))
				(set_local $l43 (i32.add (get_local $l43) (i32.const 1)))
				(if (i32.lt_s (get_local $l43) (i32.const 2)) (br $for-in-l43) (br $for-out-l43))
				
			)
		)
		(set_local $l44 (i32.const 0))
		(loop $for-in-l44 
			(block $for-out-l44 
				(f64.store (i32.add (i32.const 215520) (i32.shl (get_local $l44) (i32.const 3))) (f64.const 0.))
				(set_local $l44 (i32.add (get_local $l44) (i32.const 1)))
				(if (i32.lt_s (get_local $l44) (i32.const 2)) (br $for-in-l44) (br $for-out-l44))
				
			)
		)
		(set_local $l45 (i32.const 0))
		(loop $for-in-l45 
			(block $for-out-l45 
				(f64.store (i32.add (i32.const 215536) (i32.shl (get_local $l45) (i32.const 3))) (f64.const 0.))
				(set_local $l45 (i32.add (get_local $l45) (i32.const 1)))
				(if (i32.lt_s (get_local $l45) (i32.const 2048)) (br $for-in-l45) (br $for-out-l45))
				
			)
		)
		(set_local $l46 (i32.const 0))
		(loop $for-in-l46 
			(block $for-out-l46 
				(f64.store (i32.add (i32.const 231920) (i32.shl (get_local $l46) (i32.const 3))) (f64.const 0.))
				(set_local $l46 (i32.add (get_local $l46) (i32.const 1)))
				(if (i32.lt_s (get_local $l46) (i32.const 2)) (br $for-in-l46) (br $for-out-l46))
				
			)
		)
		(set_local $l47 (i32.const 0))
		(loop $for-in-l47 
			(block $for-out-l47 
				(f64.store (i32.add (i32.const 231936) (i32.shl (get_local $l47) (i32.const 3))) (f64.const 0.))
				(set_local $l47 (i32.add (get_local $l47) (i32.const 1)))
				(if (i32.lt_s (get_local $l47) (i32.const 2)) (br $for-in-l47) (br $for-out-l47))
				
			)
		)
		(set_local $l48 (i32.const 0))
		(loop $for-in-l48 
			(block $for-out-l48 
				(f64.store (i32.add (i32.const 231952) (i32.shl (get_local $l48) (i32.const 3))) (f64.const 0.))
				(set_local $l48 (i32.add (get_local $l48) (i32.const 1)))
				(if (i32.lt_s (get_local $l48) (i32.const 2048)) (br $for-in-l48) (br $for-out-l48))
				
			)
		)
		(set_local $l49 (i32.const 0))
		(loop $for-in-l49 
			(block $for-out-l49 
				(f64.store (i32.add (i32.const 248336) (i32.shl (get_local $l49) (i32.const 3))) (f64.const 0.))
				(set_local $l49 (i32.add (get_local $l49) (i32.const 1)))
				(if (i32.lt_s (get_local $l49) (i32.const 2)) (br $for-in-l49) (br $for-out-l49))
				
			)
		)
		(set_local $l50 (i32.const 0))
		(loop $for-in-l50 
			(block $for-out-l50 
				(f64.store (i32.add (i32.const 248352) (i32.shl (get_local $l50) (i32.const 3))) (f64.const 0.))
				(set_local $l50 (i32.add (get_local $l50) (i32.const 1)))
				(if (i32.lt_s (get_local $l50) (i32.const 2)) (br $for-in-l50) (br $for-out-l50))
				
			)
		)
		(set_local $l51 (i32.const 0))
		(loop $for-in-l51 
			(block $for-out-l51 
				(f64.store (i32.add (i32.const 248368) (i32.shl (get_local $l51) (i32.const 3))) (f64.const 0.))
				(set_local $l51 (i32.add (get_local $l51) (i32.const 1)))
				(if (i32.lt_s (get_local $l51) (i32.const 2048)) (br $for-in-l51) (br $for-out-l51))
				
			)
		)
		(set_local $l52 (i32.const 0))
		(loop $for-in-l52 
			(block $for-out-l52 
				(f64.store (i32.add (i32.const 264752) (i32.shl (get_local $l52) (i32.const 3))) (f64.const 0.))
				(set_local $l52 (i32.add (get_local $l52) (i32.const 1)))
				(if (i32.lt_s (get_local $l52) (i32.const 2)) (br $for-in-l52) (br $for-out-l52))
				
			)
		)
		(set_local $l53 (i32.const 0))
		(loop $for-in-l53 
			(block $for-out-l53 
				(f64.store (i32.add (i32.const 264768) (i32.shl (get_local $l53) (i32.const 3))) (f64.const 0.))
				(set_local $l53 (i32.add (get_local $l53) (i32.const 1)))
				(if (i32.lt_s (get_local $l53) (i32.const 2)) (br $for-in-l53) (br $for-out-l53))
				
			)
		)
		(set_local $l54 (i32.const 0))
		(loop $for-in-l54 
			(block $for-out-l54 
				(f64.store (i32.add (i32.const 264784) (i32.shl (get_local $l54) (i32.const 3))) (f64.const 0.))
				(set_local $l54 (i32.add (get_local $l54) (i32.const 1)))
				(if (i32.lt_s (get_local $l54) (i32.const 2048)) (br $for-in-l54) (br $for-out-l54))
				
			)
		)
		(set_local $l55 (i32.const 0))
		(loop $for-in-l55 
			(block $for-out-l55 
				(f64.store (i32.add (i32.const 281168) (i32.shl (get_local $l55) (i32.const 3))) (f64.const 0.))
				(set_local $l55 (i32.add (get_local $l55) (i32.const 1)))
				(if (i32.lt_s (get_local $l55) (i32.const 2)) (br $for-in-l55) (br $for-out-l55))
				
			)
		)
		(set_local $l56 (i32.const 0))
		(loop $for-in-l56 
			(block $for-out-l56 
				(f64.store (i32.add (i32.const 281184) (i32.shl (get_local $l56) (i32.const 3))) (f64.const 0.))
				(set_local $l56 (i32.add (get_local $l56) (i32.const 1)))
				(if (i32.lt_s (get_local $l56) (i32.const 1024)) (br $for-in-l56) (br $for-out-l56))
				
			)
		)
		(set_local $l57 (i32.const 0))
		(loop $for-in-l57 
			(block $for-out-l57 
				(f64.store (i32.add (i32.const 289376) (i32.shl (get_local $l57) (i32.const 3))) (f64.const 0.))
				(set_local $l57 (i32.add (get_local $l57) (i32.const 1)))
				(if (i32.lt_s (get_local $l57) (i32.const 2)) (br $for-in-l57) (br $for-out-l57))
				
			)
		)
		(set_local $l58 (i32.const 0))
		(loop $for-in-l58 
			(block $for-out-l58 
				(f64.store (i32.add (i32.const 289392) (i32.shl (get_local $l58) (i32.const 3))) (f64.const 0.))
				(set_local $l58 (i32.add (get_local $l58) (i32.const 1)))
				(if (i32.lt_s (get_local $l58) (i32.const 512)) (br $for-in-l58) (br $for-out-l58))
				
			)
		)
		(set_local $l59 (i32.const 0))
		(loop $for-in-l59 
			(block $for-out-l59 
				(f64.store (i32.add (i32.const 293488) (i32.shl (get_local $l59) (i32.const 3))) (f64.const 0.))
				(set_local $l59 (i32.add (get_local $l59) (i32.const 1)))
				(if (i32.lt_s (get_local $l59) (i32.const 2)) (br $for-in-l59) (br $for-out-l59))
				
			)
		)
		(set_local $l60 (i32.const 0))
		(loop $for-in-l60 
			(block $for-out-l60 
				(f64.store (i32.add (i32.const 293504) (i32.shl (get_local $l60) (i32.const 3))) (f64.const 0.))
				(set_local $l60 (i32.add (get_local $l60) (i32.const 1)))
				(if (i32.lt_s (get_local $l60) (i32.const 512)) (br $for-in-l60) (br $for-out-l60))
				
			)
		)
		(set_local $l61 (i32.const 0))
		(loop $for-in-l61 
			(block $for-out-l61 
				(f64.store (i32.add (i32.const 297600) (i32.shl (get_local $l61) (i32.const 3))) (f64.const 0.))
				(set_local $l61 (i32.add (get_local $l61) (i32.const 1)))
				(if (i32.lt_s (get_local $l61) (i32.const 2)) (br $for-in-l61) (br $for-out-l61))
				
			)
		)
		(set_local $l62 (i32.const 0))
		(loop $for-in-l62 
			(block $for-out-l62 
				(f64.store (i32.add (i32.const 297616) (i32.shl (get_local $l62) (i32.const 3))) (f64.const 0.))
				(set_local $l62 (i32.add (get_local $l62) (i32.const 1)))
				(if (i32.lt_s (get_local $l62) (i32.const 256)) (br $for-in-l62) (br $for-out-l62))
				
			)
		)
		(set_local $l63 (i32.const 0))
		(loop $for-in-l63 
			(block $for-out-l63 
				(f64.store (i32.add (i32.const 299664) (i32.shl (get_local $l63) (i32.const 3))) (f64.const 0.))
				(set_local $l63 (i32.add (get_local $l63) (i32.const 1)))
				(if (i32.lt_s (get_local $l63) (i32.const 2)) (br $for-in-l63) (br $for-out-l63))
				
			)
		)
		
	)
	(func $init (param $dsp i32) (param $samplingFreq i32)
		(call $classInit (get_local $dsp) (get_local $samplingFreq))
		(call $instanceInit (get_local $dsp) (get_local $samplingFreq))
		
	)
	(func $instanceInit (param $dsp i32) (param $samplingFreq i32)
		(call $instanceConstants (get_local $dsp) (get_local $samplingFreq))
		(call $instanceResetUserInterface (get_local $dsp))
		(call $instanceClear (get_local $dsp))
		
	)
	(func $getSampleRate (param $dsp i32) (result i32)
		(return (i32.load offset=299680 (i32.const 0)))
	)
	(func $setParamValue (param $dsp i32) (param $index i32) (param $value f64)
		(f64.store 
			(i32.add (get_local $dsp) (get_local $index))
			(get_local $value)
		)
	)
	(func $getParamValue (param $dsp i32) (param $index i32) (result f64)
		(return (f64.load (i32.add (get_local $dsp) (get_local $index))))
	)
	(func $compute (param $dsp i32) (param $count i32) (param $inputs i32) (param $outputs i32)
		(local $input0 i32)
		(local $input1 i32)
		(local $output0 i32)
		(local $output1 i32)
		(local $fSlow0 f64)
		(local $fSlow1 f64)
		(local $fSlow2 f64)
		(local $fSlow3 f64)
		(local $fSlow4 f64)
		(local $i i32)
		(local $fTemp0 f64)
		(local $fTemp1 f64)
		(local $fTemp2 f64)
		(local $fTemp3 f64)
		(local $fRec7 f64)
		(local $fRec5 f64)
		(local $fRec3 f64)
		(local $fRec1 f64)
		(local $fTemp4 f64)
		(local $fRec31 f64)
		(local $fRec29 f64)
		(local $fRec27 f64)
		(local $fRec25 f64)
		(set_local $input0 (i32.const 0))
		(set_local $input1 (i32.const 0))
		(set_local $output0 (i32.const 0))
		(set_local $output1 (i32.const 0))
		(set_local $fSlow0 (f64.const 0.))
		(set_local $fSlow1 (f64.const 0.))
		(set_local $fSlow2 (f64.const 0.))
		(set_local $fSlow3 (f64.const 0.))
		(set_local $fSlow4 (f64.const 0.))
		(set_local $i (i32.const 0))
		(set_local $fTemp0 (f64.const 0.))
		(set_local $fTemp1 (f64.const 0.))
		(set_local $fTemp2 (f64.const 0.))
		(set_local $fTemp3 (f64.const 0.))
		(set_local $fRec7 (f64.const 0.))
		(set_local $fRec5 (f64.const 0.))
		(set_local $fRec3 (f64.const 0.))
		(set_local $fRec1 (f64.const 0.))
		(set_local $fTemp4 (f64.const 0.))
		(set_local $fRec31 (f64.const 0.))
		(set_local $fRec29 (f64.const 0.))
		(set_local $fRec27 (f64.const 0.))
		(set_local $fRec25 (f64.const 0.))
		(set_local $input0 (i32.load (i32.add (get_local $inputs) (i32.const 0))))
		(set_local $input1 (i32.load (i32.add (get_local $inputs) (i32.const 4))))
		(set_local $output0 (i32.load (i32.add (get_local $outputs) (i32.const 0))))
		(set_local $output1 (i32.load (i32.add (get_local $outputs) (i32.const 4))))
		(set_local $fSlow0 (f64.load (i32.const 0)))
		(set_local $fSlow1 (f64.add (f64.mul (f64.const 0.28000000000000003) (f64.load offset=8 (i32.const 0))) (f64.const 0.69999999999999996)))
		(set_local $fSlow2 (f64.mul (f64.const 0.40000000000000002) (f64.load offset=16 (i32.const 0))))
		(set_local $fSlow3 (f64.sub (f64.const 1.) (get_local $fSlow2)))
		(set_local $fSlow4 (f64.sub (f64.const 1.) (get_local $fSlow0)))
		(set_local $i (i32.const 0))
		(loop $for-in-i 
			(block $for-out-i 
				(f64.store offset=24 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=32 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=16440 (i32.const 0)))))
				(set_local $fTemp0 (f64.load (i32.add (get_local $input0) (get_local $i))))
				(set_local $fTemp1 (f64.load (i32.add (get_local $input1) (get_local $i))))
				(set_local $fTemp2 (f64.mul (f64.const 0.014999999999999999) (f64.add (get_local $fTemp0) (get_local $fTemp1))))
				(f64.store (i32.add (i32.const 48) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (f64.mul (get_local $fSlow1) (f64.load offset=24 (i32.const 0))) (get_local $fTemp2)))
				(f64.store offset=16432 (i32.const 0) (f64.load (i32.add (i32.const 48) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1116)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=16448 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=16456 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=32856 (i32.const 0)))))
				(f64.store (i32.add (i32.const 16464) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=16448 (i32.const 0)))))
				(f64.store offset=32848 (i32.const 0) (f64.load (i32.add (i32.const 16464) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1188)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=32864 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=32872 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=49272 (i32.const 0)))))
				(f64.store (i32.add (i32.const 32880) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=32864 (i32.const 0)))))
				(f64.store offset=49264 (i32.const 0) (f64.load (i32.add (i32.const 32880) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1277)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=49280 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=49288 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=65688 (i32.const 0)))))
				(f64.store (i32.add (i32.const 49296) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=49280 (i32.const 0)))))
				(f64.store offset=65680 (i32.const 0) (f64.load (i32.add (i32.const 49296) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1356)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=65696 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=65704 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=82104 (i32.const 0)))))
				(f64.store (i32.add (i32.const 65712) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=65696 (i32.const 0)))))
				(f64.store offset=82096 (i32.const 0) (f64.load (i32.add (i32.const 65712) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1422)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=82112 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=82120 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=98520 (i32.const 0)))))
				(f64.store (i32.add (i32.const 82128) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=82112 (i32.const 0)))))
				(f64.store offset=98512 (i32.const 0) (f64.load (i32.add (i32.const 82128) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1491)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=98528 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=98536 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=114936 (i32.const 0)))))
				(f64.store (i32.add (i32.const 98544) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=98528 (i32.const 0)))))
				(f64.store offset=114928 (i32.const 0) (f64.load (i32.add (i32.const 98544) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1557)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=114944 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=114952 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=131352 (i32.const 0)))))
				(f64.store (i32.add (i32.const 114960) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=114944 (i32.const 0)))))
				(f64.store offset=131344 (i32.const 0) (f64.load (i32.add (i32.const 114960) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1617)) (i32.const 2047)) (i32.const 3)))))
				(set_local $fTemp3 (f64.add (f64.add (f64.add (f64.add (f64.add (f64.add (f64.add (f64.load offset=16432 (i32.const 0)) (f64.load offset=32848 (i32.const 0))) (f64.load offset=49264 (i32.const 0))) (f64.load offset=65680 (i32.const 0))) (f64.load offset=82096 (i32.const 0))) (f64.load offset=98512 (i32.const 0))) (f64.load offset=114928 (i32.const 0))) (f64.load offset=131344 (i32.const 0))))
				(f64.store (i32.add (i32.const 131360) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 1023)) (i32.const 3))) (f64.add (get_local $fTemp3) (f64.mul (f64.const 0.5) (f64.load offset=139560 (i32.const 0)))))
				(f64.store offset=139552 (i32.const 0) (f64.load (i32.add (i32.const 131360) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 556)) (i32.const 1023)) (i32.const 3)))))
				(set_local $fRec7 (f64.sub (f64.load offset=139560 (i32.const 0)) (get_local $fTemp3)))
				(f64.store (i32.add (i32.const 139568) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 511)) (i32.const 3))) (f64.add (get_local $fRec7) (f64.mul (f64.const 0.5) (f64.load offset=143672 (i32.const 0)))))
				(f64.store offset=143664 (i32.const 0) (f64.load (i32.add (i32.const 139568) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 441)) (i32.const 511)) (i32.const 3)))))
				(set_local $fRec5 (f64.sub (f64.load offset=143672 (i32.const 0)) (get_local $fRec7)))
				(f64.store (i32.add (i32.const 143680) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 511)) (i32.const 3))) (f64.add (get_local $fRec5) (f64.mul (f64.const 0.5) (f64.load offset=147784 (i32.const 0)))))
				(f64.store offset=147776 (i32.const 0) (f64.load (i32.add (i32.const 143680) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 341)) (i32.const 511)) (i32.const 3)))))
				(set_local $fRec3 (f64.sub (f64.load offset=147784 (i32.const 0)) (get_local $fRec5)))
				(f64.store (i32.add (i32.const 147792) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 255)) (i32.const 3))) (f64.add (get_local $fRec3) (f64.mul (f64.const 0.5) (f64.load offset=149848 (i32.const 0)))))
				(f64.store offset=149840 (i32.const 0) (f64.load (i32.add (i32.const 147792) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 225)) (i32.const 255)) (i32.const 3)))))
				(set_local $fRec1 (f64.sub (f64.load offset=149848 (i32.const 0)) (get_local $fRec3)))
				(f64.store (i32.add (get_local $output0) (get_local $i)) (f64.add (f64.mul (get_local $fSlow0) (get_local $fRec1)) (f64.mul (get_local $fSlow4) (get_local $fTemp0))))
				(f64.store offset=149856 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=149864 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=166264 (i32.const 0)))))
				(f64.store (i32.add (i32.const 149872) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=149856 (i32.const 0)))))
				(f64.store offset=166256 (i32.const 0) (f64.load (i32.add (i32.const 149872) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1139)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=166272 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=166280 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=182680 (i32.const 0)))))
				(f64.store (i32.add (i32.const 166288) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=166272 (i32.const 0)))))
				(f64.store offset=182672 (i32.const 0) (f64.load (i32.add (i32.const 166288) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1211)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=182688 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=182696 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=199096 (i32.const 0)))))
				(f64.store (i32.add (i32.const 182704) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=182688 (i32.const 0)))))
				(f64.store offset=199088 (i32.const 0) (f64.load (i32.add (i32.const 182704) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1300)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=199104 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=199112 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=215512 (i32.const 0)))))
				(f64.store (i32.add (i32.const 199120) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=199104 (i32.const 0)))))
				(f64.store offset=215504 (i32.const 0) (f64.load (i32.add (i32.const 199120) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1379)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=215520 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=215528 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=231928 (i32.const 0)))))
				(f64.store (i32.add (i32.const 215536) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=215520 (i32.const 0)))))
				(f64.store offset=231920 (i32.const 0) (f64.load (i32.add (i32.const 215536) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1445)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=231936 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=231944 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=248344 (i32.const 0)))))
				(f64.store (i32.add (i32.const 231952) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=231936 (i32.const 0)))))
				(f64.store offset=248336 (i32.const 0) (f64.load (i32.add (i32.const 231952) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1514)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=248352 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=248360 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=264760 (i32.const 0)))))
				(f64.store (i32.add (i32.const 248368) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=248352 (i32.const 0)))))
				(f64.store offset=264752 (i32.const 0) (f64.load (i32.add (i32.const 248368) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1580)) (i32.const 2047)) (i32.const 3)))))
				(f64.store offset=264768 (i32.const 0) (f64.add (f64.mul (get_local $fSlow2) (f64.load offset=264776 (i32.const 0))) (f64.mul (get_local $fSlow3) (f64.load offset=281176 (i32.const 0)))))
				(f64.store (i32.add (i32.const 264784) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 2047)) (i32.const 3))) (f64.add (get_local $fTemp2) (f64.mul (get_local $fSlow1) (f64.load offset=264768 (i32.const 0)))))
				(f64.store offset=281168 (i32.const 0) (f64.load (i32.add (i32.const 264784) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 1640)) (i32.const 2047)) (i32.const 3)))))
				(set_local $fTemp4 (f64.add (f64.add (f64.add (f64.add (f64.add (f64.add (f64.add (f64.load offset=166256 (i32.const 0)) (f64.load offset=182672 (i32.const 0))) (f64.load offset=199088 (i32.const 0))) (f64.load offset=215504 (i32.const 0))) (f64.load offset=231920 (i32.const 0))) (f64.load offset=248336 (i32.const 0))) (f64.load offset=264752 (i32.const 0))) (f64.load offset=281168 (i32.const 0))))
				(f64.store (i32.add (i32.const 281184) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 1023)) (i32.const 3))) (f64.add (get_local $fTemp4) (f64.mul (f64.const 0.5) (f64.load offset=289384 (i32.const 0)))))
				(f64.store offset=289376 (i32.const 0) (f64.load (i32.add (i32.const 281184) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 579)) (i32.const 1023)) (i32.const 3)))))
				(set_local $fRec31 (f64.sub (f64.load offset=289384 (i32.const 0)) (get_local $fTemp4)))
				(f64.store (i32.add (i32.const 289392) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 511)) (i32.const 3))) (f64.add (get_local $fRec31) (f64.mul (f64.const 0.5) (f64.load offset=293496 (i32.const 0)))))
				(f64.store offset=293488 (i32.const 0) (f64.load (i32.add (i32.const 289392) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 464)) (i32.const 511)) (i32.const 3)))))
				(set_local $fRec29 (f64.sub (f64.load offset=293496 (i32.const 0)) (get_local $fRec31)))
				(f64.store (i32.add (i32.const 293504) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 511)) (i32.const 3))) (f64.add (get_local $fRec29) (f64.mul (f64.const 0.5) (f64.load offset=297608 (i32.const 0)))))
				(f64.store offset=297600 (i32.const 0) (f64.load (i32.add (i32.const 293504) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 364)) (i32.const 511)) (i32.const 3)))))
				(set_local $fRec27 (f64.sub (f64.load offset=297608 (i32.const 0)) (get_local $fRec29)))
				(f64.store (i32.add (i32.const 297616) (i32.shl (i32.and (i32.load offset=40 (i32.const 0)) (i32.const 255)) (i32.const 3))) (f64.add (get_local $fRec27) (f64.mul (f64.const 0.5) (f64.load offset=299672 (i32.const 0)))))
				(f64.store offset=299664 (i32.const 0) (f64.load (i32.add (i32.const 297616) (i32.shl (i32.and (i32.sub (i32.load offset=40 (i32.const 0)) (i32.const 248)) (i32.const 255)) (i32.const 3)))))
				(set_local $fRec25 (f64.sub (f64.load offset=299672 (i32.const 0)) (get_local $fRec27)))
				(f64.store (i32.add (get_local $output1) (get_local $i)) (f64.add (f64.mul (get_local $fSlow0) (get_local $fRec25)) (f64.mul (get_local $fSlow4) (get_local $fTemp1))))
				(f64.store offset=32 (i32.const 0) (f64.load offset=24 (i32.const 0)))
				(i32.store offset=40 (i32.const 0) (i32.add (i32.load offset=40 (i32.const 0)) (i32.const 1)))
				(f64.store offset=16440 (i32.const 0) (f64.load offset=16432 (i32.const 0)))
				(f64.store offset=16456 (i32.const 0) (f64.load offset=16448 (i32.const 0)))
				(f64.store offset=32856 (i32.const 0) (f64.load offset=32848 (i32.const 0)))
				(f64.store offset=32872 (i32.const 0) (f64.load offset=32864 (i32.const 0)))
				(f64.store offset=49272 (i32.const 0) (f64.load offset=49264 (i32.const 0)))
				(f64.store offset=49288 (i32.const 0) (f64.load offset=49280 (i32.const 0)))
				(f64.store offset=65688 (i32.const 0) (f64.load offset=65680 (i32.const 0)))
				(f64.store offset=65704 (i32.const 0) (f64.load offset=65696 (i32.const 0)))
				(f64.store offset=82104 (i32.const 0) (f64.load offset=82096 (i32.const 0)))
				(f64.store offset=82120 (i32.const 0) (f64.load offset=82112 (i32.const 0)))
				(f64.store offset=98520 (i32.const 0) (f64.load offset=98512 (i32.const 0)))
				(f64.store offset=98536 (i32.const 0) (f64.load offset=98528 (i32.const 0)))
				(f64.store offset=114936 (i32.const 0) (f64.load offset=114928 (i32.const 0)))
				(f64.store offset=114952 (i32.const 0) (f64.load offset=114944 (i32.const 0)))
				(f64.store offset=131352 (i32.const 0) (f64.load offset=131344 (i32.const 0)))
				(f64.store offset=139560 (i32.const 0) (f64.load offset=139552 (i32.const 0)))
				(f64.store offset=143672 (i32.const 0) (f64.load offset=143664 (i32.const 0)))
				(f64.store offset=147784 (i32.const 0) (f64.load offset=147776 (i32.const 0)))
				(f64.store offset=149848 (i32.const 0) (f64.load offset=149840 (i32.const 0)))
				(f64.store offset=149864 (i32.const 0) (f64.load offset=149856 (i32.const 0)))
				(f64.store offset=166264 (i32.const 0) (f64.load offset=166256 (i32.const 0)))
				(f64.store offset=166280 (i32.const 0) (f64.load offset=166272 (i32.const 0)))
				(f64.store offset=182680 (i32.const 0) (f64.load offset=182672 (i32.const 0)))
				(f64.store offset=182696 (i32.const 0) (f64.load offset=182688 (i32.const 0)))
				(f64.store offset=199096 (i32.const 0) (f64.load offset=199088 (i32.const 0)))
				(f64.store offset=199112 (i32.const 0) (f64.load offset=199104 (i32.const 0)))
				(f64.store offset=215512 (i32.const 0) (f64.load offset=215504 (i32.const 0)))
				(f64.store offset=215528 (i32.const 0) (f64.load offset=215520 (i32.const 0)))
				(f64.store offset=231928 (i32.const 0) (f64.load offset=231920 (i32.const 0)))
				(f64.store offset=231944 (i32.const 0) (f64.load offset=231936 (i32.const 0)))
				(f64.store offset=248344 (i32.const 0) (f64.load offset=248336 (i32.const 0)))
				(f64.store offset=248360 (i32.const 0) (f64.load offset=248352 (i32.const 0)))
				(f64.store offset=264760 (i32.const 0) (f64.load offset=264752 (i32.const 0)))
				(f64.store offset=264776 (i32.const 0) (f64.load offset=264768 (i32.const 0)))
				(f64.store offset=281176 (i32.const 0) (f64.load offset=281168 (i32.const 0)))
				(f64.store offset=289384 (i32.const 0) (f64.load offset=289376 (i32.const 0)))
				(f64.store offset=293496 (i32.const 0) (f64.load offset=293488 (i32.const 0)))
				(f64.store offset=297608 (i32.const 0) (f64.load offset=297600 (i32.const 0)))
				(f64.store offset=299672 (i32.const 0) (f64.load offset=299664 (i32.const 0)))
				(set_local $i (i32.add (get_local $i) (i32.const 8)))
				(if (i32.lt_s (get_local $i) (i32.mul (i32.const 8) (get_local $count))) (br $for-in-i) (br $for-out-i))
				
			)
		)
		
	)
	
)
