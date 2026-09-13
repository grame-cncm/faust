#!/bin/bash
# build-two.sh [CXX_A] [CXX_B]
#
# Builds faust twice from this tree, with two C++ compilers (default g++ and
# clang++), into tests/determinism/bin/faust-a and faust-b. Two full builds
# (several minutes each) : the build's cmake directories are build/det-a and
# build/det-b, and the binaries are copied out of build/bin/faust, which the
# two builds share, so they run one after the other.
set -eu
HERE=$(cd "$(dirname "$0")" && pwd); ROOT=$(cd "$HERE/../.." && pwd)
CXX_A=${1:-g++}; CXX_B=${2:-clang++}
mkdir -p "$HERE/bin"
# the two compilers must evaluate the arguments of a call in different orders,
# or the pair cannot detect an unsequenced construction (see order.cpp)
orders=""
for pair in "a:$CXX_A" "b:$CXX_B"; do
    name=${pair%%:*}; cxx=${pair#*:}
    "$cxx" -O2 -o "$HERE/bin/order-$name" "$HERE/order.cpp"
    o=$("$HERE/bin/order-$name"); orders="$orders $o"
    echo "$cxx evaluates the arguments of a call in the order $o"
done
if [ "$(echo $orders | tr ' ' '\n' | sort -u | wc -l)" -lt 2 ]; then
    echo "WARNING : both compilers evaluate arguments in the same order ; this pair cannot reveal an"
    echo "          unsequenced construction (today only GCC on x86-64 evaluates right to left)."
    echo "          The check still compares the two builds, but a 'same' proves nothing about that family."
fi
for pair in "a:$CXX_A" "b:$CXX_B"; do
    name=${pair%%:*}; cxx=${pair#*:}
    echo "== faust-$name with $cxx : $($cxx --version | head -1)"
    make -C "$ROOT/build" FAUSTDIR="det-$name" cmake BACKENDS=regular.cmake TARGETS=regular.cmake \
         CMAKEOPT="-DCMAKE_CXX_COMPILER=$cxx -DINCLUDE_LLVM=OFF" > "$HERE/bin/cmake-$name.log" 2>&1
    make -C "$ROOT/build" FAUSTDIR="det-$name" faust > "$HERE/bin/make-$name.log" 2>&1
    cp "$ROOT/build/bin/faust" "$HERE/bin/faust-$name"
    "$HERE/bin/faust-$name" --version | sed 's/^/    /'
done
echo "now : make -C $HERE check"
