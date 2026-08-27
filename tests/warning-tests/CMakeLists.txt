file(GLOB tests *dsp)

foreach(test ${tests})
    string(REPLACE .dsp "" test_name ${test} )

    add_test(NAME ${test_name}
         COMMAND faust ${test})

    set_property(TEST ${test_name}
        PROPERTY PASS_REGULAR_EXPRESSION "WARNING"
    )

endforeach()

add_test(NAME numeric_stability_analysis_nsa
    COMMAND faust -nsa ${CMAKE_CURRENT_SOURCE_DIR}/numeric-stability-analysis.dsp)

set_property(TEST numeric_stability_analysis_nsa
    PROPERTY PASS_REGULAR_EXPRESSION "numeric stability analysis"
)
