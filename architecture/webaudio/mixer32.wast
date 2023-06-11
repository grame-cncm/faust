
(module

    (export "clearOutput" (func $clearOutput))
    (export "mixCheckVoice" (func $mixCheckVoice))
    (export "fadeOut" (func $fadeOut))
    (import "memory" "memory" (memory $0 2))

    (func $clearOutput (param $count i32) (param $channels i32) (param $outputs i32)

        (local $output i32)
        (local $i i32)
        (local $chan i32)

        (local.set $chan (i32.const 0))

        (loop $for-in-chan
            (block $for-out-chan
                (local.set $output (i32.load (i32.add (local.get $outputs) (i32.shl (local.get $chan) (i32.const 2)))))
                (local.set $i (i32.const 0))
                (loop $for-in-i
                    (block $for-out-i
                        (f32.store (i32.add (local.get $output) (i32.shl (local.get $i) (i32.const 2))) (f32.const 0))
                        (local.set $i (i32.add (local.get $i) (i32.const 1)))
                        (if (i32.lt_s (local.get $i) (local.get $count)) (br $for-in-i) (br $for-out-i))
                    )
                )
                (local.set $chan (i32.add (local.get $chan) (i32.const 1)))
                (if (i32.lt_s (local.get $chan) (local.get $channels)) (br $for-in-chan) (br $for-out-chan))
            )
        )
    )

	(func $mixCheckVoice (param $count i32) (param $channels i32) (param $inputs i32) (param $outputs i32) (result f32)

        (local $input i32)
        (local $output i32)
        (local $i i32)
        (local $chan i32)
        (local $level f32)
        (local $sample_in f32)
        (local $sample_out f32)

        (local.set $chan (i32.const 0))
        (local.set $level (f32.const 0))

        (loop $for-in-chan
            (block $for-out-chan
                (local.set $i (i32.const 0))
                (local.set $input (i32.load (i32.add (local.get $inputs) (i32.shl (local.get $chan) (i32.const 2)))))
                (local.set $output (i32.load (i32.add (local.get $outputs) (i32.shl (local.get $chan) (i32.const 2)))))
                (loop $for-in-i
                    (block $for-out-i
                        (local.set $sample_in (f32.load (i32.add (local.get $input) (i32.shl (local.get $i) (i32.const 2)))))
                        (local.set $level (f32.max (local.get $level) (f32.abs (local.get $sample_in))))
                        (local.set $sample_out (f32.load (i32.add (local.get $output) (i32.shl (local.get $i) (i32.const 2)))))
                        (f32.store (i32.add (local.get $output) (i32.shl (local.get $i) (i32.const 2))) (f32.add (local.get $sample_out) (local.get $sample_in)))
                        (local.set $i (i32.add (local.get $i) (i32.const 1)))
                        (if (i32.lt_s (local.get $i) (local.get $count)) (br $for-in-i) (br $for-out-i))
                    )
                )
                (local.set $chan (i32.add (local.get $chan) (i32.const 1)))
                (if (i32.lt_s (local.get $chan) (local.get $channels)) (br $for-in-chan) (br $for-out-chan))
            )
        )
        (return (local.get $level))
    )

    (func $fadeOut (param $count i32) (param $channels i32) (param $outputs i32)

        (local $output i32)
        (local $i i32)
        (local $chan i32)
        (local $sample f32)
        (local $factor f32)
        (local $step f32)
       
        (local.set $chan (i32.const 0))
       
        (loop $for-in-chan
            (block $for-out-chan
                (local.set $i (i32.const 0))
                (local.set $output (i32.load (i32.add (local.get $outputs) (i32.shl (local.get $chan) (i32.const 2)))))
                (local.set $factor (f32.const 1.0))
                (local.set $step (f32.div (local.get $factor) (f32.convert_i32_s (local.get $count))))
                (loop $for-in-i
                    (block $for-out-i
                        (local.set $sample (f32.load (i32.add (local.get $output) (i32.shl (local.get $i) (i32.const 2)))))
                        (local.set $sample (f32.mul (local.get $sample) (local.get $factor)))
                        (local.set $factor (f32.sub (local.get $factor) (local.get $step)))
                        (f32.store (i32.add (local.get $output) (i32.shl (local.get $i) (i32.const 2))) (local.get $sample))
                        (local.set $i (i32.add (local.get $i) (i32.const 1)))
                        (if (i32.lt_s (local.get $i) (local.get $count)) (br $for-in-i) (br $for-out-i))
                    )
                )
                (local.set $chan (i32.add (local.get $chan) (i32.const 1)))
                (if (i32.lt_s (local.get $chan) (local.get $channels)) (br $for-in-chan) (br $for-out-chan))
            )
        )
    )

)

