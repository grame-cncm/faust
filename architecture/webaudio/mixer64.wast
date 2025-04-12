
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
                        (f64.store (i32.add (local.get $output) (i32.shl (local.get $i) (i32.const 3))) (f64.const 0))
                        (local.set $i (i32.add (local.get $i) (i32.const 1)))
                        (if (i32.lt_s (local.get $i) (local.get $count)) (br $for-in-i) (br $for-out-i))
                    )
                )
                (local.set $chan (i32.add (local.get $chan) (i32.const 1)))
                (if (i32.lt_s (local.get $chan) (local.get $channels)) (br $for-in-chan) (br $for-out-chan))
            )
        )
    )

	(func $mixCheckVoice (param $count i32) (param $channels i32) (param $inputs i32) (param $outputs i32) (result f64)

        (local $input i32)
        (local $output i32)
        (local $i i32)
        (local $chan i32)
        (local $sumSquares f64)
        (local $sample_in f64)
        (local $sample_out f64)
        (local $totalSamples f64)

        (local.set $chan (i32.const 0))
        (local.set $sumSquares (f64.const 0))

        (loop $for-in-chan
            (block $for-out-chan
                (local.set $i (i32.const 0))
                ;; Get buffer addresses for this channel
                (local.set $input (i32.load (i32.add (local.get $inputs) (i32.shl (local.get $chan) (i32.const 2)))))
                (local.set $output (i32.load (i32.add (local.get $outputs) (i32.shl (local.get $chan) (i32.const 2)))))

                (loop $for-in-i
                    (block $for-out-i
                        ;; Load input sample
                        (local.set $sample_in (f64.load (i32.add (local.get $input) (i32.shl (local.get $i) (i32.const 3)))))

                        ;; Accumulate sum of squares
                        (local.set $sumSquares
                            (f64.add
                                (local.get $sumSquares)
                                (f64.mul (local.get $sample_in) (local.get $sample_in))
                            )
                        )

                        ;; Mix to output buffer
                        (local.set $sample_out (f64.load (i32.add (local.get $output) (i32.shl (local.get $i) (i32.const 3)))))
                        (f64.store
                            (i32.add (local.get $output) (i32.shl (local.get $i) (i32.const 3)))
                            (f64.add (local.get $sample_out) (local.get $sample_in))
                        )

                        ;; Next frame
                        (local.set $i (i32.add (local.get $i) (i32.const 1)))
                        (if (i32.lt_s (local.get $i) (local.get $count)) (br $for-in-i) (br $for-out-i))
                    )
                )

                ;; Next channel
                (local.set $chan (i32.add (local.get $chan) (i32.const 1)))
                (if (i32.lt_s (local.get $chan) (local.get $channels)) (br $for-in-chan) (br $for-out-chan))
            )
        )

        ;; Compute RMS = sqrt(sumSquares / (count * channels))
        (local.set $totalSamples
            (f64.convert_i32_s (i32.mul (local.get $count) (local.get $channels)))
        )

        (return
            (f64.sqrt
                (f64.div (local.get $sumSquares) (local.get $totalSamples))
            )
        )
    )
    
    (func $fadeOut (param $count i32) (param $channels i32) (param $outputs i32)

        (local $output i32)
        (local $i i32)
        (local $chan i32)
        (local $sample f64)
        (local $factor f64)
        (local $step f64)
       
        (local.set $chan (i32.const 0))
       
        (loop $for-in-chan
            (block $for-out-chan
                (local.set $i (i32.const 0))
                (local.set $output (i32.load (i32.add (local.get $outputs) (i32.shl (local.get $chan) (i32.const 2)))))
                (local.set $factor (f64.const 1.0))
                (local.set $step (f64.div (local.get $factor) (f64.convert_i32_s (local.get $count))))
                (loop $for-in-i
                    (block $for-out-i
                        (local.set $sample (f64.load (i32.add (local.get $output) (i32.shl (local.get $i) (i32.const 3)))))
                        (local.set $sample (f64.mul (local.get $sample) (local.get $factor)))
                        (local.set $factor (f64.sub (local.get $factor) (local.get $step)))
                        (f64.store (i32.add (local.get $output) (i32.shl (local.get $i) (i32.const 3))) (local.get $sample))
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

