file(GLOB examples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *dsp)

set(flags vec scal omp fun sch)

foreach(flag ${flags})
    foreach(test ${examples})
        string(REPLACE .dsp "" test_name ${test} )
        set(test_name ${test_name}_${flag})

        add_test(NAME ${test_name}
            COMMAND faust ${CMAKE_CURRENT_SOURCE_DIR}/${test})

        add_custom_target(
            ${test_name}.cpp ALL
            COMMAND faust -a minimal.cpp -${flag} -o ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${test}
            DEPENDS ${test} faust ../architecture/minimal.cpp
        )

        add_test(NAME ${test_name}_compile
        COMMAND ${CMAKE_CXX_COMPILER} -c ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.cpp)
    endforeach()
endforeach()