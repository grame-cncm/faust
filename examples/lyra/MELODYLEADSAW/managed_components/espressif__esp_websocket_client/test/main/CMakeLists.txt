idf_component_register(SRCS "test_websocket_client.c"
                       REQUIRES test_utils
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES unity esp_websocket_client esp_event)
