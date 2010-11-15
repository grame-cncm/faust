file(GLOB examples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *dsp)

foreach(test ${examples})
    string(REPLACE .dsp "" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust ${CMAKE_CURRENT_SOURCE_DIR}/${test})

    add_custom_target(
        ${test_name}.cpp ALL
         COMMAND faust -a minimal.cpp -o ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${test}
         DEPENDS ${test} faust ../architecture/minimal.cpp
    )

    add_test(NAME ${test_name}_compile
      COMMAND ${CMAKE_CXX_COMPILER} -c ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.cpp)
endforeach()
