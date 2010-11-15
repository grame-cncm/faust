file(GLOB tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *dsp)

foreach(test ${tests})
    string(REPLACE .dsp "" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust -a jack-gtk.cpp -o ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.hpp ${CMAKE_CURRENT_SOURCE_DIR}/${test})
endforeach()

foreach(test ${tests})
    string(REPLACE .dsp ".vec" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust -vec ${CMAKE_CURRENT_SOURCE_DIR}/${test})
endforeach()

foreach(test ${tests})
    string(REPLACE .dsp ".omp" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust -omp ${CMAKE_CURRENT_SOURCE_DIR}/${test})
endforeach()

foreach(test ${tests})
    string(REPLACE .dsp ".sch" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust -sch ${CMAKE_CURRENT_SOURCE_DIR}/${test})
endforeach()
