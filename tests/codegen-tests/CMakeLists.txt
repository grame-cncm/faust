file(GLOB tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *dsp)

foreach(test ${tests})
    string(REPLACE .dsp "" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust ${CMAKE_CURRENT_SOURCE_DIR}/${test})

    add_custom_target(#OUTPUT
        ${test_name}.cpp ALL
         COMMAND faust -a minimal.cpp -o ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${test}
         DEPENDS ${test} faust
    )

    add_test(NAME ${test_name}_compile
      COMMAND ${CMAKE_CXX_COMPILER} -c ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.cpp)

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
