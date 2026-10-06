#!/bin/bash
# The interval tests (README.md) : check.sh [faust]

FAUST=${1:-../../build/bin/faust}
CXX=${CXX:-c++}
ARCH=../../architecture
OUT=build
mkdir -p $OUT
fail=0

result() { # result <status> <description>
    if [ $1 -eq 0 ]; then echo "ok    $2"; else echo "FAIL  $2"; fail=1; fi
}

# 1. the directed rounding against the rounding modes of the machine
$CXX -std=c++17 -O2 -I ../../compiler/interval directed.cpp -o $OUT/directed && $OUT/directed
result $? "directed rounding"

# 2. no access out of a table at run time : the sliders at their bounds, the inputs at
#    -1 and 1, the tables checked by -fsanitize=array-bounds
for dsp in *.dsp; do
    for p in single double; do
        name=$(basename $dsp .dsp)-$p
        $FAUST -$p -a bounds-driver.cpp -I $ARCH $dsp -o $OUT/$name.cpp &&
            $CXX -std=c++17 -O2 -fsanitize=array-bounds -fsanitize-trap=array-bounds -I $ARCH \
                $OUT/$name.cpp -o $OUT/$name &&
            $OUT/$name
        result $? "$name stays within its tables"
    done
done

# 3. the generated code : an FMA shows at run time only where the C++ compiler fuses
#    a*b + c (arm64), a comparison wrongly decided at compile time and a double guard
#    never do
count() { # count <dsp> <precision> <pattern>
    $FAUST -$2 $1 | grep -c -F -e "$3"
}
guarded='itbl0mydspSIG0[std::max<int>(0, std::min<int>('
twice='std::max<int>(0, std::min<int>(std::max<int>(0, std::min<int>('
for p in single double; do
    [ "$(count fma_edge.dsp $p "$guarded")" = 1 ]
    result $? "fma_edge-$p keeps its guard"
    [ "$(count tabulate_clamped.dsp $p "$twice")" = 0 ]
    result $? "tabulate_clamped-$p is not guarded twice"
done
[ "$(count zone_edge.dsp double 'static_cast<double>(fHslider0) < 0.7)')" = 1 ]
result $? "zone_edge-double keeps its comparison"

exit $fail
