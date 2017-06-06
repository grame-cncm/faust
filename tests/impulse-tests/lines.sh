
function countLines () {
    params=$1
    file=$2
    echo "=========================================="
    echo "Count cpp lines in $params mode"
    echo "=========================================="

    cd codes-to-test
    echo "" > $file
    for p in *.dsp; do
        #echo $p
        faust $params $p -o ${p%.dsp}.cpp
        wc -l ${p%.dsp}.cpp >> $file
        rm ${p%.dsp}.cpp
    done
    cd ..

    echo "=========================================="
    echo "Diff cpp lines in $params mode"
    echo "=========================================="

    diff codes-to-test/$file expected-responses/$file
}

countLines "" lines_scal.txt
countLines "-inpl" lines_scal_inpl.txt
countLines "-vec -lv 0" lines_vec0.txt
countLines "-vec -lv 1" lines_vec1.txt
countLines "-vec -lv 1 -vs 64" lines_vec1vs32.txt
countLines "-vec -lv 1 -g" lines_vec1g.txt
countLines "-vec -lv 1 -dfs" lines_vec1dfs.txt
countLines "-sch" lines_sch.txt
countLines "-sch -vs 64" lines_schvs32.txt


