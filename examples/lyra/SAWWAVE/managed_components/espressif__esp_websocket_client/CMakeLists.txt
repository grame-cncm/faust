idf_build_get_property(target IDF_TARGET)

if(NOT CONFIG_WS_TRANSPORT AND NOT CMAKE_BUILD_EARLY_EXPANSION)
    message(STATUS "Websocket transport is disabled so the esp_websocket_client component will not be built")
    # note: the component is still included in the build so it can become visible again in config
    # without needing to re-run CMake. However no source or header files are built.
    idf_component_register()
    return()
endif()

if(${IDF_TARGET} STREQUAL "linux")
	idf_component_register(SRCS "esp_websocket_client.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp-tls tcp_transport http_parser esp_event nvs_flash esp_stubs json
                    PRIV_REQUIRES esp_timer)
else()
    idf_component_register(SRCS "esp_websocket_client.c"
                    INCLUDE_DIRS "include"
                    REQUIRES lwip esp-tls tcp_transport http_parser esp_event
                    PRIV_REQUIRES esp_timer)
endif()
