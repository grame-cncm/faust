if (NOT TARGET gen_compressed_ota)
    add_custom_target(gen_compressed_ota)

    if (CONFIG_SECURE_SIGNED_ON_UPDATE_NO_SECURE_BOOT OR CONFIG_SECURE_BOOT_V2_ENABLED)
        set(COMPRESSED_OTA_BIN_SIGN_PARA --sign_key ${PROJECT_DIR}/${CONFIG_SECURE_BOOT_SIGNING_KEY})
    else()
        set(COMPRESSED_OTA_BIN_SIGN_PARA )
    endif()

    set(GEN_COMPRESSED_BIN_CMD  ${CMAKE_CURRENT_LIST_DIR}/scripts/gen_custom_ota.py ${COMPRESSED_OTA_BIN_SIGN_PARA} --add_app_header)

    add_custom_command(TARGET gen_compressed_ota
    POST_BUILD
    COMMAND ${PYTHON} ${GEN_COMPRESSED_BIN_CMD}
    COMMENT "The gen compresssed bin cmd is: ${GEN_COMPRESSED_BIN_CMD}"
    )
    add_dependencies(gen_compressed_ota gen_project_binary)
endif()