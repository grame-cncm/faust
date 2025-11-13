# Extend command to idf.py

# Generate single bin with name ${CMAKE_PROJECT_NAME}_merged.bin
if (NOT TARGET gen_single_bin)
    add_custom_target(
        gen_single_bin
        COMMAND ${CMAKE_COMMAND} -E echo "Merge bin files to ${CMAKE_PROJECT_NAME}_merged.bin"
        COMMAND ${ESPTOOLPY} --chip ${IDF_TARGET} merge_bin -o ${CMAKE_PROJECT_NAME}_merged.bin @flash_args
        COMMAND ${CMAKE_COMMAND} -E echo "Merge bin done"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS gen_project_binary bootloader
        VERBATIM USES_TERMINAL
    )
endif()

# Flash bin ${CMAKE_PROJECT_NAME}_merged.bin to target chip
if (NOT TARGET flash_single_bin)
    add_custom_target(
        flash_single_bin
        COMMAND ${CMAKE_COMMAND} -E echo "Flash merged bin ${CMAKE_PROJECT_NAME}_merged.bin to address 0x0"
        COMMAND ${ESPTOOLPY} --chip ${IDF_TARGET} write_flash 0x0 ${CMAKE_PROJECT_NAME}_merged.bin
        COMMAND ${CMAKE_COMMAND} -E echo "Flash merged bin done"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS gen_single_bin
        VERBATIM USES_TERMINAL
    )
endif()
