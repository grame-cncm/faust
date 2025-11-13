set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_MODULE_PATH})

if(CONFIG_CU_DIAGNOSTICS_COLOR_ALWAYS)
    add_compile_options(-fdiagnostics-color=always)
elseif(CONFIG_CU_DIAGNOSTICS_COLOR_AUTO)
    add_compile_options(-fdiagnostics-color=auto)
elseif(CONFIG_CU_DIAGNOSTICS_COLOR_NEVER)
    add_compile_options(-fdiagnostics-color=never)
endif()
