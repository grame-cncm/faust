#!/bin/bash
# The command line, on small programs whose outputs are known: every expected
# value here comes from the program's definition, not from a recording.
#
#   ./tests/run.sh                    run from tools/faustprobe
#   FAUSTPROBE=path ./tests/run.sh    test another binary

cd "$(dirname "$0")/.." || exit 2
PROBE=${FAUSTPROBE:-./faustprobe}
DSP=tests/dsp
OUT=tests/out
mkdir -p $OUT
failures=0
checks=0

# check NAME STATUS TEXT ARGS...: the exit status is STATUS and TEXT is printed.
check() {
    local name=$1 status=$2 text=$3
    shift 3
    local output got
    output=$("$PROBE" "$@" 2>&1)
    got=$?
    checks=$((checks + 1))
    if [ "$got" != "$status" ] || ! grep -qF -- "$text" <<<"$output"; then
        echo "FAIL $name: exit $got (expected $status), looking for \`$text\` in:"
        head -12 <<<"$output" | cut -c1-160
        failures=$((failures + 1))
    fi
}

# Rendering
check plain 0 "3,0.5" --double -n 4 --in dc $DSP/gain.dsp
check set 0 "0,0.25" --double -n 1 --in dc --set gain=0.25 $DSP/gain.dsp
check single_text 0 "0,0.3" -n 1 --in dc --set gain=0.3 $DSP/gain.dsp
check at_exact_frame 0 "6,1.0" --double -n 8 --in dc --at 6 gain=1 $DSP/gain.dsp
check not_before_it 0 "5,0.5" --double -n 8 --in dc --at 6 gain=1 $DSP/gain.dsp
check statistics 0 "peak=0.5 rms=0.5 dc=0.5 finite=yes peak_at=0" --double --quiet -n 64 --in dc $DSP/gain.dsp
check skip 0 "window=8..16 (8 frames)" --double --quiet -n 16 --skip 8 --in dc $DSP/gain.dsp
check bargraph 0 "# bargraph /filt/level=0.5" --double --quiet -n 1 $DSP/filt.dsp
check bargraph_column 0 "frame,out0,out1,/filt/level" --double -n 1 --bargraphs $DSP/filt.dsp
check list 0 "/filt/level" --list-params $DSP/filt.dsp
check impulse_channel 0 "0,0.5" --double -n 1 --in impulse:1 $DSP/twice.dsp
check silence_note 0 "every output is exactly zero" --double --quiet -n 8 --in zero $DSP/gain.dsp
check ir 0 "     1 :  0.500000" --double --format ir -n 2 --in dc $DSP/gain.dsp
check protocol 0 "number_of_frames  :  15000" --protocol impulse-test $DSP/gain.dsp
check json 0 '"schema_version": 1' --double --format json -n 8 $DSP/gain.dsp
check determinism 0 "# check determinism out0: identical" --double --quiet -n 256 --check determinism $DSP/filt.dsp
check block_sizes 0 "# check block=7 out1: identical" --double --quiet -n 256 --check block $DSP/filt.dsp
check reset 0 "# check reset out0: identical" --double --quiet -n 256 --check reset $DSP/filt.dsp
check vector_mode 0 "# check block=7 out0: identical" --double -vec -vs 16 --quiet -n 256 --check block=7 $DSP/filt.dsp

# The optimiser does not change what a length truncates to: pow(53, 1) is 53
for level in 0 1 3 -1; do
    check pow_exact_$level 0 "0,53.0,53.0" --double --opt-level $level -n 1 --in zero $DSP/powint.dsp
done

# Refusals
check unknown_control 1 "no control matching" --set nope=1 $DSP/gain.dsp
check out_of_range 1 "outside the range [0, 1]" --set gain=2 $DSP/gain.dsp
check clamp 0 "# clamped /gain/gain: 2 -> 1" --double --quiet -n 1 --clamp --set gain=2 $DSP/gain.dsp
check bargraph_write 1 "is a bargraph" --set level=1 $DSP/filt.dsp
check no_input 1 "the program has one input, channel 0" --in impulse:3 $DSP/gain.dsp
check compile_error 1 "ERROR" $DSP/broken.dsp
check missing_file 1 "cannot read" $DSP/absent.dsp
check usage 2 "unexpected argument" --nope $DSP/gain.dsp
check no_file 2 "<FILE>" -n 1
check protocol_conflict 1 "remove --sr" --protocol impulse-test --sr 48000 $DSP/gain.dsp
check memory_manager 1 "-mem0 needs a memory manager" -mem0 $DSP/gain.dsp
check non_finite 1 "render produced non-finite samples" --double --quiet -n 5000 --in dc --set fb=4 $DSP/runaway.dsp
check fail_above 1 "a sample exceeds --fail-above 100" --double --quiet -n 500 --in dc --fail-above 100 --set fb=2 $DSP/runaway.dsp

# Comparison
check compare_same 0 "# compare out0: identical" --double --quiet -n 64 --compare $DSP/gain.dsp $DSP/gain.dsp
check compare_set 1 "first: frame 0, out0: 0.25 vs 0.5" --double --quiet -n 64 --in dc --set-a gain=0.25 --compare $DSP/gain.dsp $DSP/gain.dsp
"$PROBE" --double -n 64 --out $OUT/ref.npy $DSP/filt.dsp >/dev/null
check ref_same 0 "# compare out1: identical" --double --quiet -n 64 --ref $OUT/ref.npy $DSP/filt.dsp
check ref_differs 1 "beyond the tolerance" --double --quiet -n 64 --set pole=0.4 --ref $OUT/ref.npy $DSP/filt.dsp
check in_file 0 "1,0.125" --double -n 2 --in file:$OUT/ref.npy:0 $DSP/gain.dsp

# Sweeps and measures
check sweep 0 "0.25,0.25,0.25,0.25" --double -n 8 --in dc --sweep gain=0.25,0.5 $DSP/gain.dsp
check reduce 0 "0.5,0.5" --double -n 8 --in dc --sweep gain=0.5 --reduce rms $DSP/gain.dsp
printf 'gain\n0.25\n0.75\n' >$OUT/points.csv
check points 0 "0.75,0.75" --double -n 8 --in dc --points $OUT/points.csv --reduce peak $DSP/gain.dsp
check describe 0 "# describe loudness=-6.0205999132796" --double --quiet -n 4410 --in dc --describe loudness $DSP/gain.dsp

# --eval: a geometric impulse response, read in a library that has no process
check eval 0 "3,0.125" --double -n 4 --eval 'onepole(0.5)' $DSP/small.lib
check eval_library_import 0 "0,2.0" --double -n 1 --in zero --eval 'two' $DSP/small.lib
check eval_columns 0 'frame,pair[0],pair[1]' --double -n 1 --in zero --eval pair $DSP/small.lib
check eval_two 0 '0,1.5,1.0,2.0' --double -n 1 --in zero --eval 'half(3)' --eval pair $DSP/small.lib
check eval_label_quoted 0 '"max(1, 2)"' --double -n 1 --in zero --eval 'max(1, 2)' $DSP/small.lib
check eval_error 1 "<eval 0>:1 : ERROR" --double --eval 'nope' $DSP/small.lib
check eval_note 1 "is \`--eval 'nope'\`" --double --eval 'nope' $DSP/small.lib

# --freqresp: y[n] = 0.5 x[n] + 0.5 y[n-1] at Nyquist is 0.5 / 1.5
check freqresp 0 "22050.0,-9.54242509439" --double --freqresp 1:22050:22050 --eval '*(0.5) : onepole(0.5)' $DSP/small.lib
check not_homogeneous 1 "homogeneity" --double --freqresp 8 $DSP/nonlin.dsp
check not_invariant 1 "time invariance" --double --freqresp 8 $DSP/lfo.dsp

# Polyphony: the outputs are what the note wrote
check poly_note 0 "0,440.0,1.0,1.0" --double --nvoices 1 -n 1 --note 69:127@0 $DSP/synth.dsp
check poly_key_off 0 "4,440.0,1.0,0.0" --double --nvoices 1 -n 5 --note 69:127@0..4 $DSP/synth.dsp
check poly_two 0 "active_voices=2" --double --nvoices 2 --quiet -n 8 --chord 60,64@0 $DSP/synth.dsp
check poly_silent 0 "no --note or --chord" --double --nvoices 2 --quiet -n 8 $DSP/synth.dsp
check poly_broadcast 0 "peak=0.25" --double --nvoices 1 --quiet -n 8 --in dc --note 60:127@0 --set gain=0.25 --effect $DSP/gain.dsp $DSP/gain.dsp
check jit_max 0 "12,16.0,16.0" --double -n 14 --every 1 $DSP/jit_max.dsp

# --train: the two gains of gain_fit.dsp come out at 0.5 and -0.25
check fd_check 0 "worst relative error" --double --in white:1 --block 256 --train g1,g2 --fd-check --blocks 0 $DSP/gain_fit.dsp
check train 0 "# trained /gain_fit/g1=0.5000000" --double --in white:1 --block 256 --train g1,g2 --lr 0.02 --blocks 300 --every 300 $DSP/gain_fit.dsp
check train_bound 0 "a control that ends on a bound is stopped" --double --in white:1 --block 256 --train g1 --grad-lane 1 --lr 1 --blocks 3 $DSP/runaway_train.dsp
check train_lanes 1 "do not fit" --double --train g1,g2 --grad-lane 2 --blocks 1 $DSP/gain_fit.dsp

# --svg: one file per diagram, in DIR alone, and the same names on every run
rm -rf $OUT/svg $OUT/svg2
check svg 0 "process.svg,process" --svg $OUT/svg $DSP/filt.dsp
check svg_refuses_render 2 "cannot be used with" --svg $OUT/svg -n 8 $DSP/filt.dsp
check svg_eval 0 "process.svg,onepole(0.5)" --svg $OUT/svg2 --fold 0 --eval 'onepole(0.5)' $DSP/small.lib
if ! [ -f $OUT/svg/process.svg ] || ls $OUT/svg | grep -qE -- '-[0-9]{3,}\.svg|^\.'; then
    echo "FAIL svg_files: $(ls -a $OUT/svg | tr '\n' ' ')"
    failures=$((failures + 1))
fi

rm -rf $OUT
if [ $failures -eq 0 ]; then
    echo "run: $checks checks passed"
else
    echo "run: $failures of $checks checks failed"
    exit 1
fi
