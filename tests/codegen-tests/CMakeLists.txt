cmake_minimum_required(VERSION 3.4)

file(GLOB tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *dsp)

list(REMOVE_ITEM tests freeverb.dsp)


if (EXTENSIVE_TESTSUITE)
  set(flags vec scal omp fun sch)
else()
  set(flags vec scal sch)
endif()

foreach(flag ${flags})
    foreach(test ${tests})
        string(REPLACE .dsp "" test_name ${test} )
        set(test_name ${test_name}_${flag})

        add_test(NAME ${test_name}
            COMMAND faust -${flag} ${CMAKE_CURRENT_SOURCE_DIR}/${test})

        add_test(NAME ${test_name}_compile
          COMMAND ${CMAKE_SOURCE_DIR}/run_test_cpp.sh -m -${flag} -f ${CMAKE_BINARY_DIR}/compiler/faust -c ${CMAKE_CXX_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/${test})

        add_test(NAME ${test_name}_fir
            COMMAND faust -lang fir -${flag} ${CMAKE_CURRENT_SOURCE_DIR}/${test})

    endforeach()
endforeach()
