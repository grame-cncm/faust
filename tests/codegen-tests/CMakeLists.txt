file(GLOB tests *dsp)

foreach(test ${tests})
    string(REPLACE .dsp "" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust ${test})
endforeach()

foreach(test ${tests})
    string(REPLACE .dsp ".vec" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust -vec ${test})
endforeach()

foreach(test ${tests})
    string(REPLACE .dsp ".omp" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust -omp ${test})
endforeach()

foreach(test ${tests})
    string(REPLACE .dsp ".sch" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust -sch ${test})
endforeach()
