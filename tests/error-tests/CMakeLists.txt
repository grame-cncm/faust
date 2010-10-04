file(GLOB tests *dsp)

foreach(test ${tests})
    string(REPLACE .dsp "" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust ${test})

    set_property(TEST ${test_name}
        PROPERTY WILL_FAIL TRUE)
endforeach()
