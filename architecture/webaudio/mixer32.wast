
(module

    (export "clearOutput" (func $clearOutput))
    (export "mixVoice" (func $mixVoice))
    (import "memory" "memory" (memory $0 2))

    (func $clearOutput (param $count i32) (param $channels i32) (param $outputs i32)

        (local $output i32)
        (local $i i32)
        (local $chan i32)

        (set_local $chan (i32.const 0))

        (loop $for-in-chan
            (block $for-out-chan
                (set_local $output (i32.load (i32.add (get_local $outputs) (i32.shl (get_local $chan) (i32.const 2)))))
                (set_local $i (i32.const 0))
                (loop $for-in-i
                    (block $for-out-i
                        (f32.store (i32.add (get_local $output) (i32.shl (get_local $i) (i32.const 2))) (f32.const 0))
                        (set_local $i (i32.add (get_local $i) (i32.const 1)))
                        (if (i32.lt_s (get_local $i) (get_local $count)) (br $for-in-i) (br $for-out-i))
                    )
                )
                (set_local $chan (i32.add (get_local $chan) (i32.const 1)))
                (if (i32.lt_s (get_local $chan) (get_local $channels)) (br $for-in-chan) (br $for-out-chan))
            )
        )
    )

	(func $mixVoice (param $count i32) (param $channels i32) (param $inputs i32) (param $outputs i32) (result f32)

        (local $input i32)
        (local $output i32)
        (local $i i32)
        (local $chan i32)
        (local $level f32)
        (local $sample_in f32)
        (local $sample_out f32)

        (set_local $chan (i32.const 0))
        (set_local $level (f32.const 0))

        (loop $for-in-chan
            (block $for-out-chan
                (set_local $i (i32.const 0))
                (set_local $input (i32.load (i32.add (get_local $inputs) (i32.shl (get_local $chan) (i32.const 2)))))
                (set_local $output (i32.load (i32.add (get_local $outputs) (i32.shl (get_local $chan) (i32.const 2)))))
                (loop $for-in-i
                    (block $for-out-i
                        (set_local $sample_in (f32.load (i32.add (get_local $input) (i32.shl (get_local $i) (i32.const 2)))))
                        (set_local $level (f32.max (get-local $level) (f32.abs (get_local $sample_in))))
                        (set_local $sample_out (f32.load (i32.add (get_local $output) (i32.shl (get_local $i) (i32.const 2)))))
                        (f32.store (i32.add (get_local $output) (i32.shl (get_local $i) (i32.const 2))) (f32.add (get_local $sample_out) (get_local $sample_in)))
                        (set_local $i (i32.add (get_local $i) (i32.const 1)))
                        (if (i32.lt_s (get_local $i) (get_local $count)) (br $for-in-i) (br $for-out-i))
                    )
                )
                (set_local $chan (i32.add (get_local $chan) (i32.const 1)))
                (if (i32.lt_s (get_local $chan) (get_local $channels)) (br $for-in-chan) (br $for-out-chan))
            )
        )
        (return (get-local $level))
    )

)

