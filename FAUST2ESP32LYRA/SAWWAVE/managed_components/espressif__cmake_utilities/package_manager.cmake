# cu_pkg_get_version
#
# @brief Get the package's version information, the package is installed by component manager.
#
# @param[in] pkg_path the package's path, normally it's ${CMAKE_CURRENT_LIST_DIR}.
#
# @param[out] ver_major the major version of the package
# @param[out] ver_minor the minor version of the package
# @param[out] ver_patch the patch version of the package
function(cu_pkg_get_version pkg_path ver_major ver_minor ver_patch)
    set(yml_file "${pkg_path}/idf_component.yml")
    if(EXISTS ${yml_file})
        file(READ ${yml_file} ver)
        string(REGEX MATCH "(^|\n)version: \"?([0-9]+).([0-9]+).([0-9]+)\"?" _ ${ver})
        set(${ver_major} ${CMAKE_MATCH_2} PARENT_SCOPE)
        set(${ver_minor} ${CMAKE_MATCH_3} PARENT_SCOPE)
        set(${ver_patch} ${CMAKE_MATCH_4} PARENT_SCOPE)
    else()
        message(WARNING " ${yml_file} not exist")
    endif()
endfunction()

# cu_pkg_define_version
#
# @brief Add the package's version definitions using format ${NAME}_VER_MAJOR ${NAME}_VER_MINOR ${NAME}_VER_PATCH,
# the ${NAME} will be inferred from package path, and namespace like `espressif__` will be removed if the package download from esp-registry
# eg. espressif__usb_stream and usb_stream will generate same version definitions USB_STREAM_VER_MAJOR ...
#
# @param[in] pkg_path the package's path, normally it's ${CMAKE_CURRENT_LIST_DIR}.
#
macro(cu_pkg_define_version pkg_path)
    cu_pkg_get_version(${pkg_path} ver_major ver_minor ver_patch)
    get_filename_component(pkg_name ${pkg_path} NAME)
    string(FIND ${pkg_name} "__" pkg_name_pos)
    if(pkg_name_pos GREATER -1)
        math(EXPR pkg_name_pos "${pkg_name_pos} + 2")
        string(SUBSTRING ${pkg_name} ${pkg_name_pos} -1 pkg_name)
    endif()
    string(TOUPPER ${pkg_name} pkg_name)
    string(REPLACE "-" "_" pkg_name ${pkg_name})
    message(STATUS "${pkg_name}: ${ver_major}.${ver_minor}.${ver_patch}")
    list(LENGTH pkg_name_list len)
    target_compile_options(${COMPONENT_LIB} PUBLIC
        -D${pkg_name}_VER_MAJOR=${ver_major} -D${pkg_name}_VER_MINOR=${ver_minor} -D${pkg_name}_VER_PATCH=${ver_patch})
endmacro()
