idf_component_register(SRCS "websocket_linux.c"
                    REQUIRES esp_websocket_client protocol_examples_common)

if(CONFIG_GCOV_ENABLED)
    target_compile_options(${COMPONENT_LIB} PUBLIC --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(${COMPONENT_LIB} PUBLIC  --coverage -fprofile-arcs -ftest-coverage)

    idf_component_get_property(esp_websocket_client esp_websocket_client COMPONENT_LIB)

    target_compile_options(${esp_websocket_client} PUBLIC --coverage -fprofile-arcs -ftest-coverage)
    target_link_options(${esp_websocket_client} PUBLIC  --coverage -fprofile-arcs -ftest-coverage)
endif()
