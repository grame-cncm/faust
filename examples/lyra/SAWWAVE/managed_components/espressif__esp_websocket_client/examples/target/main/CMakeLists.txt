set(SRC_FILES "websocket_example.c") # Define source files
set(INCLUDE_DIRS ".") # Define include directories
set(EMBED_FILES "") # Initialize an empty list for files to embed

# Conditionally append files to the list based on configuration
#if(CONFIG_WS_OVER_TLS_MUTAL_AUTH)
    list(APPEND EMBED_FILES
        "certs/client_cert.pem"
        "certs/ca_cert.pem"
        "certs/client_key.pem")
#endif()

# Register the component with source files, include dirs, and any conditionally added embedded files
idf_component_register(SRCS "${SRC_FILES}"
                       INCLUDE_DIRS "${INCLUDE_DIRS}"
                       EMBED_TXTFILES "${EMBED_FILES}")
